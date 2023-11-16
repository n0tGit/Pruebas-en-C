#include "stackHead.h"

// n0tEll10T.
/*
    Este código es una mezcla (y modificación) de estos dos:
    https://www.cprogrammingnotes.com/question/dynamic-stack.html
    https://www.geeksforgeeks.org/convert-infix-expression-to-postfix-expression/
*/

struct nodo *cima = NULL;

void apilar(char item[64]) {
    struct nodo *nptr =
        malloc(sizeof(struct nodo));
    strcpy(nptr->data, item);
    nptr->siguiente = cima;
    cima = nptr;
}

void mostrar(void) {
    if (cima == NULL) 
        puts("La pila esta vacia.");
    else {
        int i = 0, j = 0;
        struct nodo *temp;
        temp = cima;
        while (temp != NULL) {
            temp = temp->siguiente;
            i++;
        }
        printf("Valores en pila: %d\n", i);
        temp = cima;
        while (temp != NULL) {
            printf("\"%s\"", temp->data);
            j++;
            if (j < i) printf(", ");
            temp = temp->siguiente;
        }
    }
    puts("");
}

void desapilar(void) {
    if (cima == NULL) 
        puts("La pila esta vacia.");
    else {
        struct nodo *temp;
        temp = cima;
        cima = cima->siguiente;
        printf("\nValor \"%s\" eliminado de la pila.", temp->data);
        free(temp);
    }
}

void vaciarPila(void) {
    if (cima == NULL) 
        puts("La pila ya esta vacia.");
    else {
        struct nodo *temp;
        temp = cima;
        while (temp != NULL) {
            desapilar();
            temp = temp->siguiente;
        }
        puts("\n\nHecho.");
    }
}

int precedencia(char operador) {
    // Se lee el caracter y se determina si coincide
    // con alguno de los operadores debajo.
    switch (operador) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return -1;
    }
}

int esOperador(char expr) {
    return (expr == '+' || expr == '-' || expr == '*' || expr == '/'
            || expr == '^');
}

