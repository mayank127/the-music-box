#include "camera.h"
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

camera::camera(){
	this->u = 0;
	this->du = 0.01;
	this->pathValid = false;
	this->z = 40;
	this->ex = 0;
	this->ey = 0;
	this->ez = 50;
	this->startCamera = false;
	lookAtPoint.resize(4);
	lookAtPoint[0]=0;
	lookAtPoint[1]=-20;
	lookAtPoint[2]=0;
	lookAtPoint[3]=0;
}
void camera::addPoint(float x,float y){
	vector<float> temp (3);
	temp[0] = x;
	temp[1] = y;
	temp[2] = this->z;
	(this->control_points).push_back(temp);
	this->pathValid = false;
	path.clear();
	this->startCamera = false;
	this->u = 0;
}
void camera::drawPoints(){
	if(!this->startCamera){
		glPointSize(5);
		glBegin(GL_POINTS);
			for(int i=0; i<(this->control_points).size(); i++){
				glVertex3f(control_points[i][0],control_points[i][1],control_points[i][2]);
			}
		glEnd();
	}
}
void camera::erasePoint(){
	if(!this->control_points.empty()){
		this->control_points.erase(this->control_points.end());
		this->pathValid = false;
		path.clear();
		this->u = 0;
	}
}
void camera::calcPath(){
	if(!pathValid){
		for(float u = du; u<1-du; u+=this->du){
			(this->path).push_back(this->calculatePoint(u));
		}
		pathValid = true;
	}

}
void camera::drawPath(){
	if(pathValid){
		glBegin(GL_LINE_STRIP);
		for(int i=0; i<(this->path).size(); i++){
				glVertex3f(path[i][0], path[i][1], path[i][2]);
		}
		glEnd();
	}
}
void camera::nextPoint(){
	if(pathValid && this->u<path.size()){
		this->ex = path[u][0];
		this->ey = path[u][1];
		this->ez = path[u][2];
		this->z = path[u][2];
		lookAtPoint[0] = 0;
		lookAtPoint[1] = -30;
		lookAtPoint[2] = -10;
		this->u++;
	}else{
		this->u = 0;
		this->startCamera = false;
		this->control_points.clear();
	}
}

vector<float> camera::calculatePoint(float u){
	vector<float> ret(3,0.0);
	if(u>1)
		return ret;
	int size = this->control_points.size();
	if(size<1)
		return ret;
	vector< vector<float> > control_points_copy(this->control_points);
	while(size>1){
		for(int i=0;i<size-1;i++){
			control_points_copy[i][0] = (1-u) * control_points_copy[i][0] + u * control_points_copy[i+1][0];
			control_points_copy[i][1] = (1-u) * control_points_copy[i][1] + u * control_points_copy[i+1][1];
			control_points_copy[i][2] = (1-u) * control_points_copy[i][2] + u * control_points_copy[i+1][2];
		}
		size--;
	}
	ret[0] = control_points_copy[0][0];
	ret[1] = control_points_copy[0][1];
	ret[2] = control_points_copy[0][2];
	return ret;
}
