#include "m_list.h"

int
m_list_find(m_list* list, int(*fn)(void*, void*), void* key, void** output)
{
	m_list_elem* runner;

	if (list == NULL || fn == NULL)
		return M_LIST_E_NULL;

	runner = list->first;
	while (runner != NULL) {
		if (fn(runner->data, key)) {
			if (output != NULL)
				*output = runner->data;
			return M_LIST_TRUE;
		}
		runner = runner->next;
	}

	return M_LIST_FALSE;
}

