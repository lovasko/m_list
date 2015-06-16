#include <string.h>

#include "m_list.h"

int
m_list_join(struct m_list* list, uint8_t copy, void* data, size_t size)
{
	struct m_elem* runner;
	struct m_elem* elem;

	if (list == NULL)
		return M_LIST_E_NULL;

	if (list->first == NULL)
		return M_LIST_OK;

	runner = list->first;
	while (runner->next != NULL) {
		elem = malloc(sizeof(struct m_elem));	
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
		list->size++;
		runner = elem->next;
	}

	return M_LIST_OK;
}

