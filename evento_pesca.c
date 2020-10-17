#include "evento_pesca.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define LECTURA "r"
#define ESCRITURA "w"
const int SIN_POKEMONES = 0;
const int LEIDOS_ESPERADOS = 4;
#define FORMATO_LECTURA_ARRECIFE "%[^;];%i;%i;%[^\n]\n"
#define FORMATO_ESCRITURA_ACUARIO "%s;%i;%i;%s\n"

#define SEPARADOR_EXTENSION '.'

const int ERROR = -1; //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int EXITO = 0;
const int UN_POKEMON = 1;

/*
* Pre: El archivo debe estar abierto en modo LECTURA y ser de texto. El vector 
	de pokemones no debe estar inicializado.
* Post: Lee los pokemones del archivo, con el formato FORMATO_LECTURA_ARRECIFE, 
	y los almacena  en el vector recibido. Devuelve la cantidad de pokemones leidos 
	y almacenados en el vector. Si no pudo leer ninguno, devuelve 0.
*/
int leer_pokemones(FILE* archivo, arrecife_t* arrecife) {

	pokemon_t p; // Variable de lectura auxiliar

	int i = 0;
	int leidos = fscanf(archivo, FORMATO_LECTURA_ARRECIFE, p.especie, &(p.velocidad), (&p.peso), p.color);

	pokemon_t* pokemon_aux; // Variable auxiliar para reallocs
	pokemon_aux = realloc((*arrecife).pokemon, sizeof(pokemon_t)*((size_t)i+1));
	if (pokemon_aux == NULL)
		return i;
	// El realloc salió bien, actualizo la dirección de memoria.
	(*arrecife).pokemon = pokemon_aux;
	
	bool realloc_exitoso = true;
	while (leidos == LEIDOS_ESPERADOS && realloc_exitoso) {
		
		// Asigno el pokemon leído al vector de pokemones.
		(*arrecife).pokemon[i] = p;
		i++;

		// Guardo memoria para el siguiente pokemon.
		pokemon_aux = realloc(pokemon_aux, sizeof(pokemon_t)*((size_t)i+1));
		if (pokemon_aux != NULL) {
			// Como pude guardar memoria, leo de nuevo y lo guardo en la variable auxiliar. 	
			leidos = fscanf(archivo, FORMATO_LECTURA_ARRECIFE, p.especie, &(p.velocidad), (&p.peso), p.color);
			// El realloc salió bien, actualizo la dirección de memoria.
			(*arrecife).pokemon = pokemon_aux;
		} else {
			realloc_exitoso = false;
		}
	}
	// Si salió con los realloc bien hechos, y más de un pokemon leído
	if(i > 0 && realloc_exitoso)
		(*arrecife).pokemon = pokemon_aux; // actualizo la dirección de memoria.

	printf("Hay %i pokemones antes.\n", i);////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return i;
}

/*
* Pre: La ruta debe tener extensión (tener un punto '.' que
	separe la ruta de la extensión).
* Post: Devuelve true si la ruta recibida corresponde a un archivo
	de texto .txt, sino, devuelve false.
*/
bool es_archivo_txt(const char* ruta) {
	while((*ruta) != SEPARADOR_EXTENSION) {
		ruta++;
	}
	return (strcmp(ruta, ".txt") == 0);
}

/*
* Pre: -
* Post: Inicializa el arrecife recibido con los valores por defecto.
*/
void inicializar_arrecife(arrecife_t* arrecife) {
	(*arrecife).pokemon = NULL;
	(*arrecife).cantidad_pokemon = SIN_POKEMONES;
}

// FUNCIÓN PÚBLICA
arrecife_t* crear_arrecife(const char* ruta_archivo) {
	// Chequeo que el archivo sea .txt
	if (!es_archivo_txt(ruta_archivo)) {
		printf("Ese formato de archivo es inválido. El archivo debe ser un .txt\n");
		return NULL;
	}

	FILE* archivo = fopen(ruta_archivo, LECTURA);
	// Chequeo la correcta apertura del archivo.
	if (archivo == NULL) {
		printf("No se ha podido abrir el archivo.\n");
		return NULL;
	}

	arrecife_t* p_arrecife = malloc(sizeof(arrecife_t));
	// Chequeo que se haya reservado memoria para el arrecife correctamente.
	if (p_arrecife == NULL) {
		fclose(archivo);
		printf("No se ha podido asignar memoria para el arrecife.\n");
		return NULL;
	}

	inicializar_arrecife(p_arrecife);

	(*p_arrecife).cantidad_pokemon = leer_pokemones(archivo, p_arrecife);
	if ((*p_arrecife).cantidad_pokemon == SIN_POKEMONES) {
		liberar_arrecife(p_arrecife);//////////////////////////////////////////////////////////////////////////////////////////
		fclose(archivo);
		printf("No se ha podido leer pokemones.\n");
		return NULL;
	}

	fclose(archivo);

	return p_arrecife;
}

/*
* Pre: -
* Post: Inicializa el arrecife recibido con los valores por defecto.
*/
void inicializar_acuario(acuario_t* acuario) {
	(*acuario).pokemon = NULL;
	(*acuario).cantidad_pokemon = SIN_POKEMONES;
}

