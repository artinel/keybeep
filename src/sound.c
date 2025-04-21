#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define MUSIC_PATH "../beep.mp3"

short sound_init(){
	if(SDL_Init(SDL_INIT_AUDIO) < 0){
		fprintf(stderr, "Failed to initialize SDL3!!!\n");
		return 1;
	}

	const int flags = MIX_INIT_MP3;
	int result = 0;
	if(flags != (result = Mix_Init(flags))){
		fprintf(stderr, "Could not initialize mixer(%d)!!!\n", result);
		fprintf(stderr, "Mix_Init : %s\n", Mix_GetError());
		return 1;
	}

	return 0;
}

void sound_play(){
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	Mix_Music* music = Mix_LoadMUS(MUSIC_PATH);
	Mix_PlayMusic(music, 1);
//	Mix_FreeMusic(music);	
}
