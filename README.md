# Gran Pesca Pokemon - Trabajo Práctico 1 Algoritmos y Programación II

El presente trabajo práctico consiste en un simulador de traslado de pokemones. Su finalidad es mover pokemones que cumplan ciertas condiciones necesarias para el evento de pesca, del arrecife al acuario de Misty. Cuando se trasladan, se va informando el estado del arrecife, para preservar las especies.
Por defecto, los traslados se realizan con las siguientes funciones: ` {se_parece_a_charmander, es_rgb, se_parece_a_pikachu, es_gordo_y_lento, se_parece_a_shrek}.`</br><br>

- ## Código
    <br>
	Se basa en hacer una lectura del archivo de arrecife recibido, donde se encuentran los pokemones de este escritos con un formato que indica su especie,
	velocidad, peso y color; luego se realizan los traslados del arrecife al acuario, censando el arrecife después de cada uno, y finalmente se guardan en el archivo del acuario recibido.<br>
	Primero, se crea el arrecife, reservando memoria para este en el heap. Para realizar la lectura, se utiliza memoria dinámica para ir agrandando el vector de pokemones del arrecife a medida que se van leyendo del archivo. Una vez leídos todos los pokemones, comienza un bucle descrito a continuación:
    <br><br>

	- Se elige de manera aleatoria, con un número entre 1 y `MAX_TRASLADOS` (20), la cantidad de pokemones a trasladar.

	- Se informa el número de traslado, junto con la cantidad a trasladar.

	- Se realiza el traslado de la siguiente manera. Primero, se recorre el vector de pokemones del arrecife, comprobando que haya la cantidad necesaria de pokemones que 
	cumplen con la condición pedida para ser seleccionados. Al mismo tiempo, se van guardando en un vector de posiciones de búsqueda, las posiciones de los pokemones que cumplan
	los criterios de selección, esto me pareció más eficiente que recorrer dos veces el arrecife. Si hay suficientes pokemones, se comienza a trasladar. Se leen desde el final hacia el inicio, las posiciones del vector de posiciones buscadas. Se lee una, se copia el pokemon en esa posición del arrecife al acuario (reservando la memoria necesaria), y luego se copia el último pokemon del arrecife al pokemon movido para borrarlo, y se achica el vector de pokemones del arrecife en uno (eliminación física), liberando la memoria necesaria para ello.
	    > Aclaración: El vector de posiciones se lee de atrás para adelante, para así asegurar que, al mover el último pokemon del arrecife, la posición de este ya no sea relevante, pues ya fue descartada. Es decir, si el último pokemon del arrecife fuera uno seleccionado, si leyera de inicio a fin, y moviera el último pokemon a otra posición, ya no podría trasladar al seleccionado, pues ya no sería el último del arrecife porque su posición cambiaría.

	- Si algo salió mal en el traslado, se informa al usuario que no fue posible realizarlo.

	- Si se pudo realizar el traslado, se censa el arrecife, mostrando los pokemones restantes en él, para realizar los traslados teniendo en cuenta la preservación de las especies.
	El censo se muestra de una forma diferente para cada traslado, es decir hay 5 formas de mostrar, ya que hay 5 traslados..</br></br>

	El bucle se repite hasta terminar con la cantidad de selecciones esperadas (5).

	Al finalizar el bucle, se guardan los pokemones que se trasladaron al acuario en el archivo recibido como segundo parámetro.

	Para concluir, se libera tanto la memoria reservada previamente del arrecife como la del acuario.</br></br>



- ## Compilación y Ejecución
</br>
	Para realizar una compilación más prolija y fácil, se creó un makefile que simplifica los comandos a la hora de compilar y ejecutar. A continuación los comandos:</br></br>

- Si el usuario quiere **compilar**: ` make`

- Si el usuario quiere **compilar y ejecutar** (pasa por defecto los parámetros arrecife.txt y acuario.txt): 	`make exe`</br>
    > Ver más abajo si quiere cambiar los parámetros

- Si el usuario por alguna razón cambió el código...
    -  y quiere usar valgrind para **comprobar la pérdida de memoria**: `make test`

    - y quiere usar gdb para **debuggear** el código en caso de errores: `make debug`


Si el usuario no desea utilizar el makefile, puede compilar con la línea: 	gcc *.c -g -Wall -Werror -Wconversion -std=c99 -o evento_pesca

Si quiere **ejecutar con otros parámetros**: `./evento_pesca archivo_arrecife.txt archivo_acuario.txt`
Siendo estos los archivos de arrecife y acuario que el usuario desee utilizar, respectivamente. Hay que tener en cuenta que *los archivos deben ser de texto* (.txt).</br></br>


- ## Se construyó con
</br>

