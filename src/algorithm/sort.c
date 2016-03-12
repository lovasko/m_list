#include "m_list.h"

static m_list_elem*
merge_sort(m_list_elem* first,
           uint64_t length,
           int(*cmp_fn)(void*, void*, void*),
           void* payload)
{
	m_list_elem* a;
	m_list_elem* b;
	m_list_elem* e;
	m_list_elem* tail;
	uint64_t segment_size;
	uint64_t a_size;
	uint64_t b_size;
	uint64_t i;

	for (segment_size = 1; segment_size < length; segment_size *= 2) {
		a = first;
		first = NULL;
		tail = NULL;

		while (a != NULL) {
			b = a;
			a_size = 0;
			for (i = 0; i < segment_size; i++) {
				a_size++;
				b = b->next;
				if (b == NULL)
					break;
			}

			b_size = segment_size;

			while (a_size > 0 || (b_size > 0 && b != NULL)) {
				if (a_size == 0) {
					e = b; b = b->next; b_size--;
				} else if (b_size == 0 || b == NULL) {
					e = a; a = a->next; a_size--;
				} else if (cmp_fn(a->data, b->data, payload) <= 0) {
					e = a; a = a->next; a_size--;
				} else {
					e = b; b = b->next; b_size--;
				}

				if (tail != NULL)
					tail->next = e;
				else
					first = e;

				e->prev = tail;
				tail = e;
			}
			a = b;
		}
		tail->next = NULL;
	}

	return first;
}

int
m_list_sort(m_list* list,
            int(*cmp_fn)(void*, void*, void*),
            void* payload)
{
	if (list == NULL || cmp_fn == NULL)
		return M_LIST_E_NULL;

	if (list->length < 2)
		return M_LIST_OK;

	list->first = merge_sort(list->first, list->length, cmp_fn, payload);
	return M_LIST_OK;
}

