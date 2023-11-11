#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include "avion.h"
#include "bala.h"
#include "musica.h"
#include "enemigo.h"
#include <random>

using namespace std;

const int ALTO_ENEMIGO1 = 60;
const int ANCHO_ENEMIGO1 = 60;

class Enemigo1 : public EnemigoBase {
	private:
		
		float velocidad;
		int direccion;
		int frameIndex;
		int frameTime;
		int vidas{ 8};

		Uint32 tiempo_anterior; 
		Uint32 ultimo_cambio_direccion;
		TTF_Font* fuente ;
		std::vector<SDL_Texture*> imagenes;
	
		
	public:
		Enemigo1(int x, int y, SDL_Renderer* renderizador, float velocidad, int vidas) : 
			EnemigoBase(x, y, renderizador), direccion(1), tiempo_anterior(SDL_GetTicks()), velocidad(velocidad), vidas(vidas) {
			
			for (int i = 1; i < 6; i++) {
				std::string filename = "imagenes/imagen" + std::to_string(i) + ".png";
				SDL_Surface* superficies = IMG_Load(filename.c_str());
				imagenes.push_back(SDL_CreateTextureFromSurface(renderizador, superficies));
				SDL_FreeSurface(superficies);
			}
			
			ultimo_cambio_direccion = SDL_GetTicks();
			this->frameIndex = 1;
			this->frameTime = 0;
			
			fuente = TTF_OpenFont("letras.ttf", 24);
		}

		Enemigo1(){	}

		void pintar_enemigo(SDL_Renderer* renderizador) override {
			SDL_Rect rectangulo = { x, y, ANCHO_ENEMIGO1, ALTO_ENEMIGO1 };
			if (frameIndex >= 0 && frameIndex < imagenes.size()) {
				SDL_SetTextureBlendMode(imagenes[frameIndex], SDL_BLENDMODE_BLEND);
				SDL_RenderCopy(renderizador, imagenes[frameIndex], nullptr, &rectangulo);
			}

			
			std::string texto_vidas = std::to_string(vidas);
			SDL_Color color = { 255, 255, 255 }; 
			SDL_Surface* superficie_texto = TTF_RenderText_Solid(fuente, texto_vidas.c_str(), color);
			SDL_Texture* textura_texto = SDL_CreateTextureFromSurface(renderizador, superficie_texto);

			int ancho_texto, alto_texto;
			SDL_QueryTexture(textura_texto, NULL, NULL, &ancho_texto, &alto_texto);
			SDL_Rect rectangulo_texto = { x + ANCHO_ENEMIGO1 / 2 - ancho_texto / 2, y + ALTO_ENEMIGO1 / 2 - alto_texto / 2, ancho_texto, alto_texto };

			SDL_RenderCopy(renderizador, textura_texto, NULL, &rectangulo_texto);

			SDL_FreeSurface(superficie_texto);
			SDL_DestroyTexture(textura_texto);
		}

		void mover_enemigo(SDL_Renderer* renderizador) {
			Uint32 tiempo_actual = SDL_GetTicks();
			float deltaTiempo = (tiempo_actual - tiempo_anterior) / 1000.0f;
			y += velocidad * deltaTiempo;
			tiempo_anterior = tiempo_actual;

			x += direccion ;
			if ((x > 800 - ANCHO_ENEMIGO1 || x < 0) ) {
				direccion *= -1;
			}

			if (y >= 600) {

				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> distribucion_x(1, 800-32);
				uniform_int_distribution<> distribucion_y(-600, -200);
				x = distribucion_x(gen);
				y = distribucion_y(gen);
			}

			frameTime++;
			if (frameTime >= 100) {
				frameIndex++;
				frameTime = 0;
			}
			if (frameIndex >= imagenes.size()) {
				frameIndex = 1;
			}
			pintar_enemigo(renderizador);
		}

		void choque_enemigo(Avion& avion, Musica& musica, SDL_Renderer* renderizador) override {

			if (x >= avion.getcoordenada_x() && x < avion.getcoordenada_x() + 80 && y >= avion.getcoordenada_y() && y <= avion.getcoordenada_y() + 80) {
				avion.reducirVida();
				avion.pintar_avion(renderizador);
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> distribucion_x(0, 800 - 32);
				uniform_int_distribution<> distribucion_y(-600, -200);
				x = distribucion_x(gen);
				y = distribucion_y(gen);

				musica.reproducir_colision();
			}
		}

		SDL_Rect getRect() const override {
			SDL_Rect rect = { x, y, 60, 60 };
			return rect;
		}

		void reducirVida(unsigned int cantidad = 1) override {
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

		virtual ~Enemigo1() {
			for (auto& textur : imagenes) {
				SDL_DestroyTexture(textur);
			}
		}
};

#endif