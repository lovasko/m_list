#include "m_list.h"

int
m_list_find(struct m_list* list, int(*fn)(void*, void*), void* key, void** output)
{
	struct m_elem* runner;

	if (list == NULL || fn == NULL)
		return M_LIST_E_NULL;

	runner = list->first;
	while (runner != NULL) {
		if (fn(runner->data, key)) {
			if (output != NULL)
				*output = runner->data;
			return M_LIST_OK;
		}
		runner = runner->next;
	}

	return M_LIST_NOT_FOUND;
}

