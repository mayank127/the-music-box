

#include <cstdlib>
#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>
#include "SOIL.h"
#include "bone.h"
#include "joint.h"
#include "body.h"
#include "box.h"
#include <iostream>
using namespace std;

float x=0.0f,y=10.0f,z=50.0f,r=50.0;
float angle=0,ratio;
body body1,body2;
joint* toRotate;
box box1;
body* bs;


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


void initTexture2(){
	GLuint jeans_tex = SOIL_load_OGL_texture
	(
	  "images/jeans.jpeg",
	  SOIL_LOAD_AUTO,
	  SOIL_CREATE_NEW_ID,
	  SOIL_FLAG_INVERT_Y
	);
	GLuint shirt_tex = SOIL_load_OGL_texture
	(
	  "images/shirt2.jpeg",
	  SOIL_LOAD_AUTO,
	  SOIL_CREATE_NEW_ID,
	  SOIL_FLAG_INVERT_Y
	);
	GLuint skin_tex = SOIL_load_OGL_texture
	(
	  "images/skin.jpeg",
	  SOIL_LOAD_AUTO,
	  SOIL_CREATE_NEW_ID,
	  SOIL_FLAG_INVERT_Y
	);


	body2.torso3.texture = shirt_tex;
	body2.torso1.texture = shirt_tex;
	body2.head.texture = SOIL_load_OGL_texture
	(
	  "images/face.png",
	  SOIL_LOAD_AUTO,
	  SOIL_CREATE_NEW_ID,
	  SOIL_FLAG_INVERT_Y
	);
	body2.thighL.texture = jeans_tex;
	body2.thighR.texture = jeans_tex;
	body2.legL.texture = jeans_tex;
	body2.legR.texture = jeans_tex;
	body2.footL.texture = skin_tex;
	body2.footR.texture = skin_tex;
	body2.uarmL.texture = shirt_tex;
	body2.uarmR.texture = shirt_tex;
	body2.larmL.texture = skin_tex;
	body2.larmR.texture = skin_tex;
	body2.handL.texture = skin_tex;
	body2.handR.texture = skin_tex;

	body2.torso2.texture = shirt_tex;
	body2.neck.texture = skin_tex;
	body2.hipL.texture = jeans_tex;
	body2.hipR.texture = jeans_tex;
	body2.kneeL.texture = jeans_tex;
	body2.kneeR.texture = jeans_tex;
	body2.ankleL.texture = jeans_tex;
	body2.ankleR.texture = jeans_tex;
	body2.shoulderL.texture = shirt_tex;
	body2.shoulderR.texture = shirt_tex;
	body2.elbowL.texture = skin_tex;
	body2.elbowR.texture = skin_tex;
	body2.wristL.texture = skin_tex;
	body2.wristR.texture = skin_tex;

}

void printHelp(){
	cout<<"Here are the controls...\n";
	cout<<"Arrow keys to move your camera\n";
	cout<<"2 - Close Box\t\t";
	cout<<"8 - Open Box"<<endl<<endl;

	cout<<"5 - Switch Body"<<endl;
	cout<<"1 - Rotate x -\t\t";
	cout<<"3 - Rotate x +"<<endl;
	cout<<"4 - Rotate y -\t\t";
	cout<<"6 - Rotate y +"<<endl;
	cout<<"7 - Rotate z -\t\t";
	cout<<"9 - Rotate x +"<<endl<<endl;

	cout<<"n - Neck"<<endl;
	cout<<"t - Torso"<<endl;
	cout<<"h - Hip Left\t\t";
	cout<<"H - Hip Right"<<endl;
	cout<<"k - Knee Left\t\t";
	cout<<"K - Knee Right"<<endl;
	cout<<"a - Ankle Left\t\t";
	cout<<"A - Ankle Right"<<endl;
	cout<<"s - Shoulder L\t\t";
	cout<<"S - Shoulder R"<<endl;
	cout<<"e - Elbow Left\t\t";
	cout<<"E - Elbow Right"<<endl;
	cout<<"w - Wrist Left\t\t";
	cout<<"W - Wrist Right"<<endl;
}

void initScene()
{
	glEnable(GL_DEPTH_TEST);
	glEnable( GL_TEXTURE_2D );
	body1 = body(-10,0,0,0,0,0);
	body1.init();
	bs = &(body1);
	toRotate = &(bs->torso2);
	box1 = box(10, 6, 90, 0, 0, 0);
	body2 = body(20,0,0,0,0,0);
	body2.init();
	initTexture2();
	printHelp();

	box1.texture = SOIL_load_OGL_texture
	(
	  "images/wood.jpg",
	  SOIL_LOAD_AUTO,
	  SOIL_CREATE_NEW_ID,
	  SOIL_FLAG_INVERT_Y
	);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	body1.draw();
	body2.draw();
	box1.draw();
	glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key){
		case 27:
			exit(0);
		case 'n':
		case 'N':
			toRotate = &(bs->neck);
			cout<<"\nNeck Activated...!!!\n";
			break;
		case 't':
		case 'T':
			toRotate = &(bs->torso2);
			cout<<"\nTorso Activated...!!!\n";
			break;
		case 'h':
			toRotate = &(bs->hipL);
			cout<<"\nHip Left Activated...!!!\n";
			break;
		case 'H':
			toRotate = &(bs->hipR);
			cout<<"\nHip Right Activated...!!!\n";
			break;
		case 'k':
			toRotate = &(bs->kneeL);
			cout<<"\nKnee Left Activated...!!!\n";
			break;
		case 'K':
			toRotate = &(bs->kneeR);
			cout<<"\nKnee Right Activated...!!!\n";
			break;
		case 'a':
			toRotate = &(bs->ankleL);
			cout<<"\nAnkle Left Activated...!!!\n";
			break;
		case 'A':
			toRotate = &(bs->ankleR);
			cout<<"\nAnkle Right Activated...!!!\n";
			break;
		case 's':
			toRotate = &(bs->shoulderL);
			cout<<"\nShoulder Left Activated...!!!\n";
			break;
		case 'S':
			toRotate = &(bs->shoulderR);
			cout<<"\nShoulder Right Activated...!!!\n";
			break;
		case 'e':
			toRotate = &(bs->elbowL);
			cout<<"\nElbow Left Activated...!!!\n";
			break;
		case 'E':
			toRotate = &(bs->elbowR);
			cout<<"\nElbow Right Activated...!!!\n";
			break;
		case 'w':
			toRotate = &(bs->wristL);
			cout<<"\nWrist Left Activated...!!!\n";
			break;
		case 'W':
			toRotate = &(bs->wristR);
			cout<<"\nWrist Right Activated...!!!\n";
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
		case '8':
			box1.rx-=1;
			break;
		case '2':
			box1.rx+=1;
			break;
		case '5':
			if(bs==&(body1)){
				bs = &(body2);
				cout<<"\nBody 2 Activated...!!!\n";
			}
			else{
				bs = &(body1);
				cout<<"\nBody 1 Activated...!!!\n";
			}
			toRotate = &(bs->torso2);
			break;
	}
	glutPostRedisplay();
}


void orientMe(float ang)
{
	x = r * sin(ang);
	z = r * cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z, 0, 0, 0 , 0.0f, 1.0f, 0.0f);
}


void moveMeFlat(int i)
{
	y-=i;
	orientMe(angle);
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

	cout<<"Welcome to Music Box 3D...!!!\n";
	initScene();
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(inputKey);

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutReshapeFunc(resize);

	glutMainLoop();

	return(0);
}
