#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//NECESITAS INCLUIR LAS BIBLIOTECAS REQUERIDAS PARA ESTA CABECERA.
/*
    Estas incluyen:
    - <math.h>
    - <time.h>
    - <stdio.h>
    - <stdlib.h>
    - <stdbool.h> (REQUIERE REVISIÓN DE CÓDIGO, PODRÍA DESCARTARSE)
*/
//NO INCLUYAS ESTAS BIBLIOTECAS EN EL PROGRAMA DONDE SE UTILICE ESTA CABECERA.

/**
    * Ordena los valores del arreglo de menor a mayor.
    * @note Una variable auxiliar se crea para poder almacenar valores de forma temporal.
    * @note En un bucle anidado, el valor auxiliar guarda el valor de arreglo[i].
    * @note Luego, redeclara el valor de arreglo[i] al valor de arreglo[j].
    * @note Y por último, el valor auxiliar se utiliza para redeclarar al valor de arreglo[j].
    *
    * @param arreglo El arreglo a ordenar.
    * @param tam El tamaño del arreglo.
    * @return Nada.
*/
void ordenarArr(long* arreglo, int tam) {
    int aux = 0;
    for (int i = 0; i < tam; i++) {
        for (int j = i+1; j < tam; j++) {
            if (arreglo[i] > arreglo[j]) {
                aux = arreglo[i];
                arreglo[i] = arreglo[j];
                arreglo[j] = aux;
            }
        }
    }
}

/**
    * Crea el arreglo de enteros y le asigna valores aleatorios.
    * @note La función crea un arreglo de enteros, asignando memoria en base al tamaño enviado.
    * @note Entonces, se asigna un valor aleatorio a cada valor del arreglo; el valor varía entre 0 y la semilla.
    * @note Si el valor de la semilla es mayor al valor máximo del aleatorizador, los valores del arreglo estarán compuestos por la semilla menos el valor aleatorio generado (éste multiplicado por 3).
    * @note De lo contrario, se generan los valores sin ninguna alteración.
    * @note Si no se puede asignar memoria (excediendo la memoria) para el arreglo, el programa se cerrará.
    * @note SI SE VA A AUTOLLENAR TODO EL ARREGLO, CONFIGURAR valInicio A 0.
    * @note
    * @note Ejemplo: Se tiene un arreglo de tamaño 5.
    * @note a. Si se quiere llenar el arreglo 
    *
    * @param tam El tamaño del arreglo.
    * @param semilla No es una semilla tal cual, sino que es el valor máximo que se puede generar.
    * @param valInicio El valor inicial del arreglo. Si se va a llenar al arreglo de forma automática, dejar en cero.
    * @param autollenar Si se asignarán o no valores al arreglo de forma automática; esto sirve en caso de que se le dé la opción al usuario de llenar el arreglo de forma manual.
    * @return Los valores del arreglo.
*/
int* crearArrNum(int tam, int semilla, int valInicio, bool autollenar) {
    int* arreglo = calloc(tam, sizeof(int));
    srand(time(NULL));
    if (arreglo != NULL) {
        if (autollenar) {
            if (RAND_MAX < semilla) {
                printf("La semilla supera al max. del generador de valores aleatorios (%d > %d).\nEs posible que haya inconsistencias en los valores generados.", semilla, RAND_MAX);
                for (int i = valInicio; i < tam; i++) {
                    arreglo[i] = semilla - (rand() % semilla)*3;
                }
            } else {
                for (int i = 0; i < tam; i++) {
                    arreglo[i] = rand() % semilla;
                }
            }
        }
    } else {
        puts ("Memoria excedida. Cerrando programa...");
        exit(1);
    }
    return arreglo;
}

/**
    * @param arreglo El arreglo a destruir.
    * @return Nada.
*/
void liberarMemNum(int* arreglo) { free(arreglo); }

/**
    * Muestra los valores del arreglo en un bucle.
    * @note La función crea un arreglo de enteros, asignando memoria en base al tamaño enviado.
    * @note Entonces, se asigna un valor aleatorio a cada valor del arreglo; el valor varía entre 0 y 100 (a verificar).
    * @note Si no se puede asignar memoria (excediendo la memoria) para el arreglo, el programa se cerrará.
    *
    * @param arreglo El arreglo a mostrar.
    * @param tam El tamaño del arreglo.
    * @return Nada.
*/
void mostrarArr(char arreglo[], int tam) {
    for (int i = 0; i < tam; i++) {
        printf("Valor %d/%d: %s\n", i+1, tam, arreglo[i]);
    }
}