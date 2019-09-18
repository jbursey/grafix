#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Init(int width, int height, float nearZ, float farZ)
{
	//_position = DirectX::XMFLOAT4(0, 0, 0, 1);
	_up = DirectX::XMFLOAT4(0, 1, 0, 0); //w = 0 = vector
	_lookAt = DirectX::XMFLOAT4(0, 0, 1, 0);	

	_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(75.0 * (DirectX::XM_PI / 180.0), width / height, nearZ, farZ);
}

void Camera::SetPosition(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

void Camera::SetOrientation(float roll, float pitch, float yaw)
{
	_roll = roll;
	_pitch = pitch;
	_yaw = yaw;
}

DirectX::XMMATRIX Camera::GetCameraMatrix()
{
	//-- mat = S*R*T
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0, 1.0, 1.0);
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(_x, _y, _z);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(_pitch, _yaw, _roll);
	
	//return S * R * T;
	return T * R * S;
}

DirectX::XMMATRIX Camera::GetProjectionMatrix()
{
	return _projectionMatrix;
}

/*

Lets think of movement on the XZ 2d plane. Lets also make use of trig to determine "forward" / "backward".

Movement is a function of time (grafix constants) and orientation round the Y (yaw) axis.

Lets assume that +z is into the screen initially
Lets assume that +x is to the right of the screen initially.
Lets assume the camera is positioned at 0,0,0 looking at +z.

So moviging forward will affect the x and z position based on the orientation.

Here are a few examples.

ex: Yaw is 0 degrees. 

z += 1.0 * cos(0) = 1.0
x += 1.0 * sin(0) = 0.0

ex: Yaw is 90 degrees

z += 1.0 * cos(90) = 0.0
x += 1.0 * sin(90) = 1.0

Remember that the camera stays stationary from a graphics perspective. The whole world moves around the camera. So if the camera wants to "look" right we actually just rotate the entire world left.
.... boom
.... mind blown... i know.



*/

void Camera::MoveForward()
{
	// lets say we want to move 5 units per 1000 ms
	// knowing that the grafix constant is 1ms per update
	/*
		5      X
	   ---- = ----
	   1000    1

	   X = 5 / 1000.0
	*/
	double moveUnits = (GrafixConstants::CameraMoveUnitsPerSecond * GrafixConstants::MillisecondsPerUpdate) / 1000.0;

	_z -= moveUnits * cos(_yaw);
	_x += moveUnits * sin(_yaw);	
}

void Camera::MoveBackward()
{
	double moveUnits = (GrafixConstants::CameraMoveUnitsPerSecond * GrafixConstants::MillisecondsPerUpdate) / 1000.0;

	_z += moveUnits * cos(_yaw);
	_x -= moveUnits * sin(_yaw);
}

void Camera::TurnRight()
{
	//--each time this is called we can assume a constant time has passed
	//--lets decide we want to turn 90 deg per 1000 ms
	//--knowing this we are guaranteed that 1ms has occured due to the update logic
	/*
		90       X
	   ---- =  ----
	   1000     1

	   X = 90 / 1000
	   X = the number of degrees we need to turn
	*/

	double degreesToTurn = (GrafixConstants::CameraTurnDegreesPerSecond * GrafixConstants::MillisecondsPerUpdate) / 1000.0;
	double radiansToTurn = degreesToTurn * (DirectX::XM_PI / 180.0);

	_yaw -= radiansToTurn;
}

void Camera::TurnLeft()
{
	double degreesToTurn = (GrafixConstants::CameraTurnDegreesPerSecond * GrafixConstants::MillisecondsPerUpdate) / 1000.0;
	double radiansToTurn = degreesToTurn * (DirectX::XM_PI / 180.0);

	_yaw += radiansToTurn;
}
