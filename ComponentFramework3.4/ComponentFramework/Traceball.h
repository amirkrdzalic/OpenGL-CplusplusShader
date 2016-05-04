#pragma once
#ifndef TRACEBALL_H 
#define TRACEBALL_H 
#include "MMath.h"

namespace GAME {
	using namespace MATH; 

	class Traceball
	{
	private: Matrix4 mouserotationmatrix; 
			 Vec3 begin, end; 

	public:
		void onLeftDown(int x, int y); 
		void onMousetMove(int x, int y); 
		Matrix4 Getmatrix4() const { return mouserotationmatrix;  }
	//Matrix3 Getmatrix3() const { return  Matrix3(mouserotationmatrix); }
	};

}

#endif // !TRACEBALL_H 



