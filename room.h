#ifndef ROOM_H
#define ROOM_H

using namespace std;

#include <GL/glut.h>
//Class for box object
class room {
	private:
		void createSide(float, float);
	public:
		GLuint walls,door,table,chair,cabinet,stool,lamp;
		GLuint table_tex, wall_tex, door_tex, silver_tex, walls_tex, wall1_tex, wall2_tex;
		float rd;
		//constructor for box
		room();											//null constructor

		void init();
		void draw();		//draw function
		void drawLeftWall();
};
#endif
