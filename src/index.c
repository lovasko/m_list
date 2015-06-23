#include "m_list.h"

int
m_list_build_index(struct m_list* list)
{
	uint64_t i;
	struct m_elem* runner;

	if (list == NULL)
		return M_LIST_E_NULL;

	m_list_drop_index(list);

	list->index = malloc(sizeof(struct m_elem*) * list->length);
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
m_list_drop_index(struct m_list* list)
{
	if (list == NULL)
		return M_LIST_E_NULL;

	if (list->index != NULL) {
		free(list->index);
		list->index = NULL;
	}

	return M_LIST_OK;
}

