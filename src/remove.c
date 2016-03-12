#include "m_list.h"

int
m_list_remove_all(m_list* list)
{
	m_list_elem* runner;

	for (runner = list->last; runner != NULL; ) {
		if (runner->copy == M_LIST_COPY_DEEP)
			free(runner->data);

		runner = runner->prev;

		if (runner != NULL)
			free(runner->next);
	}

	list->length = 0;
	list->first = NULL;
	list->last = NULL;
	m_list_drop_index(list);

	return M_LIST_OK;
}

static int
handle_edges(m_list* list, m_list_elem* elem)
{
	if (elem == list->first && elem == list->last) {
		list->first = NULL;
		list->last = NULL;
	} else if (elem == list->first) {
		list->first = elem->next;
		list->first->prev = NULL;
	} else if (elem == list->last) {
		list->last = elem->prev;
		list->last->next = NULL;
	} else {
		return 0;
	}

	return 1;
}

int
m_list_remove(m_list* list, m_list_elem* elem)
{
	if (list->length == 0)
		return M_LIST_E_NOT_PRESENT;

	if (!handle_edges(list, elem)) {
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
	}

	if (elem->copy == M_LIST_COPY_DEEP)
		free(elem->data);
	free(elem);

	list->length--;
	m_list_drop_index(list);

	return M_LIST_OK;
}

int
m_list_remove_safe(m_list* list, m_list_elem* elem)
{
	m_list_elem* runner;
	uint8_t found;

	found = 0;

	if (list->length == 0)
		return M_LIST_E_NOT_PRESENT;

	if (!handle_edges(list, elem)) {
		for (runner = list->first; runner != NULL; runner = runner->next) {
			if (elem == runner) {
				found = 1;
				break;
			}
		}
	}

	if (found) {
		if (elem->copy == M_LIST_COPY_DEEP)
			free(elem->data);
		free(elem);
	} else {
		return M_LIST_E_NOT_PRESENT;
	}

	list->length--;
	m_list_drop_index(list);

	return M_LIST_OK;
}

int
m_list_remove_first(m_list* list)
{
	m_list_elem* first;
	int retval;

	if ((retval = m_list_first(list, &first)) != M_LIST_OK)
		return retval;
	
	return m_list_remove(list, first);
}

int
m_list_remove_last(m_list* list)
{
	m_list_elem* last;
	int retval;

	if ((retval = m_list_last(list, &last)) != M_LIST_OK)
		return retval;
	
	return m_list_remove(list, last);
}

