#include "Camera_top.h"

Camera_top::Camera_top(){
}
Camera_top::~Camera_top(){
}

void Camera_top::init(float posx,float posy,float posz){
	position = Vector3D(posx,posy,posz);
	forward = Vector3D(0,-1,0);
	up = Vector3D(0,0,-1);
	right = Vector3D(1,0,0);
}

void Camera_top::translate_Forward(float dist){

}

void Camera_top::translate_Right(float dist){
	
}







void Camera_top::render(){
	Vector3D center = position + forward;
	gluLookAt(	position.x, position.y, position.z, 
				center.x, center.y, center.z,
				up.x, up.y, up.z);
}