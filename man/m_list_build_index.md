% m_list_build_index(3)
% Daniel Lovasko
% August 2015

# NAME
**m_list_build_index** -- build index for faster random access

# LIBRARY
m_list (libmlist, -lmlist)

# SYNOPSIS
**#include \<m_list.h\>**

int
**m_list_build_index**(struct m_list* *list*)

# DESCRIPTION
Index is an array of pointers to all *struct m_elem* instances of the list.
This allows to access every element of the *list* in constant time.

Every function that makes a change to the order of elements in the *list* will
drop the index, since it is no longer valid.

# COMPLEXITY
## TIME
O(*n*) where *n* is the length of the *list*.

## SPACE
O(*n*) where *n* is the length of the *list*.

# RETURN VALUES
## M_LIST_OK
Success.

## M_LIST_E_NULL
In case that *list* is NULL.

# SEE ALSO
m_list_nth(3), m_list_drop_index(3)

