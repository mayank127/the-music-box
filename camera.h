#ifndef CAMERA_H
#define CAMERA_H

using namespace std;

#include <vector>
#include <GL/glut.h>
//Class for camera object
class camera {
	vector< vector<float> > control_points, path;
	int u;
	float du;
	vector<float> calculatePoint(float);
	bool pathValid;

	public:
		float ex,ey,ez,z;
		bool startCamera;
		vector<float> lookAtPoint;
		camera();
		void addPoint(float,float);
		void erasePoint();
		void drawPath();
		void drawPoints();
		void nextPoint();
		void calcPath();
};
#endif