//FUNCIÓN PÚBLICA
acuario_t* crear_acuario() {

	acuario_t* acuario = malloc(sizeof(acuario_t));
	if (acuario == NULL) 
		return NULL;
	inicializar_acuario(acuario);


	return acuario;
}

/*
* Pre: ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	la posición del pokemon en el arrecife que se quiere mover.////////////////////////////////////////////////////////////////////////////////////////////////////////
* Post: Mueve el pokemon de la posición del arrecife recibida al acuario. Si lo logra, devuelve/////////////////////////////////////////////////////////////////
	true. En caso de error, devuelve false.
*/
bool mover_pokemon(arrecife_t* arrecife, acuario_t* acuario, int pos) {
	pokemon_t* pokemon_aux;
	bool pokemon_movido = false;

	// Copio el pokemon "i" buscado del arrecife al acuario.
	(*acuario).pokemon[(*acuario).cantidad_pokemon] = (*arrecife).pokemon[pos];

	// Aumento la cantidad de pokemones del acuario, ya que añadí uno.
	(*acuario).cantidad_pokemon++;

	// Copio el pokemon de la última posición del arrecife, a la posición que ya moví al acuario.
	(*arrecife).pokemon[pos] = (*arrecife).pokemon[((*arrecife).cantidad_pokemon)-1];

	// Achico el vector de pokemones del arrecife.
	pokemon_aux = realloc((*arrecife).pokemon, sizeof(pokemon_t)*(size_t)((*arrecife).cantidad_pokemon-1));

	// Cuando mueva el último, voy a hacer un realloc de 0 (un free), que me va a devolver NULL. En ese caso no resta la cantidad
	// de pokemones del arrecife ni se toma el pokemon como movido. Por eso contemplo el caso en el que quede un pokemon.
	if (pokemon_aux != NULL || (*arrecife).cantidad_pokemon == UN_POKEMON) {
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
		return ERROR;

	int i = (cant_seleccion-1);
	bool operacion_exitosa = true;
	pokemon_t* pokemon_aux;
	while(i >= 0 && operacion_exitosa) {
		// Guardo espacio en memoria para un pokemon más de los que ya hay.
		pokemon_aux = realloc((*acuario).pokemon, sizeof(pokemon_t)*(size_t)((*acuario).cantidad_pokemon+1));
		if (pokemon_aux == NULL) {
			operacion_exitosa = false;
		} else {
			// Actualizo la dirección de memoria del acuario en caso de que haya cambiado.
			(*acuario).pokemon = pokemon_aux;
			// Muevo el pokemon al acuario.
			operacion_exitosa = mover_pokemon(arrecife, acuario, posiciones_buscadas[i]);
			// Aummento el iterador de pokemones buscados.
			i--;
		}
	}
	if (!operacion_exitosa)
		return ERROR;

	return EXITO;
}

// FUNCIÓN PÚBLICA
void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)) {
	if ((*arrecife).cantidad_pokemon == SIN_POKEMONES) {
		printf("\nNo quedan más pokemones en el arrecife! No se pudieron preservar las especies.\n");
	} else {
		printf("Hay %i pokemon(es).\n\n", (*arrecife).cantidad_pokemon);
		printf("\tEspecie\t         Velocidad\tPeso\t\tColor");
		printf("\n\n");
		for (int i = 0; i < (*arrecife).cantidad_pokemon; i++) {
			mostrar_pokemon(&((*arrecife).pokemon[i]));
		}
	}
}

/*
* Pre: El archivo debe estar abierto en modo ESCRITURA y ser de texto. El vector de 
	pokemones debe ser válido, con todas sus estructuras válidas. La cantidad debe
	ser > 0.
* Post: Escribe en el archivo de texto recibido los pokemones con el formato 
	FORMATO_ESCRITURA_ACUARIO. Escribe según la cantidad recibida.
*/
void escribir_pokemones(FILE* archivo, pokemon_t pokemones[], int cantidad_pokemones) {
	for (int i = 0; i < cantidad_pokemones; i++) {
		fprintf(archivo, FORMATO_ESCRITURA_ACUARIO, pokemones[i].especie, pokemones[i].velocidad, 
			pokemones[i].peso, pokemones[i].color);
	}
}


// FUNCIÓN PÚBLICA
int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo) {
	
	FILE* archivo = fopen(nombre_archivo, ESCRITURA);

	if(archivo == NULL) {
		return ERROR;
	}
	escribir_pokemones(archivo, (*acuario).pokemon, (*acuario).cantidad_pokemon);

	fclose(archivo);

	return EXITO;
}

// FUNCIÓN PÚBLICA
void liberar_acuario(acuario_t* acuario) {
	if ((*acuario).cantidad_pokemon > SIN_POKEMONES)
		free((*acuario).pokemon);
	free(acuario);
}

// FUNCIÓN PÚBLICA
void liberar_arrecife(arrecife_t* arrecife) {	
	free((*arrecife).pokemon);
	free(arrecife);
}
