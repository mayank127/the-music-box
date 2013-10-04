

#include <cstdlib>
#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>
#include "bone.h"
#include "joint.h"
#include "body.h"
#include "box.h"

static float angle=0.0,ratio;
static float x=0.0f,y=10.0f,z=50.0f;
static float lx=0.0f,ly=0.0f,lz=-1.0f;
float d = 50;
body body1;
box box1;


void resize(int w, int h){
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0) h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(x, y, z, 0, 0, 0 , 0.0f, 1.0f, 0.0f);
}

void initScene()
{
	glEnable(GL_DEPTH_TEST);
    //body1.init();
    box1 = box();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw ground

	/*glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f,	100.0f);
	glVertex3f( 100.0f, 0.0f,	100.0f);
	glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();*/
    //body1.draw();
    box1.draw();


	glutSwapBuffers();
}

void orientMe(float ang)
{
	x = d * sin(ang);
	z = d * cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z, 0, 0, 0 , 0.0f, 1.0f, 0.0f);
}


void moveMeFlat(int i)
{
	y+=i;
    orientMe(angle);
}

void processNormalKeys(unsigned char key, int x, int y)
{

	if (key == 27) exit(0);
}


void inputKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT : angle -= 0.1f;orientMe(angle);break;
	case GLUT_KEY_RIGHT : angle +=0.1f;orientMe(angle);break;
	case GLUT_KEY_UP : moveMeFlat(1);break;
	case GLUT_KEY_DOWN : moveMeFlat(-1);break;
	}
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,360);
	glutCreateWindow("Music Box 3D");

	initScene();

	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(inputKey);

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutReshapeFunc(resize);

	glutMainLoop();

	return(0);
}
