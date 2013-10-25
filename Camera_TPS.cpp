#include "Camera_TPS.h"

Camera_TPS::Camera_TPS(){
}
Camera_TPS::~Camera_TPS(){
}

void Camera_TPS::init(float posx,float posy,float posz){
	position = Vector3D(posx,posy,posz);
	forward = Vector3D(0,0,-1);
	up = Vector3D(0,1,0);
	right = Vector3D(1,0,0);
}

void Camera_TPS::translate_Forward(float dist,Vector3D hero_f){
	position = position + hero_f.operator *(dist);
}
void Camera_TPS::translate_Up(float dist){
	
}
void Camera_TPS::translate_Right(float dist,Vector3D hero_r){
	position = position + hero_r.operator *(dist);	
}



void Camera_TPS::rotateTPS_OY(float angle, float dist_to_interes){
	Vector3D old_forward = Vector3D(forward.x,forward.y,forward.z);
	forward =  forward.operator *(cos(angle)) + right.operator *(sin(angle));
	right = forward.CrossProduct(up);
	position = position+ old_forward.operator *(dist_to_interes) -
		forward.operator *(dist_to_interes);		   
	  up.Normalize();
}
void Camera_TPS::rotateTPS_OX(float angle, float dist_to_interes){

	Vector3D f = forward;
        up = up * cos(angle) + forward * sin(angle);
        forward = up.CrossProduct(right);
        forward.Normalize();
        position = position + f * dist_to_interes - forward * dist_to_interes; 
		  up.Normalize();

}
void Camera_TPS::rotateTPS_OZ(float angle, float dist_to_interes){
 Vector3D u = up;
        right = up * sin(angle) + right * cos(angle);
        up = right.CrossProduct(forward);
        up.Normalize();
	//	 position = position + u * dist_to_interes - up * dist_to_interes; 
}


void Camera_TPS::render(){
	Vector3D center = position + forward;
	gluLookAt(	position.x, position.y, position.z, 
				center.x, center.y-0.2, center.z,
				up.x, up.y, up.z);
}