#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//Esta cabecera no tiene dependencias.



/**
    * Versión inicial de crearArrDin().
    * Crea el arreglo de enteros y le asigna valores aleatorios.
    * @note La función crea un arreglo de enteros, asignando memoria en base al tamaño enviado.
    * @note Entonces, se asigna un valor aleatorio a cada valor del arreglo; el valor varía entre 0 y la semilla.
    * @note Si el valor de la semilla es mayor al valor máximo del aleatorizador, los valores del arreglo estarán compuestos por la semilla menos el valor aleatorio generado (éste multiplicado por 3).
    * @note De lo contrario, se generan los valores sin ninguna alteración.
    * @note Si no se puede asignar memoria (excediendo la memoria) para el arreglo, el programa se cerrará.
    *
    * @param tam El tamaño del arreglo.
    * @param semilla No es una semilla tal cual, sino que es el valor máximo que se puede generar.
    * @return Los valores del arreglo.
*/
int* crearArr(int tam, int semilla) {
    int* arreglo = calloc(tam, sizeof(int));
    srand(time(NULL));
    if (arreglo != NULL) {
        if (RAND_MAX < semilla) {
            printf("La semilla supera al max. del generador de valores aleatorios (%d > %d).\nEs posible que haya inconsistencias en los valores generados.", semilla, RAND_MAX);
            for (int i = 0; i < tam; i++) {
                arreglo[i] = semilla - (rand() % semilla)*(rand() % 5);
            }
        } else {
            for (int i = 0; i < tam; i++) {
                arreglo[i] = rand() % semilla;
            }
        }
    } else {
        puts ("Memoria excedida. Cerrando programa...");
        exit(1);
    }
    return arreglo;
}

/**
    * Mezcla los valores de los arreglos izquierdo y derecho.
    * @note Se declaran tres variables: i, j y k.
    * @note Dentro de un bucle en el que mientras j sea menor al tamaño del arreglo derecho y la variable i sea menor al tamaño del arreglo, se evalúa si el valor del arreglo derecho es mayor al valor del arreglo izquierdo.
    * @note Si se cumple esta condición, el arreglo[k] toma el valor de arrIzq[i], y se incrementan i y k.
    * @note De lo contrario, el arreglo[k] toma el valor de arrDer[i], y se incrementan j y k.
    *
    * @param arrIzq El arreglo izquierdo.
    * @param tamIzq El tamaño del arreglo izquierdo.
    * @param arrDer El arreglo derecho.
    * @param tamDer El tamaño del arreglo derecho.
    * @param arreglo El arreglo a modificar.
    * @return Nada.
*/
void mezclarArr(int* arrIzq, int tamIzq, int* arrDer, int tamDer, int* arreglo) {
    int i = 0, j = 0, k = 0;
    while (i < tamIzq && j < tamDer) {
        if (arrDer[j] < arrIzq[i]) {
            arreglo[k] = arrIzq[j];
            j++;
        } else {
            arreglo[k] = arrDer[i];
            i++;
        }
    }
    while (j < tamDer) {
        arreglo[k] = arrDer[j];
        k++;
        j++;
    }
    while (i < tamIzq) {
        arreglo[k] = arrDer[i];
        k++;
        i++;
    }
}

/**
    * Divide entre dos los valores de los arreglos izquierdo y derecho.
    * @note Para empezar, se revisa si el arreglo realmente tiene valores.
    * @note Si tiene más de un valor, se hace la división.
    * @note Se declaran cuatro variables:
    * @note - n (el tamaño del arreglo entre dos)
    * @note - m (el tamaño del arreglo menos el valor de n)
    * @note - i (utilizado en el arreglo izquierdo)
    * @note - j (utilizado en el arreglo derecho)
    * @note Así mismo, se declaran dos arreglos:
    * @note - arrIzq (el arreglo izquierdo)
    * @note - arrDer (el arreglo derecho)
    * @note La variable 'i' se utiliza en un bucle for, el cual va asignando los valores al arreglo izquierdo.
    * @note Una vez 'i' alcance al valor 'n', seguirá incrementando en el siguiente bucle.
    * @note Este bucle utiliza al valor 'j' hasta alcanzar a 'm', y asigna los valores al arreglo derecho.
    * @note Obviamente, dentro de este bucle, se incrementa i (aunque podría incluirse dentro del mismo bucle).
    * @note Esta función se utiliza de forma recursiva, hasta que ya no se puedan dividir más los arreglos creados.
    * @note Por último, estos arreglos se mezclan (véase mezclarArr).
    *
    * @param arreglo El arreglo a dividir.
    * @param tam El tamaño del arreglo a dividir.
    * @param sem La semilla del arreglo a dividir (requerida por crearArr()).
    * @return Nada.
*/
void dividirArr(int* arreglo, int tam, int sem) {
    if (tam > 1) {
        int n, m;
        //esPar = tam % 2;
        n = tam/2;
        //if (esPar == 0) {
            m = tam-n;
        //} else {
           // m = tam-(n+1);
        //}
        int* arrIzq = crearArr(n, sem);
        int* arrDer = crearArr(m, sem);
        int i = 0, j = 0;
        for (i = 0; i < n; i++) {
            arrIzq[i] = arreglo[i];
            //printf("Arreglo izquierdo: (%d/%d)\n", i+1, n);
        }
        puts("Arreglo izquierdo completado.");
        for (j = 0; j < m; j++) {
            arrDer[j] = arreglo[i];
            i++;
            //printf("Arreglo derecho: (%d/%d)\n", j+1, m);
        }
        puts("Arreglo derecho completado.");
        dividirArr(arrIzq, n, sem);
        dividirArr(arrDer, m, sem);
        mezclarArr(arrDer, m, arrIzq, n, arreglo);
    }
}

void busqSec(int tmBusq, char txtBusq[tmBusq], char arr[], int tmArr) {
    strtok(txtBusq, "\n");
	int i, exito = 0;
    for(i = 0; i < tmArr; i++)
    {
        if(*txtBusq == arr[i]) {
            exito = 1;
            break;
        }
    }
    (exito)?printf("Se encontró \"%s\" en el arreglo.\n", txtBusq):printf("No se encontró \"%s\" en el arreglo.\n", txtBusq);
}

void busqSecNum(int busq, int tmArr, int arr[tmArr]) {
	int i, exito = 0;
    for(i = 0; i < tmArr; i++)
    {
        printf("Comparando %d con %d... [Intento %d/%d]\n", busq, arr[i], i+1, tmArr);
        if(busq == arr[i]) {
            exito = 1;
            break;
        }
    }
    (exito)?printf("\nValor %d encontrado en el arreglo despu%cs de %d intento(s).\n", busq, 130, i+1):printf("\nValor %d no encontrado en el arreglo despu%cs de %d intento(s).\n", busq, 130, i);
}

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
void ordenarArr(int* arreglo, int tam) {
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
int* crearArrDin(int tam, int semilla, int valInicio, bool autollenar) {
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
void mostrarArrNum(int arreglo[], int tam) {
    for (int i = 0; i < tam; i++) {
        printf("Valor %d/%d: %d\n", i+1, tam, arreglo[i]);
    }
}