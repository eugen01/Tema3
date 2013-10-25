#pragma once
#include "Vector3D.h"


class Camera_top{
	public:
		Camera_top();
		~Camera_top();

		void translate_Forward(float dist);
		void translate_Right(float dist);



		void init(float posx,float posy,float posz);
		void render();

	private:
		Vector3D forward;
		Vector3D up;
		Vector3D right;
		Vector3D position;
};