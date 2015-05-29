# m_list
General-purpose linked list implementation in the C89 language that runs on all
POSIX-compatible systems.

## Features
### Initialisation
To initialise a list, call the `m_list_init` function. 

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
separate memory managed by the `m_list`. The decision is made in one of the  
`m_list_append`, `m_list_prepend`, `m_list_insert` functions. Possible values
are either `M_LIST_DEEP_COPY` for an internal copy of the memory, or
`M_LIST_SHALLOW_COPY` for a pointer-copy only. The `size` argument (one before
the last) of the function can be ignored with value `0` in case of the shallow
copy.

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
void
print_int(void* arg, void* payload)
{
  (void) payload;
  printf("%d ", *((int*)arg));
}

int
main(void)
{
  struct m_list list;
  uint8_t i;

  m_list_init(&list);
  for (i = 0; i < 10; i++)
    m_list_append(&list, M_LIST_COPY_DEEP, &i, sizeof(uint8_t));

  m_list_map(&list, print_int, NULL);
}
```

## Return values
* `M_LIST_OK` success
* `M_LIST_E_NULL` one of the arguments is `NULL`
* `M_LIST_E_TOO_SHORT` the `n` in `n_list_nth` is beyond the bounds
* `M_LIST_E_UNKNOWN_COPY` the copy type is neither `M_LIST_SHALLOW_COPY` nor `M_LIST_DEEP_COPY`
* `M_LIST_E_NOT_PRESENT` `m_list_remove_safe` finds out that the element is not from the specified list

## Supported platforms
 * FreeBSD 10.0 with Clang 3.3
 * OS X 10.9 with Clang 3.5

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

