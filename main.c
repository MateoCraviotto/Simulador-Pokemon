#include "evento_pesca.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
//static const int ERROR = -1;
#define ERROR -1
//static const int EXITO = 0;
#define MAX_SELECCIONES 5

#define LIMITE_PRONUNCIACION 10

#define PESO_INTERMEDIO 50
#define PESO_TOMATE 20
#define VELOCIDAD_INTERMEDIA 20

#define POKEMON_ROJO "rojo"
#define POKEMON_VERDE "verde"
#define	POKEMON_AZUL "azul"
#define POKEMON_NARANJA "naranja"
#define INICIAL_CHARMANDER 'C'

#define NEGRO "\e[30m"
#define ROJO "\e[31m"
#define VERDE "\e[32m"
#define AMARILLO "\e[33m"
#define AZUL "\e[34m"
#define MAGENTA "\e[35m"
#define CYAN "\e[36m"
#define BLANCO "\e[37m"
#define RESET_COLOR "\e[0m"

#define FNEGRO "\e[40m"
#define FROJO "\e[41m"
#define FVERDE "\e[42m"
#define FAMARILLO "\e[43m"
#define FAZUL "\e[44m"
#define FMAGENTA "\e[45m"
#define FCYAN "\e[46m"
#define FBLANCO "\e[47m"
const char* COLORES[] = {FROJO, FAZUL, FAMARILLO};

/*
* Pre: El puntero a pokemon recibido debe estar inicializado y ser válido.
* Post: Devuelve true si el pokemon recibido es gordo (peso > PESO_INTERMEDIO) y 
	lento (velocidad < VELOCIDAD_INTERMEDIA).
*/
bool es_gordo_y_lento(pokemon_t* pokemon) {
	return ( (*pokemon).peso > PESO_INTERMEDIO && (*pokemon).velocidad < VELOCIDAD_INTERMEDIA );
}

/*
* Pre: El puntero a pokemon recibido debe estar inicializado y ser válido.
* Post: Devuelve true si el pokemon recibido es de colores rgb, es decir, si 
	es POKEMON_VERDE, POKEMON_AZUL, o POKEMON_ROJO.
*/
bool es_rgb(pokemon_t* pokemon) {
	return (strcmp((*pokemon).color, POKEMON_VERDE) == 0 || 
			strcmp((*pokemon).color, POKEMON_AZUL) == 0 ||
			strcmp((*pokemon).color, POKEMON_ROJO) == 0);
}

/*
* Pre: El puntero a pokemon recibido debe estar inicializado y ser válido.
* Post: Devuelve true si el pokemon recibido se parece a Charmander, es decir, 
	si tiene color POKEMON_NARANJA y su especie comienza con INICIAL_CHARMANDER.
*/
bool se_parece_a_charmander(pokemon_t* pokemon) {
	return( ((*pokemon).especie)[0] == INICIAL_CHARMANDER && 
		strcmp((*pokemon).color, POKEMON_NARANJA) == 0 );
}

/*
* Pre: El puntero a pokemon recibido debe estar inicializado y ser válido.
* Post: Devuelve true si el nombre del pokemon recibido es "impronunciable".
*/
bool es_impronunciable(pokemon_t* pokemon) {
	return( strlen((*pokemon).especie) > LIMITE_PRONUNCIACION );
}

/*
* Pre: El puntero a pokemon recibido debe estar inicializado y ser válido.
* Post:
*/
bool parece_un_tomate(pokemon_t* pokemon) {
	return ( (*pokemon).peso >= PESO_TOMATE && strcmp((*pokemon).color, POKEMON_ROJO) == 0);
}


