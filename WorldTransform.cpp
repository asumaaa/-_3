#include "WorldTransform.h"

WorldTransform::WorldTransform(XMFLOAT3 translation, XMFLOAT3 scale, XMFLOAT3 rotation)
{
	translation_ = translation;
	scale_ = scale;
	rotation_ = rotation;
}
