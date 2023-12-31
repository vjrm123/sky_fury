#ifndef GENERAL_H
#define GENERAL_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include "bala.h"
#include "nave_invasora.h"
#include "nave_blindada.h"
#include "imagen.h"
#include "proyectil.h"
#include "animaciones.h"
#include "misil.h"
#include "balaTipo1.h"
#include "enemigo.h"
#include <list>
#include <SDL_ttf.h>
#include <fstream>
const int ANCHO_VENTANAs = 800;
const int ALTO_VENTANAs = 600;

list<Proyectil*> balas;
list<Proyectil*> misiles;
list<EnemigoBase*> list_nave_blindada;
list<EnemigoBase*> list_nave_invasora;
list<Animacion*> animaciones;

Musica musicas;
Imagen imagenes;

void Avion:: mover_avion(SDL_Renderer* renderizador, SDL_Event evento, bool& salir) {
    const Uint8* teclas = SDL_GetKeyboardState(nullptr);

    if (teclas[SDL_SCANCODE_SPACE] && Bala::alarma(15)) {
        if (vidas <= 4) {
            
            balas.push_back(new Bala(coordenada_x, coordenada_y, renderizador)); 
            balas.push_back(new Bala(coordenada_x + ANCHO_AVION, coordenada_y, renderizador)); 
            balas.push_back(new BalaTipo1(coordenada_x + (ANCHO_AVION / 2) - 10, coordenada_y, renderizador));
        }
        if (vidas <= 3) {
            balas.push_back(new Bala(coordenada_x, coordenada_y, renderizador));
            balas.push_back(new Bala(coordenada_x + ANCHO_AVION, coordenada_y, renderizador));
            balas.push_back(new BalaTipo1(coordenada_x + (ANCHO_AVION / 2) - 30, coordenada_y, renderizador));
            balas.push_back(new BalaTipo1(coordenada_x + (ANCHO_AVION / 2) + 20, coordenada_y, renderizador));
        }
        else {
            
            balas.push_back(new Bala(coordenada_x + (ANCHO_AVION / 2) - 10, coordenada_y, renderizador));
        }

    } 

    for (auto it = balas.begin(); it != balas.end(); ) {
        Proyectil* b = *it;
        b->pintar_proyectil(renderizador);
        b->mover_proyectil(renderizador);

        if (b->gety() <= 1) {
            delete b; 
            it = balas.erase(it);
        }
        else {
            ++it;
        }
    }

    if (teclas[SDL_SCANCODE_D] && Bala::alarma(25) && vidas <= 3) {
        for (EnemigoBase* enemigor : list_nave_blindada) {
            misiles.push_back(new Misil(coordenada_x + (ANCHO_AVION / 2) - 10, coordenada_y, renderizador, enemigor));
        }
        musicas.reproducir_sonido_misil();
    }


    if (teclas[SDL_SCANCODE_RIGHT]) {
        if (coordenada_x + ANCHO_AVION < ANCHO_VENTANA) {
            coordenada_x += 2;
        }
    }
    if (teclas[SDL_SCANCODE_LEFT]) {

        if (coordenada_x > 0) {
            coordenada_x -= 2;
        }
    }
    if (teclas[SDL_SCANCODE_UP]) {
        if (coordenada_y > 0) {
            coordenada_y -= 1;
        }
        else {
            coordenada_y = 0;
        }
    }
    if (teclas[SDL_SCANCODE_DOWN]) {
        if (coordenada_y + ALTO_AVION < ALTO_VENTANA) {
            coordenada_y += 1;
        }
    }
    pintar_avion(renderizador);
}


void almacenar_Puntaje(int puntaje) {
    std::ofstream archivo("puntajes.txt", std::ios::app); 
    if (archivo.is_open()) {
        archivo << puntaje << std::endl; 
        archivo.close();
    }
}

std::vector<int> leerPuntajes_Maximos() {
    std::vector<int> puntajes;
    std::ifstream archivo("puntajes.txt");
    if (archivo.is_open()) {
        int puntaje;
        while (archivo >> puntaje) {
            puntajes.push_back(puntaje);
        }
        archivo.close();
    }
    std::sort(puntajes.begin(), puntajes.end(), std::greater<int>());

    if (puntajes.size() > 5) {
        puntajes.resize(5);
    }
    return puntajes;
}


