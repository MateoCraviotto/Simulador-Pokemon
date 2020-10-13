#include "evento_pesca.h"
#include <stdlib.h>
#include <stdbool.h>
#define LECTURA "r"
const int SIN_POKEMONES = 0;
const int LEIDOS_ESPERADOS = 4;
#define FORMATO_LECTURA_ARRECIFE "%[^;];%i;%i;%[^\n]\n"
const int ERROR = -1;
const int EXITO = 0;

/*
* Pre: El archivo debe estar abierto en modo LECTURA. El vector de pokemones 
	no debe estar inicializado.
* Post: Lee los pokemones del archivo, con el formato FORMATO_LECTURA_ARRECIFE, 
	y los almacena  en el vector recibido. Devuelve la cantidad de pokemones leidos 
	y almacenados en el vector. Si no pudo leer ninguno, devuelve 0.

	(*arrecife).pokemon[i].especie, 
		&((*arrecife).pokemon[i].velocidad), &((*arrecife).pokemon[i].peso), (*arrecife).pokemon[i].color);

*/
int leer_pokemones(FILE* archivo, arrecife_t* arrecife) {

	pokemon_t p;

	int i = 0;
	int leidos = fscanf(archivo, FORMATO_LECTURA_ARRECIFE, p.especie, &(p.velocidad), (&p.peso), p.color);
	
	pokemon_t* pokemon_aux;
	pokemon_aux = realloc((*arrecife).pokemon, sizeof(pokemon_t)*((size_t)i+1));
	if (pokemon_aux == NULL)
		return i;

	(*arrecife).pokemon = pokemon_aux;
	
	bool realloc_exitoso = true;

	while (leidos == LEIDOS_ESPERADOS && realloc_exitoso) {
		(*arrecife).pokemon[i] = p;
		i++;
		pokemon_aux = realloc(pokemon_aux, sizeof(pokemon_t)*((size_t)i+1));

		if (pokemon_aux != NULL) {
			
			leidos = fscanf(archivo, FORMATO_LECTURA_ARRECIFE, p.especie, &(p.velocidad), (&p.peso), p.color);

			(*arrecife).pokemon = pokemon_aux;
		} else {
			realloc_exitoso = false;
		}
	}

	if(i > 0 && realloc_exitoso)
		(*arrecife).pokemon = pokemon_aux;

	printf("Hay %i pokemones antes.\n", i);
	return i;
}

/*
* Pre: El vector de pokemones debe estar inicializado con pokemones. El 
	arrecife debe tener su cantidad de pokemones inicializada con un valor
	válido.
* Post: Guarda los pokemones del vector en el arrecife recibido.

void guardar_pokemones_en_arrecife(arrecife_t* arrecife, pokemon_t pokemones[]) {
	for (int i = 0; i < (*arrecife).cantidad_pokemon; i++) {
		(*arrecife).pokemon[i] = pokemones[i];
	}
}
*/
// FUNCIÓN PÚBLICA
arrecife_t* crear_arrecife(const char* ruta_archivo) {

	FILE* archivo = fopen(ruta_archivo, LECTURA);

	if (archivo == NULL) {
		printf("No se ha podido abrir el archivo.\n");
		return NULL;
	}

	arrecife_t* p_arrecife = malloc(sizeof(arrecife_t));
	if (p_arrecife == NULL) {
		fclose(archivo);
		printf("No se ha podido asignar memoria para el arrecife.\n");
		return NULL;
	}

	(*p_arrecife).pokemon = NULL;
	(*p_arrecife).cantidad_pokemon = 0;

	(*p_arrecife).cantidad_pokemon = leer_pokemones(archivo, p_arrecife);
	if ((*p_arrecife).cantidad_pokemon == SIN_POKEMONES) {
		fclose(archivo);
		printf("No se ha podido leer pokemones.\n");
		return NULL;
	}

	//guardar_pokemones_en_arrecife(p_arrecife, pokemones);

	fclose(archivo);

	return p_arrecife;
}



//FUNCIÓN PÚBLICA
acuario_t* crear_acuario() {

	acuario_t* acuario = malloc(sizeof(acuario_t));
	if (acuario == NULL) 
		return NULL;

	(*acuario).pokemon = NULL;
	(*acuario).cantidad_pokemon = 0;

	return acuario;
}

/*
* Pre:
* Post:
*/
bool hay_pokemones_suficientes(arrecife_t* arrecife, bool (*seleccionar_pokemon) (pokemon_t*), 
	int cant_seleccion, int posiciones_pokemones[]) {

	int i = 0;
	int j = 0;
	while(i < cant_seleccion && j < (*arrecife).cantidad_pokemon) {
		if ( seleccionar_pokemon(&((*arrecife).pokemon[j])) ) {
			posiciones_pokemones[i] = j;
			i++;
		}
		j++;
	}
	return (i >= cant_seleccion);
}

/*
* Pre: El arrecife y el acuario deben estar inicializados y ser válidos. "pos" representa
	la posición del pokemon en el arrecife que se quiere mover.
* Post: Mueve el pokemon de la posición del arrecife recibida al acuario. Si lo logra, devuelve
	true. En caso de error, devuelve false.
*/
bool mover_pokemon(arrecife_t* arrecife, acuario_t* acuario, int pos) {
	pokemon_t* pokemon_aux;
	bool pokemon_movido = false;
	
	// Copio el pokemon "i" buscado del arrecife al acuario.
	(*acuario).pokemon[(*acuario).cantidad_pokemon] = (*arrecife).pokemon[pos];
	// Aumento la cantidad de pokemones del acuario, ya que añadí uno.
	(*acuario).cantidad_pokemon++;

	// Copio el último pokemon del arrecife a la posición que ya moví, y achico el arrecife en uno.
	(*arrecife).pokemon[pos] = (*arrecife).pokemon[((*arrecife).cantidad_pokemon)-1];

	// Achico el vector de pokemones del arrecife.
	pokemon_aux = realloc((*arrecife).pokemon, sizeof(pokemon_t)*(size_t)((*arrecife).cantidad_pokemon-1));

	if (pokemon_aux != NULL) {
		pokemon_movido = true;
		// Actualizo la dirección de memoria del arrecife en caso de que haya cambiado.
		(*arrecife).pokemon = pokemon_aux;
		// Disminuyo la cantidad de pokemones del arrecife, ya que moví uno.
		(*arrecife).cantidad_pokemon--;
	}
	return pokemon_movido;
}


// FUNCIÓN PÚBLICA
int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, 
	bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion) {

	int posiciones_buscadas[cant_seleccion];

	bool hay_suficientes = hay_pokemones_suficientes(arrecife, seleccionar_pokemon, cant_seleccion, posiciones_buscadas);
	if (!hay_suficientes)
		return ERROR; ///////////// que devuelvo???? 0 o -1?

	size_t i = 0;
	bool operacion_exitosa = true;
	pokemon_t* pokemon_aux;
	while(i < cant_seleccion && operacion_exitosa) {
	
		pokemon_aux = realloc((*acuario).pokemon, sizeof(pokemon_t)*(size_t)((*acuario).cantidad_pokemon+1));
		if (pokemon_aux == NULL) {
			operacion_exitosa = false;
		} else {
			// Actualizo la dirección de memoria del acuario en caso de que haya cambiado.
			(*acuario).pokemon = pokemon_aux;

			operacion_exitosa = mover_pokemon(arrecife, acuario, posiciones_buscadas[i]);
			// Aummento el iterador de pokemones buscados.
			i++;
		}
	}

	if (!operacion_exitosa)
		return ERROR;

	return EXITO;
}
