#include "m_list.h"

int
m_list_is_sorted(m_list* list, int(*cmp_fn)(void*, void*))
{
	m_list_elem* runner;

	if (list == NULL || cmp_fn == NULL)
		return M_LIST_E_NULL;

	if (list->length < 2)
		return M_LIST_TRUE;

	runner = list->first;
	while (runner->next != NULL) {
		if (cmp_fn(runner->data, runner->next->data) > 0)
			return M_LIST_FALSE;

		runner = runner->next;
	}

	return M_LIST_TRUE;
}

