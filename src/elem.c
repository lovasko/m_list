#include "m_list.h"

int
m_list_elem_data(m_list_elem* elem, void** out_data)
{
	if (elem == NULL || out_data == NULL)
		return M_LIST_E_NULL;

	*out_data = elem->data;
	return M_LIST_OK;
}

int
m_list_elem_data_size(m_list_elem* elem, size_t* out_size)
{
	if (elem == NULL || out_size == NULL)
		return M_LIST_E_NULL;

	*out_size = elem->size;
	return M_LIST_OK;
}

int
m_list_elem_next(m_list_elem* elem, m_list_elem** out_next)
{
	if (elem == NULL || out_next == NULL)
		return M_LIST_E_NULL;

	*out_next = elem->next;
	return M_LIST_OK;
}

int
m_list_elem_prev(m_list_elem* elem, m_list_elem** out_prev)
{
	if (elem == NULL || out_prev == NULL)
		return M_LIST_E_NULL;

	*out_prev = elem->prev;
	return M_LIST_OK;
}

