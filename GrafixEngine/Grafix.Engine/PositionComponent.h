#pragma once

#include <DirectXMath.h>
#include "GraifxConstants.h"

struct PositionComponent
{
public:
	double X;
	double Y;
	double Z;
	
	double Pitch; //X
	double Yaw; //Y
	double Roll; //Z

	double ScaleX;
	double ScaleY;
	double ScaleZ;

	DirectX::XMFLOAT4X4 GetMatrix()
	{
		DirectX::XMFLOAT4X4 mat{};
		

		DirectX::XMMATRIX transMat = DirectX::XMMatrixTranslation(X, Y, Z);
		DirectX::XMMATRIX scaleMat = DirectX::XMMatrixScaling(ScaleX, ScaleY, ScaleZ);
		DirectX::XMMATRIX rotatMat = DirectX::XMMatrixRotationRollPitchYaw(Pitch, Yaw, Roll);

		DirectX::XMMATRIX finalMat = scaleMat * rotatMat * transMat;

		DirectX::XMStoreFloat4x4(&mat, finalMat);

		return mat;
	}

private:
};
