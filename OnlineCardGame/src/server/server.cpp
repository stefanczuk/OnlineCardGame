/**
 * Autor: Kamil Zieliński
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "connection.h"
#include <thread>
#include "log.h"

#define SERVER_TAG "Serwer"

int main(int argc, char **argv)
{
    int socket, http_socket;
    int getC;
    int iluGraczy;
    pthread_t http_thread;
    char haslo[200];

	std::string fileName = (currentDateTime())+".log";

    initFileName(fileName);

    printAndWriteLog(SERVER_TAG, "Podaj haslo zabezpieczajace serwer: ");
    scanf("%99[^\n]",haslo);
    printAndWriteLog(SERVER_TAG, "Podano haslo");
    getC=getchar();
    printAndWriteLog(SERVER_TAG, "Podaj ilosc graczy wymaganych do rozpoczecia rozgrywki: ");
    scanf("%d",&iluGraczy);
    std::string s = std::to_string(iluGraczy);
    char const *pchar = s.c_str();
    printAndWriteLog(SERVER_TAG, pchar);
    getC=getchar();
    if(iluGraczy<2 || iluGraczy>20)
         iluGraczy=3;
    //tworzenie socketu
    printAndWriteLog(SERVER_TAG, "\t\t\t!!!!!!!!!Uruchamiam Serwer!!!!!!!!!!!");
    socket = create_connection();
    //funkcja nasluchujaca
    listen_connections(socket,haslo,iluGraczy);
}


