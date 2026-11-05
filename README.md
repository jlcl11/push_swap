*This project has been created as part of the 42 curriculum by jocorral, jnunez-b.*

# Push_swap

## Description

**Push_swap** is a sorting project with a twist: the numbers live on two stacks, `a` and `b`, and can only be moved with a small set of operations. The program does not just sort them: it prints the list of operations that sorts them, trying to keep that list as short as possible.

All the numbers start on stack `a`, with the first argument on top, and stack `b` starts empty. After running the list, `a` must be in ascending order, with the smallest number on top, and `b` must be empty.

The available operations are:

| Operation | Effect |
| --------- | ------ |
| `sa` / `sb` | Swaps the first two elements of `a` / `b` |
| `ss` | `sa` and `sb` at the same time |
| `pa` | Moves the top of `b` to the top of `a` |
| `pb` | Moves the top of `a` to the top of `b` |
| `ra` / `rb` | Rotates `a` / `b`: the first element becomes the last |
| `rr` | `ra` and `rb` at the same time |
| `rra` / `rrb` | Reverse-rotates `a` / `b`: the last element becomes the first |
| `rrr` | `rra` and `rrb` at the same time |

The project is about **algorithmic complexity**, so every complexity class in this document is measured in **number of Push_swap operations generated**, not in CPU time.

The program includes four strategies:

| Strategy | Algorithm | Complexity in operations |
| -------- | --------- | ------------------------ |
| Simple | Selection sort | `O(n²)` |
| Medium | Chunk sort | `O(n√n)` |
| Complex | LSD radix sort | `O(n log n)` |
| Adaptive | Picks one of the above based on the disorder | Depends on the disorder |


---

## Team contributions

**`jocorral`**

* The eleven **stack operations** (the moves themselves).
* The **simple strategy** (selection sort).
* **Stack management** (`stack.c`).
* The **parser and input validation**, and flag reading.
* The **Makefile** and the organization of the project into folders.
* Merging the branches and the documentation.

**`jnunez-b`**

* The **medium strategy** (chunk sort), including `index_list`.
* The **complex strategy** (radix sort).
* The **adaptive strategy**, including the 2- and 3-number cases, and the **disorder metric**.
* The **benchmark mode**: the per-operation counters, the strategy and complexity displayed, and printing the summary (`display_bench`).


## Instructions

### Compilation

```bash
make          # builds libft and printf, and generates ./push_swap
make clean    # removes the object files
make fclean   # removes the object files and the binaries
make re       # fclean + all
```

The project has no bonus: the `Makefile` has no `bonus` rule and the repository does not contain a checker of its own.

### Usage

```bash
./push_swap [selector] [--bench] numbers
```

Flags go before the numbers. The numbers can be given as separate arguments, as a quoted list, or as a mix of both:

```bash
./push_swap 3 1 2
./push_swap "3 1 2"
./push_swap 3 "1 2"
```

The program prints one operation per line:

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

