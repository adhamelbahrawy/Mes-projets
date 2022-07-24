#include "meshquad.h"
#include "matrices.h"

void MeshQuad::clear()
{
    m_points.clear();
    m_quad_indices.clear();
    m_nb_ind_edges = 0;
}

int MeshQuad::add_vertex(const Vec3& P)
{
    m_points.push_back(P);
    return m_points.size()-1;
}

void MeshQuad::add_quad(int i1, int i2, int i3, int i4)
{
    m_quad_indices.push_back(i1);
    m_quad_indices.push_back(i2);
    m_quad_indices.push_back(i3);
    m_quad_indices.push_back(i4);
}

void MeshQuad::convert_quads_to_tris(const std::vector<int>& quads, std::vector<int>& tris)
{
	tris.clear();
	tris.reserve(3*quads.size()/2);

    // Pour chaque quad on genere 2 triangles
    // Attention a repecter l'orientation des triangles

    for(unsigned int i = 0; i < quads.size(); i += 4)
    {
        tris.push_back(quads[i]);
        tris.push_back(quads[i+1]);
        tris.push_back(quads[i+2]);
        tris.push_back(quads[i]);
        tris.push_back(quads[i+2]);
        tris.push_back(quads[i+3]);
    }
}

bool MeshQuad:: exist_edge(const std::vector<int>& edges, int i1, int i2)
{
    for(unsigned int i = 0; i < edges.size(); i++)
    {
        if(edges[i] == i1)
        {
            if(i % 2 == 0 && edges[i+1] == i2)
                return true;
            else if(i % 2 == 1 && edges[i-1] == i2)
                return true;
        }
    }
    return false;
}

void MeshQuad::convert_quads_to_edges(const std::vector<int>& quads, std::vector<int>& edges)
{
    edges.clear();
    edges.reserve(quads.size()); // ( *2 /2 !)

    for(unsigned int i = 0; i < quads.size(); i += 4)
    {
        if(!exist_edge(edges, quads[i], quads[i+1]) )
        {edges.push_back(quads[i]); edges.push_back(quads[i+1]); m_nb_ind_edges++;}
        if(!exist_edge(edges, quads[i+1], quads[i+2]))
        {edges.push_back(quads[i+1]); edges.push_back(quads[i+2]);  m_nb_ind_edges++;}
        if(!exist_edge(edges, quads[i+2], quads[i+3]))
        {edges.push_back(quads[i+2]); edges.push_back(quads[i+3]);  m_nb_ind_edges++;}
        if(!exist_edge(edges, quads[i+3], quads[i]))
        {edges.push_back(quads[i+3]); edges.push_back(quads[i]);  m_nb_ind_edges++;}
    }
}

void MeshQuad::bounding_sphere(Vec3& C, float& R)
{
    float max_dist = 0;
    Vec3 centre = Vec3(0,0,0);

    //On calcule la plus grande distance entre 2 points distincts qui est donc
    //2*rayon. Le points entre ces 2 points est le centre

    for(unsigned int i = 0; i < m_points.size(); i++)
        for(unsigned int j = 0; j < m_points.size(); j++)
        {
            if(length(m_points[i] - m_points[j]) > max_dist)
            {
                max_dist = length(m_points[i] - m_points[j]);
                centre.x = (m_points[i].x + m_points[j].x) / 2;
                centre.y = (m_points[i].y + m_points[j].y) / 2;
                centre.z = (m_points[i].z + m_points[j].z) / 2;
            }
        }
    C = centre;
    R = max_dist/2;
}

void MeshQuad::create_cube()
{
	clear();

	// ajouter 8 sommets (-1 +1)
    m_points.push_back(Vec3(-1, -1 ,-1));
    m_points.push_back(Vec3(1, -1 ,-1));
    m_points.push_back(Vec3(1, 1 ,-1));
    m_points.push_back(Vec3(-1, 1 ,-1));

    m_points.push_back(Vec3(-1, -1 ,1));
    m_points.push_back(Vec3(1, -1 ,1));
    m_points.push_back(Vec3(1, 1 ,1));
    m_points.push_back(Vec3(-1, 1 ,1));

	// ajouter 6 faces (sens trigo)
    add_quad(0,3,2,1);
    add_quad(4,5,6,7);
    add_quad(4,7,3,0);
    add_quad(5,1,2,6);
    add_quad(7,6,2,3);
    add_quad(4,0,1,5);

    //pour mettre à jour m_nb_ind_edges
    std::vector<int> edges;
    MeshQuad::convert_quads_to_edges(m_quad_indices, edges);

    gl_update();
}

Vec3 MeshQuad::normal_of(const Vec3& A, const Vec3& B, const Vec3& C)
{
    return glm::normalize(glm::cross( B - A, C - A));
}

float MeshQuad::area_of_quad(int q)
{
        // recuperation des indices de points
        int i = m_quad_indices[4*q];
        // recuperation des points
        Vec3 A =  m_points[i];
        Vec3 B =  m_points[i+1];
        Vec3 C =  m_points[i+2];

        return glm::length(B-A) * glm::length(C-B);
}

