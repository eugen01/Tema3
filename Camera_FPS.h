#pragma once
#include "Vector3D.h"


class Camera_FPS{
	public:
		Camera_FPS();
		~Camera_FPS();

		void translate_Forward(float dist);
		void translate_Right(float dist);


		void rotateFPS_OY(float angle);
		


		void init(float posx,float posy,float posz);
		void render();

	private:
		Vector3D forward;
		Vector3D up;
		Vector3D right;
		Vector3D position;
};