/*
* Pre: El puntero a pokemon recibido debe estar inicializado y ser válido.
* Post: Muestra el pokemon recibido en formato de tabla, colocando primero la especie,
	luego la velocidad, el peso y por último el color.
*/
void mostrar_tabla(pokemon_t* pokemon) {
	//printf("──────────────────────────────────────────────────────────────────────────────────────────\n");
	printf("\t%-12s\t %-6i\t \t%-6i\t \t%-12s\t\n\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso, (*pokemon).color);
	//printf("\n──────────────────────────────────────────────────────────────────────────────────────────\n\n");
}

/*
* Pre: El puntero a pokemon recibido debe estar inicializado y ser válido.
* Post: Muestra el pokemon recibido en formato de tabla, colocando primero la especie,
	luego la velocidad, el peso y por último el color. Alterna los colores de cada 
	fila (pokemon) de manera aleatoria entre rojo, azul y amarillo.
*/
void mostrar_tabla_colorida(pokemon_t* pokemon) {
	int n = (rand() % 3);
	if (n == 0) 
		printf(FROJO "\t%-12s\t %-6i\t \t%-6i\t \t%-12s\t"  RESET_COLOR "\n\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso, (*pokemon).color);
	if (n == 1)
		printf(FAMARILLO "\t%-12s\t %-6i\t \t%-6i\t \t%-12s\t" RESET_COLOR "\n\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso, (*pokemon).color);
	if (n == 2)
		printf(FAZUL "\t%-12s\t %-6i\t \t%-6i\t \t%-12s\t" RESET_COLOR "\n\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso, (*pokemon).color);
	//void (*mostrar_color[3])(pokemon_t* pokemon) = {mostrar_rojo, mostrar_amarillo, mostrar_azul};
	//mostrar_color[rand() % 3](pokemon);
}

int main() {

	/* Crear las estructuras a utilizar */
	 /* Trasladar por 1ra vez con cierta función */
	/* Listar a los pokémon que continúan en el arrecife */
 	/* Trasladar por 2da vez con cierta función */
 	/* Listar a los pokémon que continúan en el arrecife */
 	//...
 	/* Trasladar por N-écima vez con cierta función */
 	/* Listar a los pokémon que continúan en el arrecife */
 	/* Guardar los pokémon del acuario */
	/* Liberar memoria */


	// Chequear que los malloc no devuelvan NULL

	srand((unsigned)time(NULL));

	arrecife_t* arrecife = crear_arrecife("arrecife.txt");

	if (arrecife == NULL) {
		printf("No se pudo crear el arrecife.\n");
		return ERROR;
	}

	printf("Cantidad de pokemones: %i\n", (*arrecife).cantidad_pokemon); ////////////////////////////////////////////////////////////


	acuario_t* acuario = crear_acuario();

	if (acuario == NULL) {
		printf("No se pudo crear el acuario.\n");
		return ERROR;
	}
	
	bool (*seleccionar_pokemon[MAX_SELECCIONES])(pokemon_t*) = {es_gordo_y_lento, es_rgb, se_parece_a_charmander, es_impronunciable, parece_un_tomate};
	//bool (*seleccionar_pokemon)(pokemon_t*) = es_gordo_y_lento;
	//int resultado_traslado = trasladar_pokemon(arrecife, acuario, seleccionar_pokemon, 0);

	void (*mostrar_pokemon)(pokemon_t*) = mostrar_tabla;////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	for (int i = 0; i < MAX_SELECCIONES; i++) {
		int cantidad = (rand() % 20)+1; // Número entre 1 y 20
		printf("\n\t\tTraslado N°%i\n\n", i+1);
		printf("Se trasladarán %i pokemon.\nEnter para continuar.\n", cantidad);
		getchar();
		int resultado_traslado = trasladar_pokemon(arrecife, acuario, seleccionar_pokemon[i], cantidad);
		if (resultado_traslado == ERROR)
			printf("No se pudo realizar el traslado.\n");
		else
			censar_arrecife(arrecife, mostrar_pokemon);
	}

	guardar_datos_acuario(acuario, "acuario.txt");


	//mostrar_pokemon = mostrar_tabla_colorida;
	//censar_arrecife(arrecife, mostrar_pokemon);


	liberar_acuario(acuario);

	liberar_arrecife(arrecife);

	//printf("%s %s %s \n", COLORES[0], COLORES[1], COLORES[2]);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}