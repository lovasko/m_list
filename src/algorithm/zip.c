#include "m_list.h"

int
m_list_zip(struct m_list* list_a, struct m_list* list_b, void(*fn)(void*, void*, void*), void* payload)
{
	struct m_elem* runner_a;
	struct m_elem* runner_b;

	if (list_a == NULL || list_b == NULL || fn == NULL)
		return M_LIST_E_NULL;

	runner_a = list_a->first;
	runner_b = list_b->first;
	while (runner_a != NULL && runner_b != NULL) {
		fn(runner_a->data, runner_b->data, payload);
		runner_a = runner_a->next;			
		runner_b = runner_b->next;			
	}

	return M_LIST_OK;
}

