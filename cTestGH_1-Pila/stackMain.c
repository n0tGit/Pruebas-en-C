#include "..\head\headGlobal1[v3].h"
#include "stackHead.h"

// n0tEll10T.
/*
    Este código es una mezcla (y modificación) de estos dos:
    https://www.cprogrammingnotes.com/question/dynamic-stack.html
    https://www.geeksforgeeks.org/convert-infix-expression-to-postfix-expression/
*/

int main(void) {
    char valor[64], opcTemp[2];
    char* salidaExpr;
    bool primerVal = true, soloNum = true;
    do {
        puts("\n1. Agregar valor\n2. Eliminar ultimo valor\n3. Ver valores en pila\n4. Vaciar pila\n5. Evaluar expresion\n0. Salir");
        fputs("\nIntroduce una opcion: ", stdout);
        entValorRango(0, 5, 2, opcTemp, 1, 0);
        switch (atoi(opcTemp)) {
            case 1:
                /*
                    Caso 1: Agregar valor.

                    Si no se ha introducido ya un valor
                    (es decir, si primerVal es verdadero),
                    se preguntará al usuario si desea
                    hacer a la pila exclusiva a valores
                    numéricos, o si esta será indiferente
                    a cualquier texto.

                    Si se escribe 1, la variable soloNum
                    será verdadera. Si se escribe 0,
                    será falsa.

                    Una vez hecho esto, primerVal será falso
                    hasta que se vacíe la pila (véase caso 4).
                */
                if (primerVal) {
                    fputs("Escribe 1 si deseas que la pila acepte solo valores numericos, escribe 0 si quieres que acepte cualquier valor: ", stdout);
                    entValorRango(0, 1, 2, opcTemp, 1, 0);
                    switch (atoi(opcTemp)) {
                        case 0:
                            puts("A partir de ahora, se aceptara cualquier valor en la pila.");
                            soloNum = false;
                            break;
                        case 1:
                            puts("A partir de ahora, solo se aceptaran valores numericos (y enteros) en la pila.");
                            soloNum = true;
                            break;
                        default:
                            if (strlen(opcTemp) <= 0) soloNum = false;
                    }
                    primerVal = false;
                }

                /*
                    Es entonces que se le pide al usuario
                    introducir un valor para la pila.

                    Si soloNum es verdadero,
                    se obtendrá el valor a través de
                    entValor, que revisará si la entrada
                    es numérica o no (hay que tener en cuenta
                    que si se introduce un numero y una letra
                    juntos, se tomará como numérica).

                    De lo contrario, se obtiene a través de fgets().
                    Esto último, en un bucle, para evitar que se
                    añadan valores vacíos a la pila.
                    Mientras la longitud de la entrada sea menor (?) o igual
                    a 0, se volverá a pedir el valor.
                    Así mismo, al final del valor introducido, se usa un
                    terminador nulo, para reemplazar el salto de línea
                    escrito por el usuario al dar Enter.

                    Para finalizar, se apila el valor introducido por el usuario.

                    Véase stackFunc.c.
                */
                fputs("Introduce un valor: ", stdout);
                if (soloNum) entValor(4, valor, 1, 1);
                else do {
                    fgets(valor, 64+2, stdin);
                    valor[strcspn(valor, "\n")] = '\0'; // https://stackoverflow.com/a/2693826
                    if (strlen(valor) <= 0) fputs("No puedes introducir un valor vacio. Intenta de nuevo: ", stdout);
                } while(strlen(valor) <= 0);
                apilar(valor);
                printf("Valor \"%s\" apilado.", valor);
                break;
            case 2:
                // Caso 2: Desapilar.
                // Véase stackFunc.c.
                desapilar();
                break;
            case 3:
                // Caso 3: Mostrar valores en pila.
                // Véase stackFunc.c.
                mostrar();
                break;
            case 4:
                /*
                    Caso 4: Vaciar pila.
                    Véase stackFunc.c.
                    Dado a que se está vaciando la
                    pila, primerVal se vuelve falsa
                    en caso de que el usuario desee
                    tomar otra decisión a la hora de
                    introducir valores a la pila.

                    Esto no pasa en el caso 2, ya que,
                    además de que no se revisa si la
                    pila está vacía, es probable que
                    el usuario haya introducido un valor
                    incorrecto de forma accidental.

                    Hacer que primerVal sea falsa en el caso 2
                    probablemente haría tedioso el uso del programa
                    (tal vez más de lo que ya sería).
                */
                vaciarPila();
                primerVal = true;
                break;
            case 5:
                /*
                    Caso 5: Evaluar expresión.
                    Véase caso 1.
                    Al introducir una expresión,
                    se convierte de infija a posfija
                    y es asignada a salidaExpr, la
                    cual será el resultado de la
                    conversión de expresión
                    infija a posfija.

                    Este resultado se muestra al usuario
                    y se libera la memoria utilizada por
                    salidaExpr.

                    Véase stackFunc.c.
                */
                fputs("Introduce una expresion: ", stdout);
                do {
                    fgets(valor, 64+2, stdin);
                    valor[strcspn(valor, "\n")] = '\0'; // https://stackoverflow.com/a/2693826
                    if (strlen(valor) <= 0) fputs("La expresion esta vacia. Intenta de nuevo: ", stdout);
                } while(strlen(valor) <= 0);
                salidaExpr = infijoAPosfijo(valor);
                if (salidaExpr != NULL)
                    printf("Resultado: %s\n", salidaExpr);
                free(salidaExpr);
                break;
            case 0:
                exit(0);
        }
    } while(true);
}