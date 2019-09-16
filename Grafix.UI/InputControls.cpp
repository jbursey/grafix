#include "InputControls.h"



InputControls::InputControls()
{
	_mouseLastX = 0;
	_mouseLastY = 0;
	_mouseX = 0;
	_mouseY = 0;

	_keys.resize(500, false);
	for (int i = 0; i < 500; i++)
	{
		_keys[i] = false;
	}
}


InputControls::~InputControls()
{
}

void InputControls::SetKey(char key, bool isDown)
{
	_keys[(int)key] = isDown;
}

void InputControls::SetMousePosition(int x, int y)
{
	_mouseLastX = _mouseX;
	_mouseLastY = _mouseY;

	_mouseX = x;
	_mouseY = y;
}

void InputControls::SetMouseClick(bool left, bool right)
{
	_mouseLeftClick = left;
	_mouseRightClick = right;
}

bool InputControls::IsKeyDown(char key)
{
	return _keys[(int)key];
}
