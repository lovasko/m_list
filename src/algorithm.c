#include "m_list.h"

int
m_list_map(struct m_list* list, void(*fn)(void*, void*), void* payload)
{
	struct m_elem* runner;

	for(runner = list->first; runner != NULL; runner = runner->next)
		fn(runner->data, payload);

	return M_LIST_OK;
}

