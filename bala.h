#ifndef BALA_H
#define BALA_H

#include <SDL.h>
#include <SDL_image.h>
#include <list>
#include "proyectil.h"


using namespace std;


const int ANCHO_BALA = 10;
const int ALTO_BALA = 50;


class Bala : public Proyectil {
protected:
    SDL_Texture* textura = nullptr;
public:
    

    Bala(int x, int y, SDL_Renderer* renderizador) : Proyectil(x, y, renderizador)
    {

        SDL_Surface* superficie = IMG_Load("imagenes/bala.png");
        textura = SDL_CreateTextureFromSurface(renderizador, superficie);
        SDL_FreeSurface(superficie);
    }
    ~Bala()
    {
        SDL_DestroyTexture(textura);
        
        
    }


    void mover_proyectil(SDL_Renderer* renderizador) override {
        
        if (y >= 0) {
           
            y-=4     ;
            SDL_Rect rectangulo = { x, y, ANCHO_BALA, ALTO_BALA };
            SDL_RenderCopy(renderizador, textura, NULL, &rectangulo);
        }
        
        else {
            this->~Bala();
        }    
    }
    

    SDL_Texture* get_textura() const {
        return textura;
    }

    void pintar_proyectil(SDL_Renderer* renderizador) override {
        
        SDL_Rect rectangulo = { x, y, ANCHO_BALA, ALTO_BALA };
        SDL_RenderCopy(renderizador, textura, NULL, &rectangulo);
    }

    static bool alarma(int segundos) {
        static int contador = 0;

        if (segundos == 0) {
            return false;
        }

        if (contador >= segundos) {
            contador = 0;
            return true;
        }
        contador++;

        return false;
    }


    SDL_Rect getRect() const override {
        SDL_Rect rect = { x, y, ANCHO_BALA, ALTO_BALA };
        return rect;
    }
   
    
};

#endif
