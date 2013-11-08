

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
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;


bool recording=false;
unsigned int framenum=0;
unsigned char *pRGB;

int SCREEN_WIDTH=640;
int SCREEN_HEIGHT=360;

void capture_frame(unsigned int framenum)
{
	//global pointer float *pRGB
	pRGB = new unsigned char [3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1) ];


	// set the framebuffer to read
	//default for double buffered
	glReadBuffer(GL_BACK);

	glPixelStoref(GL_PACK_ALIGNMENT,1);//for word allignment

	glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pRGB);
	char filename[200];
	sprintf(filename,"frame/frame_%05d.ppm",framenum);
	std::ofstream out(filename, std::ios::out);
	out<<"P6"<<std::endl;
	out<<SCREEN_WIDTH<<" "<<SCREEN_HEIGHT<<" 255"<<std::endl;
	out.write(reinterpret_cast<char const *>(pRGB), (3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1)) * sizeof(int));
	out.close();

	//function to store pRGB in a file named count
	delete pRGB;
}

float ratio;
body body1,body2;
joint* toRotate;
box box1;
body* bs;
room room1;
camera cam;
light light1;
fstream fOut,fIn;
vector< vector< vector<float> > > frame;
int index=0;
void resize(int w, int h){
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0) h = 1;

	ratio = 1.0f * w / h;
	SCREEN_WIDTH=w;
	SCREEN_HEIGHT=h;
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
	frame.push_back(vector<vector<float> >(40));
	frame.push_back(vector<vector<float> >(40));
	for(int i=0;i<18;i++){
		frame[0][i].resize(1);
		frame[1][i].resize(1);
	}
	for(int i=18;i<40;i++){
		frame[0][i].resize(4);
		frame[1][i].resize(4);
	}
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
	if (recording)
    	capture_frame(framenum++);
}

vector<float> createQuaternion(float rx, float ry, float rz){
	rx = rx*M_PI/180;
	ry = ry*M_PI/180;
	rz = rz*M_PI/180;
	vector<float> q(4,0);
	float c1 = cos(ry/2);
		float s1 = sin(ry/2);
		float c2 = cos(rz/2);
		float s2 = sin(rz/2);
		float c3 = cos(rx/2);
		float s3 = sin(rx/2);
		float c1c2 = c1*c2;
		float s1s2 = s1*s2;
		q[0] =c1c2*c3 - s1s2*s3;
		q[1] =c1c2*s3 + s1s2*c3;
	q[2] =s1*c2*c3 + c1*s2*s3;
	q[3] =c1*s2*c3 - s1*c2*s3;
	return q;
}

vector<float> createRotAngle(vector<float> q){
	vector<float> r(3,0);
	double test = q[1]*q[2] + q[3]*q[0];
	if (test > 0.499) { // singularity at north pole
		r[1] = 2 * atan2(q[1],q[0]);
		r[2] = M_PI/2;
		r[0] = 0;
		return r;
	}
	if (test < -0.499) { // singularity at south pole
		r[1] = -2 * atan2(q[1],q[0]);
		r[2] = - M_PI/2;
		r[0] = 0;
		return r;
	}
		double sqx = q[1]*q[1];
		double sqy = q[2]*q[2];
		double sqz = q[3]*q[3];
		r[1] = atan2(2*q[2]*q[0]-2*q[1]*q[3] , 1 - 2*sqy - 2*sqz);
	r[2] = asin(2*test);
	r[0] = atan2(2*q[1]*q[0]-2*q[2]*q[3] , 1 - 2*sqx - 2*sqz);

	r[0] = r[0]*180/M_PI;
	r[1] = r[1]*180/M_PI;
	r[2] = r[2]*180/M_PI;
	return r;
}

vector<float> slerp(vector<float> q1, vector<float> q2, float alpha){
	float dot = q1[0]*q2[0] + q1[1]*q2[1] + q1[2]*q2[2] + q1[3]*q2[3];
	vector<float> q(4,0);
	if(dot>0.95){
		q[0] = q1[0]*(1-alpha) + q2[0]*alpha;
		q[1] = q1[1]*(1-alpha) + q2[1]*alpha;
		q[2] = q1[2]*(1-alpha) + q2[2]*alpha;
		q[3] = q1[3]*(1-alpha) + q2[3]*alpha;
		return q;
	}
	float theta = acos(dot);
	float t1 = sin((1-alpha)*theta)/sin(theta);
	float t2 = sin((alpha)*theta)/sin(theta);
	q[0] = q1[0]*t1 + q2[0]*t2;
	q[1] = q1[1]*t1 + q2[1]*t2;
	q[2] = q1[2]*t1 + q2[2]*t2;
	q[3] = q1[3]*t1 + q2[3]*t2;
	return q;
}

