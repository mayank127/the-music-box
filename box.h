#ifndef BOX_H
#define BOX_H

#include <list>
#include <string>
using namespace std;

//Class for box object
class box {
	public:
		float size;
		float rx,x,y,z;
		//constructor for box
		box(float,float,float,float,float);	
		box();											//null constructor

		void rectangle();
		void draw();		//draw function
};
#endif
