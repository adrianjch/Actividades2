#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <exception>
#include <iostream>
#include <string>

#include "types.h"
#include "constants.h"
#include "button.h"


bool checkIfMouseIn(SDL_Rect rect, IVec2 mouse) {
	return (mouse.x >= rect.x && mouse.x <= rect.x + rect.w && mouse.y >= rect.y && mouse.y <= rect.y + rect.h);
}


int main(int, char*[]) 
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
		throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr) 
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr) 
		throw "No es pot inicialitzar SDL_Renderer";

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) 
		throw "Error: SDL_image init";

	//-->SDL_TTF
	if (TTF_Init() == -1)
		throw "No es pot inicialitzar SDL_ttf";

	//-->SDL_Mix
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!Mix_Init(mixFlags))
		throw "No es pot inicialitzar SDL_mixer";
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == 0)///change to -1
		throw "Unable to initialize SDL_mixer audio systems";

	// --- SPRITES ---
	//Background
	SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
	if (bgTexture == nullptr) 
		throw "Error: bgTexture init";
	SDL_Rect bgRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//Player
	SDL_Texture* playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
	if (playerTexture == nullptr)
		throw "Error: kintounTexture init";
	SDL_Rect playerRect{ 0, 0, 117, 63 };

	//-->Animated Sprite ---

	// --- TEXT ---
	//Title
	TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf", 80) };
	if (font == nullptr)
		throw "No es pot inicialitzar TTF_Font";
	SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font, "My first SDL game", SDL_Color{ 255, 150, 0, 255}) };
	if (tmpSurf == nullptr)
		throw "Unable to create the SDL text surface";
	SDL_Texture *titleTexture{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	if (titleTexture == nullptr)
		throw "Error: titleTexture init";
	SDL_Rect titleRect{ 100, 50, tmpSurf->w, tmpSurf->h};

	//Play button
	font = TTF_OpenFont("../../res/ttf/saiyan.ttf", 50);
	tmpSurf = TTF_RenderText_Blended(font, "Play", SDL_Color{ 0, 0, 50, 255 });
	SDL_Texture *playNormalTexture = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	if (playNormalTexture == nullptr)
		throw "Error: playNormalTexture init";
	tmpSurf = TTF_RenderText_Blended(font, "Play", SDL_Color{ 0, 0, 255, 255 });
	SDL_Texture *playHoverTexture = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	if (playHoverTexture == nullptr)
		throw "Error: playHoverTexture init";
	tmpSurf = TTF_RenderText_Blended(font, "Play", SDL_Color{ 0, 255, 0, 255 });
	SDL_Texture *playClickTexture = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	if (playClickTexture == nullptr)
		throw "Error: playClickTexture init";
	Button play;
	play.texture = playNormalTexture;
	play.rect = { 350, 220, tmpSurf->w, tmpSurf->h };

	//Sound button
	tmpSurf = TTF_RenderText_Blended(font, "Sound off/on", SDL_Color{ 0, 0, 50, 255 });
	SDL_Texture *soundNormalTexture = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	if (soundNormalTexture == nullptr)
		throw "Error: soundNormalTexture init";
	tmpSurf = TTF_RenderText_Blended(font, "Sound off/on", SDL_Color{ 0, 0, 255, 255 });
	SDL_Texture *soundHoverTexture = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	if (soundHoverTexture == nullptr)
		throw "Error: soundHoverTexture init";
	Button sound;
	sound.texture = soundNormalTexture;
	sound.rect = { 280, 300, tmpSurf->w, tmpSurf->h };

	//Exit button
	tmpSurf = TTF_RenderText_Blended(font, "Exit", SDL_Color{ 0, 0, 50, 255 });
	SDL_Texture *exitNormalTexture = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	if (exitNormalTexture == nullptr)
		throw "Error: exitNormalTexture init";
	tmpSurf = TTF_RenderText_Blended(font, "Exit", SDL_Color{ 0, 0, 255, 255 });
	SDL_Texture *exitHoverTexture = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);
	if (exitHoverTexture == nullptr)
		throw "Error: exitHoverTexture init";
	Button exit;
	exit.texture = exitNormalTexture;
	exit.rect = { 350, 380, tmpSurf->w, tmpSurf->h };
	
	SDL_FreeSurface(tmpSurf);
	TTF_CloseFont(font);

	// --- AUDIO ---
	Mix_Music *soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundtrack)
		throw "Unable to load the Mix_Music soundtrack";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundtrack, -1);

	//General variables
	IVec2 mousePos{ 0, 0 };
	bool playActivated = false;
	bool input[static_cast<int>(InputKey::COUNT)] = {};

	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:		
				isRunning = false; 
				break;
			case SDL_KEYDOWN:	///http://wiki.libsdl.org/SDL_Keycode
				if (event.key.keysym.sym == SDLK_ESCAPE)
					input[static_cast<int>(InputKey::K_ESC)] = true;
				break;
			case SDL_MOUSEMOTION:
				mousePos.x = event.motion.x;
				mousePos.y = event.motion.y;
				input[static_cast<int>(InputKey::M_MOVED)] = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
					input[static_cast<int>(InputKey::M_LEFT)] = true;
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
					input[static_cast<int>(InputKey::M_LEFT)] = false;
				break;
			default:;
			}
		}

		// UPDATE
		if (input[static_cast<int>(InputKey::K_ESC)])
			isRunning = false;
		if (input[static_cast<int>(InputKey::M_MOVED)]) {
			play.hover = checkIfMouseIn(play.rect, mousePos);
			sound.hover = checkIfMouseIn(sound.rect, mousePos);
			exit.hover = checkIfMouseIn(exit.rect, mousePos);
		}
		if (input[static_cast<int>(InputKey::M_LEFT)]) {
			play.clicked = play.hover;
			sound.clicked = sound.hover;
			exit.clicked = exit.hover;
		}
		else {
			play.clicked = false;
			sound.clicked = false;
			exit.clicked = false;
		}
		playerRect.x += (mousePos.x - playerRect.x  - playerRect.w / 2) / 10;
		playerRect.y += (mousePos.y - playerRect.y - playerRect.h / 2) / 10;
		//play button
		if (play.clicked) {
			playActivated = true;
		}
		else
			playActivated = false;
		if (playActivated)
			play.texture = playClickTexture;
		else {
			if (play.hover)
				play.texture = playHoverTexture;
			else
				play.texture = playNormalTexture;
		}
		//sound button
		if (sound.hover)
			sound.texture = soundHoverTexture;
		else
			sound.texture = soundNormalTexture;
		if (sound.clicked) {
			if (Mix_PausedMusic())
				Mix_ResumeMusic();
			else
				Mix_PauseMusic();
			sound.clicked = false;
		}
		//exit button
		if (exit.hover)
			exit.texture = exitHoverTexture;
		else
			exit.texture = exitNormalTexture;
		if (exit.clicked) {
			isRunning = false;
			exit.clicked = false;
		}

		// DRAW
		SDL_RenderClear(m_renderer);

		//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
		SDL_RenderCopy(m_renderer, playerTexture, nullptr, &playerRect);
		SDL_RenderCopy(m_renderer, titleTexture, nullptr, &titleRect);
		SDL_RenderCopy(m_renderer, play.texture, nullptr, &play.rect);
		SDL_RenderCopy(m_renderer, sound.texture, nullptr, &sound.rect);
		SDL_RenderCopy(m_renderer, exit.texture, nullptr, &exit.rect);
		SDL_RenderPresent(m_renderer);
	}

	// --- DESTROY ---
	//audio
	Mix_CloseAudio();
	Mix_Quit();
	//ttf
	SDL_DestroyTexture(playNormalTexture);
	SDL_DestroyTexture(playHoverTexture);
	SDL_DestroyTexture(playClickTexture);
	SDL_DestroyTexture(soundNormalTexture);
	SDL_DestroyTexture(soundHoverTexture);
	SDL_DestroyTexture(exitNormalTexture);
	SDL_DestroyTexture(exitHoverTexture);
	SDL_DestroyTexture(titleTexture);
	TTF_Quit();
	//sprites
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(bgTexture);
	IMG_Quit();
	//other
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();

	return 0;
}