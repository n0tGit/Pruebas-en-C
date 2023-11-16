#include <String.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

/**
    * Esta función aún requiere análisis y correcciones.
    *  |(<- Eliminar desde aquí si no es así) Descripción del código.
    * @note Esta es una plantilla de decorador.
    * @note - Lista sin orden 1
    * @note - Lista sin orden 2
    * @note - Lista sin orden 3
    * @note - Lista sin orden 4
    * @note Más notas.
	* @note Texto.
	* @note Texto.
    * 
    * @param <param1> Descripción de param1.
    * @param <param2> Descripción de param2.
    * @param <param3> Descripción de param3.
    * @param <param4> Descripción de param4.
    * @return Valor que devuelve la función.
*/
// Texto.

/**
    * Elimina caracteres que no sean alfanuméricos.
	*  | ESTA FUNCIÓN BORRA PUNTOS; para borrar sólo espacios y puntos adicionales, véase borrarEspPunto.
    * @note Primero se declara el arreglo de salida (output) como la entrada (input).
    * @note Después, inicia un bucle en el que se lee, caracter por caracter, la entrada.
    * @note Si el caracter leído es alfanumérico, éste se escribe en la salida.
    * @note De lo contrario, el caracter es descartado.
	* @note Por ejemplo: se tiene la entrada "!123ábc".
	* @note Los caracteres descartados son "!" y "á".
    * @param input El texto a limpiar.
    * @return La misma entrada, libre de caracteres no alfanuméricos.
*/
char* borrarEspeciales(char* input) {
	char *output = input;
	int i, j;
	for(i = 0, j = 0; i < (int)strlen(input); i++, j++) {
		if (isalnum(input[i])) {
			output[j] = input[i];
		} else { j--; }
	}
	output[j] = 0;
	return output;
} // https://stackoverflow.com/a/15444641

char* borrarEspPunto(char* input, bool esEntero, bool mostrarTxt) {
	int i, j, k = 0, l = 0;
	char *output = input;
	char aviso[128] = "";
	for (i = 0, j = 0; i < (int)strlen(input); i++, j++) {
		if (input[i] != ' ') { output[j] = input[i]; }
		else { j--; }
		if (input[i] == ' ') { l++; }
	} // https://stackoverflow.com/a/13084362
	if (!esEntero) {
		for (i = 0, j = 0; i < (int)strlen(input); i++, j++) {
			if (input[i] != '.') {
				if (k < 1) { k++; }
				if (k == 1) { output[j] = input[i]; }
				else { j--; }
			}
		}
	}
	if (mostrarTxt) {
		if (l > 0 || k > 0) {
			strcpy(aviso, "Se detectaron ");
			if (l > 0) {
				strcat(aviso, "espacios ");
				if (k > 0) {
					strcat(aviso, "y ");
				}
			}
			if (k > 0) {
				strcat(aviso, "puntos adicionales ");
			}
			strcat(aviso, "y fueron removidos para leer correctamente el valor introducido.");
		}
		printf("%s\n", aviso);
	}
	output[j]=0;
	return output;
} 

