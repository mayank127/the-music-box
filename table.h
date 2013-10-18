#ifndef TABLE_H
#define TABLE_H

using namespace std;

#include <GL/glut.h>
//Class for table object
class table {
	private:
		void createSide(float, float);
	public:
		GLuint legs, top;
		int size1, size2, size3;
		//constructor for table
		table();											//null constructor

		void init();
		void draw();		//draw function
};
#endif
