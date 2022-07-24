
#include <QApplication>
#include <QGLViewer/simple_viewer.h>
#include <matrices.h>
#include <primitives.h>
#include <meshquad.h>

const Vec3 ROUGE   = {1,0,0};
const Vec3 VERT    = {0,1,0};
const Vec3 BLEU    = {0,0,1};
const Vec3 JAUNE   = {1,1,0};
const Vec3 CYAN    = {0,1,1};
const Vec3 MAGENTA = {1,0,1};
const Vec3 BLANC   = {1,1,1};
const Vec3 GRIS    = {0.5,0.5,0.5};
const Vec3 NOIR    = {0,0,0};


void draw_repere(const Primitives& prim, const Mat4& tr)
{
    prim.draw_sphere(tr*Mat4()*scale(0.2,0.2,0.2), BLANC);
    prim.draw_cone(tr*translate(.7,0,0)*rotateY(90)*scale(0.2,0.2,0.2), ROUGE);
    prim.draw_cylinder(tr*translate(0.3,0,0)*rotateY(90)*scale(0.5,0.5,3)*scale(0.2,0.2,0.2),ROUGE);
    prim.draw_cone(tr*translate(0,.7,0)*rotateX(-90)*scale(0.2,0.2,0.2), VERT);
    prim.draw_cylinder(tr*translate(0,0.3,0)*rotateX(90)*scale(0.5,0.5,3)*scale(0.2,0.2,0.2), VERT);
    prim.draw_cone(tr*translate(0,0,.7)*scale(0.2,0.2,0.2), BLEU);
    prim.draw_cylinder(tr*translate(0,0,0.3)*rotateZ(90)*scale(0.5,0.5,3)*scale(0.2,0.2,0.2), BLEU);
}


void star(MeshQuad& m)
{
    m.create_cube();
    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 15 ; j++)
        {
            m.extrude_quad(i) ;
            m.shrink_quad(i,0.9) ;
            m.tourne_quad(i,30) ;
        }
}

void spirale(MeshQuad& m)
{
    m.create_cube();
    int rot = 9;

    m.tourne_quad(1,10);
    m.extrude_quad(3);

    for(int i = 0 ; i < 100 ; i++)
    {
        m.tourne_quad(rot,10);
        m.transfo_quad(3, translate(0,5,0)) ;
        m.extrude_quad(3);
        rot += 4;
    }
}


int main(int argc, char *argv[])
{
    Primitives prim;
	int selected_quad = -1;
	glm::mat4 selected_frame;
	MeshQuad mesh;

	// init du viewer
	QApplication a(argc, argv);
	SimpleViewer::init_gl();
	SimpleViewer viewer({0.1,0.1,0.1},5);

	// GL init
	viewer.f_init = [&] ()
	{
		prim.gl_init();
		mesh.gl_init();
	};

	// drawing
	viewer.f_draw = [&] ()
	{
		mesh.set_matrices(viewer.getCurrentModelViewMatrix(),viewer.getCurrentProjectionMatrix());
		prim.set_matrices(viewer.getCurrentModelViewMatrix(),viewer.getCurrentProjectionMatrix());

		mesh.draw(CYAN);

		if (selected_quad>=0)
			draw_repere(prim,selected_frame);
	};

	// to do when key pressed
	viewer.f_keyPress = [&] (int key, Qt::KeyboardModifiers mod)
	{
		switch(key)
		{
			case Qt::Key_C:
				if (!(mod & Qt::ControlModifier))
                    mesh.create_cube();
				break;

			// e extrusion
            case Qt::Key_E:
                if (!(mod & Qt::ControlModifier && selected_quad != -1))
                {
                    mesh.extrude_quad(selected_quad);
                    selected_frame = mesh.local_frame(selected_quad);
                }
                break;

            // +/- decale
            case Qt::Key_Plus:
                if (!(mod & Qt::ControlModifier && selected_quad != -1))
                {
                    mesh.decale_quad(selected_quad,0.5);
                    selected_frame = mesh.local_frame(selected_quad);
                }
                break;

            case Qt::Key_Minus:
                if (!(mod & Qt::ControlModifier && selected_quad != -1))
                {
                    mesh.decale_quad(selected_quad,-0.5);
                    selected_frame = mesh.local_frame(selected_quad);
                }
                break;

            // z/Z shrink
            case Qt::Key_Z:
                if (!(mod & Qt::ControlModifier))
                {
                    mesh.shrink_quad(selected_quad,0.9);
                    selected_frame = mesh.local_frame(selected_quad);
                }
                break;

            // t/T tourne
            case Qt::Key_T:
                if (!(mod & Qt::ControlModifier))
                {
                    mesh.tourne_quad(selected_quad,10);
                    selected_frame = mesh.local_frame(selected_quad);
                }
                break;
			// Attention au cas m_selected_quad == -1

			// generation d'objet
            case Qt::Key_S:
                star(mesh);
                break;

            case Qt::Key_P:
                spirale(mesh);
                break;

			default:
				break;
		}

		Vec3 sc;
		float r;
		mesh.bounding_sphere(sc,r);
		viewer.setSceneCenter(qglviewer::Vec(sc[0],sc[1],sc[2]));
		viewer.setSceneRadius(r);
		viewer.camera()->centerScene();
		viewer.update();
	};

	// to do when mouse clicked (P + Dir = demi-droite (en espace objet) orthogonale à l'écran passant par le point cliqué
	viewer.f_mousePress3D = [&] (Qt::MouseButton /*b*/, const glm::vec3& P, const glm::vec3& Dir)
	{
		selected_quad = mesh.intersected_closest(P,Dir);
		if (selected_quad>=0)
			selected_frame = mesh.local_frame(selected_quad);
		std::cout << selected_quad << std::endl;
	};

	viewer.clearShortcuts();
	viewer.setShortcut(QGLViewer::EXIT_VIEWER,Qt::Key_Escape);
	viewer.show();
	return a.exec();
}
