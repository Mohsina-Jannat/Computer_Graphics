/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static int slices = 16;
static int stacks = 16;

double X1, Y1, X2, Y2;

float round_value(float v)
{
    return floor(v + 0.5);
}

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    double dx=(X2-X1);
    double dy=(Y2-Y1);
    double tangent , b;
    float x=X1,y=Y1;

    /* Clears buffers to preset values */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Plot the points */
    glBegin(GL_LINES);
    glVertex2f(0.5f,0.5f);
    glVertex2f(-0.5f,0.5f);
    glVertex2f(-0.5f,-0.5f);
    glVertex2f(0.5f,-0.5f);
    /*glBegin(GL_POINTS);
    /* Plot the first point */
    /*glVertex2d(round_value(x), round_value(y));
    int k;

    if(dx == 0)
    {
        while(y<=Y2)
        {
            y += 1.0;
            glVertex2d(round_value(x), round_value(y));
        }
    }
    else if(dy == 0)
    {
        while(x<=X2)
        {
            x += 1.0;
            glVertex2d(round_value(x),round_value(y));
        }
    }
    else
    {
        tangent = dy/dx ;
        b = y - tangent * x;

        if(tangent >= 1)
        {
            while(x<=X2)
            {
                y+=1.0;
                x = (y - b)/tangent;

                glVertex2d(round_value(x),round_value(y));
            }
        }
        else
        {
            while(y<=Y2)
            {
                x+=1.0;
                y = tangent*x + b;

                glVertex2d(round_value(x),round_value(y));

            }
        }
    }*/

    glEnd();

    glFlush();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

void Init()
{
    /* Set clear color to white */
    glClearColor(0.0,0.0,0.0,0);
    /* Set fill color to black */
    glColor3f(1.0,0.0,0.0);
    /* glViewport(0 , 0 , 640 , 480); */
    /* glMatrixMode(GL_PROJECTION); */
    /* glLoadIdentity(); */
    gluOrtho2D(-100.0 , 100.0 , -100.0 , 100.0);
}

int main(int argc, char *argv[])
{


    /*printf("Enter two end points of the line to be drawn:\n");
    printf("\n************************************");
    printf("\nEnter Point1( X1 , Y1):\n");
    scanf("%lf%lf",&X1,&Y1);
    printf("\n************************************");
    printf("\nEnter Point1( X2 , Y2):\n");
    scanf("%lf%lf",&X2,&Y2); */

    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    //glutKeyboardFunc(key);
    //glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}

