% m_list_insert(3)
% Daniel Lovasko
% August 2015

# NAME
**m_list_insert** -- add new element to the list

# LIBRARY
m_list (libmlist, -lmlist)

# SYNOPSIS
**#include \<m_list.h\>**

int
**m_list_insert**(struct m_list* *list*, uint8_t *loc*, struct m_elem* *ref*, uint8_t *copy*, void* *data*, size_t *size*)

# DESCRIPTION
This function inserts a new element to the *list*. It is inserted before or
after the *ref* element, depending on the *loc*ation value provided
(M_LIST_INSERT_BEFORE and M_LIST_INSERT_AFTER respectively).

Optionally, it is possible to attach a *data* blob of a specific *size* 
to the new element. Depending on the value of the *copy* method, only the 
pointer is stored (M_LIST_COPY_SHALLOW) or a full copy of the object at the
*data* pointer is made (M_LIST_COPY_DEEP).

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

## M_LIST_E_UNKNOWN_LOCATION
In case that the *loc*ation is neither one of the following:
M_LIST_INSERT_AFTER, M_LIST_INSERT_BEFORE.

# SEE ALSO
m_list_append(3), m_list_prepend(3), m_list_remove(3)

