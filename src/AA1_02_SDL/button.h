#pragma once
struct Button {
	SDL_Texture *texture;
	SDL_Rect rect;
	bool hover = false;
	bool clicked = false;
};