float MeshQuad::det(const Vec3& A, const Vec3& B, const Vec3& C)
{
    return( (B.x-A.x)*(C.y-A.y) - (C.x-A.x)*(B.y-A.y) );
}

bool MeshQuad::is_points_in_quad(const Vec3& P, const Vec3& A, const Vec3& B, const Vec3& C, const Vec3& D)
{
    return
    (
        (det(A,B,P) >= 0 && det(B,C,P) >= 0 && det(C,D,P) >= 0 && det(D,A,P) >= 0)
        ||
        (det(A,B,P) <= 0 && det(B,C,P) <= 0 && det(C,D,P) <= 0 && det(D,A,P) <= 0)
    );
}

bool MeshQuad::intersect_ray_quad(const Vec3& P, const Vec3& Dir, int q, Vec3& inter)
{
    // recuperation des indices de points
    int i0 = m_quad_indices[q*4];
    int i1 = m_quad_indices[q*4+1];
    int i2 = m_quad_indices[q*4+2];
    int i3 = m_quad_indices[q*4+3];
//    std::cout << "Quad " << i0 << " " << i1 << " " << i2 << " " << i3 << "\n" ;
    // recuperation des points
    Vec3 A =  m_points[i0];
    Vec3 B =  m_points[i1];
    Vec3 C =  m_points[i2];
    Vec3 D =  m_points[i3];

    // calcul de l'equation du plan (N+d)
    Vec3 N = normal_of(A,B,C);
    float d = glm::dot(N,A);

    //Si le rayon est parallèle au plan du quad alors il n'ya pas d'intersection
    if(glm::dot(Dir, N) == 0)
        return false;

    // Sinon calcul de l'intersection rayon plan
    // I = P + alpha*Dir est dans le plan => calcul de alpha
    float alpha = (d - glm::dot(P,N)) / glm::dot(Dir,N);
    // alpha => calcul de I
    inter = P + alpha*Dir;
    // I dans le quad ?
    return is_points_in_quad(inter, A, B, C, D);
}

int MeshQuad::intersected_closest(const Vec3& P, const Vec3& Dir)
{
    int  q = -1 ;
    float min = FLT_MAX_EXP ;
    Vec3 inters = Vec3() ;

    for(unsigned int i = 0; i < m_quad_indices.size()/4; i++)
    {
        if(intersect_ray_quad(P,Dir,i,inters))
            if( glm::length(P - inters)  < min)
            {
                q = i ; min = glm::length(P - inters) ;
            }
    }

    return q;
}

Mat4 MeshQuad::local_frame(int q)
{
    // Repere local = Matrice de transfo avec
    // les trois premieres colones: X,Y,Z locaux
    // la derniere colonne l'origine du repere

    // ici Z = N et X = AB
    // Origine le centre de la face
    // longueur des axes : [AB]/2

    // recuperation des indices de points
    int i0 = m_quad_indices[q*4];
    int i1 = m_quad_indices[q*4+1];
    int i2 = m_quad_indices[q*4+2];

    // recuperation des points
    Vec3 A =  m_points[i0];
    Vec3 B =  m_points[i1];
    Vec3 C =  m_points[i2];

    // calcul de Z:N / X:AB -> Y
    Vec3 X = B-A;
    Vec3 Y = C-B;
    Vec3 Z = glm::cross(X, Y);

    // calcul du centre
    Vec3 O = Vec3((A.x+C.x)/2, (A.y+C.y)/2, (A.z+C.z)/2);

    // calcul de la taille
    float s = glm::length(X) / 2.0;

    X = glm::normalize(X);
    Y = glm::normalize(Y);
    Z = glm::normalize(Z);

    // calcul de la matrice
    Mat4 res = scale(s) * Mat4(Vec4(X,0),Vec4(Y,0),Vec4(Z,0),Vec4(O,1));
    return res;
}

void MeshQuad::extrude_quad(int q)
{
    // recuperation des indices de points
    int i0 = m_quad_indices[q*4];
    int i1 = m_quad_indices[q*4+1];
    int i2 = m_quad_indices[q*4+2];
    int i3 = m_quad_indices[q*4+3];
    //std::cout << "Quad " << i0 << " " << i1 << " " << i2 << " " << i3 << "\n" ;

    // recuperatIon des points
    Vec3 A =  m_points[i0];
    Vec3 B =  m_points[i1];
    Vec3 C =  m_points[i2];
    Vec3 D =  m_points[i3];

    // calcul de la normale
    Vec3 N = normal_of(A,B,C);

    // calcul de la hauteur
    float K = sqrt(area_of_quad(q));

    // calcul et ajout des 4 nouveaux points
    Vec3 KN = K*N;
    Vec3 Ap = A + KN;
    Vec3 Bp = B + KN;
    Vec3 Cp = C + KN;
    Vec3 Dp = D + KN;

    // on remplace le quad initial par le quad du dessus
    int i0p = add_vertex(Ap);
    int i1p = add_vertex(Bp);
    int i2p = add_vertex(Cp);
    int i3p = add_vertex(Dp);

    m_quad_indices[q*4] = i0p;
    m_quad_indices[q*4+1] = i1p;
    m_quad_indices[q*4+2] = i2p;
    m_quad_indices[q*4+3] = i3p;

    // on ajoute les 4 quads des cotes
    add_quad(i0, i1, i1p, i0p);
    add_quad(i1, i2, i2p, i1p);
    add_quad(i2, i3, i3p, i2p);
    add_quad(i3, i0, i0p, i3p);

    gl_update();
}

