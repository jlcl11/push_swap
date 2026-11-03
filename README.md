*This project has been created as part of the 42 curriculum by jocorral, jnunez-b.*

# Push_swap

## Descripción

**Push_swap** es un proyecto de ordenación con una particularidad: los números están en dos pilas, `a` y `b`, y solo se pueden mover con un conjunto reducido de operaciones. El programa no se limita a ordenarlos: imprime la lista de operaciones que los ordena, procurando que sea lo más corta posible.

Todos los números empiezan en la pila `a`, con el primer argumento en la cima, y la pila `b` empieza vacía. Al ejecutar la lista, `a` debe quedar en orden ascendente, con el número más pequeño en la cima, y `b` debe quedar vacía.

Las operaciones disponibles son:

| Operación | Efecto |
| --------- | ------ |
| `sa` / `sb` | Intercambia los dos primeros elementos de `a` / `b` |
| `ss` | `sa` y `sb` a la vez |
| `pa` | Pasa la cima de `b` a la cima de `a` |
| `pb` | Pasa la cima de `a` a la cima de `b` |
| `ra` / `rb` | Rota `a` / `b`: el primer elemento pasa a ser el último |
| `rr` | `ra` y `rb` a la vez |
| `rra` / `rrb` | Rota `a` / `b` al revés: el último elemento pasa a ser el primero |
| `rrr` | `rra` y `rrb` a la vez |

El proyecto trata sobre **complejidad algorítmica**, así que todas las clases de complejidad de este documento se miden en **número de operaciones de Push_swap generadas**, no en tiempo de CPU.

El programa incluye cuatro estrategias:

| Estrategia | Algoritmo | Complejidad en operaciones |
| ---------- | --------- | -------------------------- |
| Simple | Ordenación por selección | `O(n²)` |
| Media | Ordenación por chunks | `O(n√n)` |
| Compleja | Radix sort LSD | `O(n log n)` |
| Adaptativa | Elige una de las anteriores según el desorden | Depende del desorden |


---

## Contribuciones del equipo

**`jocorral`**

* Las once **operaciones de pila**.
* La **estrategia simple** (ordenación por selección).
* La **gestión de las pilas** (`stack.c`).
* El **parser y la validación de la entrada**, y la lectura de las flags.
* El merge de las ramas y la documentación.

**`jnunez-b`**

* La **estrategia media** (ordenación por chunks), incluido `index_list`.
* La **estrategia compleja** (radix sort).
* La **estrategia adaptativa** y la **métrica de desorden**.
* El **modo benchmark**, que tiene asignado y sigue en curso.

Los dos podemos explicar cualquier parte del código.


## Instrucciones

```bash
./push_swap [selector] [--bench] números
```

Las flags van antes de los números. Los números pueden ir en argumentos separados, en una lista entre comillas o combinando ambas formas:

```bash
./push_swap 3 1 2
./push_swap "3 1 2"
./push_swap 3 "1 2"
```

El programa imprime una operación por línea:

```text
$> ./push_swap --simple 4 67 3 87 23
ra
ra
pb
ra
ra
pb
rra
pa
pa
```

Si los números ya están ordenados, o si no se pasa ninguno, no imprime nada.

### Cómo usar el checker

`checker_linux` es el binario que se entrega con el enunciado para comprobar el resultado. No forma parte de este repositorio: hay que descargarlo de la intra, dejarlo en esta carpeta y darle permisos con `chmod +x checker_linux`.

Recibe la misma lista de números que `push_swap`, lee las operaciones de la entrada estándar y las ejecuta:

| Salida | Significado |
| ------ | ----------- |
| `OK` | `a` queda ordenada y `b` queda vacía |
| `KO` | Las operaciones son válidas, pero no ordenan la lista |
| `Error` | Algún número no es válido o una operación no existe |

Lo normal es pasarle directamente la salida de `push_swap`:

```bash
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_linux $ARG
ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker_linux $ARG
```

En zsh, escribe `${=ARG}` en lugar de `$ARG`.

