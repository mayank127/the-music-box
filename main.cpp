

#include <cstdlib>
#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>
#include "SOIL.h"
#include "bone.h"
#include "joint.h"
#include "body.h"
#include "box.h"
#include "room.h"
#include "camera.h"
#include "light.h"
#include <iostream>
using namespace std;

float ratio;
body body1,body2;
joint* toRotate;
box box1;
body* bs;
room room1;
camera cam;
light light1;
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
	gluLookAt(cam.ex, cam.ey, cam.ez, cam.lookAtPoint[0], cam.lookAtPoint[1], cam.lookAtPoint[2], 0.0f, 1.0f, 0.0f);
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
	cout<<"8 - Open Box"<<endl;
	cout<<"d - Open Door\t\t";
	cout<<"D - Close Door"<<endl;
	cout<<". - wall light\t\t";
	cout<<", - lamp light"<<endl<<endl;

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
	cout<<"To make points for bezier curve click anywhere on screen and to move in or out use zoom in & zoom out.\nPress space to generate curve and Enter to move camera on it."<<endl;
}

void initScene(){
	glEnable(GL_DEPTH_TEST);
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_LIGHTING);
	glShadeModel( GL_SMOOTH );
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable( GL_NORMALIZE );
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glClearStencil(0);
	glEnable(GL_STENCIL_TEST);
	cam.startCamera = false;
	room1.init();
	light1.init();
	box1 = box(25, 15, 90, -10, -50, -10);
	box1.texture = SOIL_load_OGL_texture
	(
	  "images/wood.jpg",
	  SOIL_LOAD_AUTO,
	  SOIL_CREATE_NEW_ID,
	  SOIL_FLAG_INVERT_Y
	);

	body1 = body(-5,-85,-40,0,0,0);
	body1.init();
	bs = &(body1);
	toRotate = &(bs->torso2);

	body2 = body(15,-85,-40,0,0,0);
	body2.init();
	initTexture2();
	printHelp();
}

