#pragma once
#include <vector>
#include <DirectXMath.h>
#include "Mesh.h"
#include "FileReader.h"
#include "ByteReader.h"
#include "Perlin.h"
#include "Util.h"
#include "BitmapFile.h"

//#include "Structs.h"
//#include <BitmapFile.h>
//#include <FileReader.h>

class MeshUtil
{
public:
	~MeshUtil();
	static Mesh GetTriangle();
	static Mesh GetSphere(int radius, int numStacks, int numSlices);
	static Mesh GetGrid(int width, int depth);
	static Mesh GetGridTex(int width, int depth);
	static Mesh GetGrid(std::vector<unsigned char> fileBytes, double scaling); //fix me 

	static void CalculateNormals(Mesh& m);

private:
	static void NormalizeNormals(Mesh& m);

};