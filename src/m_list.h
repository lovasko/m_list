#ifndef M_LIST_H
#define M_LIST_H

#include <stdlib.h>
#include <stdint.h>

typedef struct m_list_elem {
	struct m_list_elem* next;
	struct m_list_elem* prev;
	void* data;
	size_t size;
	uint8_t copy;
	char padding[sizeof(void*)-1];
} m_list_elem;

typedef struct m_list {
	m_list_elem* first;
	m_list_elem* last;
	uint64_t length;
	m_list_elem** index;
} m_list;

#define M_LIST_OK                 0
#define M_LIST_TRUE               1
#define M_LIST_FALSE              2
#define M_LIST_E_NULL             3
#define M_LIST_E_OUT_OF_BOUNDS    4
#define M_LIST_E_NOT_PRESENT      5
#define M_LIST_E_UNKNOWN_COPY     6
#define M_LIST_E_UNKNOWN_LOCATION 7
#define M_LIST_E_UNKNOWN_CODE     8
#define M_LIST_E_MAX              8

#define M_LIST_COPY_DEEP    0
#define M_LIST_COPY_SHALLOW 1

#define M_LIST_INSERT_AFTER  0
#define M_LIST_INSERT_BEFORE 1

int m_list_init(m_list* list);
int m_list_length(m_list* list, uint64_t* out_length);
int m_list_copy(m_list* list_src, m_list* list_dst, uint8_t copy);
int m_list_error_string(int code, const char** out_error_string);

int m_list_insert(m_list* list, uint8_t loc, m_list_elem* ref, uint8_t copy, void* data, size_t size);
int m_list_append(m_list* list, uint8_t copy, void* data, size_t size);
int m_list_prepend(m_list* list, uint8_t copy, void* data, size_t size);
int m_list_generate(m_list* list, uint8_t copy, void(*gen_fn)(uint64_t, void*, void**, size_t*), uint64_t n, void* payload);
int m_list_concat(m_list* list_src, struct m_list* list_dst);

int m_list_is_empty(m_list* list);
int m_list_remove(m_list* list, m_list_elem* elem);
int m_list_remove_safe(m_list* list, m_list_elem* elem);
int m_list_remove_first(m_list* list);
int m_list_remove_last(m_list* list);
int m_list_remove_all(m_list* list);

int m_list_first(m_list* list, m_list_elem** out_first);
int m_list_nth(m_list* list, uint64_t n, m_list_elem** out_elem);
int m_list_build_index(m_list* list);
int m_list_drop_index(m_list* list);
int m_list_last(m_list* list, m_list_elem** out_last);

int m_list_map(m_list* list, void(*fn)(void*, void*), void* payload);
int m_list_map_ex(m_list* list, void(*fn)(m_list_elem*, uint64_t, void*), void* payload);
int m_list_map2(m_list* list, void(*fn)(void*, void*, void*), void* payload1, void* payload2);

int m_list_join(m_list* list, uint8_t copy, void* data, size_t size);
int m_list_find(m_list* list, int(*fn)(void*, void*), void* key, void** output);
int m_list_filter(m_list* list, int(*fn)(void*, void*), void* payload);
int m_list_zip(m_list* list_a, m_list* list_b, void(*fn)(void*, void*, void*), void* payload);
int m_list_reverse(m_list* list);

int m_list_equal(m_list* list_a, m_list* list_b);

int m_list_match_all(m_list* list, int(*fn)(void*, void*), void* payload);
int m_list_match_any(m_list* list, int(*fn)(void*, void*), void* payload);
int m_list_match_exactly(m_list* list, int(*fn)(void*, void*), uint64_t count, void* payload);
int m_list_match_at_least(m_list* list, int(*fn)(void*, void*), uint64_t count, void* payload);

int m_list_is_sorted(m_list* list, int(*cmp_fn)(void*, void*));
int m_list_sort(m_list* list, int(*cmp_fn)(void*, void*, void*), void*);

int m_list_elem_data(m_list_elem* elem, void** out_data);
int m_list_elem_data_size(m_list_elem* elem, size_t* out_size);
int m_list_elem_next(m_list_elem* elem, m_list_elem** out_next);
int m_list_elem_prev(m_list_elem* elem, m_list_elem** out_prev);

#endif

