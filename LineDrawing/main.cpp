#include<bits/stdc++.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
double X1, Y1, X2, Y2;
double round_value(double v)
{
    return floor(v + 0.5);
}

void SimpleLine(void)
{
    double dx=(X2-X1);
    double dy=(Y2-Y1);
    double m , c;
    double x=X1,y=Y1;

    /* Clears buffers to preset values */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Plot the points */
    glBegin(GL_POINTS);
    /* Plot the first point */
    glVertex2d(round_value(x), round_value(y));
    //int k;

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
        m = dy/dx ;
        c = y - m * x;

        if(m >= 1)
        {
            while(x<=X2)
            {
                y+=1.0;
                x = (y - c)/m;

                glVertex2d(round_value(x),round_value(y));
            }
        }
        else
        {
            while(y<=Y2)
            {
                x+=1.0;
                y = m*x + c;

                glVertex2d(round_value(x),round_value(y));

            }
        }
    }

    glEnd();

    glFlush();
}

void DDA(void)
{
    double dx=(X2-X1);
    double dy=(Y2-Y1);
    double m , c;
    double x=X1,y=Y1;

    /* Clears buffers to preset values */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Plot the points */
    glBegin(GL_POINTS);
    /* Plot the first point */
    glVertex2d(round_value(x), round_value(y));


    /*if(dx == 0)
    {
        while(y<=Y2)
        {
            y += 1.0;
            glVertex2d(round_value(x), round_value(y));
        }
    }*/
    if(dy == 0)
    {
        while(x<=X2)
        {
            x += 1.0;
            glVertex2d(round_value(x),round_value(y));
        }
    }
    else
    {
        m = dy/dx ;
        c = y - m * x;

        if(m > 1)
        {
            while(x<=X2)
            {
                y+=1.0;
                x= x + (1/m);

                glVertex2d(round_value(x),round_value(y));
            }
        }
        else
        {
            while(y<=Y2)
            {
                x+=1.0;
                y = y+m;

                glVertex2d(round_value(x),round_value(y));

            }
        }
    }

    glEnd();

    glFlush();
}


void Bresenham()
{
    double dx=X2-X1;
    double dy=Y2-Y1;
    double dT=2*(dy-dx);
    double dS=2*dy;
    double d=2*dy-dx;
    double x=X1,y=Y1;


    glClear(GL_COLOR_BUFFER_BIT);

    /* Plot the points */
    glBegin(GL_POINTS);
    /* Clears buffers to preset values */
    glVertex2d(round_value(x),round_value(y));

    while(x<X2)
    {
        x+=1.0;
        if(d<0)
        {
            d+=dS;
        }
        else{
            y+=1.0;
            d+=dT;
        }
        glVertex2d(round_value(x),round_value(y));
    }
    glEnd();
    glFlush();
}

void Init()
{
    /* Set clear color to white */
    glClearColor(0.0,0.0,0.0,0);
    /* Set fill color to black */
    glColor3f(1.0,0.0,0.0);
    /* glViewport(0 , 0 , 640 , 480); */
    /* glMatrixMode(GL_PROJECTION); */
    /* glLoadIdentity(); */
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
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

    printf("Put two end points of a line:\n");
    printf("\nPut Point1( X1 , Y1):\n");
    scanf("%lf%lf",&X1,&Y1);
    printf("\nPut Point1( X2 , Y2):\n");
    scanf("%lf%lf",&X2,&Y2);

    /* Initialise GLUT library */
    glutInit(&argc,argv);
    /* Set the initial display mode */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    /* Set the initial window position and size */
    glutInitWindowPosition(0,0);
    glutInitWindowSize(300,300);
    /* Create the window with title "DDA_Line" */
    glutCreateWindow("Simple Line Drawing Algorithm");
    /* Initialize drawing colors */
    Init();
    /* Call the displaying function */
    glutDisplayFunc(Bresenham

                    );
    /* Keep displaying untill the program is closed */
    glutMainLoop();




    glutInit(&argc, argv);
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



    return EXIT_SUCCESS;
}
