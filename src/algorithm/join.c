#include <string.h>

#include "m_list.h"

int
m_list_join(m_list* list, uint8_t copy, void* data, size_t size)
{
	m_list_elem* runner;
	m_list_elem* elem;

	if (list == NULL)
		return M_LIST_E_NULL;

	if (list->first == NULL)
		return M_LIST_OK;

	runner = list->first;
	while (runner->next != NULL) {
		elem = malloc(sizeof(m_list_elem));	
		elem->copy = copy;
		elem->next = runner->next;
		elem->prev = runner;

		if (copy == M_LIST_COPY_DEEP) {
			if (data == NULL) {
				elem->data = NULL;
			} else {
				elem->data = malloc(size);
				memcpy(elem->data, data, size);
			}
		} else if (copy == M_LIST_COPY_SHALLOW) {
			elem->data = data;
		} else {
			free(elem);
			return M_LIST_E_UNKNOWN_COPY;
		}

		runner->next->prev = elem;
		runner->next = elem;
		list->length++;
		runner = elem->next;
	}

	m_list_drop_index(list);

	return M_LIST_OK;
}

