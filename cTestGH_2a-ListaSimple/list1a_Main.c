#include "list1a_Head.h"
#include "..\head\headGlobal1[v3].h"
#include <stdbool.h>
#include <stdio.h>

//ESTE CÓDIGO REQUIERE DOCUMENTACIÓN.

int main(void) {
    char opc[2], valTemp[4], posTemp[4];
    int valor, pos;
    bool primerVal = true;
    struct nodo* lista = NULL;
    do {
        if (primerVal)
            puts("\n1. Crear lista");
        else
            puts("\n1. Agregar a lista\n2. Extraer de lista\n3. Ver lista");
        puts("0. Salir");
        fputs("Introduce una opc.: ", stdout);
        if (primerVal)
            entValorRango(0, 1, 2, opc, 1, 1);
        else
            entValorRango(0, 3, 2, opc, 1, 1);
        switch (atoi(opc)) {
            case 1:
                if (primerVal) {
                    fputs("Introduce un valor: ", stdout);
                    entValor(4, valTemp, 1, 1);
                    valor = atoi(valTemp);
                    if (lista != NULL)
                        lista->dato = valor;
                    else
                        insertarIzq(&lista, valor);
                    //printf("%d\n", valor);
                    printf("Lista creada, valor inicial: %d\n", lista->dato);
                    primerVal = false;
                } else {
                    puts("Agregar:\n1. Al inicio de la lista\n2. Al final de la lista\n3. En pos. de lista");
                    fputs("0. Volver\nIntroduce una opc.: ", stdout);
                    entValorRango(0, 3, 2, opc, 1, 1);
                    if (atoi(opc) == 0)
                        break;
                    if (atoi(opc) == 3) {
                        int j = contarElementos(lista);
                        printf("Introduce un valor del 0 al %d (-1 para cancelar): ", j);
                        entValorRango(-1, j, 4, posTemp, 1, 1);
                        pos = atoi(posTemp);
                        if (pos == -1)
                            break;
                    }
                    fputs("Introduce un valor: ", stdout);
                    entValor(4, valTemp, 1, 1);
                    valor = atoi(valTemp);
                    switch(atoi(opc)) {
                        case 1:
                            insertarIzq(&lista, valor);
                        break;
                        case 2:
                            insertarDer(&lista, valor);
                        break;
                        case 3:
                            insertarPos(&lista, pos, valor);
                        break;
                    }
                    if (estaVacia(lista))
                        primerVal = true;
                    switch (atoi(opc)) {
                        case 1:
                            printf("Valor agregado al inicio de la lista: %d\n", lista->dato);
                        break;
                        case 3:
                            printf("Valor agregado en la pos. %d de la lista: %d\n", pos, valor);
                        break;
                    }
                }
            break;
            case 2:
                if (primerVal) {
                    puts("Primero debes crear una lista.");
                    break;
                } else {
                    puts("Extraer:\n1. Al inicio de la lista\n2. Al final de la lista\n3. En pos. de lista");
                    fputs("0. Volver\nIntroduce una opc.: ", stdout);
                    entValorRango(0, 3, 2, opc, 1, 1);
                    if (atoi(opc) == 0)
                        break;
                    if (atoi(opc) == 3) {
                        int j = contarElementos(lista);
                        printf("Introduce un valor del 0 al %d (-1 para cancelar): ", j);
                        entValorRango(-1, j, 4, posTemp, 1,1);
                        pos = atoi(posTemp);
                        if (pos == -1)
                            break;
                    }
                    valor = atoi(valTemp);
                    switch(atoi(opc)) {
                        case 1:
                            if (extraerIzq(&lista)) {
                                puts("No hay mas elementos en la lista, asignando ultimo valor a 0.");
                                primerVal = true;
                            }
                        break;
                        case 2:
                            if (extraerDer(&lista)) {
                                puts("No hay mas elementos en la lista, asignando ultimo valor a 0.");
                                primerVal = true;
                            }
                        break;
                        case 3:
                            if (extraerPos(&lista, pos)) {
                                puts("No hay mas elementos en la lista, asignando ultimo valor a 0.");
                                primerVal = true;
                            }
                        break;
                    }
                }
            break;
            case 3:
                if (primerVal) {
                    puts("Primero debes crear una lista.");
                    break;
                } else 
                    mostrarLista(lista);
            break;
            case 0:
                exit(0);
        }
    } while(true);
}
