#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// n0tEll10T.

struct nodo
{
    char data[64];
    struct nodo *siguiente;
};

void mostrar(void);
void apilar(char[64]);
void desapilar(void);
void vaciarPila(void);

int precedencia(char);
int esOperador(char);
char* infijoAPosfijo(char*);
