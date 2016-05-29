/**
 * Autor: Mateusz Skolimowski
 * 
 * W tym pliku beda znajdowac sie wszystkie funkcje ktore sluza do obslugi chatu od strony gracza.
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
#include <time.h>
#include "game.h"
#include <cstring>
#include <string>
#include <iostream>
#include <thread>

void wybor(int &sock)
{
	printf("wybierz co chcesz robic\n");
	printf("1. czat\n");
	printf("2. komentowanie historycznych rozgrywek\n");
	printf("3. zakoncz\n");
	std::string s;
	std::getline(std::cin,s);
	write(sock,s.c_str(),s.length());
}	

void nasluchuj(int sock, bool &czyKoniec)
{
	char bufor[1024];
	while(!czyKoniec)
	{
		bzero(bufor,sizeof(bufor));
  		if(( recv( sock, bufor, sizeof( bufor ), 0 ) ) <= 0 )
  		{
   	  	    perror( "Blad recv\n" );
    		    exit( - 1 );
  		}
		if(std::string("exit").compare(bufor) == 0)
		{
			czyKoniec = true;
		}
		else
			printf("serwer : %s\n",bufor);
	}
}

void czatuj(int &sock)
{
	bool czyKoniec = false;
	std::thread t(nasluchuj,sock,std::ref(czyKoniec));
	printf("co chcsz napisac?\n");
	while(!czyKoniec)
	{	
		std::string s;
		std::getline(std::cin,s);
		write(sock,s.c_str(),s.length());
		if(s.compare("exit") == 0)
			break;
	}
	t.join();
}

void czatKomentowanieHistorycznych(int &sock)
{
	char bufor[1024];
	bool czyKoniecGry = false;
	while(!czyKoniecGry)
  	{
		bzero(bufor,sizeof(bufor));
  		if(( recv( sock, bufor, sizeof( bufor ), 0 ) ) <= 0 )
  		{
   	  	    perror( "Blad recv\n" );
    		    exit( - 1 );
  		}
		if(std::string("wybor").compare(bufor) == 0)
		{
			wybor(sock);
		}
		else if(std::string("czatuj").compare(bufor) == 0)
		{
			printf("bedziesz czatowac\n");
			czatuj(sock);
		}
		else if(std::string("koniec").compare(bufor) == 0)
		{
			czyKoniecGry = true;
		}
	}
}

