#include "evento_pesca.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARGUMENTOS_ESPERADOS 3

#define ERROR -1
#define MAX_SELECCIONES 5

#define LIMITE_PRONUNCIACION 9

#define PESO_INTERMEDIO 50
#define PESO_TOMATE 20
#define VELOCIDAD_INTERMEDIA 20

#define POKEMON_ROJO "rojo"
#define POKEMON_VERDE "verde"
#define	POKEMON_AZUL "azul"
#define	POKEMON_AMARILLO "amarillo"
#define POKEMON_NARANJA "naranja"
#define INICIAL_CHARMANDER 'C'
#define INICIAL_CHARMANDER_MINUS 'c'
#define INICIAL_PIKACHU 'P'
#define INICIAL_PIKACHU_MINUS 'p'

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
#define MAX_COLORES_TABLA 3

#define MAX_TRASLADOS 20
#define MAX_FORMATOS_MOSTRAR 5

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
	return( (((*pokemon).especie)[0] == INICIAL_CHARMANDER || 
			((*pokemon).especie)[0] == INICIAL_CHARMANDER_MINUS) && 
			strcmp((*pokemon).color, POKEMON_NARANJA) == 0 );
}

/*
* Pre: El puntero a pokemon recibido debe estar inicializado y ser válido.
* Post: Devuelve true si el pokemon recibido se parece a Shrek, es decir, si
	su peso supera el PESO_INTERMEDIO, y si su color es verde.
*/
bool se_parece_a_shrek(pokemon_t* pokemon) {
	return( (*pokemon).peso > PESO_INTERMEDIO &&
			strcmp((*pokemon).color, POKEMON_VERDE) == 0 );
}

/*
* Pre: El puntero a pokemon recibido debe estar inicializado y ser válido.
* Post: Devuelve true si el pokemon recibido se parece a Pikachu, es decir,
	si tiene color POKEMON_AMARILLO y su especie comienza con INICIAL_PIKACHU.
*/
bool se_parece_a_pikachu(pokemon_t* pokemon) {
	return ( (((*pokemon).especie)[0] == INICIAL_PIKACHU ||
			((*pokemon).especie)[0] == INICIAL_CHARMANDER_MINUS) && 
			strcmp((*pokemon).color, POKEMON_AMARILLO) == 0 );
}

/*
* Pre: El puntero a pokemon recibido debe estar inicializado y ser válido.
* Post: Muestra los datos del pokemon recibido dentro de un bowl, como si fueran fideos.
*/
void mostrar_bowl(pokemon_t* pokemon) {
	printf("__       ___,.-------..__        __\n");
	printf("//\\ _,-''                `'--._ //\\\n");
	printf("\\ ;'      " AMARILLO "%12s" RESET_COLOR "         `: //\n", (*pokemon).especie);
	printf(" `(        %-12s           )'\n", (*pokemon).color);
	printf("   :.          " AMARILLO "%3i" RESET_COLOR "              ,;\n", (*pokemon).velocidad);
	printf("    `.`--.___  %-3i      ___.--','\n", (*pokemon).peso);
	printf("      `.     ``-------''     ,'\n");
	printf("         -.               ,-\n");
	printf("            `-._______.-'\n");
}

/*
* Pre: El puntero a pokemon recibido debe estar inicializado y ser válido.
* Post: Muestra el pokemon recibido en formato de lista de supermercado, listando
	sus datos como si fueran productos.
*/
void mostrar_lista(pokemon_t* pokemon) {
	printf("   ______________________________\n");
	printf(" / \\                             \\.\n");
	printf("|   |                            |.\n");
	printf(" \\_ |     %12s           |.\n", (*pokemon).especie);
	printf("    |                            |.\n");
	printf("    |                            |.\n");
	printf("    |      %-12s          |.\n", (*pokemon).color);
	printf("    |                            |.\n");
	printf("    |                            |.\n");
	printf("    |      Peso: %3i             |.\n", (*pokemon).peso);
	printf("    |                            |.\n");
	printf("    |                            |.\n");
	printf("    |      Velocidad: %3i        |.\n", (*pokemon).velocidad);
	printf("    |                            |.\n");
	printf("    |                            |.\n");
	printf("    |   _________________________|___\n");
	printf("    |  /                            /.\n");
	printf("    \\_/dc__________________________/.\n\n");
}


/*
* Pre: El puntero a pokemon recibido debe estar inicializado y ser válido.
* Post: Muestra el pokemon recibido en formato de tabla, con una breve descripción de sus
	datos.
*/
void mostrar_tabla_datos(pokemon_t* pokemon) {
	//printf("──────────────────────────────────────────────────────────────────────────────────────────\n");
	//printf("\t%-12s|\t %-6i|\t \t%-6i|\t \t%-12s|\t\n\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso, (*pokemon).color);
	printf(FVERDE "Especie: %s" RESET_COLOR "\n", (*pokemon).especie);
	printf("\tEs de color %s\n", (*pokemon).color);
	printf("\t\tSe puede ver en su estado físico que su peso es de %i kg y su velocidad de %i km/h\n", (*pokemon).peso, (*pokemon).velocidad);
	printf("\n" FVERDE "─────────────────────────────────────────────────────────────────────────────────────────────────────────" RESET_COLOR "\n\n");
}


