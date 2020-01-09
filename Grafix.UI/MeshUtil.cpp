#include "MeshUtil.h"



MeshUtil::~MeshUtil()
{
}

Mesh MeshUtil::GetTriangle()
{
	Mesh m;

	Vertex v1;
	Vertex v2;
	Vertex v3;

	v1.Point = DirectX::XMFLOAT4(-1, -1, 0, 1); //1 in the w component for POSITIONS and a 0 for VECTORS
	v1.Color = DirectX::XMFLOAT4(1, 0, 0, 1);

	v2.Point = DirectX::XMFLOAT4(0, 1, 0, 1); //1 in the w component for POSITIONS and a 0 for VECTORS
	v2.Color = DirectX::XMFLOAT4(0, 1, 0, 1);

	v3.Point = DirectX::XMFLOAT4(1, -1, 0, 1); //1 in the w component for POSITIONS and a 0 for VECTORS
	v3.Color = DirectX::XMFLOAT4(0, 0, 1, 1);

	m.Vertx.push_back(v1);
	m.Vertx.push_back(v2);
	m.Vertx.push_back(v3);

	m.Indx.push_back(0);
	m.Indx.push_back(1);
	m.Indx.push_back(2);

	return m;
}

Mesh MeshUtil::GetSphere(int radius, int numStacks, int numSlices)
{
	Mesh m;

	// x = r sin(theta)cos(phi)
	// y = r cos(theta)
	// z = r sin(theta)sin(phi)

	// 360 degrees for the slices
	// 180 degrees for the stacks

	double sliceStep = 360.0 / numSlices;
	double stackStep = 180.0 / numStacks;

	Vertex north;
	north.Point = DirectX::XMFLOAT4(0, radius, 0, 1);
	north.Color = DirectX::XMFLOAT4(1, 1, 1, 1);

	m.Vertx.push_back(north);

	for (double theta = 0; theta < 360.0; theta += sliceStep)
	{
		for (double phi = 0; phi < 180.0; phi += stackStep)
		{
			double x = radius * sin(theta) * cos(phi);
			double y = radius * cos(theta);
			double z = radius * sin(theta) * sin(phi);

			Vertex v;
			v.Point = DirectX::XMFLOAT4(x, y, z, 1);
			v.Color = DirectX::XMFLOAT4(0, 1, 0, 1);

			m.Vertx.push_back(v);
		}
	}

	Vertex south;
	south.Point = DirectX::XMFLOAT4(0, -radius, 0, 1);
	south.Color = DirectX::XMFLOAT4(1, 1, 1, 1);
	m.Vertx.push_back(south);

	m.Indx.push_back(0);

	return m;
}
