#ifndef ANIMACIONES_H
#define ANIMACIONES_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <list>

class Animacion {

private:
    int x, y;
    int frame_actual=1;

public:
    Animacion(int x, int y) : x(x), y(y), frame_actual(1) {}

    bool avanzar(SDL_Renderer* renderizador) {
        if (frame_actual >= 6) {
            return false;  
        }

        std::string ruta_imagen = "imagenes/Explosion" + std::to_string(frame_actual) + ".png";
        SDL_Surface* imagen = IMG_Load(ruta_imagen.c_str());
        SDL_Texture* textura = SDL_CreateTextureFromSurface(renderizador, imagen);
        SDL_FreeSurface(imagen);

        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = 120;
        rect.h = 120;

        SDL_RenderCopy(renderizador, textura, NULL, &rect);
        SDL_DestroyTexture(textura);

        ++frame_actual;

        return true;  
    }

};

#endif 