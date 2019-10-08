#pragma once
struct IVec2{
	int x;
	int y;
};
struct Rect {
	int x;
	int y;
	int w;
	int h;
};

enum InputKey{ K_ESC, M_LEFT, M_MOVED, COUNT};