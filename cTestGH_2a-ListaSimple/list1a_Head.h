#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct nodo {
    int dato;
    struct nodo* siguiente;
};

bool estaVacia(struct nodo*);
void insertarIzq(struct nodo**, int);
void insertarDer(struct nodo**, int);
void insertarPos(struct nodo**, int, int);
bool extraerIzq(struct nodo**);
bool extraerDer(struct nodo**);
bool extraerPos(struct nodo**, int);
void mostrarLista(struct nodo*);
int contarElementos(struct nodo*);
