% m_list_error_string(3)
% Daniel Lovasko
% October 2015

# NAME
**m_list_error_string** -- convert return code to string description

# LIBRARY
m_list (libmlist, -lmlist)

# SYNOPSIS
**#include \<m_list.h\>**

int
**m_list_error_string**(int *code*, char** *out_error_string*)

# DESCRIPTION
Every **m_list** function returns an integer that describes the run and outcome
of the function. In oder to translate these codes to English, use the
**m_list_error_string** function.

# COMPLEXITY
## TIME
O(1).

## SPACE
O(1).

# RETURN VALUES
## M_LIST_OK
Success.

## M_LIST_E_NULL
In case that *out_error_string* was NULL.

# SEE ALSO
m_list_init(3)

