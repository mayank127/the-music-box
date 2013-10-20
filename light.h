#ifndef LIGHT_H
#define LIGHT_H

using namespace std;

#include <GL/glut.h>
//Class for light object
class light {
	GLfloat amb1[4], dif1[4], light_position1[4];
	GLfloat amb2[4], dif2[4], light_position2[4];
	public:
		GLuint walls,table;
		bool l1,l2;
		//constructor for light
		light();
		void init();
		void draw();		//draw function
};
#endif
