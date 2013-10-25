//clasa camera
#pragma once
#include "Vector3D.h"


class Camera_TPS{
	public:
		Camera_TPS();
		~Camera_TPS();

		void translate_Forward(float dist , Vector3D hero_f);
		void translate_Up(float dist);
		void translate_Right(float dist,Vector3D hero_r);

		void rotateTPS_OY(float angle, float dist_to_interes);
		void rotateTPS_OX(float angle, float dist_to_interes);
		void rotateTPS_OZ(float angle, float dist_to_interes);

		void init(float posx,float posy,float posz);
		void render();

	private:
		Vector3D forward;
		Vector3D up;
		Vector3D right;
		Vector3D position;
};