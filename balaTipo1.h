#include "bala.h"
class BalaTipo1 : public Bala {
public:
    BalaTipo1(int x, int y, SDL_Renderer* renderizador) : Bala(x, y, renderizador) {
        SDL_Surface* superficie = IMG_Load("imagenes/rayo.png");
        textura = SDL_CreateTextureFromSurface(renderizador, superficie);
        SDL_FreeSurface(superficie);
    }
}; 