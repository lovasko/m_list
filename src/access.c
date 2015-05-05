#include "m_list.h"

int
m_list_first(struct m_list* list, struct m_elem** out_first)
{
	if (list == NULL || out_first == NULL)
		return M_LIST_E_NULL;

	*out_first = list->first;	
	return M_LIST_OK;
}

int
m_list_last(struct m_list* list, struct m_elem** out_last)
{
	if (list == NULL || out_last == NULL)
		return M_LIST_E_NULL;

	*out_last = list->last;
	return M_LIST_OK;
}

int
m_list_nth(struct m_list* list, uint64_t n, struct m_elem** out_nth)
{
	uint64_t i;
	struct m_elem* runner;

	if (list == NULL || out_nth == NULL)
		return M_LIST_E_NULL;
	
	if (list->size <= n)
		return M_LIST_E_OUT_OF_BOUNDS;

	runner = list->first;
	for (i = 0; i < n; i++) {
		runner = runner->next;
		if (runner->next == NULL)
			return M_LIST_E_NULL;
	}

	*out_nth = runner;
	return M_LIST_OK;
}

