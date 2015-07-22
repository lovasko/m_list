#include "m_list.h"

int
m_list_match_all(struct m_list* list, int(*fn)(void*, void*), void* payload)
{
	return m_list_match_exactly(list, fn, list->length, payload);	
}

int
m_list_match_any(struct m_list* list, int(*fn)(void*, void*), void* payload)
{
	return m_list_match_at_least(list, fn, 1, payload);
}

int
m_list_match_exactly(struct m_list* list,
                     int(*fn)(void*, void*),
                     uint64_t count,
                     void* payload)
{
	uint64_t matched;
	struct m_elem* runner;

	if (list == NULL || fn == NULL)
		return M_LIST_E_NULL;

	if (count > list->length)
		return M_LIST_E_OUT_OF_BOUNDS;

	matched = 0;
	runner = list->first;
	while (runner != NULL) {
		if (fn(runner->data, payload)) {
			matched++;
			if (matched > count)
				return M_LIST_FALSE;
		}
		runner = runner->next;
	}

	if (matched == count)
		return M_LIST_TRUE;
	else
		return M_LIST_FALSE;
}

int
m_list_match_at_least(struct m_list* list,
                     int(*fn)(void*, void*),
                     uint64_t count,
                     void* payload)
{
	uint64_t matched;
	uint64_t visited;
	struct m_elem* runner;

	if (list == NULL || fn == NULL)
		return M_LIST_E_NULL;

	if (count > list->length)
		return M_LIST_E_OUT_OF_BOUNDS;

	matched = 0;
	visited = 0;
	runner = list->first;
	while (runner != NULL) {
		if (fn(runner->data, payload)) 
			matched++;

		if (matched == count)
			return M_LIST_TRUE;

		visited++;
		if (matched + (list->length - visited) < count)
			return M_LIST_FALSE;

		runner = runner->next;
	}

	return M_LIST_FALSE;
}

