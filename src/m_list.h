#ifndef M_LIST_H
#define M_LIST_H

#include <stdlib.h>
#include <stdint.h>

struct m_elem
{
	struct m_elem* next;
	struct m_elem* prev;
	void* data;
	uint8_t deep;
};

struct m_list
{
	struct m_elem* first;
	struct m_elem* last;
	uint64_t size;
};

#define M_LIST_OK 0
#define M_LIST_E_NULL 1
#define M_LIST_E_TOO_SHORT 2
#define M_LIST_E_UNKNOWN_COPY 3
#define M_LIST_E_NOT_PRESENT 4

#define M_LIST_DEEP_COPY 0
#define M_LIST_SHALLOW_COPY 1

int m_list_init(struct m_list* list);
int m_list_size(struct m_list* list, uint64_t* out_size);
int m_list_append(struct m_list* list, struct m_elem* elem);
int m_list_prepend(struct m_list* list, struct m_elem* elem);
int m_list_insert(struct m_list* list, struct m_elem* e1, struct m_elem* e2);
int m_list_clear(struct m_list* list);
int m_list_remove(struct m_list* list, struct m_elem* elem);
int m_list_remove_safe(struct m_list* list, struct m_elem* elem);
int m_list_first(struct m_list* list, struct m_elem** out_first);
int m_list_nth(struct m_list* list, uint64_t n, struct m_elem** out_elem);
int m_list_last(struct m_list* list, struct m_elem** out_last);
int m_list_map(struct m_list* list, void(*fn)(void*));

int m_elem_init(struct m_elem* elem, void* data, size_t size, uint8_t deep);
int m_elem_data(struct m_elem* elem, void** out_data);
int m_elem_next(struct m_elem* elem, struct m_elem** out_next);
int m_elem_prev(struct m_elem* elem, struct m_elem** out_prev);

#endif

