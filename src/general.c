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

int
m_list_copy(struct m_list* list_src, struct m_list* list_dst, uint8_t copy)
{
	struct m_elem* runner_src;
	struct m_elem* elem;

	if (list_src == NULL || list_dst == NULL)
		return M_LIST_E_NULL;

	runner_src = list_src->first;
	while (runner_src != NULL) {
		elem = malloc(sizeof(struct m_elem));
		elem->size = runner_src->size;

		if (runner_src->copy == M_LIST_COPY_DEEP && copy == M_LIST_COPY_DEEP) {
			elem->copy = copy;
			if (runner_src->data == NULL) {
				elem->data = NULL;
			} else {
				elem->data = malloc(runner_src->size);
				memcpy(elem->data, runner_src->data, runner_src->size);
			}
		}

		if (runner_src->copy == M_LIST_COPY_SHALLOW) {
			elem->data = runner_src->data;
			elem->copy = copy;
		}

		if (list_dst->first == NULL) {
			list_dst->first = elem;
			list_dst->last = elem;
			elem->next = NULL;
			elem->prev = NULL;
		} else {
			list_dst->last->next = elem;
			elem->prev = list_dst->last;
			elem->next = NULL;
			list_dst->last = elem;
		}

		list_dst->size++;
	}

	return M_LIST_OK;
}

