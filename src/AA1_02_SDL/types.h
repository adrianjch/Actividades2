#pragma once
struct IVec2{
	int x;
	int y;
};

struct Button {
	SDL_Texture *texture;
	SDL_Rect rect;
	bool hover = false;
	bool clicked = false;
};