#ifndef AVION_H
#define AVION_H

#include <SDL.h>
#include <SDL_image.h>
#include "bala.h"
#include <list>
#include "bala.h"

#include <SDL_ttf.h>


const int ANCHO_AVION = 100;
const int ALTO_AVION = 100;
const int ANCHO_VENTANA = 800;
const int ALTO_VENTANA = 600;

class Avion {

    private:
        int coordenada_x;
        int coordenada_y;
        unsigned int vidas=6;
        unsigned int puntos = 0;
        SDL_Texture* textura = nullptr;
        


    public:
        


        Avion(int coordenada_x, int coordenada_y, int vidas, SDL_Renderer* renderizador) :
            coordenada_x(coordenada_x), coordenada_y(coordenada_y), vidas(vidas) {

            SDL_Surface* superficie = IMG_Load("imagenes/avion_nuevo.png");
            textura = SDL_CreateTextureFromSurface(renderizador, superficie);
            SDL_FreeSurface(superficie);
        }

        ~Avion() {
            SDL_DestroyTexture(textura);

        }

        int getcoordenada_x() {
            return coordenada_x;
        }

        int getcoordenada_y() {
            return coordenada_y;
        }

        int getvidas() {
            return vidas;
        }
        int getPuntos() {
            return puntos;
        }

       
        void pintar_avion(SDL_Renderer* renderizador) {
            SDL_Rect rectangulo = { coordenada_x, coordenada_y, ANCHO_AVION, ALTO_AVION };
            SDL_RenderCopy(renderizador, textura, nullptr, &rectangulo);
        }



        void mover_avion(SDL_Renderer* renderizador, SDL_Event evento, bool& salir);


        void reducirVida(unsigned int cantidad=1) {
            vidas -= cantidad;
            if (vidas <= 0) {
                vidas = 0;
            }
        }

        void SumarPuntos(unsigned int cantidad = 5) {
            puntos += cantidad;
            
        }
};
#endif
