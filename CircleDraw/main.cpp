/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness fo r the sphere, cone
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
#include<bits/stdc++.h>
#include <stdlib.h>


int xc , yc, r;

// Plot eight points using circle's symmetrical property
void plot_point(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(xc+x, yc+y);
    glVertex2i(xc+x, yc-y);
    glVertex2i(xc+y, yc+x);
    glVertex2i(xc+y, yc-x);
    glVertex2i(xc-x, yc-y);
    glVertex2i(xc-y, yc-x);
    glVertex2i(xc-x, yc+y);
    glVertex2i(xc-y, yc+x);
    glEnd();
}

// Function to draw a circle using bresenham's
// circle drawing algorithm
void bresenham_circle(int r)
{
    int x=0,y=r;
    float pk=(3.0/2.0)-r;

    /* Plot the points */
    /* Plot the first point */
    plot_point(x,y);
    int k;
    /* Find all vertices till x=y */
    while(x < y)
    {
        x = x + 1;
        if(pk < 0)
            pk = pk + 4*x+6;
        else
        {
            y = y - 1;
            pk = pk + 4*(x - y) + 10;
        }
        plot_point(x,y);
    }
    glFlush();
}
void midpoint_circle(int r)
{
    int x=0,y=r;
    float pk = 1-r;

    /* Plot the points */
    /* Plot the first point */
    plot_point(x,y);
    int k;
    /* Find all vertices till x=y */
    while(x < y)
    {
        x = x + 1;
        if(pk < 0)
            pk = pk + 2*x + 3;
        else
        {
            y = y - 1;
            pk = pk + 2*(x - y) + 5;
        }
        plot_point(x,y);
    }
    glFlush();
}
void poly_circle(int r)
{
    int x=0,y=r;
    plot_point(x,y);
    int limit=r/sqrt(2);
    while(x<=limit)
    {
        x++;
        y=sqrt(r*r-x*x);
        plot_point(x,y);
    }
    glFlush();
}

void trigono_circle(int r)
{

    float x=0;
    float y=r;
    float theta=0;
    float range=M_PI_4;

    plot_point(x,y);
    while(theta<range)
    {
        theta+=0.000001;
        x=r*cos(theta);
        y=r*sin(theta);
        plot_point(x,y);

    }
    glEnd();
    glFlush();

}
// Function to draw two concentric circles
void concentric_circles(void)
{
    /* Clears buffers to preset values */
    glClear(GL_COLOR_BUFFER_BIT);

    int radius1 = r, radius2 = 200;
    trigono_circle(radius1);
    //bresenham_circle(radius2);
}



void Init()
{
    /* Set clear color to white */
    glClearColor(1.0,1.0,1.0,0);
    /* Set fill color to black */
    glColor3f(0.0,0.0,0.0);
    /* glViewport(0 , 0 , 640 , 480); */
    /* glMatrixMode(GL_PROJECTION); */
    /* glLoadIdentity(); */
    gluOrtho2D(-640, 640, -480, 480);
}

static int slices = 16;
static int stacks = 16;

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
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glPushMatrix();
    glTranslated(-2.4,1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutSolidSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.4,1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.4,-1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutWireSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,-1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutWireCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.4,-1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutWireTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glutSwapBuffers();
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

int main(int argc, char *argv[])
{
    /*glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

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

    glutMainLoop();*/
    /* Initialise GLUT library */
    printf("Enter center of circle.\n ");
    scanf("%d %d",&xc,&yc);
    printf("Enter radius of circle.\n");
    scanf("%d",&r);
    glutInit(&argc,argv);
    /* Set the initial display mode */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    /* Set the initial window position and size */
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    /* Create the window with title "DDA_Line" */
    glutCreateWindow("bresenham_circle");
    /* Initialize drawing colors */
    Init();
    /* Call the displaying function */
    glutDisplayFunc(concentric_circles);
    /* Keep displaying untill the program is closed */
    glutMainLoop();


    return EXIT_SUCCESS;
}
