#pragma once
#include <vector>

class InputControls
{
public:
	InputControls();
	~InputControls();
	void SetKey(char key, bool isDown);
	void SetMousePosition(int x, int y);
	void SetMouseClick(bool left, bool right);
	int GetMouseX();
	int GetMouseY();
	bool IsKeyDown(char key);
private:
	std::vector<bool> _keys;
	int _mouseX;
	int _mouseY;
	int _mouseLastX;
	int _mouseLastY;
	int _mouseLeftClick;
	int _mouseRightClick;
};

