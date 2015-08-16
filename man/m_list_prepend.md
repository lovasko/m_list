% m_list_prepend(3)
% Daniel Lovasko
% August 2015

# NAME
**m_list_prepend** -- insert new element at the beginning of the list

# LIBRARY
m_list (libmlist, -lmlist)

# SYNOPSIS
**#include \<m_list.h\>**

int
**m_list_prepend**(struct m_list* *list*, uint8_t *copy*, void* *data*, size_t *size*);

# DESCRIPTION
This function adds a new element to the beginning of the *list*. For the 
description of the *copy*, *data* and *size* parameters, please consult the
**m_list_insert** function.

# COMPLEXITY
## TIME
O(1).

## SPACE
O(1).

# RETURN VALUES
## M_LIST_OK
Success.

## M_LIST_E_NULL
In case that *list* is NULL.

## M_LIST_E_UNKNOWN_COPY
In case that the *copy* method is neither one of the following:
M_LIST_COPY_SHALLOW, M_LIST_COPY_DEEP.

# SEE ALSO
m_list_insert(3), m_list_append(3)

