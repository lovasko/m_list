#include "m_list.h"

static void
swap_elem(struct m_elem** a, struct m_elem** b)
{
	struct m_elem* tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int
m_list_reverse(struct m_list* list)
{
	struct m_elem* runner;

	if (list == NULL)
		return M_LIST_E_NULL;

	if (list->length < 2)
		return M_LIST_OK;

	runner = list->first;
	while (runner != NULL) {
		swap_elem(&runner->next, &runner->prev);
		runner = runner->prev;
	}
	swap_elem(&list->first, &list->last);

	return M_LIST_OK;
}

