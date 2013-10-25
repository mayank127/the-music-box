#ifndef ROOM_H
#define ROOM_H

using namespace std;

#include <GL/glut.h>
//Class for box object
class room {
	private:
		void createSide(float, float);
	public:
		GLuint walls,door,table,chair,cabinet,stool;
		GLuint table_tex, wall_tex, door_tex;
		float rd;
		//constructor for box
		room();											//null constructor

		void init();
		void draw();		//draw function
		void drawLeftWall();
};
#endif
