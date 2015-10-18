% m_list_length(3)
% Daniel Lovasko
% October 2015

# NAME
**m_list_length** -- get the length of the list 

# LIBRARY
m_list (libmlist, -lmlist)

# SYNOPSIS
**#include \<m_list.h\>**

int
**m_list_length**(struct m_list* *list*, uint64_t* *out_length*)

# DESCRIPTION
This function retrieves the length of the *list* in constant time and stores it
in the *out_length* argument.

# COMPLEXITY
## TIME
O(1).

## SPACE
O(1).

# RETURN VALUES
## M_LIST_OK
Success.

## M_LIST_E_NULL
In case that either *list* or *out_length* were NULL.

# SEE ALSO
m_list_copy(3), m_list_error_string(3), m_list_insert(3)

