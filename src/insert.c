#include <string.h>

#include "m_list.h"

int
m_list_insert(m_list* list,
              uint8_t loc,
              m_list_elem* ref,
              uint8_t copy,
              void* data,
              size_t size)
{
	m_list_elem* elem;

	if (list == NULL)
		return M_LIST_E_NULL;

	elem = malloc(sizeof(m_list_elem));	
	elem->copy = copy;
	elem->next = NULL;
	elem->prev = NULL;
	elem->size = size;

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
		if (list->length == 0) {
			list->first = elem;
			list->last = elem;
			list->length = 1;
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

	list->length++;
	m_list_drop_index(list);

	return M_LIST_OK;
}

int
m_list_append(m_list* list, uint8_t copy, void* data, size_t size)
{
	return m_list_insert(list, M_LIST_INSERT_AFTER, list->last, copy, data, size);
}

int
m_list_prepend(m_list* list, uint8_t copy, void* data, size_t size)
{
	return m_list_insert(list, M_LIST_INSERT_BEFORE, list->first, copy, data, size);
}

int
m_list_generate(m_list* list,
                uint8_t copy,
                void(*gen_fn)(uint64_t, void*, void**, size_t*),
                uint64_t n,
                void* payload)
{
	uint64_t i;
	void* data;
	size_t size;

	if (list == NULL || gen_fn == NULL)
		return M_LIST_E_NULL;

	if (n == 0)
		return M_LIST_OK;

	for (i = 0; i < n; i++) {
		gen_fn(i, payload, &data, &size);
		m_list_append(list, copy, data, size);
	}

	return M_LIST_OK;
}

int
m_list_concat(m_list* list_src, m_list* list_dst)
{
	if (list_src == NULL || list_dst == NULL)
		return M_LIST_E_NULL;

	if (list_dst->length == 0) {
		list_dst->first = list_src->first;
		list_dst->last = list_src->last;
	} else {
		list_dst->last->next = list_src->first;
		list_src->first->prev = list_dst->last;
	}
	
	list_dst->length += list_src->length;
	m_list_drop_index(list_dst);

	list_src->first = NULL;
	list_src->last = NULL;
	list_src->length = 0;
	m_list_drop_index(list_src);

	return M_LIST_OK;
}