/*
* Pre: Recibe un pokemon válido con todas sus estructuras válidas.
* Post: Muestra por pantalla al pokemon recibido con formato de tarjeta.
*/
void mostrar_tarjeta(pokemon_t* pokemon) {
	printf("   _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._\n");
	printf(" ,'_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._`.\n");
	printf("( (                                                         ) )\n");
	printf(" ) )                                                       ( (\n");
	printf("( (                 %14s                          ) )\n", (*pokemon).especie);
	printf(" ) )                                                       ( (\n");
	printf("( (                                                         ) )\n");
	printf(" ) )                                                       ( (\n");
	printf("( (                                                         ) )\n");
	printf(" ) )     Velocidad: %-3i km/h                               ( (\n",(*pokemon).velocidad);
	printf("( (                                                         ) )\n");
	printf(" ) )                                                       ( (\n");
	printf("( (                                                         ) )\n");
	printf(" ) )     Peso: %-3i kg                                      ( (\n", (*pokemon).peso);
	printf("( (                                                         ) )\n");
	printf(" ) )                                                       ( (\n");
	printf("( (                                                         ) )\n");
	printf(" ) )     Color: %-12s                               ( (\n", (*pokemon).color);
	printf("( (                                                         ) )\n");
	printf(" ) )                                                       ( (\n");
	printf("( (_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._) )\n");
	printf(" `._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._,'\n");
	printf("\n");
}

