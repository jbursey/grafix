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
	m.Indx.push_back(2);
	m.Indx.push_back(1);

	CalculateNormals(m);

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

	int texU = 0;
	int texV = 0;

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
			//v.Color = color;
			v.Color = DirectX::XMFLOAT4(1, 1, 1, 1);
			v.Normal = DirectX::XMFLOAT4(x, y, z, 0);
			v.TexUV = DirectX::XMFLOAT2(texU++, texV++);

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
	for (int i = southPole - (numSlices + 1); i < m.Vertx.size() - 1; i++)
	{
		m.Indx.push_back(southPole);
		m.Indx.push_back(i);
		m.Indx.push_back(i + 1);
	}

	NormalizeNormals(m);

	return m;
}

Mesh MeshUtil::GetGrid(int width, int depth)
{
	Mesh m;

	//--vertx
	Perlin p;
	p.Init(3, 3);
	//

	for (int x = 0; x < width; x++)
	{
		for (int z = 0; z < depth; z++)
		{
			Vertex v;
			double y = sin(z);
			y = p.Noise(x / (width * 1.0), z / (depth * 1.0));
			y *= 350.0;
			v.Point = DirectX::XMFLOAT4(x, y, z, 1);
			v.Color = DirectX::XMFLOAT4(1, 1, 1, 1);
			m.Vertx.push_back(v);
		}
	}

	//--indx
	/*

	B     C

	A     D

	*/
	for (int x = 0; x < width - 1; x++)
	{
		for (int z = 0; z < depth - 1; z++)
		{
			unsigned int a = z + (x * width);
			unsigned int b = a + width;
			unsigned int c = b + 1;
			unsigned int d = a + 1;

			m.Indx.push_back(a);
			m.Indx.push_back(c);
			m.Indx.push_back(b);

			m.Indx.push_back(a);
			m.Indx.push_back(d);
			m.Indx.push_back(c);
		}
	}

	CalculateNormals(m);

	return m;
}

Mesh MeshUtil::GetGridTex(int width, int depth)
{
	Mesh m;

	/*

	for each (x,z) pair we need to create a quad made up of two triangles that don't share vertices

	we will duplicate every vertex so that each triangle is using unique vertices. This is needed for texturing

	  C     D


	  A     B
	*/
	Perlin perlin;
	perlin.Init(5, 5);
	double heightScale = 100.0;
	unsigned int index = 0;
	for (int z = 0; z <= depth; z++)
	{
		for (int x = 0; x <= width; x++)
		{
			Vertex a;
			a.Point = DirectX::XMFLOAT4(x, 0, z, 1);
			a.Color = DirectX::XMFLOAT4(1, 1, 1, 1);
			a.Normal = DirectX::XMFLOAT4(0, 0, 0, 0);
			a.TexUV = DirectX::XMFLOAT2(0, 1);

			Vertex b;
			b.Point = DirectX::XMFLOAT4(x + 1, 0, z, 1);
			b.Color = DirectX::XMFLOAT4(1, 1, 1, 1);
			b.Normal = DirectX::XMFLOAT4(0, 0, 0, 0);
			b.TexUV = DirectX::XMFLOAT2(1, 1);

			Vertex c;
			c.Point = DirectX::XMFLOAT4(x, 0, z + 1, 1);
			c.Color = DirectX::XMFLOAT4(1, 1, 1, 1);
			c.Normal = DirectX::XMFLOAT4(0, 0, 0, 0);
			c.TexUV = DirectX::XMFLOAT2(0, 0);

			Vertex d;
			d.Point = DirectX::XMFLOAT4(x + 1, 0, z + 1, 1);
			d.Color = DirectX::XMFLOAT4(1, 1, 1, 1);
			d.Normal = DirectX::XMFLOAT4(0, 0, 0, 0);
			d.TexUV = DirectX::XMFLOAT2(1, 0);

			a.Point.y = perlin.Noise(a.Point.x / (width * 1.0), a.Point.z / (depth * 1.0)) * heightScale;
			b.Point.y = perlin.Noise(b.Point.x / (width * 1.0), b.Point.z / (depth * 1.0)) * heightScale;
			c.Point.y = perlin.Noise(c.Point.x / (width * 1.0), c.Point.z / (depth * 1.0)) * heightScale;
			d.Point.y = perlin.Noise(d.Point.x / (width * 1.0), d.Point.z / (depth * 1.0)) * heightScale;

			m.Vertx.push_back(a); // index
			m.Vertx.push_back(b); // index + 1
			m.Vertx.push_back(c); // index + 2
			m.Vertx.push_back(d); // index + 3

			unsigned int ia = index;
			unsigned int ib = index + 1;
			unsigned int ic = index + 2;
			unsigned int id = index + 3;

			m.Indx.push_back(ia);
			m.Indx.push_back(ic);
			m.Indx.push_back(id);

			m.Indx.push_back(ia);
			m.Indx.push_back(id);
			m.Indx.push_back(ib);

			index += 4;
		}
	}

	CalculateNormals(m);

	return m;
}

