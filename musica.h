#ifndef MUSICA_H
#define MUSICA_H


#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

class Musica {

private:
    Mix_Chunk* sonido_disparo = nullptr;
    Mix_Chunk* sonido_colision = nullptr;
    Mix_Chunk* sonido_boton = nullptr;
    Mix_Chunk* sonido_misil = nullptr;
    Mix_Chunk* sonido_colision_enemigo1 = nullptr;
    Mix_Chunk* sonido_bala = nullptr;

public:
    Musica() {
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        //sonido_disparo = Mix_LoadWAV("disparo.wav");
        sonido_colision = Mix_LoadWAV("sonidos/Explosion.wav");
        sonido_misil = Mix_LoadWAV("sonidos/sonido_misil.wav");
        sonido_boton = Mix_LoadWAV("sonidos/Button.wav");
        sonido_colision_enemigo1 = Mix_LoadWAV("sonidos/sonidos_bala.wav");
        sonido_bala = Mix_LoadWAV("sonidos/sonido_balas.MPEG");
    }

    ~Musica() {
        Mix_FreeChunk(sonido_disparo);
        Mix_FreeChunk(sonido_boton);
        Mix_FreeChunk(sonido_misil);
        Mix_FreeChunk(sonido_colision);
        Mix_FreeChunk(sonido_colision_enemigo1);
        Mix_FreeChunk(sonido_bala);
        Mix_CloseAudio();

    }

    void reproducir_disparo() {
        Mix_PlayChannel(-1, sonido_disparo, 0);
    }

    void reproducir_sonido_bala() {
        Mix_PlayChannel(-1, sonido_bala, 0);
    }

    void reproducir_sonido_misil() {
        Mix_PlayChannel(-1, sonido_misil, 0);
    }

    void reproducir_colision() {
        Mix_PlayChannel(-1, sonido_colision, 0);
    }

    void reproducir_boton() {
        Mix_PlayChannel(-1, sonido_boton, 0);
    }

    void reproducir_colision_enemigo1() {
        Mix_PlayChannel(-1, sonido_colision_enemigo1, 0);
    }
};
#endif
