#include "m_list.h"

int
m_list_map(m_list* list, void(*fn)(void*, void*), void* payload)
{
	m_list_elem* runner;

	if (list == NULL || fn == NULL)
		return M_LIST_E_NULL;

	for (runner = list->first; runner != NULL; runner = runner->next)
		fn(runner->data, payload);

	return M_LIST_OK;
}

int
m_list_map_ex(m_list* list, void(*fn)(m_list_elem*, uint64_t, void*), void* payload)
{
	m_list_elem* runner;
	uint64_t i;

	if (list == NULL || fn == NULL)
		return M_LIST_E_NULL;

	for (runner = list->first, i = 0; runner != NULL; runner = runner->next, i++)
		fn(runner, i, payload);

	return M_LIST_OK;
}

int
m_list_map2(m_list* list, void(*fn)(void*, void*, void*), void* payload1, void* payload2)
{
	m_list_elem* runner;

	if (list == NULL || fn == NULL)
		return M_LIST_E_NULL;

	for (runner = list->first; runner != NULL; runner = runner->next)
		fn(runner->data, payload1, payload2);

	return M_LIST_OK;
}

