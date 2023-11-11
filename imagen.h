#ifndef IMAGEN_H
#define IMAGEN_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "animaciones.h"
#include <list>


class Imagen {
    private:
        SDL_Renderer* renderizador = nullptr;
        std::list<Animacion> animaciones;

    public:
        void mostrar_Mensaje_Perdiste(SDL_Renderer* renderizador) {

            SDL_Surface* imagen_perdiste = IMG_Load("imagenes/perdiste.jpg");

            SDL_Texture* textura_perdiste = SDL_CreateTextureFromSurface(renderizador, imagen_perdiste);

            SDL_Rect rect_perdiste;
            rect_perdiste.x = 800 / 2 - imagen_perdiste->w / 2;
            rect_perdiste.y = 600 / 2 - imagen_perdiste->h / 2;
            rect_perdiste.w = imagen_perdiste->w;
            rect_perdiste.h = imagen_perdiste->h;

            SDL_FreeSurface(imagen_perdiste);
             
            SDL_RenderCopy(renderizador, textura_perdiste, NULL, &rect_perdiste);

            SDL_RenderPresent(renderizador);

            SDL_Delay(2000);

            SDL_DestroyTexture(textura_perdiste);
        }

};
#endif