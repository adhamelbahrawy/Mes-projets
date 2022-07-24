#include "laby.h"

//1.1
noeud nouvNoeud()
{
    noeud new = (noeud) malloc(sizeof(struct s_noeud));
    for (int i = 0; i < NDIR; i++)
    {
        new->voisins[i] = NULL;
        new->distances[i] = 0;
        new->tresors[i] = NULL;
    }
    return new;
}

//1.1 + 5.
void passage(noeud n1, noeud n2, Dir d, int dist, float tr[])
{
    n1->voisins[d] = n2;
    n2->voisins[(d+2)%4] = n1;
    
    n1->distances[d] = dist;
    n2->distances[(d+2)%4] = dist;
    
    n1->tresors[d] = tr;
}

//2.1.
listeCoord parcoursRel(noeud n, int x, int y, listeCoord l)
{
    l = adjTLc(l, n, x, y);
    for (int i = 0; i < NDIR; i++)
    {
        switch (i)
        {
        case 0:
            if(n->voisins[0] != NULL && rechLc(l, x, y + n->distances[0]) == NULL)
            {
                l = parcoursRel(n->voisins[0], x, y + n->distances[0], l);
            }
            break;
        case 1:
            if(n->voisins[1] != NULL && rechLc(l, x + n->distances[1], y) == NULL)
            {
                l = parcoursRel(n->voisins[1], x + n->distances[1], y, l);
            }
            break;
        case 2:
            if(n->voisins[2] != NULL && rechLc(l, x, y - n->distances[2]) == NULL)
            {
                l = parcoursRel(n->voisins[2], x, y - n->distances[2], l);
            }
            break;
        case 3:
            if(n->voisins[1] != NULL && rechLc(l, x - n->distances[3], y) == NULL)
            {
                l = parcoursRel(n->voisins[3], x - n->distances[3], y, l);
            }
            break;
        }
    }
    return l;  
}

void taille(noeud n, int *X, int *Y)
{
    listeCoord l = nouvLc();
    l = parcoursRel(n, 0, 0 ,l);
    *X = xMax(l) - xMin(l);
    *Y = yMax(l) - yMin(l);
    destroyLc(l);
}

//2.2
void position(noeud n, int *X, int *Y)
{
    listeCoord l = nouvLc();
    l = parcoursRel(n, 0, 0 ,l);
    *X = abs(xMin(l));
    *Y = abs(yMin(l));
}

//3
listeP parcoursRelLen(noeud n, listeP l)
{
    for (int i = 0; i < NDIR; i++)
    {
        if(n->voisins[i] != NULL && rechLp(l, n, n->voisins[i]) == NULL)
        {
            l = adjTLp(l , n, n->voisins[i]);
            l = parcoursRelLen(n->voisins[i], l);
        }
    }
    return l;  
}

int longueur(noeud n)
{
    listeP l = nouvLp(),run;
    l = parcoursRelLen(n, l);
    int len = 0;
    run = l;
    while (run != NULL)
    {
        len += run->len;
        run = run->next;
    }
    return len;
}

//4.
listeP rechLp1Sens(listeP l, noeud node1, noeud node2)
{
    listeP run = l;
    while (run != NULL)
    {
        if((run->n1 == node1 && run->n2 == node2))
            return run;
        run = run->next;
    }
    return NULL;
}

listeP parcoursRelLen1Sens(noeud n, listeP l)
{
    for (int i = 0; i < NDIR; i++)
    {
        if(n->voisins[i] != NULL && rechLp1Sens(l, n, n->voisins[i]) == NULL)
        {
            l = adjTLp(l , n, n->voisins[i]);
            l = parcoursRelLen1Sens(n->voisins[i], l);
        }
    }
    return l;  
}

float chemTres(noeud n1, noeud n2, listeCoord lt) //lt = liste de trésors
{
    int x,y;
    position(n1, &x, &y);
    int i = 0, res = 0;
    while (i<NDIR && n1->voisins[i] != n2)
        i++;
    for (int j = 0; j < n1->distances[i]; j++)
        if(n1->tresors[i][j] > 0)
        {
            switch (i)
            {
            case 0:
                if(rechLc(lt , x+j, y) == NULL)
                {
                    lt = adjTLc(lt, NULL, x+j, y); //NULL dans le champs node désigne un tresor
                    res += n1->tresors[i][j];
                }
                break;
            case 1:
                if(rechLc(lt , x, y+j) == NULL)
                {
                    lt = adjTLc(lt, NULL, x, y+j);
                    res += n1->tresors[i][j];
                }
                break;
            case 2:
                if(rechLc(lt , x-j, y) == NULL)
                {
                    lt = adjTLc(lt, NULL, x-j, y);
                    res += n1->tresors[i][j];
                }
            case 3:
                if(rechLc(lt , x, y-j) == NULL)
                {
                    lt = adjTLc(lt, NULL, x, y-j);
                    res += n1->tresors[i][j];
                }
                break;
            }
        }
    return res;
}

