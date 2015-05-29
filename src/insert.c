#include <string.h>

#include "m_list.h"

int
m_list_insert(struct m_list* list,
              uint8_t loc,
              struct m_elem* ref,
              uint8_t copy,
              void* data,
              size_t size)
{
	struct m_elem* elem;

	if (list == NULL)
		return M_LIST_E_NULL;

	elem = malloc(sizeof(struct m_elem));	
	elem->copy = copy;
	elem->next = NULL;
	elem->prev = NULL;

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

	if (ref == NULL) {
		if (list->size == 0) {
			list->first = elem;
			list->last = elem;
			list->size = 1;
			return M_LIST_OK;
		} else {
			if (elem->copy == M_LIST_COPY_DEEP) {
				free(elem->data);
			}
			free(elem);
			return M_LIST_E_NULL;
		}
	}

	if (loc == M_LIST_INSERT_AFTER) {
		if (ref == list->last) {
			elem->next = NULL;
			elem->prev = ref;
			ref->next = elem;
			list->last = elem;
		} else {
			elem->prev = ref;
			elem->next = ref->next;
			ref->next = elem;
		}
	} else if (loc == M_LIST_INSERT_BEFORE) {
		if (ref == list->first) {
			ref->prev = elem;
			elem->prev = NULL;
			elem->next = ref;
			list->first = elem;
		} else {
			elem->prev = ref->prev;
			elem->next = ref;
			ref->prev = elem;
		}
	} else {
		if (elem->copy == M_LIST_COPY_DEEP) {
			free(elem->data);
		}
		free(elem);
		return M_LIST_E_UNKNOWN_LOCATION;
	}

	list->size++;

	return M_LIST_OK;
}

int
m_list_append(struct m_list* list, uint8_t copy, void* data, size_t size)
{
	return m_list_insert(list, M_LIST_INSERT_AFTER, list->last, copy, data, size);
}

int
m_list_prepend(struct m_list* list, uint8_t copy, void* data, size_t size)
{
	return m_list_insert(list, M_LIST_INSERT_BEFORE, list->first, copy, data, size);
}

