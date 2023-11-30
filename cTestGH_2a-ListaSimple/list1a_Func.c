#include "list1a_Head.h"

bool estaVacia(struct nodo* lista) {
    return lista == NULL;
}

void insertarIzq(struct nodo** lista, int valor) {
    struct nodo* nuevo =
        malloc(sizeof(struct nodo));
    if (nuevo == NULL) {
        puts("Memoria excedida. Cerrando programa...");
        exit(1);
    }
    nuevo->dato = valor;
    if (estaVacia(*lista))
        nuevo->siguiente = NULL;
    else
        nuevo->siguiente = (*lista);
    (*lista) = nuevo;
    int j = contarElementos(*lista) + 1;
    if (j > 1)
        printf("Ahora hay %d elementos en la lista.\n", j);
}

void insertarDer(struct nodo** lista, int valor) {
    struct nodo* nuevo =
        malloc(sizeof(struct nodo));
    if (nuevo == NULL) {
        puts("Memoria excedida. Cerrando programa...");
        exit(1);
    }
    nuevo->dato = valor;
    if (estaVacia(*lista)) {
        nuevo->siguiente = NULL;
        (*lista) = nuevo;
    }
    else {
        struct nodo* temp = (*lista);
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
        temp->siguiente->siguiente = NULL;
        printf("Valor agregado al final de la lista: %d\n", temp->siguiente->dato);
    }
    int j = contarElementos(*lista) + 1;
    if (j > 0)
        printf("Ahora hay %d elementos en la lista.\n", j);
}

void insertarPos(struct nodo** lista, int posicion, int valor) {
    int j = contarElementos(*lista);
    struct nodo* nuevo =
        malloc(sizeof(struct nodo));
    if (nuevo == NULL) {
        puts("Memoria excedida. Cerrando programa...");
        exit(1);
    }
    nuevo->dato = valor;
    if (estaVacia(*lista)) 
        puts ("Sin cambios. La lista esta vacia.");
    else {
        if (posicion == 0)
            insertarIzq(lista, valor);
        else {
            struct nodo* temp = (*lista);
            for (int i = 0; i < posicion-1; i++)
                temp = temp->siguiente;
            nuevo->siguiente = temp->siguiente;
            temp->siguiente = nuevo;
        }
    }
    j++;
    if ((j > 0 || !estaVacia(*lista)) && posicion > 0)
        printf("Ahora hay %d elementos en la lista.\n", j+1);
}

bool extraerIzq(struct nodo** lista) {
    if (estaVacia(*lista))
        puts("La lista esta vacia.");
    else {
        struct nodo* temp = (*lista);
        if ((*lista)->siguiente == NULL) {
            printf("Ultimo valor extr. de la lista: %d\n", (*lista)->dato);
            (*lista)->dato = 0;
            free(temp);
            return true;
        }
        else
            (*lista) = (*lista)->siguiente;
        free(temp);
        printf("Valor extr. al inicio de la lista: %d\n", (*lista)->dato);
        if (estaVacia(*lista))
            puts("Esto no deberia de ocurrir.");
        else {
            int j = contarElementos(*lista) + 1;
            if (j > 1)
                printf("Ahora hay %d elementos en la lista.\n", j);
        }
    }
    return false;
}

bool extraerDer(struct nodo** lista) {
    if (estaVacia(*lista))
        puts("La lista esta vacia.");
    else {
        if (contarElementos((*lista)) == 0) {
            printf("Ultimo valor extr. de la lista: %d\n", (*lista)->dato);
            (*lista)->dato = 0;
            return true;
        }
        else {
            struct nodo* temp = (*lista), *prev;
            while (temp->siguiente != NULL) {
                prev = temp;
                temp = temp->siguiente;
            }
            prev->siguiente = NULL;
            printf("Valor extr. al final de la lista: %d\n", temp->dato);
            free(temp);
        }
        if (estaVacia(*lista))
            puts("Esto no deberia de ocurrir.");
        else {
            int j = contarElementos(*lista) + 1;
            //if (j > 1)
                printf("Ahora hay %d elementos en la lista.\n", j);
        }
    }
    return false;
}

bool extraerPos(struct nodo** lista, int posicion) {
    if (estaVacia(*lista)) 
        puts ("Sin cambios. La lista esta vacia.");
    else {
        int j = contarElementos(*lista);
        if (j == 0) {
            (*lista)->dato = 0;
            return true;
        } else {
            puts("1");
            if (posicion == 0) {
                extraerIzq(lista);
                return false;
            }
            else if (posicion == j) {
                extraerDer(lista);
                return false;
            }
            else {
                struct nodo* temp = (*lista), *prev;
                puts("2");
                for (int i = 0; i < posicion-1; i++) {
                    prev = temp;
                    puts("3a");
                    temp = temp->siguiente;
                    puts("3b");
                }
                prev->siguiente = temp->siguiente;
                puts("4");
                printf("Valor extr. en la pos. %d de la lista: %d\n", posicion, temp->siguiente->dato);
                free(temp);
                puts("5");
            }
            j = contarElementos(*lista);
            if ((j > 0 || !estaVacia(*lista)) && posicion > 0)
                printf("Ahora hay %d elementos en la lista.\n", j+1);
        }
    }
    return false;
}

void mostrarLista(struct nodo* lista) {
    struct nodo* temp = lista;
    //printf(" extr. en la pos. %d de la lista: %d\n", pos, valor);
    if (temp == NULL)
        puts("La lista esta vacia.");
    else {
        while (temp != NULL) {
            printf("%d\n", temp->dato);
            temp = temp->siguiente;
        }
        printf("Fin de la lista.\n%d elemento(s) encontrado(s).\n", contarElementos(lista)+1);
    }
}

int contarElementos(struct nodo* lista) {
    struct nodo* temp = lista;
    int i = 0;
    if (temp == NULL)
        puts("La lista esta vacia, cuidado.");
    else {
        while (temp != NULL) {
            //printf("%d\n", temp->dato);
            temp = temp->siguiente;
            i++;
        }
        i--;
    }
    return i;
}
