#include "m_list.h"

int
m_list_append(struct m_list* list, struct m_elem* elem)
{
	if (list == NULL || elem == NULL)
		return M_LIST_E_NULL;

	if (list->first == NULL) {
		list->first = elem;
		list->last = elem;
	} else {
		list->last->next = elem;
		elem->prev = list->last;

		list->last = elem;
	}

	list->size++;

	return M_LIST_OK;
}

int
m_list_prepend(struct m_list* list, struct m_elem* elem)
{
	if (list == NULL || elem == NULL)
		return M_LIST_E_NULL;

	list->first->prev = elem;
	elem->next = list->first;

	list->first = elem;
	list->size++;

	return M_LIST_OK;
}

int
m_list_insert(struct m_list* list, struct m_elem* e1, struct m_elem* e2)
{
	if (list == NULL || e1 == NULL || e2 == NULL)
		return M_LIST_E_NULL;

	list->size++;

	return M_LIST_OK;
}

