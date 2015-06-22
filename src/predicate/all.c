#include "m_list.h"

int
m_list_all(struct m_list* list, int(*fn)(void*, void*), void* payload)
{
	struct m_elem* runner;

	if (list == NULL || fn == NULL)
		return M_LIST_E_NULL;

	if (list->size == 0)
		return M_LIST_TRUE;

	runner = list->first;
	while (runner != NULL) {
		if (!fn(runner->data, payload))
			return M_LIST_FALSE;
		runner = runner->next;
	}

	return M_LIST_TRUE;
}

