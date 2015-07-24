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
#### Map
In order to apply a certain function to all element data, the standard _map_
function is provided under the name `m_list_map`. 
#### Join
The standard _join_ algorithm allows you to insert an element between every
consecutive pair of elements in the list. Note that this is a very powerful
ability when combined with shallow copies (hence the actual object exists only
once).

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
| `m_list_join`        | `O(n)` |
| `m_elem_init`        | `O(1)` |
| `m_elem_data`        | `O(1)` |
| `m_elem_next`        | `O(1)` |
| `m_elem_prev`        | `O(1)` |
where `n` denotes the number of list elements.

## Examples
 * [Sum of integers](examples/sum.md)
 * [Comma-separated words](examples/commas.md)

## Using m_list as other data structures
### Stack
By using only a certain subset of the `m_list` API, it is possible to achieve
the functionality of the stack data structure. Since it is possible to
manipulate with both ends of a `m_list`, it is necessary to choose one end and
be consistent. This example will use the beginning of the list.
#### top
In order to see what is on top of the stack, use the `m_list_first` function.
#### pop
To remove the top value from the stack, use the `m_list_remove_first` function.
#### push
Adding to the stack is enabled by the `m_list_prepend` function.

### Queue
As with the stack, it is necessary to choose a direction of usage of the list.
The queue in this example will retrieve elements from the beginning of the list
and add new values to the end.
#### peak
To see what will be the next dequeued element, use the `m_list_first` function.
#### enqueue
To add elements to the queue, use the `m_list_append` function.
#### dequeue
To retrieve elements from the queue, use the `m_list_remove_first` function.

## Return codes
### `M_LIST_OK`
Used by all algorithms and general-purpose functions in case of a successful
run of the function.

### `M_LIST_TRUE`
Used by all predicates and some of the general-purpose functions to indicate
that the expected conditions were met.

### `M_LIST_FALSE`
Used by all predicates and some of the general-purpose functions to indicate
that the expected conditions were _not_ met. It is important to note that this
return code is _not_ an error, but a valid logic value.

### `M_LIST_E_NULL`
Used by every function to indicate that one or more of the essential arguments
were `NULL`. Arguments such as `payload` can hold the value of `NULL`, since it
might be a valid value picked by the user.

### `M_LIST_E_OUT_OF_BOUNDS`
Used by functions that expect an index or a count that relates to the elements.
This return codes indicates that the number supplied is larger than the length
of the list.

### `M_LIST_E_NOT_PRESENT`
Returned by the `m_list_remove_safe` function in case that the element selected
for removal is not present in the list.

### `M_LIST_E_UNKNOWN_COPY`
Returned in case that the `copy` argument of a function is not one of the
following: `M_LIST_COPY_SHALLOW`, `M_LIST_COPY_DEEP`.

### `M_LIST_E_UNKNOWN_LOCATION`
Returned in case that the `loc` argument of a function is not one of the
following: `M_LIST_INSERT_BEFORE`, `M_LIST_INSERT_AFTER`.

### `M_LIST_E_UNKNOWN_CODE`
Returned by the `m_list_error_string` function, in case that the queries return
code does not exists.

## Supported platforms
 * FreeBSD 10.0 with Clang 3.3
 * OS X 10.9 with Clang 3.5
 * Linux Gentoo 2.2 with Clang 3.6

If a platform does not appear to be in the previous list, it does not mean that
`m_list` will not work in such environment. It only means that nobody tested
it - you are encouraged to do so and report either success or failure.

## Build & install
```
$ ninja
$ sudo ./install.sh
```

## License
2-clause BSD license. For more information please consult the
[LICENSE](LICENSE.md) file. In the case that you need a different license, feel
free to contact me.

## Author
Daniel Lovasko (lovasko@freebsd.org)