/*
* Pre: El puntero a pokemon recibido debe estar inicializado y ser válido.
* Post: Muestra el pokemon recibido en formato de tabla, colocando primero la especie,
	luego la velocidad, el peso y por último el color. Alterna los colores de cada 
	fila (pokemon) de manera aleatoria entre rojo, azul y amarillo.
*/
void mostrar_tabla_colorida(pokemon_t* pokemon) {
	int n = (rand() % MAX_COLORES_TABLA);
	if (n == 0) 
		printf(FROJO "\t%-12s\t %-6i\t \t%-6i\t \t%-12s\t"  RESET_COLOR "\n\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso, (*pokemon).color);
	if (n == 1)
		printf(FAMARILLO "\t%-12s\t %-6i\t \t%-6i\t \t%-12s\t" RESET_COLOR "\n\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso, (*pokemon).color);
	if (n == 2)
		printf(FAZUL "\t%-12s\t %-6i\t \t%-6i\t \t%-12s\t" RESET_COLOR "\n\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso, (*pokemon).color);
}

/*
* Pre: -
* Post: Muestra la pantalla de inicio de la Pesca Pokemón
	(Simula una caña de pescar pescando a Squirtle).
*/
void mostrar_pantalla_inicial() {


	printf(AMARILLO "                   \t                                  ,'\\\n" RESET_COLOR);
	printf(AMARILLO "             .---.\t    _.----.        ____         ,'  _\\   ___    ___     ____\n" RESET_COLOR);
	printf(AMARILLO "           .'     " RESET_COLOR "\\" AMARILLO "\t_,-'       `.     |    |  /`.   \\,-'    |   \\  /   |   |    \\  |`.\n" RESET_COLOR);
	printf(AMARILLO "         .'       " RESET_COLOR "|" AMARILLO "\t\\      __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ |  |\n" RESET_COLOR);
	printf(AMARILLO "       .'         " RESET_COLOR "|" AMARILLO "\t \\.    \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\|  |\n" RESET_COLOR);
	printf(AMARILLO "      .'          " RESET_COLOR "|" AMARILLO "\t   \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |\n" RESET_COLOR);
	printf(AMARILLO "     .'           " RESET_COLOR "|" AMARILLO "\t    \\     ,-'/  /   \\    ,'   | \\/ / ,`.|         /  /   \\  |     |\n" RESET_COLOR);
	printf(AMARILLO "     .'          " RESET_COLOR ".'" AMARILLO "\t     \\    \\ |   \\_/  |   `-.  \\    `'  /|  |    ||   \\_/  | |\\    |\n" RESET_COLOR);
	printf(AMARILLO "    .'           " RESET_COLOR "|" AMARILLO "\t      \\    \\ \\      /       `-.`.___,-' |  |\\  /| \\      /  | |   |\n" RESET_COLOR);
	printf(AMARILLO "   .'            " RESET_COLOR "|" AMARILLO "\t       \\    \\ `.__,'|  |`-._    `|      |__| \\/ |  `.__,'|  | |   |\n" RESET_COLOR);
	printf(AMARILLO "  .'             " RESET_COLOR "|" AMARILLO "\t        \\_.-'       |__|    `-._ |              '-.|     '-.| |   |\n" RESET_COLOR);
	printf(AMARILLO " .'              " RESET_COLOR "0" AMARILLO "\t                                `'                            '-._|\n" RESET_COLOR);


	printf("	       _,........__\n");
	printf("            ,-'            ''`-.\n");////
	printf("          ,'                   `-.\n");
	printf("        ,'                        \\\n");
	printf("      ,'                           .\n");
	printf("      .'\\               ,\"\".       `\n");
	printf("     ._.'|             / |  `       \\\n");
	printf("     |   |            `-.'  ||       `.\n");
	printf("     |   |            '-._,'||       | \\\n");
	printf("     .`.,'             `..,'.'       , |`-.\n");
	printf("     l                       .'`.  _/  |   `.\n");
	printf("     `-.._'-   ,          _ _'   -' \\  .     `\n");/////
	printf("`.\"\"\"\"\"\"'-.`-...,---------','         `. `....__.\n");/////
	printf(".''        `""-.___      __,\\          \\  \\\\     \\\n");
	printf("\\_ .          |   `""""'    `.           . \\     	\\\n");
	printf("  `.          |              `.          |  .     L\n");
	printf("    `.        |`--...________.'.        j   |     |\n");
	printf("      `._    .'      |          `.     .|   ,     |\n");
	printf("         `--,\\       .            `7\"\"' |  ,      |\n");
	printf("            ` `      `            /     |  |      |    _,-'\"\"\"`-.\n");/////
	printf("             \\ `.     .          /      |  '      |  ,'          `.\n");
	printf("              \\  v.__  .        '       .   \\    /| /              \\\n");
	printf("               \\/    `\"\"\\\"\"\"\"\"\"\"`.       \\   \\  /.''                |\n");
	printf("                `        .        `._ ___,j.  `/ .-       ,---.     |\n");
	printf("                ,`-.      \\         .\"     `.  |/        j     `    |\n");/////
	printf("               /    `.     \\       /         \\ /         |     /    j\n");
	printf("              |       `-.   7-.._ .          |\"          '         /\n");/////
	printf("              |          `./_    `|          |            .     _,'\n");
	printf("              `.           / `----|          |-............`---'\n");
	printf("                \\          \\      |          |\n");
	printf("               ,'           )     `.         |\n");
	printf("                7____,,..--'      /          |\n");
	printf("                                  `---.__,--.'  \n");
}


int main(int argc, char* argv[]) {

	if (argc != ARGUMENTOS_ESPERADOS)
		return ERROR;

	srand((unsigned)time(NULL));

	arrecife_t* arrecife = crear_arrecife(argv[1]);

	if (arrecife == NULL) {
		printf("No se pudo crear el arrecife.\n");
		return ERROR;
	}

	printf("Cantidad de pokemones: %i\n", (*arrecife).cantidad_pokemon);


	acuario_t* acuario = crear_acuario();

	if (acuario == NULL) {
		printf("No se pudo crear el acuario.\n");
		return ERROR;
	}
	
	mostrar_pantalla_inicial();
	// MAX_SELECCIONES Y MAX_FORMATOS_MOSTRAR DEBEN SER IGUALES
	bool (*seleccionar_pokemon[MAX_SELECCIONES])(pokemon_t*) = {se_parece_a_charmander, es_rgb, se_parece_a_pikachu, es_gordo_y_lento, se_parece_a_shrek};
	void (*mostrar_pokemon[MAX_FORMATOS_MOSTRAR])(pokemon_t*) = {mostrar_tarjeta, mostrar_tabla_datos, mostrar_tabla_colorida, mostrar_lista, mostrar_bowl};
	
	for (int i = 0; i < MAX_SELECCIONES; i++) {
		int cantidad = (rand() % MAX_TRASLADOS)+1; // Número entre 1 y MAX_TRASLADOS
		printf("\n\t\t\tTraslado N°%i\n\n", i+1);
		printf("Se trasladarán %i pokemon.\nEnter para continuar.\n", cantidad);
		getchar();
		int resultado_traslado = trasladar_pokemon(arrecife, acuario, seleccionar_pokemon[i], cantidad);
		if (resultado_traslado == ERROR)
			printf("No se pudo realizar el traslado.\n");
		else
			censar_arrecife(arrecife, mostrar_pokemon[i]);
	}

	if (guardar_datos_acuario(acuario, argv[2]) == ERROR){
		printf("No se pudieron guardar los datos en el acuario.\n");
		return ERROR; 
	} 

	liberar_acuario(acuario);

	liberar_arrecife(arrecife);

	return 0;
}