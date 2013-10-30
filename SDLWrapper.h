#pragma once
#include <functional>
#include <assert.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Singleton.hpp"
#include "tString.hpp"
#include <map>

#pragma comment(lib, "SDL2_mixer.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

namespace TUL{
	class SDLCore : public Singleton<SDLCore>{
		friend class Singleton<SDLCore>;
	public:
		SDLCore(){
			assert(SDL_Init(SDL_INIT_AUDIO) >= 0, SDL_GetError());
		}
		~SDLCore(){
			SDL_Quit();
		}
	private:
	};


	class SDLSound : public Singleton<SDLSound>{
		friend class Singleton<SDLSound>;
	public:
		SDLSound(){
			_parent = GetSingleton<SDLCore>();
			assert(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024)>=0, SDL_GetError());
			Mix_AllocateChannels(16);
		}
		Mix_Music * loadMusic(TUL::tString path){
			if(_musics.find(path)==_musics.end()){
				assert( (_musics[path]=Mix_LoadMUS(TUL::to_string(path).c_str())) != nullptr);
			}
			return _musics[path];
		}
		Mix_Chunk * loadSound(TUL::tString path){
			if(_chunks.find(path)==_chunks.end()){
				assert( (_chunks[path]=Mix_LoadWAV(TUL::to_string(path).c_str())) != nullptr);
			}
			return _chunks[path];
		}

		~SDLSound(){
			for(auto it=_musics.begin(); it!=_musics.end(); ++it){
				Mix_FreeMusic(it->second);
			}
			for(auto it=_chunks.begin(); it!=_chunks.end(); ++it){
				Mix_FreeChunk(it->second);
			}
			Mix_CloseAudio();
		}
	private:
		std::shared_ptr<SDLCore> _parent;
		std::map<TUL::tString,Mix_Music *> _musics;
		std::map<TUL::tString,Mix_Chunk *> _chunks;
	};
};