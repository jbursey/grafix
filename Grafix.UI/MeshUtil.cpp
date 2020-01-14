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

	// x = r sin(theta) cos(phi)
	// y = r cos(theta)
	// z = r sin(theta) sin(phi)

	// 360 degrees for the slices
	// 180 degrees for the stacks

	double r = radius * 1.0;

	double sliceStep = 360.0 / (numSlices * 1.0);
	double stackStep = 180.0 / (numStacks * 1.0);

	double phi = 0;
	double theta = 0;

	Vertex north;
	Vertex south;

	north.Point = DirectX::XMFLOAT4(0, radius, 0, 1);
	north.Color = DirectX::XMFLOAT4(1, 1, 1, 1);

	m.Vertx.push_back(north);

	for (int i = 1; i < numStacks; i++)
	{
		auto color = Util::CreateRandomColor();

		for (int j = 0; j <= numSlices; j++)
		{
			theta = i * stackStep;
			phi = j * sliceStep;

			if (phi >= 360.0) phi -= 360.0;
			if (theta >= 180.0) theta -= 180.0;

			double thetaRadians = theta * (DirectX::XM_PI / 180.0);
			double phiRadians = phi * (DirectX::XM_PI / 180.0);

			double x = r * sin(thetaRadians) * cos(phiRadians);
			double y = r * cos(thetaRadians);
			double z = r * sin(thetaRadians) * sin(phiRadians);

			Vertex v;
			v.Point = DirectX::XMFLOAT4(x, y, z, 1);
			v.Color = color;
				
			m.Vertx.push_back(v);
		}
	}

	south.Point = DirectX::XMFLOAT4(0, -radius, 0, 1);
	south.Color = DirectX::XMFLOAT4(1, 1, 1, 1);

	m.Vertx.push_back(south);

	//--indexes
	int northPole = 0;
	int southPole = m.Vertx.size() - 1;

	//--top pie
	for (int i = 1; i <= numSlices; i++)
	{
		m.Indx.push_back(northPole);
		m.Indx.push_back(i + 1);
		m.Indx.push_back(i + 0);
	}

	//--middle
	/*
		A      B


		C      D
	*/
	for (int i = 0; i < numStacks - 2; i++)
	{
		for (int j = 0; j <= numSlices; j++)
		{
			int a = 1 + j + (i * numSlices);
			int b = a + 1;
			int c = a + numSlices + 1;
			int d = c + 1;

			m.Indx.push_back(a);
			m.Indx.push_back(b);
			m.Indx.push_back(c);

			m.Indx.push_back(b);
			m.Indx.push_back(d);
			m.Indx.push_back(c);

			int z = 0;
			//break;
		}
		
		//if (i == 1)
		//{
		//	break;
		//}
	}

	//--bottom pie
	

	return m;
}
