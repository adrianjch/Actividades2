#pragma once
bool checkPointInRect(SDL_Rect rect, IVec2 mouse) {
	return (mouse.x >= rect.x && mouse.x <= rect.x + rect.w && mouse.y >= rect.y && mouse.y <= rect.y + rect.h);
}

bool checkRectInRect(SDL_Rect rect1, SDL_Rect rect2) {
	return (checkPointInRect(rect1, { rect2.x, rect2.y }) || 
			checkPointInRect(rect1, { rect2.w, rect2.y }) || 
			checkPointInRect(rect1, { rect2.x, rect2.h }) || 
			checkPointInRect(rect1, { rect2.w, rect2.h }));
}