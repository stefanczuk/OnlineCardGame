/**
 * Autor: Mateusz Skolimowski
 * 
 * W tym pliku beda znajdowac sie wszystkie funkcje ktore sluza do obslugi gry od strony serwera.
 * 
 */
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "karta.h"
#include <iostream>
#include <time.h>
#include <cstring>
#include <string>

struct client_t
{
    int socket;
    pthread_mutex_t* mutex;
    char nick[50];
    int trybGracza;
    std::vector<karta> kartyGracza;
};

std::vector<karta> stworzVectorWszystkichKart();
std::vector<struct client_t*> rozlosujKarty(std::vector<struct client_t*> clientList,std::vector<karta> wszystkieKarty);
std::string zamienKartyGraczaNaString(struct client_t*);
/*funkcja zamieniajaca typ karty podany jako liczba na string*/
std::string typKarty(int j)
{
	switch(j)
	{
		case 0:
			return "PIK";
		case 1:
			return "TREFL";
		case 2: 
			return "KARO";
		case 3:
			return "KIER";
	}
}
/*funkcja zamieniajaca numer karty podany jako liczba na string*/
std::string numerKarty(int i)
{
	switch(i)
	{
		case 0:
			return "9";
		case 1:
			return "10";
		case 2: 
			return "J";
		case 3:
			return "D";
		case 4: 
			return "K";
		case 5:
			return "A";
	}
}

void wyslij(struct client_t* c,std::string wiadomosc)
{
	write(c->socket,wiadomosc.c_str(),wiadomosc.length());
}

bool czyKoniecGry(std::vector<struct client_t*> clientList)
{
	if(clientList.size() == 1)
	{
		return false;
	}
	return true;
}

bool sprawdzCzyRuchDozwolony(struct client_t* c,int ktoraKarta,std::vector<karta> stosKart)
{
	if(stosKart.empty())
		return true;	
	if(stosKart[stosKart.size()-1].porownajKarty(c->kartyGracza[ktoraKarta]))
	{
		return true;
	}
	else
		return false;
}

int ruchGracza(int numerGracza , std::vector<struct client_t*> &clientList,std::vector<karta> &stosKart)
{
	std::string s = zamienKartyGraczaNaString(clientList[numerGracza]);
	wyslij(clientList[numerGracza], s);
	sleep(1);
	wyslij(clientList[numerGracza], "wykonaj ruch");
	sleep(1);
	char b[1024];
	bzero(b,sizeof(b));
	if(( recv( clientList[numerGracza]->socket, b, sizeof( b ), 0 ) ) <= 0 )
  	{
   		perror( "Blad recv\n" );
    		exit( - 1 );
  	}
	printf("klient %d : %s\n",numerGracza,b);\
	if(sprawdzCzyRuchDozwolony(clientList[numerGracza],b[15]-'0',stosKart))
	{
		printf("ruch dowzowolny\n");
		stosKart.push_back(clientList[numerGracza]->kartyGracza[b[15]-'0']);
	}
	else
	{
		printf("nope\n");
	}
	char numer[20];
	sprintf(numer,"gracz %d wykonal ruch",numerGracza);
	for(int i = 0 ; i < clientList.size() ; i++)
	{
		if(i!= numerGracza)
			wyslij(clientList[i],std::string(numer));
	}
	return 0;
}

/*glowna funkcja obslugujaca gre*/
int game(std::vector<struct client_t*> clientList, int iloscGraczy)
{
	std::vector<karta> wszystkieKarty = stworzVectorWszystkichKart();
	clientList = rozlosujKarty(clientList,wszystkieKarty);
	for(int i=0;i<clientList.size();++i)
		wyslij(clientList[i],"Rozpoczynamy gre");
	sleep(1);
	for(int i=0;i<clientList.size();++i)
	{
		std::string s = zamienKartyGraczaNaString(clientList[i]);
		wyslij(clientList[i], s);
	}
	sleep(1);
	int numer = 0;
	std::vector<karta> stosKart;
	while(czyKoniecGry(clientList))
	{
		numer = ruchGracza(numer,clientList,stosKart);
	}
}

/*funkcja ktora zamienia wszystkie karty gracza na ciag znakow*/
std::string zamienKartyGraczaNaString(struct client_t* c)
{
	std::string s = "\n";
	for(int i = 0 ; i < c->kartyGracza.size() ; i++)
	{
		char numer[2];
		sprintf(numer,"%d",i);
		s = s + numer + "." + c->kartyGracza[i].getNumer() + " " + c->kartyGracza[i].getTyp() + "\n";
	}
	return s;
}
/*funkcja ktora tworzy vector wszystkich kart aby mozna bylo je rozlosowac miedzy graczy*/
std::vector<karta> stworzVectorWszystkichKart()
{
	std::vector<karta> v;
	for(int i = 0 ; i < 6 ; i++)
	{
		for(int j = 0 ; j < 4 ; j++)
		{
			v.push_back(karta(typKarty(j),numerKarty(i)));
		}
	}
	return v;
}
/*funkcja ktora rozlosowuje karty pomiedzy graczy*/
std::vector<struct client_t*> rozlosujKarty(std::vector<struct client_t*> clientList,std::vector<karta> wszystkieKarty)
{
	srand(time(NULL));
	for(int i = 0 ; 0 < wszystkieKarty.size(); i++)
	{
		if (i%clientList.size() == 0)
			i = 0;
		int losowa = rand() % wszystkieKarty.size();
		clientList.at(i)->kartyGracza.push_back(karta(wszystkieKarty.at(losowa).getTyp(),wszystkieKarty.at(losowa).getNumer()));
		std::vector<karta>::iterator it;
		it = wszystkieKarty.begin();
		it += losowa;
		wszystkieKarty.erase(it);
	}
	return clientList;
}