If the numbers are already sorted, or if none are given, it prints no operations. With `--bench` and a sorted list it does print the summary on `stderr`, as shown in [How to run the benchmark](#how-to-run-the-benchmark).

### How to use the checker

`checker_linux` is the binary provided with the subject to check the result. It is not part of this repository: you have to download it from the intra, put it in this folder and make it executable with `chmod +x checker_linux`.

It takes the same list of numbers as `push_swap`, reads the operations from standard input and runs them:

| Output | Meaning |
| ------ | ------- |
| `OK` | `a` ends up sorted and `b` ends up empty |
| `KO` | The operations are valid, but they do not sort the list |
| `Error` | A number is invalid or an operation does not exist |

The usual way is to pipe the output of `push_swap` straight into it:

```bash
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_linux $ARG
ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker_linux $ARG
```

In zsh, write `${=ARG}` instead of `$ARG`.

To test with 500 random numbers and count the operations, as in the subject:

```bash
shuf -i 0-9999 -n 500 > args.txt
./push_swap $(cat args.txt) | ./checker_linux $(cat args.txt)
./push_swap $(cat args.txt) | wc -l
```

`shuf` writes one number per line. `push_swap` does not read tabs or newlines: it is the shell that removes them when splitting the arguments of `$(cat args.txt)`, as long as it is not quoted.

You can also type the operations by hand, one per line, and finish with `Ctrl+D`:

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

### How to run the benchmark

To generate `args.txt` with `shuf`, see the summary in the terminal and pipe the operations into the checker:

```bash
shuf -i 0-9999 -n 500 > args.txt ; ./push_swap --bench $(cat args.txt) | ./checker_linux $(cat args.txt)
```

The pipe only carries `stdout`, so the checker receives only the operations and the `stderr` summary shows up in the terminal:

```text
[bench] disorder: 51.99%
[bench] strategy: Adaptive / O(nlogn)
[bench] total_ops: 6784
[bench] sa: 0  sb: 0  ss: 0  pa: 2284  pb: 2284
[bench] ra: 2216  rb: 0  rr: 0  rra: 0  rrb: 0  rrr: 0
OK
```

To save the summary in `bench.txt` instead of seeing it in the terminal:

```bash
shuf -i 0-9999 -n 500 > args.txt
./push_swap --bench $(cat args.txt) 2> bench.txt | ./checker_linux $(cat args.txt)
cat bench.txt
```

**Already sorted list.** If no selector is forced, the program uses no strategy, because there are no moves to make. It shows this with `(None!)` instead of the complexity, and prints no operations:

```text
$> ./push_swap --bench 1 2 3 4 5
[bench] disorder: 0.00%
[bench] strategy: Adaptive / (None!)
[bench] total_ops: 0
[bench] sa: 0  sb: 0  ss: 0  pa: 0  pb: 0
[bench] ra: 0  rb: 0  rr: 0  rra: 0  rrb: 0  rrr: 0
```

With a forced selector no algorithm runs either, but the summary shows the requested selector and its class, for example `Simple / O(n²)`, with `total_ops: 0`.

---

### How to check memory with valgrind

```bash
valgrind --leak-check=full --show-leak-kinds=all ./push_swap 4 67 3 87 23 > /dev/null
```

`> /dev/null` hides the operations so that you only see the valgrind report, which is written to `stderr`. There are no leaks or errors if it ends like this:

```text
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Strategy selection

| Selector | Effect |
| -------- | ------ |
| `--simple` | Forces selection sort |
| `--medium` | Forces chunk sort |
| `--complex` | Forces radix sort |
| `--adaptive` | Chooses based on the disorder. This is the default if no selector is given |

---

## Benchmark

`--bench` writes the following to `stderr` after sorting, leaving the operations on `stdout`:

* The disorder, as a percentage with two decimals.
* The strategy used and its complexity class.
* The total number of operations.
* The number of operations of each type.

The operations are always printed, including with `--bench`. The commands and sample outputs are in [How to run the benchmark](#how-to-run-the-benchmark), including the case of an already sorted list.

---

## Algorithms

Before sorting, `index_list` gives each number its final position (from `0` to `n - 1`). Chunk sort and radix sort work with these positions instead of the original values, so large or negative numbers add no extra cost.

### 1. Simple: selection sort

1. Finds the smallest number in `a`.
2. Brings it to the top by the shortest path, with `ra` or `rra`.
3. If what remains in `a` is already sorted, it stops. Otherwise, it moves the number to `b` with `pb`.
4. Once `a` is sorted, it moves everything back with `pa`. `b` holds the smallest numbers with the largest of them on top, so they land in the right order.

**Why this algorithm:** it is simple to explain and has a clear `O(n²)` bound. Also, because it stops as soon as `a` is sorted, it is cheap on nearly sorted input, which is why the adaptive strategy uses it.

**Upper bound:** reaching the minimum of `k` elements costs at most `k/2` rotations. Summing this over every `k` gives about `n²/4` rotations, plus at most `2n` pushes: **`O(n²)`**.

### 2. Medium: chunk sort

1. Splits the positions into ranges (chunks) of about `√n` numbers each.
2. Moves all the numbers of the current chunk to `b`, always taking the first one found from the top of `a`. Numbers in the lower half of their chunk are also sent to the bottom of `b` with `rb`.
3. Repeats with the next chunk until `a` is empty.
4. Brings the largest remaining number to the top of `b` by the shortest path and moves it back with `pa`, until `b` is empty.

**Why this algorithm:** the subject suggests it for this class, and step 2 leaves `b` roughly sorted, with the largest numbers near both of its ends. This keeps the rotations in step 4 short.

**Upper bound:** each chunk needs roughly one pass over `a`, that is, at most about `n` rotations, and there are about `√n` chunks. This gives about `n√n` rotations, plus `n` pushes and at most `n` `rb` in the first phase. In the second, the next number to move back is about `√n` positions or fewer from one end of `b`, which adds another `n√n`: **`O(n√n)`**.

### 3. Complex: radix sort (LSD)

For each bit of the positions, from least to most significant:

1. Looks once at each of the `n` numbers in `a`: `pb` if the bit is `0`, `ra` if it is `1`.
2. Moves everything back with `pa`.

After the last bit, `a` is sorted.

**Why this algorithm:** it needs no special cases and its cost depends only on `n`. The same size always costs the same, whatever the order of the numbers: 500 numbers always take 6,784 operations.

**Upper bound:** there are `⌈log₂ n⌉` bits, and each costs at most `n` operations in step 1 and `n` in step 2. In total, at most `2n⌈log₂ n⌉` operations: **`O(n log n)`**.

### 4. Adaptive strategy

`compute_disorder` runs before any move. It compares every pair of numbers and returns the fraction of pairs in the wrong order: `0` means sorted and `1` means fully reversed.

| Input | Method | Complexity in operations |
| ----- | ------ | ------------------------ |
| 2 or 3 numbers | Direct cases (`sa`, `ra`, `rra`) | At most 2 operations |
| 4 or 5 numbers | Selection sort | At most 12 operations |
| Disorder `< 0.2` | Selection sort | `O(n²)` |
| `0.2 ≤` disorder `< 0.5` | Chunk sort | `O(n√n)` |
| Disorder `≥ 0.5` | Radix sort | `O(n log n)` |

**Rationale for the thresholds.** The values `0.2` and `0.5` and their complexity targets come from the subject. The methods were chosen as follows:

* **Low disorder:** selection stops early, so it can beat the other methods when very little is out of place.
* **Medium disorder:** the cost of selection has already grown a lot, while chunk sort stays within the required class.
* **High disorder:** radix sort has a fixed cost and meets the strictest target.

Operations measured with a single sample per row, with 500 numbers shuffled through random swaps:

| Disorder | Selection | Chunks | Radix |
| -------- | --------- | ------ | ----- |
| 0.002 | 1,001 | 1,749 | 6,784 |
| 0.048 | 3,897 | 3,629 | 6,784 |
| 0.123 | 10,044 | 6,117 | 6,784 |
| 0.222 | 17,020 | 6,767 | 6,784 |
| 0.346 | 28,752 | 7,464 | 6,784 |
| 0.506 | 31,916 | 7,577 | 6,784 |

The table also shows a known limitation: selection is not the cheapest method across the whole low-disorder range. At 0.123 it costs more than the other two, although it still meets the required `O(n²)`.

**Small inputs.** With 5 numbers or fewer, the strategy ignores the disorder thresholds and uses the direct cases or selection. This does not change any complexity class, because on inputs this small the cost is bounded by a constant.

**Space.** All strategies work with the `n` nodes created during parsing. The operations only relink those nodes and allocate no memory, so space is `O(n)` in total and `O(1)` apart from the two stacks.

---

## Performance

Moves measured with random lists of distinct numbers. Each cell shows **average / maximum**:

| Numbers | Runs | Default (adaptive) | `--simple` | `--medium` | `--complex` |
| ------- | ---- | ------------------ | ---------- | ---------- | ----------- |
| 3 | 1,000 | 1.2 / 2 | 2.2 / 4 | 6.5 / 8 | 8.4 / 10 |
| 5 | 1,000 | 7.9 / 12 | 7.9 / 12 | 15.2 / 17 | 24.8 / 25 |
| 100 | 200 | 928.0 / 1,084 | 1,464.0 / 1,742 | 785.9 / 822 | 1,084.0 / 1,084 |
| 500 | 100 | 7,243.1 / 7,726 | 32,349.8 / 34,334 | 7,586.3 / 7,782 | 6,784.0 / 6,784 |

The outputs of these 9,200 runs were checked with `checker_linux` and with a separately written stack simulator: all of them leave `a` sorted and `b` empty.

* **3 and 5 numbers:** the random samples include lists that were already sorted (163 of 1,000 with 3 numbers and 8 of 1,000 with 5), which count as 0 moves in the average. Testing all permutations as well (6 and 120), the maximum for the default strategy is 2 and 12 moves, respectively.
* **100 and 500 numbers:** the disorder of a random list is around `0.5`, right at the threshold between chunks and radix, so the default strategy uses one or the other depending on the list. With 100 numbers it chose chunks in 103 runs and radix in 97; with 500, chunks in 58 and radix in 42. That is why its maximum matches radix at 100 numbers (1,084), even though `--medium` is cheaper at that size.

---

## Input validation

If the input is invalid, the program writes `Error` followed by a newline to `stderr`, writes nothing to `stdout` and frees all its memory. These cases are invalid:

* **Arguments that are not integers:**

```bash
./push_swap 1 2 hello 4
./push_swap "0 ++1 +-3"
```

* **Values outside the `int` range:**

```bash
./push_swap 1 2147483648 3
```

* **Duplicates**, compared by value, so `0` and `-0` count as the same number:

```bash
./push_swap 3 2 3 1
./push_swap 0 -0
```

* **Empty arguments** or arguments with only spaces:

```bash
./push_swap 3 "" 2
```

* **Unknown or repeated flags, or two selectors at once:**

```bash
./push_swap --foo 2 1
./push_swap --bench --bench 2 3 1
./push_swap --medium --simple 2 3 1
```

* **Flags after the numbers:**

```bash
./push_swap 2 3 1 --bench
```

* **Tabs or newlines inside a quoted argument.** `push_swap` does not read them as separators, only spaces:

```bash
./push_swap "$(printf '3\t1\t2')"
./push_swap "$(cat args.txt)"
```

---

## Resources

* [42 Push_swap subject](https://projects.intra.42.fr/projects/42cursus-push_swap): rules, complexity and performance targets.
* [Big O notation](https://en.wikipedia.org/wiki/Big_O_notation): how complexity classes are defined.
* [Selection sort](https://en.wikipedia.org/wiki/Selection_sort): basis of the simple strategy.
* [Bucket sort](https://en.wikipedia.org/wiki/Bucket_sort): the idea of splitting values into ranges, as chunk sort does.
* [Radix sort](https://en.wikipedia.org/wiki/Radix_sort): basis of the complex strategy.
* GeeksforGeeks articles on [stacks](https://www.geeksforgeeks.org/dsa/stack-data-structure/), [Big O analysis](https://www.geeksforgeeks.org/dsa/analysis-algorithms-big-o-analysis/), [selection sort](https://www.geeksforgeeks.org/dsa/selection-sort-algorithm-2/), [bucket sort](https://www.geeksforgeeks.org/dsa/bucket-sort-2/) and [radix sort](https://www.geeksforgeeks.org/dsa/radix-sort/).
* [Push_swap Visualizer](https://push-swap42-visualizer.vercel.app/): to see step by step how the stacks move during sorting.

### Use of AI

* **Git:** resolving merge conflicts between our branches.
* **Norm fixes:** in `adaptative_algorithm.c`, `chunck_algorithm.c`, `compute_disorder.c`, `radix_sort_algorithm.c` and `lib/printf/ft_printf.c`.
* **Documentation:** the draft of this README and the script used to obtain the figures in the performance section.

---

## File structure

```text
.
├── Makefile
├── README.md
├── main.c                  # entry point and --bench summary
├── push_swap.h
├── ficheros/
│   ├── algoritmos/
│   │   ├── adaptative_algorithm.c    # adaptive strategy and the 2- and 3-number cases
│   │   ├── chunck_algorithm.c        # chunk sort and index_list
│   │   ├── compute_disorder.c        # disorder metric
│   │   ├── radix_sort_algorithm.c    # radix sort
│   │   └── selection_algorithm.c     # selection sort and is_sorted
│   ├── operaciones/
│   │   ├── op_utils.c
│   │   ├── push.c
│   │   ├── reverse_rotate.c
│   │   ├── rotate.c
│   │   └── swap.c
│   ├── parseo/
│   │   ├── flags.c                   # selectors and --bench
│   │   ├── parse.c
│   │   └── parse_utils.c
│   └── stack/
│       └── stack.c                   # stack management
└── lib/
    ├── libft/
    └── printf/
```

