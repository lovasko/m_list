#include "m_list.h"

int
m_list_build_index(m_list* list)
{
	uint64_t i;
	m_list_elem* runner;

	if (list == NULL)
		return M_LIST_E_NULL;

	m_list_drop_index(list);

	list->index = malloc(sizeof(m_list_elem*) * (size_t)list->length);
	i = 0;
	runner = list->first;
	while (runner != NULL) {
		list->index[i] = runner;
		i++;
		runner = runner->next;
	}

	return M_LIST_OK;
}

int
m_list_drop_index(m_list* list)
{
	if (list == NULL)
		return M_LIST_E_NULL;

	if (list->index != NULL) {
		free(list->index);
		list->index = NULL;
	}

	return M_LIST_OK;
}

