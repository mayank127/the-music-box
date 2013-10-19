#ifndef LIGHT_H
#define LIGHT_H

using namespace std;

#include <GL/glut.h>
//Class for light object
class light {
	public:
		GLuint walls,table;
		//constructor for light
		light();
		void init();
		void draw();		//draw function
};
#endif
