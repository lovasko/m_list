#include <string.h>

#include "m_list.h"

int
m_list_equal(struct m_list* list_a, struct m_list* list_b)
{
	struct m_elem* a;
	struct m_elem* b;

	if (list_a == NULL || list_b == NULL)
		return M_LIST_E_NULL;

	if (list_a->length != list_b->length)
		return M_LIST_FALSE;

	a = list_a->first;
	b = list_b->first;
	while (a != NULL || b != NULL) {
		if (a->copy != b->copy)
			return M_LIST_FALSE;

		if (a->size != b->size)
			return M_LIST_FALSE;

		if (a->copy == M_LIST_COPY_SHALLOW)
			if (a->data != b->data)
				return M_LIST_FALSE;

		if (a->copy == M_LIST_COPY_DEEP)
			if (memcmp(a->data, b->data, a->size) != 0)
				return M_LIST_FALSE;

		a = a->next;
		b = b->next;
	}

	return M_LIST_TRUE;
}

