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

	double sliceStep = 360.0 / (numSlices * 1.0);
	double stackStep = 180.0 / (numStacks * 1.0);

	Vertex north;
	north.Point = DirectX::XMFLOAT4(0, radius, 0, 1);
	north.Color = DirectX::XMFLOAT4(1, 1, 1, 1);

	m.Vertx.push_back(north);

	double theta = 0;
	for (int stack = 1; stack < numStacks; stack++)
	{
		auto color = Util::CreateRandomColor();

		theta = stack * stackStep;
		theta = theta * (DirectX::XM_PI / 180.0);

		double phi = 0;
		for(int slice = 0; slice < numSlices; slice++)
		{
			phi = slice * sliceStep;
			phi = phi * (DirectX::XM_PI / 180.0);

			double x = radius * sin(theta) * cos(phi);
			double y = radius * cos(theta);
			double z = radius * sin(theta) * sin(phi);

			Vertex v;
			v.Point = DirectX::XMFLOAT4(x, y, z, 1);
			v.Color = color;

			m.Vertx.push_back(v);
		}	
	}


	Vertex south;
	south.Point = DirectX::XMFLOAT4(0, -radius, 0, 1);
	south.Color = DirectX::XMFLOAT4(1, 1, 1, 1);
	m.Vertx.push_back(south);


	//--indexs
	int top = 0;
	int bottom = m.Vertx.size();

	//--top pie
	for (int i = 1; i <= numSlices; i++)
	{
		m.Indx.push_back(top);
		m.Indx.push_back(i + 1);
		m.Indx.push_back(i + 0);
	}

	//--middle
	/*
	   A      B
	

	   C      D
	*/
	for (int stack = 0; stack < numStacks - 2; stack++)
	{
		int a = 0;
		int b = 0;
		int c = 0;
		int d = 0;

		for (int slice = 0; slice < numSlices; slice++)
		{
			//a = 1 + (slice * stack);
			a = (1 + slice) + (numSlices * stack);
			b = a + 1;
			c = (1 + slice) + (numSlices * (stack + 1));
			d = c + 1;

			m.Indx.push_back(a);
			m.Indx.push_back(b);
			m.Indx.push_back(c);

			m.Indx.push_back(b);
			m.Indx.push_back(d);
			m.Indx.push_back(c);		

			int zzzz = 0;
		}		
		
		//if (stack == 2)
		//{
		//	break;
		//}
	}
//
//	//--bottom pie	
//	for (int i = bottom - numSlices; i < numSlices; i++)
//	{
//		m.Indx.push_back(i);
//		m.Indx.push_back(i+1);
//		m.Indx.push_back(bottom);
//	}

	return m;
}