void MeshQuad::transfo_quad(int q, const glm::mat4& tr)
{
    // recuperation des indices de points
    int i0 = m_quad_indices[q*4];
    int i1 = m_quad_indices[q*4+1];
    int i2 = m_quad_indices[q*4+2];
    int i3 = m_quad_indices[q*4+3];
    //std::cout << "Quad " << i0 << " " << i1 << " " << i2 << " " << i3 << "\n" ;

    // recuperation des (references de) points
    Vec3 &A =  m_points[i0];
    Vec3 &B =  m_points[i1];
    Vec3 &C =  m_points[i2];
    Vec3 &D =  m_points[i3];

    // generation de la matrice de transfo globale:
    // indice utilisation de glm::inverse() et de local_frame
    Mat4 lf = local_frame(q);
    //il faut vérifier si la matrice est inversible ou non
    Mat4 lfinv = glm::inverse(lf);

    //on se ramène à l'orgine puis transfo puis retour au local frame
    Mat4 T = lf * tr * lfinv;

    // Application au 4 points du quad 
    A = Vec3(T * Vec4(A, 1));
    B = Vec3(T * Vec4(B, 1));
    C = Vec3(T * Vec4(C, 1));
    D = Vec3(T * Vec4(D, 1));

    gl_update();
}

void MeshQuad::decale_quad(int q, float d)
{
    transfo_quad(q, translate(0, 0, d));
    gl_update();
}

void MeshQuad::shrink_quad(int q, float s)
{
    transfo_quad(q, scale(s,s,1));
    gl_update();
}

void MeshQuad::tourne_quad(int q, float a)
{
    transfo_quad(q, rotateZ(a));
    gl_update();
}


MeshQuad::MeshQuad():
	m_nb_ind_edges(0)
{}

void MeshQuad::gl_init()
{
	m_shader_flat = new ShaderProgramFlat();
	m_shader_color = new ShaderProgramColor();

	//VBO
	glGenBuffers(1, &m_vbo);

	//VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glEnableVertexAttribArray(m_shader_flat->idOfVertexAttribute);
	glVertexAttribPointer(m_shader_flat->idOfVertexAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);

	glGenVertexArrays(1, &m_vao2);
	glBindVertexArray(m_vao2);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glEnableVertexAttribArray(m_shader_color->idOfVertexAttribute);
	glVertexAttribPointer(m_shader_color->idOfVertexAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);

	//EBO indices
	glGenBuffers(1, &m_ebo);
	glGenBuffers(1, &m_ebo2);
}

void MeshQuad::gl_update()
{
	//VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * m_points.size() * sizeof(GLfloat), &(m_points[0][0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	std::vector<int> tri_indices;
	convert_quads_to_tris(m_quad_indices,tri_indices);

	//EBO indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,tri_indices.size() * sizeof(int), &(tri_indices[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::vector<int> edge_indices;
	convert_quads_to_edges(m_quad_indices,edge_indices);
	m_nb_ind_edges = edge_indices.size();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_nb_ind_edges * sizeof(int), &(edge_indices[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



void MeshQuad::set_matrices(const Mat4& view, const Mat4& projection)
{
	viewMatrix = view;
	projectionMatrix = projection;
}

void MeshQuad::draw(const Vec3& color)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);

	m_shader_flat->startUseProgram();
	m_shader_flat->sendViewMatrix(viewMatrix);
	m_shader_flat->sendProjectionMatrix(projectionMatrix);
	glUniform3fv(m_shader_flat->idOfColorUniform, 1, glm::value_ptr(color));
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ebo);
	glDrawElements(GL_TRIANGLES, 3*m_quad_indices.size()/2,GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	m_shader_flat->stopUseProgram();

	glDisable(GL_POLYGON_OFFSET_FILL);

	m_shader_color->startUseProgram();
	m_shader_color->sendViewMatrix(viewMatrix);
	m_shader_color->sendProjectionMatrix(projectionMatrix);
	glUniform3f(m_shader_color->idOfColorUniform, 0.0f,0.0f,0.0f);
	glBindVertexArray(m_vao2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ebo2);
	glDrawElements(GL_LINES, m_nb_ind_edges,GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	m_shader_color->stopUseProgram();
	glDisable(GL_CULL_FACE);
}

