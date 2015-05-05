#include <string.h>

#include "m_list.h"

int
m_list_init(struct m_list* list)
{
	if (list == NULL)
		return M_LIST_E_NULL;

	list->first = NULL;
	list->last = NULL;
	list->size = 0;

	return M_LIST_OK;
}

int
m_list_size(struct m_list* list, uint64_t* out_size)
{
	if (list == NULL || out_size == NULL)
		return M_LIST_E_NULL;

	*out_size = list->size;
	return M_LIST_OK;
}

int
m_elem_data(struct m_elem* elem, void** out_data)
{
	if (elem == NULL || out_data == NULL)
		return M_LIST_E_NULL;

	*out_data = elem->data;
	return M_LIST_OK;
}