char* infijoAPosfijo(char* exprIF) {
    int i, j, cimaTemp = -1;
    int numParAb = 0,
        numParCer = 0,
        numLlavAb = 0,
        numLlavCer = 0,
        numCorAb = 0,
        numCorCer = 0;
    int tmTexto = strlen(exprIF);
    char* exprPF =
        (char*)malloc(sizeof(char) * (tmTexto + 2));
    char pila[tmTexto];
    bool //parntAbierto = false,
         //parntCerrado = false,
         parntCompleto = false;
 
    for (i = 0, j = 0; i < tmTexto; i++) {
        if (exprIF[i] == ' ' || exprIF[i] == '\t')
            continue;

        // Si el caracter leido es un operando,
        // este se agregará a la expresión posfija.
        if (isalnum(exprIF[i])) {
            exprPF[j++] = exprIF[i];
        }
       
        /*
            Apilar caracter '('.
            Se aumenta el numero de caracteres leidos.
            Véase en el siguiente caracter qué ocurre
            con este número.
        */
        else if (exprIF[i] == '(') {
            pila[++cimaTemp] = exprIF[i];
            puts("Abriendo parentesis.");
            numParAb++;
        }
       
        /*
            Apilar caracter ')'.
            Al igual que con el caracter '(',
            se aumenta la cantidad de caracteres leidos.
            Si la cantidad de parentesis abiertos
            coincide con la cantidad de parentesis cerrados,
            se determinará que el paréntesis está completo.
            De lo contrario, se determina falso (parntCompleto).
            esto ocurre con las llaves y los corchetes.

            Probablemente una alternativa poco viable (y/o practica),
            pero funciona para revisar las expresiones solicitadas
            en la práctica.

            Véase más abajo para ver qué ocurre con parntCompleto.
        */
        else if (exprIF[i] == ')') {
            while (cimaTemp > -1 && pila[cimaTemp] != '(') {
                exprPF[j++] = pila[cimaTemp--];
            }
            
            puts("Cerrando parentesis.");

            numParCer++;

            if (numParAb == numParCer)
                parntCompleto = true;
            else parntCompleto = false;

            if (parntCompleto) { puts("Parentesis completo."); }
            else { puts("Parentesis incompleto."); }
            
            cimaTemp--;
        }
       
        // Apilar caracter '{'.
        else if (exprIF[i] == '{') {
            pila[++cimaTemp] = exprIF[i];
            puts("Abriendo llave.");
            numLlavAb++;
        }
       
        // Apilar caracter '}'.
        else if (exprIF[i] == '}') {
            while (cimaTemp > -1 && pila[cimaTemp] != '(') {
                exprPF[j++] = pila[cimaTemp--];
            }

            numLlavCer++;
            if (numLlavAb == numLlavCer)
                parntCompleto = true;
            else parntCompleto = false;

            if (parntCompleto) { puts("Llave completa."); }
            else { puts("Llave incompleta."); }
            puts("Cerrando llave.");

            cimaTemp--;
        }
       
        // Apilar caracter '['.
        else if (exprIF[i] == '[') {
            pila[++cimaTemp] = exprIF[i];
            puts("Abriendo corchete.");
            numCorAb++;
        }
       
        // Apilar caracter ']'.
        else if (exprIF[i] == ']') {
            while (cimaTemp > -1 && pila[cimaTemp] != '(') {
                exprPF[j++] = pila[cimaTemp--];
            }
            numCorCer++;
            if (numCorAb == numCorCer) 
                parntCompleto = true;
            else parntCompleto = false;
            if (parntCompleto) { puts("Corchete completo."); }
            else { puts("Corchete incompleto."); }
            puts("Cerrando corchete.");
            
            cimaTemp--;
        }
       
        // Apilar caracter operador.
        else if (esOperador(exprIF[i])) {
            while (cimaTemp > -1
                   && precedencia(pila[cimaTemp])
                          >= precedencia(exprIF[i]))
                exprPF[j++] = pila[cimaTemp--];
            pila[++cimaTemp] = exprIF[i];
        }
    }
 
    /*
        Desapila los elementos restantes.
        Si el caracter de la pila es un parentesis abierto,
        Se determinará como expresión inválida.
        Aún desconozco el por qué es exclusivo a este caracter.
    */
    while (cimaTemp > -1) {
        if (pila[cimaTemp] == '(') {
            puts("Error de sintaxis. Verifica tus parentesis. [1]");
            return 0;
        }
        exprPF[j++] = pila[cimaTemp--];
    }
    /* 
        Si el parentesis no esta completo y el inicio,
        se determinará como expresión inválida.
        Tanto esta condición, como las demás,
        muy probablemente sean condiciones poco prácicas
        para determinar una expresión inválida.
        De nuevo, funciona para las especificadas
        en la práctica.
    */
    if (!parntCompleto && (exprPF[0] >= 0 && exprPF[0] <= 9)) {
        puts("Error de sintaxis. Verifica tus parentesis. [2]");
        return 0;
    }

    /* 
        Si el número de paréntesis abiertos es diferente al
        número de paréntesis cerrados, se determinará
        como expresión inválida; esto aplica también tanto en
        llaves como en corchetes.
    */
    if (numParAb != numParCer) {
        puts("Error de sintaxis. Verifica tus parentesis. [3a]");
        return 0;
    } else if (numLlavAb != numLlavCer) {
        puts("Error de sintaxis. Verifica tus llaves. [3b]");
        return 0;
    } else if (numCorAb != numCorCer) {
        puts("Error de sintaxis. Verifica tus corchetes. [3c]");
        return 0;
    }

    puts("Expresion valida.");

    /*
        Si la expresión por alguna razón está vacía,
        o no tiene valores numéricos, se devuelve un 0.
        Al devolverse un 0, sólo se determina que la expresión
        es válida, en lugar de mostrar un resultado
        posiblemente incorrecto; cabe mencionar que no
        siempre funciona.

        En cualquier otro caso, se devuelve la
        expresión convertida a posfija.
    */
    if (exprPF[0] == '\0' || (exprPF[0] >= '0' && exprPF[0] <= '9'))
        return 0;

    exprPF[j] = '\0';

    return exprPF;
}