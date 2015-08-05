% m_list_drop_index(3)
% Daniel Lovasko
% August 2015

# NAME
**m_list_drop_index** -- discard the index data structure 

# LIBRARY
m_list (libmlist, -lmlist)

# SYNOPSIS
**#include \<m_list.h\>**

int
**m_list_drop_index**(struct m_list* *list*)

# DESCRIPTION
Free the memory allocated to hold the index structure of the *list*.

Running this function with a *list* that has no index built is allowed and
leads to a no-op behaviour.

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

# SEE ALSO
m_list_nth(3), m_list_build_index(3)

