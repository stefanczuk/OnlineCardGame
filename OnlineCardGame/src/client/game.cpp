/**
 * Autor: Mateusz Skolimowski
 * 
 * W tym pliku beda znajdowac sie wszystkie funkcje ktore sluza do obslugi gry od strony gracza.
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

bool czyTenSamString(char *b, std::string b2)
{
	int size;
	//printf("size of b = %d\n",sizeof(b));
	//printf("length of b2 = %d\n",b2.length());
	if(sizeof(b) <= b2.length())
		size = sizeof(b);
	else
		size = b2.length();
	//printf("size : %d\n",size);
	for(int  i = 0 ; i < size ; i++)
	{
		//printf("b[%d] = %c , b2[%d] = %c\n",i,b[i],i,b2[i]);
		if(b[i] != b2[i])
			return false;
	}
	return true;
}

void game(int &sock)
{
	char bufor[1024];
	while(1)
  	{
		bzero(bufor,sizeof(bufor));
  		if(( recv( sock, bufor, sizeof( bufor ), 0 ) ) <= 0 )
  		{
   	  	    perror( "Blad recv\n" );
    		    exit( - 1 );
  		}
  		printf("Server: %s \n", bufor );
		if (czyTenSamString(bufor,"test"))
		{
			printf("TESTUJE\n");
		}
		else if (czyTenSamString(bufor,"wykonaj ruch"))
		{
			printf("Twoja kolej aby wykonac ruch\n");
			write(sock,"test ruch",9);
			//pokaz karty jakie sa na stole i jakie ma na rece gracz
			//tutaj dodac write z odpowiedzia jaki chce wykonac ruch
		}
		else if (czyTenSamString(bufor,"bledny ruch"))
		{
			printf("Ruch ktory chcesz wykonac jest niepoprawny. Wykonaj inny\n");
			//pokaz karty jakie sa na stole i jakie ma na rece gracz
			//tutaj dodac write z odpowiedzia jaki chce wykonac ruch
		}
		else if (czyTenSamString(bufor,"inny gracz wykonal ruch"))
		{
			printf("Gracz wykonal ruch\n");//dodac jaki to gracz
			//pokaz karty jakie sa na stole
		}
  	}
}

