#ifndef M_LIST_H
#define M_LIST_H

#include <stdlib.h>
#include <stdint.h>

struct m_elem
{
	struct m_elem* next;
	struct m_elem* prev;
	void* data;
	uint8_t copy;
};

struct m_list
{
	struct m_elem* first;
	struct m_elem* last;
	uint64_t size;
};

#define M_LIST_OK 0
#define M_LIST_E_NULL 1
#define M_LIST_E_OUT_OF_BOUNDS 2
#define M_LIST_E_UNKNOWN_COPY 3
#define M_LIST_E_NOT_PRESENT 4
#define M_LIST_E_UNKNOWN_LOCATION 5

#define M_LIST_COPY_DEEP 0
#define M_LIST_COPY_SHALLOW 1

#define M_LIST_INSERT_AFTER 0
#define M_LIST_INSERT_BEFORE 1

int m_list_init(struct m_list* list);
int m_list_size(struct m_list* list, uint64_t* out_size);

int m_list_insert(struct m_list* list, uint8_t loc, struct m_elem* ref, uint8_t copy, void* data, size_t size);
int m_list_append(struct m_list* list, uint8_t copy, void* data, size_t size);
int m_list_prepend(struct m_list* list, uint8_t copy, void* data, size_t size);

int m_list_clear(struct m_list* list);
int m_list_remove(struct m_list* list, struct m_elem* elem);
int m_list_remove_safe(struct m_list* list, struct m_elem* elem);

int m_list_first(struct m_list* list, struct m_elem** out_first);
int m_list_nth(struct m_list* list, uint64_t n, struct m_elem** out_elem);
int m_list_last(struct m_list* list, struct m_elem** out_last);

int m_list_map(struct m_list* list, void(*fn)(void*, void*), void* payload);
int m_list_join(struct m_list* list, uint8_t copy, void* data, size_t size);

int m_elem_data(struct m_elem* elem, void** out_data);
int m_elem_next(struct m_elem* elem, struct m_elem** out_next);
int m_elem_prev(struct m_elem* elem, struct m_elem** out_prev);

#endif

