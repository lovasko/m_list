#include "m_list.h"

int
m_list_is_empty(struct m_list* list)
{
	if (list->length == 0)
		return M_LIST_TRUE;
	else
		return M_LIST_FALSE;
}