float valeurTotalTresorsAux(noeud n, listeP pv, listeCoord lt)
{
    float total = 0;
    for (int i = 0; i < NDIR; i++)
    {
        if (n->voisins[i] != NULL && rechLp1Sens(pv, n, n->voisins[i]) == NULL)
        {
            pv = adjTLp(pv, n, n->voisins[i]);
            total += chemTres(n, n->voisins[i], lt) + valeurTotalTresorsAux(n->voisins[i], pv, lt);
        }
    }
    return total;
}

float valeurTotalTresors(noeud n)
{
    listeP pv = nouvLp();
    listeCoord lt = nouvLc();
    return valeurTotalTresorsAux(n, pv, lt);
}

//Mini opérations utiles
int abs(int x){return(x > 0 ? x : -x);};

//Les listes de coordonées
//Opérations sur les listes de coordonées
listeCoord nouvLc(){return NULL;} 

listeCoord adjTLc(listeCoord l, noeud n, int abs, int ord)
{
    listeCoord new = (listeCoord)malloc(sizeof(struct s_listeCoord));
	if (new == NULL) { printf("fatal error: no memory allocation possible.\n"); abort(); }
	new->next = l;
	new->node = n;
    new->x = abs;
    new->y = ord;
	return new;
}

listeCoord rechLc(listeCoord l, int abs, int ord)
{
    if (l == NULL) return NULL;
	if (l->x == abs && l->y == ord) return l;
	return rechLc(l->next, abs, ord);
}

listeCoord supKiemeLc(listeCoord l, unsigned int k)
{
    if (l == NULL) return NULL;
	if (k == 0)
	{
		listeCoord n = l->next;
		free(l);
		return n;
	}
	l->next = supKiemeLc(l->next, k - 1);
	return l;
}

void destroyLc(listeCoord l)
{
    while (l != NULL)
        l = supKiemeLc(l,0);
}
//Sélécteurs utiles des listes de coordonnées
int xMax(listeCoord l)
{
    int max = l->x;
    listeCoord run = l;
    while (run != NULL)
    {
        if(max < run->x)
        {
            max = run->x;
        }
        run = run->next;
    }
    return max;
}

int xMin(listeCoord l)
{
    int min = l->x;
    listeCoord run = l->next;
    while (run != NULL)
    {
        if(min > run->x)
            min = run->x;
        run = run->next;
    }
    return min;
}

int yMax(listeCoord l)
{
    int max = l->y;
    listeCoord run = l->next;
    while (run != NULL)
    {
        if(max < run->y) max = run->y;
        run = run->next;
    }
    return max;
}

int yMin(listeCoord l)
{
    int min = l->y;
    listeCoord run = l->next;
    while (run != NULL)
    {
        if(min > run->y) min = run->y;
        run = run->next;
    }
    return min;
}

//Les listes de passages
//Opérations utiles sur les listes de passages
listeP nouvLp(){return NULL;}

listeP adjTLp(listeP l, noeud node1, noeud node2)
{
    int i = 0;
    while (i < 4 && node1->voisins[i] != node2)
    {
        i++;
    }
    if (i == 4)
    {
       printf("Les 2 noeuds ne sont pas voisins");
       return l;
    }
    listeP new = (listeP) malloc(sizeof(struct s_listeP));
    if (new == NULL) { printf("fatal error: no memory allocation possible.\n"); abort(); }
    new->n1 = node1;
    new->n2 = node2;
    new->len = node1->distances[i];
    new->next = l;
    return new;
}

listeP rechLp(listeP l, noeud node1, noeud node2)
{
    listeP run = l;
    while (run != NULL)
    {
        if((run->n1 == node1 && run->n2 == node2)||(run->n1 == node2 && run->n2 == node1))
            return run;
        run = run->next;
    }
    return NULL;
}

listeP supKiemeLp(listeP l, unsigned int k)
{
    if (l == NULL) return NULL;
	if (k == 0)
	{
		listeP n = l->next;
		free(l);
		return n;
	}
	l->next = supKiemeLp(l->next, k - 1);
	return l;
}

void destroyLp(listeP l)
{
    while (l != NULL)
        l = supKiemeLp(l,0);
}