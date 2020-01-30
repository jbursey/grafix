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
		if (i == 2)
		{
			int zsadjfklasfj = 0;
		}

		for (int j = 0; j < numSlices - 0; j++)
		{
			int a = 1 + j + (i * (numSlices + 1));
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
			
			//if (j == 5)
			//{
			//	break;
			//}
		}

		//if (i == 3)
		//{
		//	break;
		//}

	}

	//--bottom pie
	for (int i = southPole - (numSlices + 1); i < m.Vertx.size(); i++)
	{
		m.Indx.push_back(southPole);
		m.Indx.push_back(i);
		m.Indx.push_back(i + 1);
	}
	

	return m;
}

Mesh MeshUtil::GetGrid(int width, int depth)
{
	Mesh m;

	//--vertx
	for (int x = 0; x < width; x++)
	{
		for (int z = 0; z < depth; z++)
		{
			Vertex v;
			v.Point = DirectX::XMFLOAT4(x, 0, z, 1);
			v.Color = DirectX::XMFLOAT4(1, 1, 1, 1);
			m.Vertx.push_back(v);
		}
	}

	//--indx
	/*
	
	B     C

	A     D
	
	*/
	for (int x = 0; x < width - 1 ; x++)
	{
		for (int z = 0; z < depth - 1; z++)
		{
			unsigned int a = z + (x * width);
			unsigned int b = a + width;
			unsigned int c = b + 1;
			unsigned int d = a + 1;

			m.Indx.push_back(a);
			m.Indx.push_back(b);
			m.Indx.push_back(c);

			m.Indx.push_back(a);
			m.Indx.push_back(c);
			m.Indx.push_back(d);
		}
	}

	return m;
}

Mesh MeshUtil::GetGrid(std::string bitmapFile, double scaling)
{
	Mesh m;
	
	FileReader fr;
	std::vector<unsigned char> fileBytes = fr.ReadAllBytes(bitmapFile);

	BitmapFile bitmap;
	bitmap.Parse(fileBytes);

	//--vertx	
	for (int x = 0; x < bitmap.Width; x++)
	{
		for (int z = 0; z < bitmap.Height; z++)
		{
			int i = z + (x * bitmap.Width);

			Color c = bitmap.Colors[i];

			double height = ((c.r + c.b + c.g) * scaling) / 3.0;

			Vertex v;
			v.Point = DirectX::XMFLOAT4(x, height, z, 1);
			v.Color = DirectX::XMFLOAT4(1, 1, 1, 1);

			m.Vertx.push_back(v);
		}
	}

	//--indx
	/*
	
	B      C


	A      D
	
	*/
	for (int x = 0; x < bitmap.Width - 1; x++)
	{
		for (int z = 0; z < bitmap.Height - 1; z++)
		{
			int a = 0;
			int b = 0;
			int c = 0;
			int d = 0;

			a = z + (x * bitmap.Width);
			b = a + bitmap.Width;
			c = b + 1;
			d = a + 1;

			m.Indx.push_back(a);
			m.Indx.push_back(b);
			m.Indx.push_back(c);

			m.Indx.push_back(a);
			m.Indx.push_back(c);
			m.Indx.push_back(d);
		}
	}

	return m;
}
