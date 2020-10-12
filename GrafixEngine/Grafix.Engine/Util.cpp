#include "Util.h"

DirectX::XMFLOAT4 Util::CreateRandomColor()
{
	double r = (rand() % 255) / 255.0;
	double g = (rand() % 255) / 255.0;
	double b = (rand() % 255) / 255.0;
	double a = (rand() % 255) / 255.0;

	return DirectX::XMFLOAT4(r, g, b, 1);
}

void Util::Test_DeleteMe_PerlinNoiseVisual()
{

}