double cmx = -90;
double cmy = -30.0;
double cmz = 0;
void mirror (bool check) {
	if(check){
		glBegin(GL_QUADS);		// Draw whole mirror
			glNormal3f(1,0,0);
			glVertex3f(cmx, cmy - 40, cmz - 20.0);
			glVertex3f(cmx, cmy - 40, cmz + 20.0);
			glVertex3f(cmx, cmy + 40, cmz + 20.0);
			glVertex3f(cmx, cmy + 40, cmz - 20.0);
		glEnd();
	}else{
		glBegin(GL_QUADS);		// Draw whole mirror
			glNormal3f(1,0,0);
			glVertex3f(cmx, cmy - 50, cmz - 30.0);
			glVertex3f(cmx, cmy - 50, cmz + 30.0);
			glVertex3f(cmx, cmy + 50, cmz + 30.0);
			glVertex3f(cmx, cmy + 50, cmz - 30.0);
		glEnd();
	}
	
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam.ex, cam.ey, cam.ez, cam.lookAtPoint[0], cam.lookAtPoint[1], cam.lookAtPoint[2], 0.0f, 1.0f, 0.0f);

	glEnable(GL_STENCIL_TEST);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	mirror(true);
	// Clear the colour buffer before displaying the scene.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glPushMatrix();
		glTranslatef(cmx, cmy, cmz);		// Move to centre of mirror.
		glScalef(-1.0, 1.0, 1.0);			// Reflect in X axis.
		glTranslatef(-cmx, -cmy, -cmz);		// Move back again.
		light1.draw();
		room1.draw();
		body1.draw();
		body2.draw();
		box1.draw();
	glPopMatrix();


	glStencilFunc(GL_NOTEQUAL, 1, 1);
	light1.draw();
	room1.drawLeftWall();
	mirror(false);


	glDisable(GL_STENCIL_TEST);
	cam.drawPoints();
	cam.drawPath();
	room1.draw();
	body1.draw();
	body2.draw();
	box1.draw();
	glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y){
	switch (key){
		case 27:
			exit(0);
		case 32:
			cam.calcPath();
			break;
		case 13:
			cam.startCamera = true;
			break;
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
		case ',':
			light1.l1 = !light1.l1;
			break;
		case '.':
			light1.l2 = !light1.l2;
			break;
		case 'd':
			room1.rd += 5;
			break;
		case 'D':
			room1.rd += -5;
			break;
		case '+': {
				float angle = atan((cam.lookAtPoint[0]-cam.ex)/(cam.lookAtPoint[2] - cam.ez));
				if(cam.lookAtPoint[2]-cam.ez>=0){
					cam.ex += sin(angle);
					cam.ez += cos(angle);
					cam.lookAtPoint[0] += sin(angle);
					cam.lookAtPoint[2] += cos(angle);
					cam.z = cam.lookAtPoint[2];
				}else{
					cam.ex -= sin(angle);
					cam.ez -= cos(angle);
					cam.lookAtPoint[0] -= sin(angle);
					cam.lookAtPoint[2] -= cos(angle);
					cam.z = cam.lookAtPoint[2];
				}
				break;
			}
		case '-': {
				float angle = atan((cam.lookAtPoint[0]-cam.ex)/(cam.lookAtPoint[2]-cam.ez));
				if(cam.lookAtPoint[2]-cam.ez<0){
					cam.ex += sin(angle);
					cam.ez += cos(angle);
					cam.lookAtPoint[0] += sin(angle);
					cam.lookAtPoint[2] += cos(angle);
					cam.z = cam.lookAtPoint[2];
				}else{
					cam.ex -= sin(angle);
					cam.ez -= cos(angle);
					cam.lookAtPoint[0] -= sin(angle);
					cam.lookAtPoint[2] -= cos(angle);
					cam.z = cam.lookAtPoint[2];
				}
				break;
			}
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
			if(box1.dx<14){
				body1.y+=0.3;
				body2.y+=0.3;
				box1.dx+=0.15;
			}
			break;
		case '2':
			box1.rx+=1;
			if(box1.dx>0){
				body1.y-=0.32;
				body2.y-=0.32;
				box1.dx-=0.16;
			}
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


void processSpecialKey(int key, int x, int y){
	switch (key) {
		case GLUT_KEY_UP:
			cam.lookAtPoint[1]+=1;
			break;
		case GLUT_KEY_DOWN:
			cam.lookAtPoint[1]-=1;
			break;
		case GLUT_KEY_LEFT:
			cam.lookAtPoint[3]-=.01;
			cam.lookAtPoint[0]=10*sin(cam.lookAtPoint[3])+cam.ex;
			cam.lookAtPoint[2]=-10*cos(cam.lookAtPoint[3])+cam.ez;
			cam.z = cam.lookAtPoint[2];
			break;
		case GLUT_KEY_RIGHT:
			cam.lookAtPoint[3]+=.01;
			cam.lookAtPoint[0]=10*sin(cam.lookAtPoint[3])+cam.ex;
			cam.lookAtPoint[2]=-10*cos(cam.lookAtPoint[3])+cam.ez;
			cam.z = cam.lookAtPoint[2];
			break;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
	if (state == GLUT_DOWN)	{
		if (button == GLUT_LEFT_BUTTON){
			GLdouble modelMatrix[16];
			GLdouble projMatrix[16];
			GLint viewport[4];

			glGetIntegerv(GL_VIEWPORT, viewport);
			glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
			glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);

			GLdouble x0, x1, y0, y1, z0, z1;
			gluUnProject(x, viewport[1] + viewport[3] - y, 0, modelMatrix, projMatrix, viewport, &x0, &y0, &z0);
			gluUnProject(x, viewport[1] + viewport[3] - y, 1, modelMatrix, projMatrix, viewport, &x1, &y1, &z1);
			if(z0 != z1){
				GLfloat t = (z0 - cam.z) / (z0 - z1);
				GLfloat fx = x0 + (x1 - x0) * t,
						fy = y0 + (y1 - y0) * t;
				cam.addPoint(fx,fy);
			}
		}
		if (button == GLUT_RIGHT_BUTTON){
			cam.erasePoint();
		}
	}
	glutPostRedisplay();
}

void moveCamera(int value){
	if(cam.startCamera){
		cam.nextPoint();
	}
	glutPostRedisplay();
	glutTimerFunc(100,moveCamera,0);

}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,360);
	glutCreateWindow("Music Box 3D");

	cout<<"Welcome to Music Box 3D...!!!\n";
	initScene();
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKey);
	glutMouseFunc(mouse);

	glutTimerFunc(100,moveCamera,0);

	glutDisplayFunc(display);

	glutReshapeFunc(resize);

	glutMainLoop();

	return(0);
}