void captureData(){
	//save data here
	fOut<<box1.rx<<" "<<box1.dx<<" ";
	fOut<<body1.x<<" "<<body1.y<<" "<<body1.z<<" "<<body1.ry<<" ";
	fOut<<body2.x<<" "<<body2.y<<" "<<body2.z<<" "<<body2.ry<<" ";
	fOut<<body1.kneeL.rx<<" "<<body1.kneeR.rx<<" "<<body1.elbowL.rz<<" "<<body1.elbowR.rz<<" ";
	fOut<<body2.kneeL.rx<<" "<<body2.kneeR.rx<<" "<<body2.elbowL.rz<<" "<<body2.elbowR.rz<<" ";	//18 single
	vector<float> q(4,0);

	q = createQuaternion(body1.torso2.rx, body1.torso2.ry, body1.torso2.rz);	//22 quat
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body1.neck.rx, body1.neck.ry, body1.neck.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body1.hipL.rx, body1.hipL.ry, body1.hipL.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body1.hipR.rx, body1.hipR.ry, body1.hipR.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body1.ankleL.rx, body1.ankleL.ry, body1.ankleL.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body1.ankleR.rx, body1.ankleR.ry, body1.ankleR.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body1.shoulderL.rx, body1.shoulderL.ry, body1.shoulderL.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body1.shoulderR.rx, body1.shoulderR.ry, body1.shoulderR.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body1.wristL.rx, body1.wristL.ry, body1.wristL.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body1.wristR.rx, body1.wristR.ry, body1.wristR.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body1.stickjoint.rx, body1.stickjoint.ry, body1.stickjoint.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";

	q = createQuaternion(body2.torso2.rx, body2.torso2.ry, body2.torso2.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body2.neck.rx, body2.neck.ry, body2.neck.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body2.hipL.rx, body2.hipL.ry, body2.hipL.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body2.hipR.rx, body2.hipR.ry, body2.hipR.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body2.ankleL.rx, body2.ankleL.ry, body2.ankleL.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body2.ankleR.rx, body2.ankleR.ry, body2.ankleR.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body2.shoulderL.rx, body2.shoulderL.ry, body2.shoulderL.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body2.shoulderR.rx, body2.shoulderR.ry, body2.shoulderR.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body2.wristL.rx, body2.wristL.ry, body2.wristL.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body2.wristR.rx, body2.wristR.ry, body2.wristR.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	q = createQuaternion(body2.stickjoint.rx, body2.stickjoint.ry, body2.stickjoint.rz);
	fOut<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<" ";
	fOut<<endl;
}
float a = 1.1;
void interpolate(float init, float end, float alpha, float* param){
	*param = (1-alpha) * init + end * alpha;
}
void interpolate(vector<float> init, vector<float>	end, float alpha, joint* j){
	vector<float> rot = createRotAngle(slerp(init,end,alpha));
	j->rx =(isnan(rot[0])? 0:rot[0]);
	j->ry =(isnan(rot[1])? 0:rot[1]);
	j->rz =(isnan(rot[2])? 0:rot[2]);
}
void play(int value){
	//animate from reading a single line in file
	if(a<1){
		int i=0;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(box1.rx)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(box1.dx)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body1.x)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body1.y)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body1.z)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body1.ry)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body2.x)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body2.y)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body2.z)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body2.ry)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body1.kneeL.rx)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body1.kneeR.rx)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body1.elbowL.rz)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body1.elbowR.rz)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body2.kneeL.rx)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body2.kneeR.rx)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body2.elbowL.rz)); i++;
		interpolate(frame[index][i][0], frame[(index+1)%2][i][0], a, &(body2.elbowR.rz)); i++;

		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body1.torso2)); i++;	//22 quat
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body1.neck)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body1.hipL)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body1.hipR)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body1.ankleL)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body1.ankleR)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body1.shoulderL)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body1.shoulderR)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body1.wristL)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body1.wristR)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body1.stickjoint)); i++;

		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body2.torso2)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body2.neck)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body2.hipL)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body2.hipR)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body2.ankleL)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body2.ankleR)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body2.shoulderL)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body2.shoulderR)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body2.wristL)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body2.wristR)); i++;
		interpolate(frame[index][i], frame[(index+1)%2][i], a, &(body2.stickjoint)); i++;
		a+=0.1;
		glutPostRedisplay();
		glutTimerFunc(200, play, 0);
	}
	else if(fIn.good()){
		string line;
		getline (fIn,line);
		stringstream input(line);
		for(int i=0;i<18;i++)
			input>>frame[index][i][0];
		for(int i=18;i<40;i++)
			input>>frame[index][i][0]>>frame[index][i][1]>>frame[index][i][2]>>frame[index][i][3];
		index++;
		index%=2;
		a=0;
		glutTimerFunc(200, play, 0);
	}
}
bool moveB;
void processNormalKeys(unsigned char key, int x, int y){
	switch (key){
		case 27:
			if(fOut.is_open()) fOut.close();
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
			moveB = false;
			break;
		case 't':
		case 'T':
			toRotate = &(bs->torso2);
			cout<<"\nTorso Activated...!!!\n";
			moveB = false;
			break;
		case 'h':
			toRotate = &(bs->hipL);
			cout<<"\nHip Left Activated...!!!\n";
			moveB = false;
			break;
		case 'H':
			toRotate = &(bs->hipR);
			cout<<"\nHip Right Activated...!!!\n";
			moveB = false;
			break;
		case 'k':
			toRotate = &(bs->kneeL);
			cout<<"\nKnee Left Activated...!!!\n";
			moveB = false;
			break;
		case 'K':
			toRotate = &(bs->kneeR);
			cout<<"\nKnee Right Activated...!!!\n";
			moveB = false;
			break;
		case 'a':
			toRotate = &(bs->ankleL);
			cout<<"\nAnkle Left Activated...!!!\n";
			moveB = false;
			break;
		case 'A':
			toRotate = &(bs->ankleR);
			cout<<"\nAnkle Right Activated...!!!\n";
			moveB = false;
			break;
		case 's':
			toRotate = &(bs->shoulderL);
			cout<<"\nShoulder Left Activated...!!!\n";
			moveB = false;
			break;
		case 'S':
			toRotate = &(bs->shoulderR);
			cout<<"\nShoulder Right Activated...!!!\n";
			moveB = false;
			break;
		case 'e':
			toRotate = &(bs->elbowL);
			cout<<"\nElbow Left Activated...!!!\n";
			moveB = false;
			break;
		case 'E':
			toRotate = &(bs->elbowR);
			cout<<"\nElbow Right Activated...!!!\n";
			moveB = false;
			break;
		case 'w':
			toRotate = &(bs->wristL);
			cout<<"\nWrist Left Activated...!!!\n";
			moveB = false;
			break;
		case 'W':
			toRotate = &(bs->wristR);
			cout<<"\nWrist Right Activated...!!!\n";
			moveB = false;
			break;
		case 'q':
			toRotate = &(bs->stickjoint);
			cout<<"Sword Activated...!!!\n";
			moveB = false;
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
		case 'r':
			recording = true;
			break;
		case 'c':
		case 'C':
			if(!fOut.is_open()){
				fOut.open("animate/savedData", fstream::out | fstream::app);
			}
			captureData();
			break;
		case 'p':
		case 'P': {
			// char inFile[100];
			// cout<<"Input file name"<<endl;
			// cin>>inFile;
			fIn.open("animate/savedData", fstream::in);
			if(fIn.is_open()){
				if(fIn.good()){
					string line;
					getline (fIn,line);
					stringstream input(line);
					for(int i=0;i<18;i++)
						input>>frame[index][i][0];
					for(int i=18;i<40;i++)
						input>>frame[index][i][0]>>frame[index][i][1]>>frame[index][i][2]>>frame[index][i][3];
					index++;
					index%=2;
				}
				play(0);
			}
			else
				cout<<"Some error occured in opening file"<<endl;
			break;
		}
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
		case 'b':
			moveB = true;
			break;
		case '1':
			if(!moveB)
				toRotate->rx -= 1.0;
			else
				bs->x-= 2;
			break;
		case '3':
			if(!moveB)
				toRotate->rx += 1.0;
			else
				bs->x+= 2;
			break;
		case '4':
			if(!moveB)
				toRotate->ry -= 1.0;
			else
				bs->ry-= 1.0;
			break;
		case '6':
			if(!moveB)
				toRotate->ry += 1.0;
			else
				bs->ry+= 1.0;
			break;
		case '7':
			if(!moveB)
				toRotate->rz -= 1.0;
			else
				bs->z-= 2;
			break;
		case '9':
			if(!moveB)
				toRotate->rz += 1.0;
			else
				bs->z+=2;
			break;
		case '8':
			box1.rx-=1;
			if(box1.dx<14){
				body1.y+=0.32;
				body2.y+=0.32;
				box1.dx+=0.16;
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
