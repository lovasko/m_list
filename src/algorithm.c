#include <string.h>

#include "m_list.h"

int
m_list_map(struct m_list* list, void(*fn)(void*, void*), void* payload)
{
	struct m_elem* runner;

	if (list == NULL || fn == NULL)
		return M_LIST_E_NULL;

	for (runner = list->first; runner != NULL; runner = runner->next)
		fn(runner->data, payload);

	return M_LIST_OK;
}

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

int
m_list_find(struct m_list* list, int(*fn)(void*, void*), void* key, void** output)
{
	struct m_elem* runner;

	if (list == NULL || fn == NULL)
		return M_LIST_E_NULL;

	runner = list->first;
	while (runner != NULL) {
		if (fn(runner->data, key)) {
			if (output != NULL)
				*output = runner->data;
			return M_LIST_OK;
		}
		runner = runner->next;
	}

	return M_LIST_NOT_FOUND;
}

