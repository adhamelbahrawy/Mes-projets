#include "laby.h"

//1.2
int main(int argc, char const *argv[])
{
    noeud n1 = nouvNoeud();
    noeud n2 = nouvNoeud();
    noeud n3 = nouvNoeud();
    noeud n4 = nouvNoeud();
    noeud n5 = nouvNoeud();
    noeud n6 = nouvNoeud();
    noeud n7 = nouvNoeud();
    noeud n8 = nouvNoeud();
    noeud n9 = nouvNoeud();
    noeud n10 = nouvNoeud();
    noeud n11 = nouvNoeud();
    noeud n12 = nouvNoeud();
    
    float chemN1N2[60] = {0.0};
    passage(n1, n2, 1, 60, chemN1N2);
    float chemN2N1[60] = {0.0};
    passage(n2, n1, 3, 60, chemN2N1);
    
    float chemN2N3[80] = {0.0};
    passage(n2, n3, 1, 80, chemN2N3);
    float chemN3N2[80] = {0.0};
    passage(n3, n2, 3, 80, chemN3N2);

    float chemN3N9[30] = {0.0};
    passage(n3, n9, 2, 30, chemN3N9);
    float chemN9N3[30] = {0.0};
    passage(n9, n3, 0, 30, chemN9N3);
    
    float chemN9N10[30] = {0.0};
    passage(n9, n10, 1, 30, chemN9N10);
    float chemN10N9[30] = {0.0};
    passage(n10, n9, 3, 30, chemN10N9);

    float chemN10N4[30] = {0.0};
    chemN10N4[15] = 1000.0;
    passage(n10, n4, 0, 30, chemN10N4);
    float chemN4N10[30] = {0.0};
    chemN4N10[15] = 1000.0;
    passage(n4, n10, 2, 30, chemN4N10);
    
    float chemN2N7[30] = {0.0};
    passage(n2, n7, 2, 30, chemN2N7);
    float chemN7N2[30] = {0.0};
    chemN7N2[0] = 1000.0;
    passage(n7, n2, 0, 30, chemN7N2);

    float chemN5N6[20] = {0.0};
    passage(n5, n6, 2, 20, chemN5N6);
    float chemN6N5[20] = {0.0};
    passage(n6,n5, 0, 20, chemN6N5);

    float chemN6N7[70] = {0.0};
    passage(n6, n7, 1, 70, chemN6N7);
    float chemN7N6[70] = {0.0};
    chemN7N6[0] = 1000.0; 
    passage(n7, n6, 3, 70, chemN7N6);

    float chemN7N8[50] = {0.0};
    chemN7N8[0] = 1000.0;
    passage(n7, n8, 1, 50, chemN7N8);
    float chemN8N7[50] = {0.0};
    passage(n8, n7, 3, 50, chemN8N7);

    float chemN8N9[30] = {0.0};
    passage(n8, n9, 1, 30, chemN8N9);
    float chemN9N8[30] = {0.0};
    passage(n9, n8, 3, 30, chemN9N8);

    float chemN6N11[20] = {0.0};
    passage(n6, n11, 2, 20, chemN6N11);
    float chemN11N6[20] = {0.0};
    passage(n11, n6, 0, 20, chemN11N6);

    float chemN11N12[120] = {0.0};
    chemN11N12[1] = 1000.0;
    passage(n11, n12, 1, 120, chemN11N12);
    float chemN12N11[120] = {0.0};
    chemN12N11[119] = 1000.0;
    passage(n12, n11, 3, 120, chemN12N11);

    float chemN8N12[20] = {0.0};
    passage(n8, n12, 2, 20, chemN8N12);
    float chemN12N8[20] = {0.0};
    passage(n12, n8, 0, 20, chemN12N8);
    
    int x = 0;
    int y = 0;
    taille(n7, &x, &y);
    printf("Largeur = %d\nLongueur = %d\n", x, y);
    position(n7, &x, &y);
    printf("La position du point noir est (%d ; %d)\n",x,y);
    int len = longueur(n7);
    printf("La longueur du labyrinthe est de %dm\n", len);
    float valTresors = valeurTotalTresors(n7);
    printf("La valeur totale des trésors est %f\n",valTresors);
    return 0;
}