% m_list_first(3)
% Daniel Lovasko
% August 2015

# NAME
**m_list_first** -- retrieve the first element of the list

# LIBRARY
m_list (libmlist, -lmlist)

# SYNOPSIS
**#include \<m_list.h\>**

int
**m_list_first**(struct m_list* *list*, struct m_elem** *out_first*)

# DESCRIPTION
Retrieve the first element of the *list*. The first element is returned as a
pointer to the *struct m_elem* in the second argument of the function. The
return value of the function can be used to perform error-checking.

# COMPLEXITY
## TIME
O(1).

## SPACE
O(1).

# RETURN VALUES
## M_LIST_OK
Success.

## M_LIST_E_NULL
In case that either *list* or *out_first* are NULL.

# SEE ALSO
m_list_last(3), m_list_nth(3)

