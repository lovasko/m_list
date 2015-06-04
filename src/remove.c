#include "m_list.h"

int
m_list_clear(struct m_list* list)
{
	struct m_elem* runner;

	for (runner = list->last; runner != NULL; ) {
		if (runner->copy == M_LIST_COPY_DEEP)
			free(runner->data);

		runner = runner->prev;
		free(runner->next);
	}

	list->size = 0;

	return M_LIST_OK;
}

static int
handle_edges(struct m_list* list, struct m_elem* elem)
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
m_list_remove(struct m_list* list, struct m_elem* elem)
{
	if (list->size == 0)
		return M_LIST_E_NOT_PRESENT;

	if (!handle_edges(list, elem)) {
		elem->prev->next = elem->next;
	}

	if (elem->copy == M_LIST_COPY_DEEP)
		free(elem->data);
	free(elem);

	list->size--;

	return M_LIST_OK;
}

int
m_list_remove_safe(struct m_list* list, struct m_elem* elem)
{
	struct m_elem* runner;
	uint8_t found;

	found = 0;

	if (list->size == 0)
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

	list->size--;

	return M_LIST_OK;
}

int
m_list_remove_first(struct m_list* list)
{
	struct m_elem* first;
	int retval;

	if ((retval = m_list_first(list, &first)) != M_LIST_OK)
		return retval;
	
	return m_list_remove(list, first);
}

int
m_list_remove_last(struct m_list* list)
{
	struct m_elem* last;
	int retval;

	if ((retval = m_list_last(list, &last)) != M_LIST_OK)
		return retval;
	
	return m_list_remove(list, last);
}