class GENERAL
{
public:
    void ejecutar() {

        SDL_Init(SDL_INIT_VIDEO);
        IMG_Init(IMG_INIT_PNG);

        TTF_Init();
        TTF_Font* fuente = TTF_OpenFont("letras.ttf", 40);

        
        SDL_Window* ventana = SDL_CreateWindow("        VENTANA DE SKY FURY        ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_VENTANA, ALTO_VENTANA, SDL_WINDOW_SHOWN);
        SDL_Renderer* renderizador = SDL_CreateRenderer(ventana, -1, 0);
        SDL_Texture* textura_fondo = IMG_LoadTexture(renderizador, "imagenes/fondo.JPG");

        /*comensar*/ 

        SDL_Surface* superficie_boton = IMG_Load("imagenes/menu.png");
        SDL_Texture* textura_boton = SDL_CreateTextureFromSurface(renderizador, superficie_boton);
        SDL_Rect rect_boton;
        rect_boton.x = 0; 
        rect_boton.y = 0; 
        rect_boton.w = ANCHO_VENTANAs;
        rect_boton.h = ALTO_VENTANAs;

        
        SDL_Rect rect_central;
        rect_central.x = ANCHO_VENTANAs / 2 - 350;
        rect_central.y = ALTO_VENTANAs / 2 - 150;
        rect_central.w = 100;
        rect_central.h = 100;

        // PARA QUE SE MUESTRE NUMEROS
        SDL_Color color = { 255, 255, 255 };
        SDL_Rect rect_contador;
        rect_contador.w = 100; 
        rect_contador.h = 100; 
        rect_contador.x = (ANCHO_VENTANA - rect_contador.w) / 2;
        rect_contador.y = (ALTO_VENTANA - rect_contador.h) / 2;
        
        SDL_Surface* superficie_3 = TTF_RenderText_Solid(fuente, "3", color);
        SDL_Texture* textura_3 = SDL_CreateTextureFromSurface(renderizador, superficie_3);
        SDL_Surface* superficie_2 = TTF_RenderText_Solid(fuente, "2", color);
        SDL_Texture* textura_2 = SDL_CreateTextureFromSurface(renderizador, superficie_2);
        SDL_Surface* superficie_1 = TTF_RenderText_Solid(fuente, "1", color);
        SDL_Texture* textura_1 = SDL_CreateTextureFromSurface(renderizador, superficie_1);
        SDL_Surface* superficie_go = TTF_RenderText_Solid(fuente, "GOOO", color);
        SDL_Texture* textura_go = SDL_CreateTextureFromSurface(renderizador, superficie_go);


        Avion avion(ANCHO_VENTANA / 2 - ANCHO_AVION / 2, ALTO_VENTANA / 2 - ALTO_AVION / 2 +100, 6, renderizador);

        for (int i = 0; i < 4; i++) {
            list_nave_blindada.push_back(new NaveBlindada(rand() % 800, -800, renderizador, 200, 8));
        }

        for (int i = 0; i < 5; i++) {
            list_nave_invasora.push_back(new NaveInvasora(rand() % 800, -800, renderizador));
        }


        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        Mix_Music* musica = Mix_LoadMUS("sonidos/misions.MPEG");


        SDL_Event evento;
        bool salir = false;
        bool juego_comenzado = false;

        while (!salir) {
            while (SDL_PollEvent(&evento)) {
                if (evento.type == SDL_QUIT) {
                    salir = true;
                }

                if (evento.type == SDL_MOUSEBUTTONDOWN) {
                    musicas.reproducir_boton();

                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (x > rect_central.x && x < rect_central.x + rect_central.w && y > rect_central.y && y < rect_central.y + rect_central.h) {
                        juego_comenzado = true; 

                        SDL_RenderClear(renderizador);
                        SDL_RenderCopy(renderizador, textura_3, nullptr, &rect_contador);
                        SDL_RenderPresent(renderizador);
                        SDL_Delay(1000); 
                        musicas.reproducir_boton();
                        SDL_FreeSurface(superficie_3); 

                        SDL_RenderCopy(renderizador, textura_2, nullptr, &rect_contador);
                        SDL_RenderPresent(renderizador);
                        SDL_Delay(1000); 
                        musicas.reproducir_boton();
                        SDL_FreeSurface(superficie_2); 

                        SDL_RenderClear(renderizador);
                        SDL_RenderCopy(renderizador, textura_1, nullptr, &rect_contador);
                        SDL_RenderPresent(renderizador);
                        SDL_Delay(1000); 
                        musicas.reproducir_boton();
                        SDL_FreeSurface(superficie_1);

                        SDL_RenderClear(renderizador);
                        SDL_RenderCopy(renderizador, textura_go, nullptr, &rect_contador);
                        SDL_RenderPresent(renderizador);
                        SDL_Delay(1000);
                        SDL_FreeSurface(superficie_go);

                        Mix_PlayMusic(musica, -1);
                    }
                }

            }
           
            SDL_RenderCopy(renderizador, textura_fondo, nullptr, nullptr);

            

            if (!juego_comenzado) {

                SDL_RenderCopy(renderizador, textura_boton, nullptr, &rect_boton);
            }
            else {

                avion.mover_avion(renderizador, evento, salir);
                avion.pintar_avion(renderizador);

                

                for (auto itA = list_nave_blindada.begin(); itA != list_nave_blindada.end(); itA++) {
                    (*itA)->mover_enemigo(renderizador);
                    (*itA)->choque_enemigo(avion, musicas, renderizador); 
                }


                for (auto ite = list_nave_invasora.begin(); ite != list_nave_invasora.end(); ite++) {
                    (*ite)->mover_enemigo(renderizador);
                    (*ite)->choque_enemigo(avion, musicas, renderizador);
                }
       

                for (auto itB = balas.begin(); itB != balas.end(); ) {
                    bool balaEliminada = false;
                    SDL_Rect rect_bala = (*itB)->getRect();

                    for (auto itE = list_nave_blindada.begin(); itE != list_nave_blindada.end(); ) {
                        SDL_Rect rect_enemigo = (*itE)->getRect();

                        if (SDL_HasIntersection(&rect_bala, &rect_enemigo)) {
                            
                            musicas.reproducir_colision_enemigo1();
                            (*itE)->reducirVida();

                            if ((*itE)->getvidas() == 0) {
                                delete* itE;
                                avion.SumarPuntos(10);
                                itE = list_nave_blindada.erase(itE);

                                animaciones.push_back(new Animacion((*itB)->getx(), (*itB)->gety()));
                                list_nave_blindada.push_back(new NaveBlindada(rand() % 800, -800, renderizador, 250, 20));
                            }

                            delete* itB;
                            itB = balas.erase(itB);

                            balaEliminada = true;
                            break;
                        }
                        else {
                            ++itE;
                        }

                        // Bucle para enemigo2
                        for (auto itE2 = list_nave_invasora.begin(); itE2 != list_nave_invasora.end() && !balaEliminada; ) {
                            SDL_Rect rect_enemigo2 = (*itE2)->getRect();

                            if (SDL_HasIntersection(&rect_bala, &rect_enemigo2)) {

                                animaciones.push_back(new Animacion((*itE2)->getx(), (*itE2)->gety()));
                                list_nave_invasora.push_back(new NaveInvasora(rand() % 800, -800, renderizador));
                                musicas.reproducir_colision_enemigo1();

                                delete* itE2;
                                itE2 = list_nave_invasora.erase(itE2);
                                avion.SumarPuntos();

                                delete* itB;
                                itB = balas.erase(itB);
                                balaEliminada = true;
                                break;
                            }
                            else {     
                                ++itE2;
                            }
                        }
                    }

                    if (!balaEliminada) {
                        ++itB;
                    }
                } 
                
                for (auto itM = misiles.begin(); itM != misiles.end(); ) {
                    Misil* misil = dynamic_cast<Misil*>(*itM);  

                    if (misil != NULL) { 

                        if (std::find(list_nave_blindada.begin(), list_nave_blindada.end(), misil->getObjetivo()) == list_nave_blindada.end()) {
                            if (!list_nave_blindada.empty()) {
                                misil->setObjetivo(list_nave_blindada.front());
                            }
                            else {
                                misil->setObjetivo(NULL);
                            }
                        }

                        misil->mover_proyectil(renderizador);
                        misil->pintar_proyectil(renderizador);

                        if (misil->getDebeSerDestruido()) {
                            delete* itM;
                            itM = misiles.erase(itM);

                            continue;
                        }

                        bool misilEliminado = false;
                        SDL_Rect rect_misil = (*itM)->getRect();

                        for (auto itE = list_nave_blindada.begin(); itE != list_nave_blindada.end(); ) {
                            SDL_Rect rect_enemigo = (*itE)->getRect();

                            if (SDL_HasIntersection(&rect_misil, &rect_enemigo)) {

                                delete* itM;
                                itM = misiles.erase(itM);
                                avion.SumarPuntos();
                                misilEliminado = true;

                                animaciones.push_back(new Animacion((*itE)->getx(), (*itE)->gety()));
                                list_nave_blindada.push_back(new NaveBlindada(rand() % 800, -800, renderizador, 250, 20));

                                delete* itE;
                                itE = list_nave_blindada.erase(itE);
                                break;
                            }
                            else {
                                ++itE;
                            }
                        }

                        if (!misilEliminado) {
                            ++itM;
                        }
                    }
                }
            }

            for (auto it = animaciones.begin(); it != animaciones.end(); ) {
                if (!(*it)->avanzar(renderizador)) {
                    delete* it;
                    it = animaciones.erase(it);
                }
                else {
                    ++it;
                }
            }
            

            SDL_Color color = { 250, 250, 250 };
            std::string texto = "Vidas: " + std::to_string(avion.getvidas());
            
            SDL_Surface* superficie_texto = TTF_RenderText_Solid(fuente, texto.c_str(), color);
            SDL_Texture* textura_texto = SDL_CreateTextureFromSurface(renderizador, superficie_texto);

            int ancho_texto=50, alto_texto=50;
            SDL_QueryTexture(textura_texto, NULL, NULL, &ancho_texto, &alto_texto);
            SDL_Rect rect_texto = { ANCHO_VENTANA - ancho_texto - 10, 10, ancho_texto, alto_texto };
            SDL_RenderCopy(renderizador, textura_texto, NULL, &rect_texto);

            SDL_FreeSurface(superficie_texto);
            SDL_DestroyTexture(textura_texto);


            SDL_Color colors = { 250, 250, 250 };
            std::string textos = "Puntos: " + std::to_string(avion.getPuntos());

            SDL_Surface* superficie_textos = TTF_RenderText_Solid(fuente, textos.c_str(), colors);
            SDL_Texture* textura_textos = SDL_CreateTextureFromSurface(renderizador, superficie_textos);

            int ancho_textos = 50, alto_textos = 50;
            SDL_QueryTexture(textura_textos, NULL, NULL, &ancho_textos, &alto_textos);
            SDL_Rect rect_textos = { ANCHO_VENTANA - ancho_textos - 200, 10, ancho_textos, alto_textos };
            SDL_RenderCopy(renderizador, textura_textos, NULL, &rect_textos);

            SDL_FreeSurface(superficie_textos);
            SDL_DestroyTexture(textura_textos);


    
            SDL_RenderPresent(renderizador);

            SDL_Delay(1);

            

            if (avion.getvidas() == 0) {
                imagenes.mostrar_Mensaje_Perdiste(renderizador);
                SDL_RenderClear(renderizador);
                almacenar_Puntaje(avion.getPuntos());

                std::vector<int> puntajesMaximos = leerPuntajes_Maximos();
                SDL_Color colore = { 255, 255, 255 };

                for (int i = 0; i < puntajesMaximos.size(); i++) {
                    std::string textoMaximo = "Puntaje mas alto " + std::to_string(i + 1) + ": " + std::to_string(puntajesMaximos[i]);

                    SDL_Surface* superficieMaximo = TTF_RenderText_Solid(fuente, textoMaximo.c_str(), colore);
                    SDL_Texture* texturaMaximo = SDL_CreateTextureFromSurface(renderizador, superficieMaximo);

                    int anchoMaximo = 20, altoMaximo = 20;
                    SDL_QueryTexture(texturaMaximo, NULL, NULL, &anchoMaximo, &altoMaximo);
                    SDL_Rect rectMaximo = { ANCHO_VENTANA / 2 - 200, ALTO_VENTANA / 2 - 200 + i * altoMaximo, anchoMaximo, altoMaximo };
                    SDL_RenderCopy(renderizador, texturaMaximo, NULL, &rectMaximo);

                    SDL_FreeSurface(superficieMaximo);
                    SDL_DestroyTexture(texturaMaximo);
                }

                SDL_RenderPresent(renderizador); 

                SDL_Delay(10000);
               
                salir = true;
            }
        }
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
    }
};
#endif
