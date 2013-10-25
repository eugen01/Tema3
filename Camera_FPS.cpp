#include "Camera_FPS.h"

Camera_FPS::Camera_FPS(){
}
Camera_FPS::~Camera_FPS(){
}

void Camera_FPS::init(float posx,float posy,float posz){
	position = Vector3D(posx,posy,posz);
	forward = Vector3D(0,0,-1);
	up = Vector3D(0,1,0);
	right = Vector3D(1,0,0);
}

void Camera_FPS::translate_Forward(float dist){
	position = position + forward.operator *(dist);
	
}	

void Camera_FPS::translate_Right(float dist){
position = position + right.operator *(dist);

}






void Camera_FPS::rotateFPS_OY(float angle){
forward = forward.operator *(cos(angle)) + right.operator *(sin(angle));
right = forward.CrossProduct(up);

}




void Camera_FPS::render(){
	Vector3D center = position + forward;
	gluLookAt(	position.x, position.y, position.z, 
				center.x, center.y, center.z,
				up.x, up.y, up.z);
}