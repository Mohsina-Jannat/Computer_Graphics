#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<bits/stdc++.h>
#include <stdlib.h>
#define PI acos(-1)
using namespace std;

vector<pair<float,float> > v;
float a1,b1,a2,b2,a3,b3;
int n,t,th,a;
float x,y,S;

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glVertex2f(a1,b1);
    glVertex2f(a2,b2);
    glVertex2f(a3,b3);
    glEnd();
    glFlush();

}

static void translation(void)
{
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glVertex2f(a1,b1);
    glVertex2f(a2,b2);
    glVertex2f(a3,b3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(a1+x,b1+y);
    glVertex2f(a2+x,b2+y);
    glVertex2f(a3+x,b3+y);
    glEnd();
    glFlush();

}


static void rotation(void)
{
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glVertex2f(a1,b1);
    glVertex2f(a2,b2);
    glVertex2f(a3,b3);
    glBegin(GL_LINE_LOOP);
    th=(th*PI)/180.0;
    glVertex2f((a1-x)*cos(th)-(b1-y)*sin(th)+x,(a1-x)*sin(th)+(b1-y)*cos(th)+y);
    glVertex2f((a2-x)*cos(th)-(b2-y)*sin(th)+x,(a2-x)*sin(th)+(b2-y)*cos(th)+y);
    glVertex2f((a3-x)*cos(th)-(b3-y)*sin(th)+x,(a3-x)*sin(th)+(b3-y)*cos(th)+y);
    glEnd();
    glFlush();

}


static void scaling(void)
{
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glVertex2f(a1,b1);
    glVertex2f(a2,b2);
    glVertex2f(a3,b3);
    glBegin(GL_LINE_LOOP);
    glVertex2f((a1-x)*S+x,(b1-y)*S+y);
    glVertex2f((a2-x)*S+x,(b2-y)*S+y);
    glVertex2f((a3-x)*S+x,(b3-y)*S+y);
    glEnd();
    glFlush();

}

static void Xmirror(void)
{
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glVertex2f(a1,b1);
    glVertex2f(a2,b2);
    glVertex2f(a3,b3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(a1,-b1);
    glVertex2f(a2,-b2);
    glVertex2f(a3,-b3);
    glEnd();
    glFlush();

}


static void Ymirror(void)
{
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glVertex2f(a1,b1);
    glVertex2f(a2,b2);
    glVertex2f(a3,b3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-a1,b1);
    glVertex2f(-a2,b2);
    glVertex2f(-a3,b3);
    glEnd();
    glFlush();

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
    gluOrtho2D(-100, 100, -100, 100);
}


int main(int argc, char *argv[])
{

    v=vector<pair<float,float> >(n);
    printf("Enter first point:\n");
    scanf("%f %f",&a1,&b1);
    printf("Enter second point:\n");
    scanf("%f %f",&a2,&b2);

    printf("Enter third point:\n");
    scanf("%f %f",&a3,&b3);

    printf("Enter operation:\n1.Translation\n2.Rotation\n3.Scaling\n4.Mirroring\n");
    scanf("%d",&t);

    /* Initialise GLUT library */
    glutInit(&argc,argv);
    /* Set the initial display mode */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    /* Set the initial window position and size */
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    /* Create the window with title "DDA_Line" */
    glutCreateWindow("Scan Line");
    /* Initialize drawing colors */
    Init();
    /* Call the displaying function */
    glutDisplayFunc(display);
    /* Keep displaying untill the program is closed */
    if(t==1)
    {
        printf("Provide the translation Vector\n");
        scanf("%f %f",&x,&y);
        glutDisplayFunc(translation);
    }

    else if(t==2)
    {
        printf("Rotate by how many degrees?\n");
        scanf("%d",&th);
        printf("With respect to which point?\n");
        scanf("%f %f",&x,&y);
        glutDisplayFunc(rotation);
    }
    else if(t==3)
    {
        cout<<"WRT which point?\n";
        cin>>x>>y;
        cout<<"Scaling factor?\n";
        cin>>S;
        glutDisplayFunc(scaling);
    }
    else
    {
        cout<<"WRT which axis?\n1.x\n2.y\n";
        cin >> a;
        if(a==1)
        {
            glutDisplayFunc(Xmirror);
        }
        else
        {

            glutDisplayFunc(Ymirror);
        }



    }

    glutMainLoop();

    return EXIT_SUCCESS;
}
