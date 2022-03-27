# Informe del Juego de la Oca

## Funcionalidad Extra
Describw el diseño y la implementación de cualquier funcionalidad adicional que hayáis agregado a la práctica.

### ¿Cuál es el objetivo de los cambios?
Al cambiar el tablero de una estructura estática a una dinámica buscamos optimizar la
memoria, mejorando así el rendimiento del programa.
Al incluir la opción de solucionar el tablero, creando con esta y sus funciones la
estructura de los pasos y la secuencia y sus correspondientes funciones, buscamos que
el ordenador encuentre recursivamente la manera óptima de llegar al final del tablero.

### ¿Cuál es el resultado esperado?
Con estos cambios esperamos que el programa se ejecute más rápido, ya que no
tenemos que crear un espacio fijo en la memoria, y que el programa nos de la mejor
forma de superar el tablero seleccionado.

### ¿Qué cambios en estructuras hicisteis y por qué?
En la estructura del tablero (board) convertimos el array de casillas de estático a dinámico
para optimizar el uso de memoria. Para esto, implementamos como array un puntero que
crea el espacio necesario después en la función de inicialización.
En la estructura del paso (step) implementamos para cada paso una posición, un valor de
dado y un puntero al siguiente paso, el cual se usará en la estructura de secuencia.
La estructura de secuencia (sequence) está formada por un puntero al primer paso de la
secuencia, un puntero al último y un entero que indica la cantidad de pasos que forma la
secuencia.
Estas dos últimas estructuras se usarán para buscar la mejor combinación de tiradas
para superar un tablero determinado.

### ¿Qué funciones se añadieron o modificaron?
La función init_board la modificamos para crear el espacio necesario en la memoria
dinámica para el tablero, haciendo uso de malloc.

En sequence.c se añaden/modifican las siguientes funciones:
- init_sequence: Inicializa una secuencia instaurando como primero y como último el
paso nulo y como tamaño 0.
- init_step: Inicializa un paso creando el espacio necesario para ello y instaurando
como posición y como valor de dado las dadas mediante parámetros. Además,
instaura como siguiente paso el dado también por parámetros.
- add_step_as_first: Si la secuencia no tiene primer paso, inicializa este paso y lo
instaura como primero con siguiente nulo y como último y si la secuencia ya tiene
primer paso instaura este como primero y el anterior como siguiente a este.
Además, aumenta en una unidad el tamaño de la secuencia.
- add_step_as_last: Si la secuencia no tiene último paso, significa que no tiene ningún
paso, por lo que inicializa este paso y lo instaura como primer y último de la
secuencia, con siguiente paso nulo. Si la secuencia tiene último paso, instaura este
como siguiente al último paso y, por tanto, nuevo último con siguiente paso nulo.
Además, aumenta en una unidad el tamaño de la secuencia.
- clear_sequence: Libera la secuencia, dejándola vacía y cambiando su tamaño a 0.
- print_sequence: Imprime la secuencia, imprimiendo la posición y el valor de dado de
cada paso que la constituye.

En menu.c se añade la opción para mostrar la mejor secuencia para resolver el tablero.

En game.c se añaden/modifican las siguientes funciones:
- do_recursive_move: Recibe como parámetros el estado, un valor de dado y la
profundidad del tablero. Si el nº de dados tirados es igual al nº de pasos de la
secuencia, si no hay ningún jugador o si el jugador no está en ninguna casilla, la
función retorna NULL. Si no, mira la posición actual de la ficha y, si esta posición no
es el final del tablero, mueve la ficha. Si lo es, acaba la partida. Después, se crea
una secuencia y si el tablero se ha ganado ya se crea el espacio para la secuencia y
si no se tiran los dados. Después, si la secuencia es nula, se añade esta anterior
tirada como primera y se retorna la secuencia.
- try_dice_values: Se crea un puntero a la mejor secuencia, que se instaura
inicialmente como nula. Con una iteración de 6 a 1, crea una secuencia que llama a
do_recursive_move y, si esta última secuencia no es nula y si la mejor secuencia es
nulo o el tamaño de esta secuencia es menor al tamaño de la instaurada como
mejor secuencia, si la mejor secuencia no es nula se vacía y se instaura como mejor
secuencia la secuencia encontrada, retornando al final la mejor secuencia
encontrada.


### ¿Cuál es el propósito de cada una de las modificaciones?
Al modificar la función init_board buscábamos la optimización del uso de la memoria.
Las funciones de sequence y step son usadas para encontrar la mejor secuencia posible
para resolver el tablero, lo cual se hace probando distintas combinaciones de tiradas y
comparándolas entre ellas.

## Organización
Al principio de la práctica, para la primera entrega, nos dividimos el trabajo en tareas y
cada uno realizó determinadas tareas, pero después, al juntarlo todo, nos dimos cuenta
de que para las siguientes entregas era mejor mirar lo que se pedía los 3 juntos y
construir una visión conjunta sobre cómo conseguir cumplir los objetivos que se pedían,
en vez de trabajar cada uno por su cuenta y juntarlo después. Por lo tanto, al final nos
juntábamos, bien en persona o por Discord, para analizar exactamente lo que se nos
pedía en la práctica y buscar una solución general para los problemas y, a partir de ahí,
intentábamos categorizar las tareas y dividirlas para trabajar sobre ellas. Después,
volvíamos a juntarnos para revisar lo que cada uno había hecho y ver si alguno de
nosotros lo hubiese hecho de otra forma.

#### Durante el desarrollo de este proyecto, ¿cómo dividieron las tareas?
Al principio las tareas las dividimos aleatoriamente, pero después, al mirar
detalladamente los objetivos y categorizarlos, era más fácil la división contemplando las
virtudes de cada uno, por lo que dividíamos las tareas considerando lo que a cada uno
se le daba mejor aunque después siempre revisábamos lo de los otros para intentar
entender el programa en su totalidad.

#### Si dividieron el trabajo, ¿quién hizo qué parte?
Los cambios iniciales necesarios en las estructuras y en la inicialización del tablero los
realizó Ferran, de las funciones de secuencias y pasos y el cambio en el menú se encargó
Iria y, por último, Pau trabajó en las funciones necesarias para resolver el tablero, aunque
para el razonamiento y planteamiento fue donde más se notó la colaboración de los 3, ya
que queríamos pensarlas de la forma más lógica posible para todos.

#### ¿Planificaron su trabajo juntos?
Sí, intentamos relacionar las distintas tareas de la entrega para después poder
interconectarlas más fácilmente. Además, al plantear los 3 las posibles soluciones para
los distintos problemas veíamos distintos puntos de vista, lo que nos ayudaba para
mejorar el nuestro y llegar a uno común optimizado.

## Realimentación
En esta última práctica hemos aprendido el funcionamiento de la memoria dinamica y de las 
funciones recursivas, algo que ya hemos visto en los seminarios, y ahora hemos aplicado en un ejercicio mas completo.

En cuanto a la práctica en general, estamos todos los miembros de acuerdo en que han sido de gran ayuda los templates 
de cada entrega, ya que sinó uno no sabe por donde empezar. Así pues, creemos que esta practica es una manera ideal 
para aprender las bases de la programación y de C, siempre es mejor aprender mientras aplicas los conceptos, te 
equivocas y arreglas aquellas partes que no funcionan.
