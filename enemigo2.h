#ifndef ENEMIGO2_H
#define ENEMIGO2_H


#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include "avion.h"
#include "bala.h"
#include "enemigo.h"
#include <random>

using namespace std;
 
const int ALTO_ENEMIGO2 = 60;
const int ANCHO_ENEMIGO2 = 60;

class Enemigo2 : public EnemigoBase {

private:
    int vidas;
    int velocidad_y;
    SDL_Texture* textura = nullptr;

public:

    Enemigo2(int x, int y, SDL_Renderer* renderizador) : EnemigoBase(x, y, renderizador), velocidad_y{ 1 }, vidas{ 6 } {
        
        SDL_Surface* superficie = IMG_Load("imagenes/enemigo2.png");
        textura = SDL_CreateTextureFromSurface(renderizador, superficie);
        SDL_FreeSurface(superficie);
    }

    Enemigo2(){}

    void pintar_enemigo(SDL_Renderer* renderizador) override {

        SDL_Rect rectangulo = { x, y, ANCHO_ENEMIGO2, ALTO_ENEMIGO2 };
        SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(renderizador, textura, nullptr, &rectangulo);
    }

    void mover_enemigo(SDL_Renderer* renderizador) override {
        
        
         y += 1;
        if (y > 600) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distribucion_x(0, 800 - 32);
            uniform_int_distribution<> distribucion_y(-600, -200);
            x = distribucion_x(gen);
            y = distribucion_y(gen);
            
        }
        pintar_enemigo(renderizador);
    }

    void choque_enemigo(Avion& aviones, Musica& musica, SDL_Renderer* renderizador) override {
        if (x >= aviones.getcoordenada_x() && x < aviones.getcoordenada_x() + 50 && y >= aviones.getcoordenada_y() && y <= aviones.getcoordenada_y() + 50) {
            aviones.pintar_avion(renderizador);
            
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distribucion_x(0, 800 - 60);
            uniform_int_distribution<> distribucion_y(-600, 0);
            x = distribucion_x(gen);
            y = distribucion_y(gen);

            aviones.reducirVida(1);
        }
    }

    SDL_Rect getRect() const override {
        SDL_Rect rect = { x, y, 60, 60 } ;
        return rect;
    }

    void reducirVida(unsigned int cantidad = 0) override {
        if (vidas < 0) {
            vidas = 0;
        }
        else {
            vidas -= cantidad;
        }
    }

    int getvidas() const override {
        return vidas;
    }

    ~Enemigo2() {
        SDL_DestroyTexture(textura);
    }
};



#endif