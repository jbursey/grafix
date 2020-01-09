#pragma once
#include "Structs.h"
#include "Util.h"
#include <vector>
#include <DirectXMath.h>

class MeshUtil
{
public:	
	~MeshUtil();
	static Mesh GetTriangle();
	static Mesh GetSphere(int radius, int numStacks, int numSlices);
};

