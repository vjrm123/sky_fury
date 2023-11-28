#ifndef MISIL_H
#define MISIL_H

#include "proyectil.h"
#include "enemigo.h"

const int ANCHO_MISIL = 20;
const int ALTO_MISIL = 70;

class Misil : public Proyectil {
private:

    EnemigoBase* objetivo = nullptr;
    SDL_Texture* textura = nullptr;
    bool debeSerDestruido = false;
    float velocidad{ 2.5 };

public:
    Misil(int x, int y, SDL_Renderer* renderizador, EnemigoBase* objetivo) : Proyectil(x, y, renderizador), objetivo(objetivo) {

        SDL_Surface* superficie = IMG_Load("imagenes/misil.png");
        textura = SDL_CreateTextureFromSurface(renderizador, superficie);
        SDL_FreeSurface(superficie);
    }
    ~Misil()
    {
        SDL_DestroyTexture(textura);
    }

    void mover_proyectil(SDL_Renderer* renderizador) override {
        
        float dx = objetivo->getx() - x;
        float dy = objetivo->gety() - y;

        
        float longitud = sqrt(dx * dx + dy * dy);
        dx /= longitud;
        dy /= longitud;

       
        x += dx * velocidad;
        y += dy * velocidad;

        
        if (y <= 0 || y >= 600 || x <= 0 || x >= 800) {
            debeSerDestruido = true;
        }
        else {
            SDL_Rect rectangulo = { static_cast<int>(x), static_cast<int>(y), ANCHO_MISIL, ALTO_MISIL };
            SDL_RenderCopy(renderizador, textura, NULL, &rectangulo);
        }
    }

    void pintar_proyectil(SDL_Renderer* renderizador) override {
        SDL_Rect rectangulo = { x, y, ANCHO_MISIL, ALTO_MISIL };
        SDL_RenderCopy(renderizador, textura, NULL, &rectangulo);
    }



    SDL_Rect getRect() const override {
        SDL_Rect rect = { x, y, ANCHO_MISIL, ALTO_MISIL };
        return rect;
    }

    bool getDebeSerDestruido() const override {
        return debeSerDestruido;
    }

    EnemigoBase* getObjetivo() const {
        return objetivo;
    }

    
    void setObjetivo(EnemigoBase* nuevo_objetivo) {
        objetivo = nuevo_objetivo;
    }

};

 #endif