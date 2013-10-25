#include "light.h"
#include <GL/glut.h>
#include <iostream>

light::light(){
	l1 = true;
	l2 = true;
}
void light::init(){
	amb1[0] = 0;
	amb1[1] = 0;
	amb1[2] = 0;
	amb1[3] = 1;

	dif1[0] = 1;
	dif1[1] = 1;
	dif1[2] = 1;
	dif1[3] = 1;

	light_position1[0] = 70;
	light_position1[1] = -30;
	light_position1[2] = -100;
	light_position1[3] = 1;

	amb2[0] = 0;
	amb2[1] = 0;
	amb2[2] = 0;
	amb2[3] = 1;

	dif2[0] = 1;
	dif2[1] = 1;
	dif2[2] = 1;
	dif2[3] = 1;

	light_position2[0] = 0;
	light_position2[1] = 20;
	light_position2[2] = 90;
	light_position2[3] = 1;

}
void light::draw(){
	if(l1){
		glLightfv(GL_LIGHT0, GL_DIFFUSE,dif1);
		glLightfv(GL_LIGHT0, GL_AMBIENT,amb1);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
		glEnable(GL_LIGHT0);
		glBegin(GL_POINTS);
			glVertex3f(light_position1[0],light_position1[1],light_position1[2]);
		glEnd();
	}else{
		glDisable(GL_LIGHT0);
	}
	if(l2){
		glLightfv(GL_LIGHT1, GL_DIFFUSE,dif2);
		glLightfv(GL_LIGHT1, GL_AMBIENT,amb2);
		glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
		glEnable(GL_LIGHT1);
		glBegin(GL_POINTS);
			glVertex3f(light_position2[0],light_position2[1],light_position2[2]);
		glEnd();
	}else{
		glDisable(GL_LIGHT1);
	}
}