### 1. **Punteros**
</br> 
Un puntero es un tipo de dato cuyo tamaño es 4 bytes, en el caso de una arquitectura de 32 bits, u 8bytes, en una arquitectura de 64 bits. Su valor es o apunta a una dirección de memoria de la computadora. Un puntero se puede desreferenciar, obteniendo
así el valor de la variable almacenada en la dirección de memoria a la que apunta. Esto se realiza con el operador (*). Para declarar en C un puntero a, por ejemplo, un entero se usa:
`int* puntero_a_entero;`
Se dice que este puntero es de tipo de dato "int pointer", o que apunta a un entero.</br></br>


### 2. **Aritmética de punteros** 
</br>
La aritmética de punteros consiste en realizar operaciones que involucren punteros. Para ello hay distintos operadores:</br></br>

- Operador de dirección **(&)**: Se utiliza para obtener la dirección de memoria de la variable a la que se lo aplica. Por ejemplo, si tengo un entero y quiero saber su dirección de memoria, uso el operador &:

    `int numero = 10;`</br>
    `int* direccion_numero = &numero;`</br>
    `printf("Dirección de memoria de la variable numero: %p\n", direccion_numero);`</br>

- Operador de indirección **(*)**: Se utiliza para desreferenciar un puntero, es decir, si tengo una dirección de memoria y quiero saber cuál es el valor que almacena. Usando el ejemplo anterior:</br>
`int valor_numero = (*direccion_numero);`</br>
Así le asigno el valor al que apunta direccion_numero a la variable valor_numero. Para eso, debo tener en cuenta de que direccion_numero apunta, en este caso, a un int.</br>

- Incrementos **(++)** y decrementos **(--)**: Con estos operadores accedo a las direcciones de memoria posteriores y anteriores de un puntero. Esto es muy útil cuando se trabaja con arreglos, pues puedo usar esta notación para iterar por un arreglo, por ejemplo.</br></br>



### 3. **Punteros a funciones**
</br>
Los punteros a funciones se explican por si solos. Se declara un puntero a función y se le asigna una función. Por ejemplo, si yo tengo la siguiente función:

`char una_función(int num) {`</br>
    `...`</br>
`}`

Y quiero que un puntero apunte a ella, hago lo siguiente:

`char (*puntero_a_una_funcion)(int) = una_funcion;`

De la misma manera puedo hacer un arreglo de funciones, teniendo en cuenta que las funciones del arreglo deben tener los mismos valores de entrada y salida entre sí:

`char (*arreglo_de_funciones[MAX_FUNCIONES])(int) = {una_funcion, otra_funcion, ...};`

En este ejemplo, todas las funciones del arreglo deben recibir un `int` y devolver un `char`.
Los punteros a funciones son extremadamente útiles, ya que con ellos podemos pasar una función como parámetro a otra función. Las posibilidades que nos brinda esto son casi infinitas.</br></br>


### 4. **Memoria dinámica** (malloc, realloc) 
</br>
Para el uso de la memoria dinámica, es decir, memoria en el HEAP, es importante tener en cuenta las funciones malloc y realloc.</br></br>

- `malloc(tamanio_a_reservar)`:</br>
Es una función que recibe como único parámetro el tamaño en bytes de la estructura para la que va a reservar memoria dinámica. La función reserva    un bloque del tamaño recibido en el HEAP, y, si pudo reservar memoria, devuelve la dirección de memoria del bloque que reservó. Hay que tener en cuenta que esta función puede devolver `NULL` si no es capaz de reservar la memoria solicitada, por lo que siempre hay que verificar que se haya podido reservar memoria.

- `realloc(direccion_del_bloque_a_modificar, tamanio_nuevo_bloque)`:</br>
Agranda o achica el bloque de memoria recibido según el tamaño en bytes especificado. realloc recibe como primer parámetro la dirección de memoria del bloque de memoria cuyo tamaño va a modificar, y como segundo parámetro el tamaño del nuevo bloque modificado. Esta función tiene 3 posibles resultados y valores de retorno:

    1. Puede agrandar/achicar el bloque sin moverlo, por lo que su dirección de memoria queda igual.

    2. Puede agrandar el bloque, pero no en la misma dirección de memoria. Es decir, no logra agrandarlo, por lo que busca un bloque de memoria libre que satisfaga el tamaño solicitado. Lo encuentra, y mueve el bloque de memoria a esa nueva dirección. En esta caso, la dirección cambia.

    3. No puede agrandar/achicar el bloque de memoria, por lo que devuelve `NULL`.

Es muy importante tener en cuenta estos 3 posibles casos, para lo que se recomienda tener una variable auxiliar que almacene el retorno de la función realloc. Luego de verificar que sea distinto de `NULL`, asigno la variable auxiliar a la variable original. Así evito perder la dirección de memoria original.

Otra cosa a tener en cuenta es que si a realloc se le pasa `NULL` como primer parámetro, tiene el mismo comportamiento que malloc, ya que reserva un bloque de memoria nuevo del tamaño especificado.</br></br>


### El **enunciado** del trabajo práctico se encuentra en el archivo 2020_2C_TP1_Algo2.pdf
