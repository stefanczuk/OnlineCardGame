/**
 * Autor: Mateusz Skolimowski
 */
#ifndef GAME_H
#define GAME_H

#include <string>
#include "karta.h"

int game(std::vector<struct client_t*> clientList, int iloscGraczy);
std::vector<karta> stworzVectorWszystkichKart();
std::vector<struct client_t*> rozlosujKarty(std::vector<struct client_t*> clientList,std::vector<karta> wszystkieKarty,int &numerGraczaKtoryRozpoczyna);
std::string zamienKartyGraczaNaString(struct client_t*);
std::string typKarty(int j);
std::string numerKarty(int i);
void wyslij(struct client_t* c,std::string wiadomosc);
bool czyKoniecGry(std::vector<struct client_t*> clientList);
bool sprawdzCzyRuchDozwolony(struct client_t* c,int ktoraKarta,std::vector<karta> stosKart);
int ruchGracza(int numerGracza , std::vector<struct client_t*> &clientList,std::vector<karta> &stosKart);
int game(std::vector<struct client_t*> clientList, int iloscGraczy);
std::string zamienKartyGraczaNaString(struct client_t* c);
std::vector<karta> stworzVectorWszystkichKart();
std::vector<struct client_t*> rozlosujKarty(std::vector<struct client_t*> clientList,std::vector<karta> wszystkieKarty, int &numerGraczaKtoryRozpoczyna);


#endif
