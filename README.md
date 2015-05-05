# m_list
General-purpose linked list implementation in the C89 language that runs on all
POSIX-compatible systems.

## Features
### Initialisation
To initialise a list, call `m_list_init` function. A slightly more complicated
function exists with the purpose of initialising the elements - `m_elem_init`
that expects pointer to the content data and an information whether it should
make a deep copy of the content data in question.

### Access
The first and the last element of the list can be accessed with the
`m_list_first` and `m_list_last` functions respectively. The _n_-th element of
the list can be accessed with the `n_list_nth` function. Once you have obtained
the `struct m_elem` entry, you can move to the previous or the next element
with `m_elem_prev` and `m_elem_next` functions. To obtain the actual data
stored in the element, use the `m_elem_data` function.

### Insertion
To append or prepend elements to the list, use `m_list_append` and
`m_list_prepend` functions. To insert an element after another element that is
already in the list, use the `m_list_insert` function.

### Length
To retrieve the length of the list, use the function `m_list_length`. The
function operates in constant time.

### Modification
To remove an element from the list, use the function `m_list_remove` or
`m_list_remove_safe`. The difference between these two functions is that the
`safe` variant verifies that the element selected for removal belongs to the
specified list.
To remove all elements, use `m_list_clear`.

### Algorithms
In order to apply a certain function to all element data, the standard _map_
function is provided under the name `m_list_map`. 

### Deep/shallow copy
It is up to you to decide if the list element should point to already
existing data that you `mallloc`ed earlier or whether it should be copied to a
separate memory managed by the `m_list`. The decision is made in the
`m_elem_init` function, namely the last argument. Possible values are either 
`M_LIST_DEEP_COPY` for an internal copy of the memory, or `M_LIST_SHALLOW_COPY`
for a pointer-copy only. The `size` argument (one before the last) of the
function can be ignored with value `0` in case of the shallow copy.

## Time and space complexity
All operations have `O(1)` space complexity.

| Operation            |  Time  |
|----------------------|--------|
| `m_list_init`        | `O(1)` |
| `m_list_append`      | `O(1)` |
| `m_list_prepend`     | `O(1)` |
| `m_list_insert`      | `O(1)` |
| `m_list_length`      | `O(1)` |
| `m_list_first`       | `O(1)` |
| `m_list_last`        | `O(1)` |
| `m_list_nth`         | `O(n)` |
| `m_list_clear`       | `O(n)` |
| `m_list_remove`      | `O(1)` |
| `m_list_remove_safe` | `O(n)` |
| `m_list_map`         | `O(n)` |
| `m_elem_init`        | `O(1)` |
| `m_elem_data`        | `O(1)` |
| `m_elem_next`        | `O(1)` |
| `m_elem_prev`        | `O(1)` |
where `n` denotes the number of list elements.

## Example
Initialise the list with numbers between `0` to `9` inclusive and print them to
the `stdout`.
```C
#include <stdio.h>
#include <stdint.h>
#include <m_list.h>

void
print_int(void* arg)
{
  printf("%d ", *((int*)arg));
}

int
main(void)
{
  struct m_list list;
  struct m_elem* elem;
  uint8_t i;
  int* content;

  m_list_init(&list);
  for (i = 0; i < 10; i++) {
    content = malloc(sizeof(int));
    *content = i;

    struct m_elem* elem = malloc(sizeof(struct m_elem));
    m_elem_init(elem, content, 0, M_LIST_SHALLOW_COPY);

    m_list_append(&list, elem);
  }

  m_list_map(&list, print_int);
}
```

## Supported platforms
 * FreeBSD 10.0
 * OS X 10.9

If a platform does not appear to be in the previous list, it does not mean that
`m_list` will not work in such environment. It only means that nobody tested
it - you are encouraged to do so and report either success or failure.

## Build
```
$ ninja
```

## License
2-clause BSD license. For more information please consult the
[LICENSE](LICENSE.md) file. In the case that you need a different license, feel
free to contact me.

## Author
Daniel Lovasko (lovasko@freebsd.org)

