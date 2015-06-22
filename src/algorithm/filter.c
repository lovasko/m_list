#include "m_list.h"

int
m_list_filter(struct m_list* list, int(*fn)(void*, void*), void* payload)
{
	struct m_elem* runner;
	struct m_elem* prev;
	int retval;
	uint64_t removed_count;

	if (list == NULL || fn == NULL)
		return M_LIST_E_NULL;

	removed_count = 0;
	runner = list->first;
	while (runner != NULL) {
		if (!fn(runner->data, payload)) {
			prev = runner->prev;	
			if ((retval = m_list_remove(list, runner)) != M_LIST_OK)
				return retval;
			removed_count++;
		}
		runner = prev->next;
	}

	if (removed_count > 0)
		m_list_drop_index(list);

	return M_LIST_OK;
}

