# push_swap: documentación técnica (parte de Jose)

Este documento describe todo lo que hay implementado hasta ahora: cómo está
organizado el código, cómo funciona cada pieza y qué queda pendiente para
conectarlo con la parte de Jose T. No sustituye al `README.md` que pide el
subject (ver [Pendiente](#10-pendiente)).

Reparto de tareas (archivo `Repartotareah`):

| Persona | Tareas | Estado |
|---|---|---|
| Jose | Operaciones (`sa`, `pb`, `rr`…), algoritmo simple, creación de las pilas, parseo y validación de la entrada | ✅ Hecho |
| Jose T | Algoritmos intermedio, complejo y adaptativo, índice de desorden, selector de estrategia, benchmark | Pendiente |

---

## 1. Compilar y ejecutar

```sh
make            # compila libft, ft_printf y push_swap
make clean      # borra los .o (también los de libft y printf)
make fclean     # además borra push_swap, libft.a y libftprintf.a
make re         # fclean + all
```

`make` no vuelve a enlazar si no ha cambiado nada (un segundo `make` responde
"Nothing to be done").

```sh
./push_swap 3 1 2              # tres argumentos
./push_swap "3 1 2"            # un argumento con espacios
./push_swap 3 "1 2"            # mezcla
./push_swap --simple 5 4 3 2 1 # forzar estrategia
./push_swap --bench --complex 3 1 2
```

El programa escribe en stdout una operación por línea y nada más. Los errores
salen por stderr como `Error\n`.

---

## 2. Estructura del proyecto

```
push_swap/
├── Makefile
├── push_swap.h          # tipos y prototipos de todo el proyecto
├── main.c               # flujo principal y salida de error
├── flags.c              # --simple, --medium, --complex, --adaptive, --bench
├── parse.c              # argv → pila a (usa ft_split)
├── parse_utils.c        # is_number, ft_atol, has_duplicates
├── stack.c              # crear, añadir, contar y liberar nodos
├── algorithm.c          # is_sorted y bubble_sort (estrategia simple)
├── debug.c              # print_stacks (solo para depurar, no se llama)
├── operations/
│   ├── swap.c           # sa, sb, ss
│   ├── push.c           # pa, pb
│   ├── rotate.c         # ra, rb, rr
│   └── reverse_rotate.c # rra, rrb, rrr
├── libft/               # libft propia → libft.a
└── printf/              # ft_printf propia → libftprintf.a (usa ../libft)
```

Los objetos se generan en `obj/`, con la misma estructura de carpetas
(`obj/operations/swap.o`…). La regla de los `.o` crea la subcarpeta con
`mkdir -p $(dir $@)`.

Todos los archivos pasan norminette.

---

## 3. Estructuras de datos (`push_swap.h`)

### La pila

```c
typedef struct s_stack
{
	int				value;
	struct s_stack	*next;
}	t_stack;
```

Cada pila es una lista enlazada simple. El **primer nodo es la cima**. Una pila
vacía es un puntero `NULL`. Todas las funciones que modifican una pila reciben
`t_stack **`, para poder cambiar la cima.

**¿Por qué no `t_list` de libft?** En `t_list`, `content` es un `void *`: habría
que reservar memoria para cada `int` y escribir `*(int *)nodo->content` en todo
el código. Con un struct propio el valor va dentro del nodo, hay la mitad de
mallocs y el código de los algoritmos se lee mejor. Si Jose T necesita más datos
por nodo (por ejemplo, un `index` con la posición que tendrá el número una vez
ordenado), basta con añadir un campo aquí.

### Flags

```c
typedef enum e_strategy
{
	STRAT_ADAPTIVE,   /* por defecto */
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX
}	t_strategy;

typedef struct s_flags
{
	t_strategy	strategy;
	int			bench;    /* 1 si se ha pasado --bench */
}	t_flags;
```

---

## 4. Flujo del programa (`main.c`)

```
argv
 │
 ├─ parse_flags ──── error ───────────────► "Error" a stderr, exit 1
 │      │
 │      └─ devuelve `first` = índice del primer número
 │
 ├─ first == argc (no hay números) ───────► no imprime nada, exit 0
 │
 ├─ parse_args(argv + first) ── error ────► libera a, "Error", exit 1
 │
 ├─ is_sorted(a)? ── sí ──────────────────► no imprime nada
 │      └─ no → bubble_sort(&a)             (TODO: selector de Jose T)
 │
 └─ stack_clear(&a), stack_clear(&b), exit 0
```

`error_exit` escribe el error con `ft_putendl_fd("Error", 2)` (ft_printf solo
escribe en stdout) y libera la pila antes de salir, así no hay fugas tampoco en
los casos de error.

---

## 5. Parseo y validación

### 5.1 Flags (`flags.c`)

`parse_flags(argc, argv, &flags)` recorre los argumentos **del principio** que
empiezan por `--`. En cuanto encuentra uno que no empieza por `--`, para y
devuelve su índice: desde ahí todo se trata como números.

- `is_flag(arg, "--simple")` compara con
  `ft_strncmp(arg, flag, ft_strlen(flag) + 1)`. El `+ 1` incluye el `'\0'` en
  la comparación, así `--simplex` no se toma por `--simple`.
- `set_strategy` guarda la estrategia y marca `chosen`. Un segundo selector es
  un error.

| Entrada | Resultado |
|---|---|
| (sin flags) | estrategia `--adaptive`, sin bench |
| `--bench --simple 3 1 2` | ✅ el orden de las flags da igual |
| `--bench` (sin números) | no imprime nada, como si no hubiera argumentos |
| `--simple --complex 1 2` | Error (dos selectores) |
| `--bench --bench 1 2` | Error (flag repetida) |
| `--foo 1`, `--simplex 1`, `-- 1` | Error (flag desconocida) |
| `1 --simple` | Error (después de un número, `--simple` no es un número) |

Los números negativos (`-5`) empiezan por un solo guion, así que no se
confunden con flags.

### 5.2 Números (`parse.c`)

`parse_args(count, args, &a)` recibe solo los argumentos de números (`main`
le pasa `argc - first, argv + first`).

1. **Partir por espacios.** Cada argumento pasa por `ft_split(args[i], ' ')`.
   Las comillas las quita la shell antes de que el programa arranque:
   `./push_swap 3 "1 2"` llega como `argv = {"3", "1 2"}`. `ft_split`
   convierte `"1 2"` en `{"1", "2"}`, y `"3"` en `{"3"}`. Así se tratan igual
   los argumentos con y sin comillas.
2. **Argumento vacío.** Si `ft_split` devuelve un array vacío (`""` o `"   "`),
   es un error.
3. **Cada trozo** pasa por `add_numbers`: validar con `is_number`, convertir con
   `ft_atol`, comprobar que cabe en un `int`, crear el nodo con `stack_new` y
   añadirlo al fondo con `stack_add_back`. Así el **primer número del input
   queda en la cima**.
4. Al terminar, `has_duplicates` busca repetidos.

El array de `ft_split` se libera siempre con `free_split`, tanto si todo va bien
como si hay error a mitad. Si hay error, los nodos que ya estaban en `a` los
libera `main` con `stack_clear`.

### 5.3 Utilidades (`parse_utils.c`)

**`is_number(str)`**: un signo opcional (`+` o `-`) seguido de **al menos** un
dígito, y nada más.
- Usa `ft_strchr("+-", str[i])` para el signo. Antes comprueba que `str[i]` no
  sea `'\0'`, porque `ft_strchr` también encuentra el terminador y daría por
  bueno un signo inexistente.
- Usa `ft_isdigit` para el resto.

**`ft_atol(str)`**: igual que `ft_atoi` pero devuelve `long`.
- **Por qué hace falta:** `ft_atoi` devuelve `int`, así que con `2147483648` ya
  ha desbordado antes de que se pueda comprobar el rango. Con `long` se compara
  `n > INT_MAX || n < INT_MIN` sin problemas.
- Deja de acumular en cuanto `n > INT_MAX + 1`. Así un número de 30 cifras
  tampoco desborda el `long` (el resultado ya está fuera de rango, y eso basta
  para dar Error).
- `-2147483648` (`INT_MIN`) es válido: llega a `2147483648`, que no supera
  `INT_MAX + 1`, y al aplicarle el signo cabe en un `int`.

**`has_duplicates(stack)`**: compara cada nodo con todos los siguientes,
O(n²). Compara los valores ya convertidos, así que `0`, `-0`, `+0` y `00`
cuentan como el mismo número.

### 5.4 Tabla de casos probados

| Entrada | Salida |
|---|---|
| *(nada)* | nada, exit 0 |
| `""`, `"   "` | Error |
| `1a`, `+`, `-`, `1.5` | Error |
| `1 2 1`, `0 -0` | Error (duplicado) |
| `2147483648`, `99999999999999999999` | Error (fuera de int) |
| `-2147483648 5` | ✅ válido |
| `"1   2"` | ✅ los espacios repetidos se ignoran |
| `"1\t2"` | Error (solo se parte por espacios) |
| `1 2 3` | nada (ya está ordenado) |

---

## 6. Operaciones (`operations/`)

Cada archivo tiene una función `static` que hace el movimiento **sin imprimir**,
y las funciones públicas, que la llaman e imprimen el nombre con `ft_printf`.
Las dobles (`ss`, `rr`, `rrr`) llaman dos veces a la función interna e
imprimen **una sola** línea.

Todas las operaciones sobre pilas con 0 o 1 elementos (o `push` desde una pila
vacía) no hacen nada, pero **sí imprimen**. El algoritmo es quien decide cuándo
tiene sentido llamarlas.

| Archivo | Interna | Públicas | Qué hace | Coste |
|---|---|---|---|---|
| `swap.c` | `swap` | `sa sb ss` | intercambia los dos primeros nodos: `[1]→[2]→[3]` ⇒ `[2]→[1]→[3]` | O(1) |
| `push.c` | `push` | `pa pb` | saca la cima de una pila y la pone en la cima de la otra | O(1) |
| `rotate.c` | `rotate` | `ra rb rr` | la cima pasa al fondo: `[1]→[2]→[3]` ⇒ `[2]→[3]→[1]` | O(n) |
| `reverse_rotate.c` | `reverse_rotate` | `rra rrb rrr` | el fondo pasa a la cima: `[1]→[2]→[3]` ⇒ `[3]→[1]→[2]` | O(n) |

- `pa` mueve de **b a a**, y `pb` de **a a b**.
- `swap`, `push` y `reverse_rotate` solo reencadenan punteros: nunca crean ni
  liberan nodos.
- `rotate` reutiliza `stack_add_back`, y `push` y `reverse_rotate` reutilizan
  `stack_push`.
- `rotate` y `reverse_rotate` son O(n) porque hay que recorrer la lista hasta el
  final. No afecta al número de operaciones (lo que se evalúa), solo al tiempo
  de ejecución.

---

## 7. Gestión de pilas (`stack.c`)

| Función | Qué hace |
|---|---|
| `stack_new(value)` | crea un nodo con `ft_calloc`, que ya deja `next = NULL`. Devuelve `NULL` si falla la reserva |
| `stack_push(&s, node)` | pone `node` en la cima |
| `stack_add_back(&s, node)` | pone `node` al fondo (O(n)) |
| `stack_size(s)` | número de nodos |
| `stack_clear(&s)` | libera todos los nodos y deja `s = NULL` |

Si falla `malloc` durante el parseo, `add_numbers` devuelve 0 y el programa
termina con `Error`, liberando lo que ya se había reservado.

---

## 8. Algoritmo simple (`algorithm.c`)

**`is_sorted(stack)`**: devuelve 1 si cada valor es menor que el siguiente.
Es pública porque `main` la usa para no hacer nada con una entrada ya ordenada.
Jose T también puede usarla.

**`bubble_sort(&a)`**: ordenación de burbuja usando solo `sa` y `ra`, sin
tocar la pila b.

```
mientras a no esté ordenada:
    repetir size-1 veces:
        si cima > segundo: sa      # el mayor de los dos baja una posición
        ra                         # avanzar un puesto
    ra                             # una rotación más: la pila vuelve a su sitio
```

Tras `size` rotaciones la pila da la vuelta completa, y en cada pasada el mayor
de los que quedan "flota" hasta su sitio, como en la burbuja clásica.

- **Complejidad:** como mucho n pasadas de unas 2n operaciones ⇒ **O(n²)**
  operaciones. Memoria O(1) extra (no crea nodos).
- **Medido** (entradas aleatorias): 5 números ≈ 6 ops, 10 ≈ 70, 50 ≈ 2 900,
  100 ≈ 12 200.
- **Verificado** con un simulador del checker sobre entradas aleatorias de
  20 a 100 números, también negativos: siempre deja a ordenada y b vacía.

Cumple como estrategia `--simple` (O(n²)). Para inputs medianos o grandes
hacen falta las estrategias de Jose T.

### `debug.c`

`print_stacks(a, b)` imprime las dos pilas en columnas, con la cima arriba. Se
compila pero **no se llama**: la salida entregada solo puede tener operaciones.
Para depurar, llámala temporalmente desde `main` y quita la llamada antes de
hacer commit.

---

## 9. Uso de libft y ft_printf

| Función | Dónde | Para qué |
|---|---|---|
| `ft_split` | `parse.c` | partir cada argumento por espacios |
| `ft_isdigit` | `parse_utils.c` | validar y convertir dígitos |
| `ft_strchr` | `parse_utils.c` | detectar el signo `+`/`-` |
| `ft_strncmp`, `ft_strlen` | `flags.c` | comparar flags exactas |
| `ft_calloc` | `stack.c` | crear nodos a cero |
| `ft_putendl_fd` | `main.c` | `Error\n` por stderr |
| `ft_printf` | `operations/*.c`, `debug.c` | imprimir operaciones y pilas |

No se usa `ft_atoi` porque no permite detectar desbordamientos (ver
`ft_atol`). Tampoco se usan las funciones `ft_lst*`, por el motivo explicado en
la sección 3.

`printf/` y `libft/` se suben al repo como archivos normales: en la evaluación
se clona y se compila con `make`, así que tienen que estar.

---

## 10. Pendiente

### Integración con Jose T
- **Selector de estrategia.** En `main.c` hay un `TODO` donde ahora se llama a
  `bubble_sort`. Ahí debe ir la llamada al selector pasándole `flags`, por
  ejemplo `sort_stack(&a, &b, &flags)`. Ahora mismo **todas las flags ejecutan
  bubble_sort**.
- **Firma común de los algoritmos.** `bubble_sort` recibe solo `t_stack **`.
  Los demás necesitarán también b. Conviene pactar una firma común, por
  ejemplo `void algo(t_stack **a, t_stack **b)`.
- **Benchmark.** `--bench` ya se lee (`flags.bench`), pero no hace nada. Su
  salida tiene que ir a **stderr**, y contar las operaciones de cada tipo
  requiere un contador en las operaciones (por ejemplo, un struct de contadores
  que se pase a cada operación, o que se incremente al imprimir).

### README.md obligatorio (subject, capítulo VII)
Tiene que estar en la raíz e incluir:
- la primera línea en cursiva: *Este proyecto ha sido creado como parte del
  currículo de 42 por jocorral, &lt;login de Jose T&gt;*;
- secciones **Descripción**, **Instrucciones** y **Recursos** (incluido para
  qué se ha usado IA y en qué partes);
- la contribución de cada persona;
- la explicación y justificación de los algoritmos, los umbrales del índice de
  desorden y el análisis de complejidad.

Este documento sirve como base para las partes de parseo, operaciones y
algoritmo simple.
