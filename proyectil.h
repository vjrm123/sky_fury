#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class Proyectil {
protected:
    int x, y;
    SDL_Texture* textura = nullptr;

public:
    Proyectil(int x, int y, SDL_Renderer* renderizador) : x{ x }, y{ y } { }

    virtual ~Proyectil() {
        SDL_DestroyTexture(textura);
    }

    int getx() const {
        return x;
    }

    int gety() const {
        return y;
    }

    virtual void mover_proyectil(SDL_Renderer* renderizador) = 0;
    virtual void pintar_proyectil(SDL_Renderer* renderizador) = 0;
    virtual SDL_Rect getRect() const = 0;
    virtual bool getDebeSerDestruido() const {
        return false;
    }
};

#endif