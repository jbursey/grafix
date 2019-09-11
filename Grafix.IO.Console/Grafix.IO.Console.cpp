// Grafix.IO.Console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#pragma comment(lib, "Grafix.IO.lib")
#include <vector>
#include <ByteReader.h>
#include <FileReader.h>
#include <BitmapFile.h>
int main()
{

    std::cout << "Hello World!\n";

	//---byte reader---------------------------------------
	int val = 2123456789;
	unsigned char v1 = (unsigned char)(val >> 24);
	unsigned char v2 = (unsigned char)(val >> 16);
	unsigned char v3 = (unsigned char)(val >> 8);
	unsigned char v4 = (unsigned char)(val >> 0);

	std::vector<unsigned char> data;
	data.push_back(v1);
	data.push_back(v2);
	data.push_back(v3);
	data.push_back(v4);

	ByteReader* br = new ByteReader(data);	
	unsigned char readByteV1 = br->ReadByte();
	br->Reset();
	int readVal = br->ReadInt(false);

	delete br;
	br = nullptr;
	//------------------------------------------------------

	//---file reader----------------------------------------
	std::vector<unsigned char> bmpData = FileReader::ReadAllBytes("..\\test_bitmap.bmp");
	BitmapFile bmp;
	bmp.Parse(bmpData);
	//------------------------------------------------------

	int x = 0; 
	std::cin >> x;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
