#include "m_list.h"

int
m_list_one(struct m_list* list, int(*fn)(void*, void*), void* payload)
{
	struct m_elem* runner;
	int match;

	if (list == NULL || fn == NULL)
		return M_LIST_E_NULL;

	if (list->length == 0)
		return M_LIST_FALSE;

	match = 0;
	runner = list->first;
	while (runner != NULL) {
		if (fn(runner->data, payload)) {
			if (match)
				return M_LIST_FALSE;
			else
				match = 1;
		}
		runner = runner->next;
	}

	if (match)
		return M_LIST_TRUE;
	else
		return M_LIST_FALSE;
}

