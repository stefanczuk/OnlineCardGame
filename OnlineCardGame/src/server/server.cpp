/**
 * Autor: Kamil Zieliński
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "connection.h"

int main(int argc, char **argv)
{
    int socket, http_socket;
    int getC;
    int iluGraczy;
    pthread_t http_thread;
    char haslo[200];
    printf("Podaj haslo zabezpieczajace serwer: ");
    scanf("%99[^\n]",haslo);
    getC=getchar();
    printf("Podaj ilosc graczy wymaganych do rozpoczecia rozgrywki: ");
    scanf("%d",&iluGraczy);
    getC=getchar();
    if(iluGraczy<2 || iluGraczy>20)
         iluGraczy=3;
    //tworzenie socketu
    printf("\t\t\t!!!!!!!!!Uruchamiam Serwer!!!!!!!!!!!");
    socket = create_connection();
    //funkcja nasluchujaca
    listen_connections(socket,haslo,iluGraczy);
}