/**
    * Esta función aún requiere análisis y correcciones.
    *  | Revisa el valor enviado por entValor.
    * @note Si esEntero es verdadero, se revisan las siguientes condiciones:
    * @note - El valor es numérico.
    * @note - El valor es 0.
    * @note - El valor es es menor a 0.
    * @note - El valor contiene un punto, el cual podría determinar que se introdujo un valor decimal.
    * @note Si esEntero es falso, se revisan las mismas condiciones, a excepción de si contiene un punto, pues se implica que el valor es real.
	* @note Si valorNeg es falso, se revisa que la entrada no sea un número negativo.
	* @note Asímismo, se eliminan espacios y puntos adicionales, mas no elimina caracteres especiales. (Véase borrarEspPunto())
	* @note El salto de línea introducido por el usuario también es eliminado.
	* @note Esta función acepta valores nulos.
    * 
    * @param tmTexto El tamaño del texto a revisar.
    * @param texto El texto a revisar.
    * @param esEntero Si el valor a revisar es entero o no.
    * @param valorNeg Si el valor a revisar puede ser negativo o no.
    * @return Verdadero o falso (véase entValor).
*/
int revisarValor(int tmTexto, char texto[tmTexto], bool esEntero, bool valorNeg) {
	errno = 0;
    char *pEnd = NULL;
	bool err0 = false;
	borrarEspPunto(texto, esEntero, 1);
	strtok(texto,"\n");

	if (esEntero && !strtol(texto, &pEnd, 10)) {
		if (atoi(texto) == 0) {
			err0 = false;
		} else {
			err0 = true;
			fputs("No se introdujo un valor entero.", stdout);
		}
	}

	if (esEntero && strtol(texto, &pEnd, 10)) {
		if (!valorNeg && atoi(texto) < 0) {
			err0 = true;
			fputs("No se aceptan valores negativos.", stdout);
		}
        if (strstr(".", texto)) {
			err0 = true;
		}
	}

	if (!esEntero && !strtof(texto, &pEnd)) {
		err0 = true;
		fputs("No se introdujo un valor decimal.", stdout);
	}

	if (!esEntero && strtol(texto, &pEnd, 10) == 0) {
		err0 = false;
	}

	if (!esEntero && strtof(texto, &pEnd)) {
		if (!valorNeg && strtof(texto, &pEnd) < 0) {
			err0 = true;
			fputs("No se aceptan valores negativos.", stdout);
		} else { err0 = false; }
	}

	if (texto == pEnd) {
		fputs("El valor introducido no es numerico.", stdout);
		err0 = true;
	}

	return err0;
}

/**
    * Esta función aún requiere análisis y correcciones.
    *  | Lee el valor introducido por el usuario. Véase notas.
    * @note esEntero no es muy relevante en esta función. Si es verdadero, el texto tDato se cambia a "entero", si es falso, se cambia a "decimal".
    * @note Se lee el valor introducido por el usuario.
    * @note Luego, se remueve el salto de línea introducido.
    * @note Después, se evalúa si el valor es numérico (véase revisarValor).
    * @note (Depuración) Se muestra el valor introducido (%s) seguido del valor de err0 (%d, 0/1). Esta función está comentada.
    * @note Si revisarValor devuelve 1, el usuario estará dentro de un bucle, en el cual se le pedirá un valor numérico.
    * @note No se saldrá de este bucle hasta que se introduzca un valor numérico, que a su vez cumpla con lo requerido por revisarValor.
    * @note Entre lo requerido, se encuentra la positividad del valor introducido, o que éste no sea decimal.
    * 
    * @param tmTexto El tamaño del texto a leer.
    * @param texto El texto a leer.
    * @param esEntero Si el valor leído es entero o no.
    * @return Nada. Véase notas.
*/
void entValor(int tmTexto, char texto[tmTexto+2], bool esEntero, bool valorNeg) {
	errno = 0;
	bool err0 = false;
	fgets(texto, sizeof(char *), stdin);
	texto[strcspn(texto, "\n")] = '\0';
	err0 = revisarValor(strlen(texto), texto, esEntero, valorNeg);
	//printf("[%s, %d]\n", texto, err0); //[Entrada, Error(0/1)]
    while (err0) {
		//printf("[%d]\n", err0);
		fputs(" Intenta de nuevo: ", stdout);
        fgets(texto, sizeof(char *), stdin);
		texto[strcspn(texto, "\n")] = '\0';
		err0 = revisarValor(strlen(texto), texto, esEntero, valorNeg);
    }
}

void entValorRango(int min, int max, int tmTexto, char texto[tmTexto+2], bool esEntero, bool valorNeg) {
	entValor(tmTexto, texto, esEntero, valorNeg);
	while (atoi(texto) < min || atoi(texto) > max) {
		printf("No se introdujo un valor del %d al %d. Intenta de nuevo: ", min, max);
		entValor(tmTexto, texto, esEntero, valorNeg);
	}
}