Mesh MeshUtil::GetGrid(std::vector<unsigned char> fileBytes, double scaling)
{
	Mesh m;

	BitmapFile bitmap;
	bitmap.Parse(fileBytes);

	auto color = Util::CreateRandomColor();

	//--vertx	
	m.Vertx.resize(bitmap.Width * bitmap.Height);
	int vertexIndex = 0;
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
			//v.Color = color;

			m.Vertx[vertexIndex++] = v;
			//m.Vertx.push_back(v);
		}
	}

	//--indx
	/*

	B      C


	A      D

	*/
	m.Indx.resize(((bitmap.Width - 1) * (bitmap.Height - 1)) * 6);
	int indexIndex = 0;
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

			m.Indx[indexIndex++] = a;
			m.Indx[indexIndex++] = c;
			m.Indx[indexIndex++] = b;

			m.Indx[indexIndex++] = a;
			m.Indx[indexIndex++] = d;
			m.Indx[indexIndex++] = c;
		}
	}

	CalculateNormals(m);
	return m;
}

void MeshUtil::CalculateNormals(Mesh& m)
{
	//--lets assume triangle strips for now
	for (int i = 0; i < m.Indx.size() - 3; i += 3)
	{
		unsigned int indx1 = m.Indx[i + 0];
		unsigned int indx2 = m.Indx[i + 1];
		unsigned int indx3 = m.Indx[i + 2];

		Vertex& v1 = m.Vertx[indx1];
		Vertex& v2 = m.Vertx[indx2];
		Vertex& v3 = m.Vertx[indx3];

		//v1 in the direction of v2
		//v1 in the direction of v3
		DirectX::XMFLOAT3 v1v2 = DirectX::XMFLOAT3(v2.Point.x - v1.Point.x, v2.Point.y - v1.Point.y, v2.Point.z - v1.Point.z);
		DirectX::XMFLOAT3 v1v3 = DirectX::XMFLOAT3(v3.Point.x - v1.Point.x, v3.Point.y - v1.Point.y, v3.Point.z - v1.Point.z);
		DirectX::XMVECTOR xmv1v2 = DirectX::XMLoadFloat3(&v1v2);
		DirectX::XMVECTOR xmv1v3 = DirectX::XMLoadFloat3(&v1v3);
		DirectX::XMVECTOR xmnorm = DirectX::XMVector3Cross(xmv1v2, xmv1v3);

		//store the cross product for the normal
		DirectX::XMFLOAT3 normal;
		DirectX::XMStoreFloat3(&normal, xmnorm);

		double magnitudeNormal = sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2));
		auto test = DirectX::XMVector3Length(xmnorm);

		DirectX::XMFLOAT4 unitnormal = DirectX::XMFLOAT4(normal.x / magnitudeNormal, normal.y / magnitudeNormal, normal.z / magnitudeNormal, 0); //0 = vector

		v1.Normal = unitnormal;
		v2.Normal = unitnormal;
		v3.Normal = unitnormal;
	}
}

void MeshUtil::NormalizeNormals(Mesh& m)
{
	for (int i = 0; i < m.Vertx.size(); i++)
	{
		Vertex& v = m.Vertx[i];

		double mag = sqrt((v.Normal.x * v.Normal.x) + (v.Normal.y * v.Normal.y) + (v.Normal.z * v.Normal.z));
		if (mag != 0)
		{
			v.Normal.x /= mag;
			v.Normal.y /= mag;
			v.Normal.z /= mag;
		}
	}
}
