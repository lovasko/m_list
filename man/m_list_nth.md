% m_list_nth(3)
% Daniel Lovasko
% August 2015

# NAME
**m_list_nth** -- retrieve the nth element of the list

# LIBRARY
m_list (libmlist, -lmlist)

# SYNOPSIS
**#include \<m_list.h\>**
**#include \<stdint.h\>**

int
**m_list_nth**(struct m_list* *list*, uint64_t *n*, struct m_elem** *out_first*)

# DESCRIPTION
Retrieve the *n*th element of the list.

This function is closely related with the concept of a list index, a data
structure that enables a constant time access to the list elements.

# COMPLEXITY
## TIME
O(1) in case that the index is available, O(*n*) otherwise, where *n* is the
length of the *list*.

## SPACE
O(1).

# RETURN VALUES
## M_LIST_OK
Success.

## M_LIST_E_NULL
In case that either *list* or *out_first* are NULL.

## M_LIST_E_OUT_OF_BOUNDS
In case that the *nth* value is greater than the length of the *list*.

# SEE ALSO
m_list_last(3), m_list_nth(3), m_list_build_index(3), m_list_drop_index(3)

