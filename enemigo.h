#ifndef ENEMIGOBASE_H
#define ENEMIGOBASE_H

#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include "avion.h"
#include "musica.h"

class EnemigoBase {
protected:
    int x;
    int y;
  
public:
    EnemigoBase(int x, int y, SDL_Renderer* renderizador) : x(x), y(y) {}

    EnemigoBase(){}

    virtual SDL_Rect getRect() const {
        SDL_Rect rect = { x, y, 60, 60 };
        return rect;
    }

    virtual int getx() {
        return x;
    }

    virtual int gety() {
        return y;
    }

    virtual void mover_enemigo(SDL_Renderer* renderizador) =0;
    virtual void pintar_enemigo(SDL_Renderer* renderizador) =0;
    virtual void choque_enemigo(Avion& aviones, Musica& musica, SDL_Renderer* renderizador) =0;
    virtual void reducirVida(unsigned int cantidad = 1) =0;
    virtual int getvidas() const = 0;
}; 

#endif