Para probar con 500 números aleatorios y contar las operaciones, como en el enunciado:

```bash
shuf -i 0-9999 -n 500 > args.txt
./push_swap $(cat args.txt) | ./checker_linux $(cat args.txt)
./push_swap $(cat args.txt) | wc -l
```

`shuf` escribe un número por línea. `push_swap` no lee tabuladores ni saltos de línea: es el shell quien los elimina al separar los argumentos de `$(cat args.txt)`, siempre que vaya sin comillas.

También se pueden escribir las operaciones a mano, una por línea, y terminar con `Ctrl+D`:

```text
$> ./checker_linux 3 2 1 0
rra
pb
sa
rra
pa
OK
```

---

### Cómo comprobar la memoria con valgrind

```bash
valgrind --leak-check=full --show-leak-kinds=all ./push_swap 4 67 3 87 23 > /dev/null
```

`> /dev/null` oculta las operaciones para que se vea solo el informe de valgrind, que se escribe en `stderr`. No hay fugas ni errores si termina así:

```text
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

Conviene repetirlo con una entrada grande y con una que dé error, porque ese camino también debe liberar la memoria:

```bash
ARG=$(shuf -i 0-9999 -n 500 | tr '\n' ' ')
valgrind --leak-check=full --show-leak-kinds=all ./push_swap $ARG > /dev/null
valgrind --leak-check=full --show-leak-kinds=all ./push_swap 1 2 hello > /dev/null
```

## Selección de estrategia

| Selector | Efecto |
| -------- | ------ |
| `--simple` | Fuerza la ordenación por selección |
| `--medium` | Fuerza la ordenación por chunks |
| `--complex` | Fuerza radix sort |
| `--adaptive` | Elige según el desorden. Es la opción por defecto si no se indica ningún selector |

---

## Benchmark

`--bench` está pensado para escribir lo siguiente en `stderr` después de ordenar, dejando las operaciones en `stdout`:

* El desorden, en porcentaje con dos decimales.
* La estrategia usada y su clase de complejidad.
* El número total de operaciones.
* El número de operaciones de cada tipo.

Las operaciones se imprimen siempre, también con `--bench`. Para generar `args.txt` con `shuf`, guardar el resumen en `bench.txt` y pasar las operaciones al checker:

```bash
shuf -i 0-9999 -n 500 > args.txt
./push_swap --bench $(cat args.txt) 2> bench.txt | ./checker_linux $(cat args.txt)
cat bench.txt
```

`2> bench.txt` guarda solo `stderr`, y el pipe solo pasa `stdout`, así que el checker recibe únicamente las operaciones. Debe imprimir `OK`.

**Estado actual:** la flag se acepta, pero este resumen aún no está implementado, así que no imprime nada adicional.

---

## Algoritmos

Antes de ordenar, `index_list` asigna a cada número su posición final (de `0` a `n - 1`). La ordenación por chunks y radix sort trabajan con estas posiciones en lugar de con los valores originales, así que los números grandes o negativos no suponen ningún coste adicional.

### 1. Simple: ordenación por selección

1. Busca el número más pequeño de `a`.
2. Lo sube a la cima por el camino más corto, con `ra` o `rra`.
3. Si lo que queda en `a` ya está ordenado, se detiene. Si no, pasa el número a `b` con `pb`.
4. Cuando `a` está ordenada, lo devuelve todo con `pa`. `b` guarda los números más pequeños con el mayor de ellos en la cima, así que quedan en el orden correcto.

**Por qué este algoritmo:** es sencillo de explicar y tiene una cota `O(n²)` clara. Además, al detenerse en cuanto `a` está ordenada, resulta barato con entradas casi ordenadas, y por eso lo usa la estrategia adaptativa.

**Cota superior:** llegar al mínimo de `k` elementos cuesta como mucho `k/2` rotaciones. Al sumarlo para cada `k` salen unas `n²/4` rotaciones, más un máximo de `2n` pushes: **`O(n²)`**.

### 2. Media: ordenación por chunks

1. Divide las posiciones en rangos (chunks) de unos `√n` números cada uno.
2. Pasa a `b` todos los números del chunk actual, tomando siempre el primero que encuentra desde la cima de `a`. Los números de la mitad inferior de su chunk se envían además al fondo de `b` con `rb`.
3. Repite con el chunk siguiente hasta vaciar `a`.
4. Sube a la cima de `b` el mayor número restante por el camino más corto y lo devuelve con `pa`, hasta vaciar `b`.

**Por qué este algoritmo:** el enunciado lo propone para esta clase, y el paso 2 deja `b` más o menos ordenada, con los números mayores cerca de sus dos extremos. Así, las rotaciones del paso 4 son cortas.

**Cota superior:** cada chunk necesita aproximadamente una pasada por `a`, es decir, unas `n` rotaciones como mucho, y hay unos `√n` chunks. Eso da unas `n√n` rotaciones, más `n` pushes y un máximo de `n` `rb` en la primera fase. En la segunda, el siguiente número que hay que devolver está a unas `√n` posiciones o menos de un extremo de `b`, lo que suma otras `n√n`: **`O(n√n)`**.

### 3. Compleja: radix sort (LSD)

Para cada bit de las posiciones, del menos al más significativo:

1. Mira una vez cada uno de los `n` números de `a`: `pb` si el bit es `0`, `ra` si es `1`.
2. Lo devuelve todo con `pa`.

Tras el último bit, `a` está ordenada.

**Por qué este algoritmo:** no necesita casos especiales y su coste solo depende de `n`. El mismo tamaño cuesta siempre lo mismo, sea cual sea el orden de los números: 500 números siempre requieren 6 784 operaciones.

**Cota superior:** hay `⌈log₂ n⌉` bits, y cada uno cuesta como mucho `n` operaciones en el paso 1 y `n` en el paso 2. En total, como mucho `2n⌈log₂ n⌉` operaciones: **`O(n log n)`**.

### 4. Estrategia adaptativa

`compute_disorder` se ejecuta antes de cualquier movimiento. Compara todos los pares de números y devuelve la fracción de pares en orden incorrecto: `0` significa ordenado y `1`, totalmente invertido.

| Entrada | Método | Complejidad en operaciones |
| ------- | ------ | -------------------------- |
| 2 o 3 números | Casos directos (`sa`, `ra`, `rra`) | 2 operaciones como mucho |
| 4 o 5 números | Ordenación por selección | 12 operaciones como mucho |
| Desorden `< 0.2` | Ordenación por selección | `O(n²)` |
| `0.2 ≤` desorden `< 0.5` | Ordenación por chunks | `O(n√n)` |
| Desorden `≥ 0.5` | Radix sort | `O(n log n)` |

**Justificación de los umbrales.** Los valores `0.2` y `0.5` y sus objetivos de complejidad vienen del enunciado. Los métodos se eligieron así:

* **Desorden bajo:** la selección se detiene pronto, así que puede superar a los otros métodos cuando hay muy poco fuera de sitio.
* **Desorden medio:** el coste de la selección ya ha crecido mucho, mientras que la ordenación por chunks se mantiene dentro de la clase exigida.
* **Desorden alto:** radix sort tiene un coste fijo y cumple el objetivo más estricto.

Operaciones medidas con una sola muestra por fila, con 500 números desordenados mediante intercambios aleatorios:

| Desorden | Selección | Chunks | Radix |
| -------- | --------- | ------ | ----- |
| 0,002 | 1 001 | 1 749 | 6 784 |
| 0,048 | 3 897 | 3 629 | 6 784 |
| 0,123 | 10 044 | 6 117 | 6 784 |
| 0,222 | 17 020 | 6 767 | 6 784 |
| 0,346 | 28 752 | 7 464 | 6 784 |
| 0,506 | 31 916 | 7 577 | 6 784 |

La tabla muestra también una limitación conocida: la selección no es el método más barato en todo el tramo de desorden bajo. Con 0,123 cuesta más que los otros dos, aunque sigue cumpliendo el `O(n²)` exigido.

**Entradas pequeñas.** Con 5 números o menos, la estrategia ignora los umbrales de desorden y usa los casos directos o la selección. Esto no cambia ninguna clase de complejidad, porque en entradas tan pequeñas el coste está acotado por una constante.

**Espacio.** Todas las estrategias trabajan con los `n` nodos creados durante el parseo. Las operaciones solo reenlazan esos nodos y no reservan memoria, así que el espacio es `O(n)` en total y `O(1)` aparte de las dos pilas.

---

## Validación de la entrada

Si la entrada no es válida, el programa escribe `Error` seguido de un salto de línea en `stderr`, no escribe nada en `stdout` y libera toda su memoria. Estos casos no son válidos:

* **Argumentos que no son enteros:**

```bash
./push_swap 1 2 hello 4
./push_swap "0 ++1 +-3"
```

* **Valores fuera del rango de `int`:**

```bash
./push_swap 1 2147483648 3
```

* **Duplicados**, comparados por valor, así que `0` y `-0` cuentan como el mismo número:

```bash
./push_swap 3 2 3 1
./push_swap 0 -0
```

* **Argumentos vacíos** o solo con espacios:

```bash
./push_swap 3 "" 2
```

* **Flags desconocidas o repetidas, o dos selectores a la vez:**

```bash
./push_swap --foo 2 1
./push_swap --bench --bench 2 3 1
./push_swap --medium --simple 2 3 1
```

* **Flags después de los números:**

```bash
./push_swap 2 3 1 --bench
```

* **Tabuladores o saltos de línea dentro de un argumento entre comillas.** `push_swap` no los lee como separadores, solo los espacios:

```bash
./push_swap "$(printf '3\t1\t2')"
./push_swap "$(cat args.txt)"
```

---

## Recursos

* [Enunciado de Push_swap de 42](https://projects.intra.42.fr/projects/42cursus-push_swap): reglas, objetivos de complejidad y de rendimiento.
* [Notación Big O](https://en.wikipedia.org/wiki/Big_O_notation): cómo se definen las clases de complejidad.
* [Ordenación por selección](https://en.wikipedia.org/wiki/Selection_sort): base de la estrategia simple.
* [Bucket sort](https://en.wikipedia.org/wiki/Bucket_sort): la idea de dividir los valores en rangos, como hace la ordenación por chunks.
* [Radix sort](https://en.wikipedia.org/wiki/Radix_sort): base de la estrategia compleja.
* Artículos de GeeksforGeeks sobre [pilas](https://www.geeksforgeeks.org/dsa/stack-data-structure/), [análisis Big O](https://www.geeksforgeeks.org/dsa/analysis-algorithms-big-o-analysis/), [ordenación por selección](https://www.geeksforgeeks.org/dsa/selection-sort-algorithm-2/), [bucket sort](https://www.geeksforgeeks.org/dsa/bucket-sort-2/) y [radix sort](https://www.geeksforgeeks.org/dsa/radix-sort/).
* [Push_swap Visualizer](https://push-swap42-visualizer.vercel.app/): para ver paso a paso cómo se mueven las pilas durante la ordenación.

### Uso de IA

Usamos Claude Code (Anthropic) para estas tareas:

* **Pruebas y análisis:** revisar el estado del proyecto frente al enunciado, medir el rendimiento y ejecutar las pruebas de la hoja de evaluación.
* **Git:** resolver los conflictos de merge entre nuestras ramas.
* **Correcciones de norma:** en `adaptative_algorithm.c`, `chunck_algorithm.c`, `compute_disorder.c`, `radix_sort_algorithm.c` y `lib/printf/ft_printf.c`.
* **Código:** `run_strategy` en `main.c`, que conecta las flags con cada algoritmo; `selection_sort` en `selection_algorithm.c`; y el uso de la selección con 5 números o menos en `adaptative_sort`.
* **Documentación:** el borrador de este README.

Hemos revisado y probado este trabajo nosotros mismos, y los dos somos responsables de entenderlo.

