#include "evento_pesca.h"
#include <stdlib.h>

bool seleccionar_gordos(pokemon_t* pokemon) {
	return ((*pokemon).peso > 50);
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

	arrecife_t* arrecife = crear_arrecife("arrecife.txt");

	if (arrecife == NULL) {
		printf("No se pudo crear el arrecife.\n");
		return -1;
	}

	printf("Cantidad de pokemones: %i\n", (*arrecife).cantidad_pokemon);

	for (int i = 0; i < (*arrecife).cantidad_pokemon; i++) {
		printf("Especie: %s\n", (*arrecife).pokemon[i].especie);
	}

	acuario_t* acuario = crear_acuario();

	bool (*seleccionar_pokemon)(pokemon_t*) = seleccionar_gordos;

	trasladar_pokemon(arrecife, acuario, seleccionar_pokemon, 3);

	for (int i = 0; i < (*acuario).cantidad_pokemon; i++) {
		printf("Especie: %s. Peso: %i\n", (*acuario).pokemon[i].especie, (*acuario).pokemon[i].peso);
	}


	return 0;
}