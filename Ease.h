#pragma once
#include "math.h"

class Ease {	//�C�[�W���O�N���X��`
public:
	static double InQuad(double change, double base, double duration, double time);
	static double OutQuad(double change, double base, double duration, double time);
	static double InOutQuad(double change, double base, double duration, double time);
};

