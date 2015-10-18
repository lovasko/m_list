% m_list_init(3)
% Daniel Lovasko
% October 2015

# NAME
**m_list_init** -- initialise the list

# LIBRARY
m_list (libmlist, -lmlist)

# SYNOPSIS
**#include \<m_list.h\>**

int
**m_list_init**(struct m_list* *list*)

# DESCRIPTION
Initialise the *list*. This function must be called before the list is used by
any other function. Failing to do so will result in undefined behaviour.

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
m_list_copy(3), m_list_error_string(3), m_list_insert(3)

