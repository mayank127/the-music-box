

#include <cstdlib>
#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>
#include "bone.h"
#include "joint.h"
#include "body.h"

static float angle=0.0,ratio;
static float x=0.0f,y=10.0f,z=50.0f;
static float lx=0.0f,ly=0.0f,lz=-1.0f;
float d = 50;
body body1;
joint* toRotate;

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
	body1.init();
	toRotate = &(body1.torso2);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	body1.draw();


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
	d-=i;
	orientMe(angle);
}

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key){
		case 27:
			exit(0);
		case 'n':
		case 'N':
			toRotate = &(body1.neck);
			break;
		case 't':
		case 'T':
			toRotate = &(body1.torso2);
			break;
		case 'h':
			toRotate = &(body1.hipL);
			break;
		case 'H':
			toRotate = &(body1.hipR);
			break;
		case 'k':
			toRotate = &(body1.kneeL);
			break;
		case 'K':
			toRotate = &(body1.kneeR);
			break;
		case 'a':
			toRotate = &(body1.ankleL);
			break;
		case 'A':
			toRotate = &(body1.ankleR);
			break;
		case 's':
			toRotate = &(body1.shoulderL);
			break;
		case 'S':
			toRotate = &(body1.shoulderR);
			break;
		case 'e':
			toRotate = &(body1.elbowL);
			break;
		case 'E':
			toRotate = &(body1.elbowR);
			break;
		case 'w':
			toRotate = &(body1.wristL);
			break;
		case 'W':
			toRotate = &(body1.wristR);
			break;
		case '1':
			toRotate->rx -= 0.5;
			break;
		case '3':
			toRotate->rx += 0.5;
			break;
		case '4':
			toRotate->ry -= 0.5;
			break;
		case '6':
			toRotate->ry += 0.5;
			break;
		case '7':
			toRotate->rz -= 0.5;
			break;
		case '9':
			toRotate->rz += 0.5;
			break;
	}
	glutPostRedisplay();
}


void inputKey(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT:
			angle -= 0.1f;
			orientMe(angle);
			break;
		case GLUT_KEY_RIGHT:
			angle +=0.1f;
			orientMe(angle);
			break;
		case GLUT_KEY_UP:
			moveMeFlat(1);
			break;
		case GLUT_KEY_DOWN:
			moveMeFlat(-1);
			break;
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
