#ifndef IMAGEN_H
#define IMAGEN_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "animaciones.h"
#include <list>
#include <vector>


class Imagen {
    private:
        SDL_Renderer* renderizador = nullptr;
        std::list<Animacion> animaciones;

    public:
        void mostrar_Mensaje_Perdiste(SDL_Renderer* renderizador) {

            SDL_Surface* imagen_perdiste = IMG_Load("imagenes/perdiste.jpg");

            SDL_Texture* textura_perdiste = SDL_CreateTextureFromSurface(renderizador, imagen_perdiste);

            SDL_Rect rect_perdiste;
            rect_perdiste.x = 0;
            rect_perdiste.y = 0;
            rect_perdiste.w = 800;
            rect_perdiste.h = 600;

            SDL_FreeSurface(imagen_perdiste);
             
            SDL_RenderCopy(renderizador, textura_perdiste, NULL, &rect_perdiste);

            SDL_RenderPresent(renderizador);

            SDL_Delay(5000);

            SDL_DestroyTexture(textura_perdiste);
        }

        void mostrar_Mensaje_ganaste(SDL_Renderer* renderizador) {

            SDL_Surface* imagen_perdiste = IMG_Load("imagenes/perdiste.jpg");

            SDL_Texture* textura_perdiste = SDL_CreateTextureFromSurface(renderizador, imagen_perdiste);

            SDL_Rect rect_perdiste;
            rect_perdiste.x = 0;
            rect_perdiste.y = 0;
            rect_perdiste.w = 800;
            rect_perdiste.h = 600;

            SDL_FreeSurface(imagen_perdiste);

            SDL_RenderCopy(renderizador, textura_perdiste, NULL, &rect_perdiste);

            SDL_RenderPresent(renderizador);

            SDL_Delay(5000);

            SDL_DestroyTexture(textura_perdiste);
        }

};
#endif