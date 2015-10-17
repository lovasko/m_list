#ifndef M_LIST_H
#define M_LIST_H

#include <stdlib.h>
#include <stdint.h>

struct m_elem
{
	struct m_elem* next;
	struct m_elem* prev;
	void* data;
	size_t size;
	uint8_t copy;
};

struct m_list
{
	struct m_elem* first;
	struct m_elem* last;
	uint64_t length;
	struct m_elem** index;
};

#define M_LIST_OK                 0
#define M_LIST_E_NULL             1
#define M_LIST_E_OUT_OF_BOUNDS    2
#define M_LIST_E_NOT_PRESENT      3
#define M_LIST_E_UNKNOWN_COPY     4
#define M_LIST_E_UNKNOWN_LOCATION 5
#define M_LIST_E_UNKNOWN_CODE     6
#define M_LIST_E_MAX              6

#define M_LIST_TRUE  0
#define M_LIST_FALSE 1

#define M_LIST_COPY_DEEP    0
#define M_LIST_COPY_SHALLOW 1

#define M_LIST_INSERT_AFTER  0
#define M_LIST_INSERT_BEFORE 1

int m_list_init(struct m_list* list);
int m_list_length(struct m_list* list, uint64_t* out_length);
int m_list_copy(struct m_list* list_src, struct m_list* list_dst, uint8_t copy);
int m_list_error_string(int code, char** out_error_string);

int m_list_insert(struct m_list* list, uint8_t loc, struct m_elem* ref, uint8_t copy, void* data, size_t size);
int m_list_append(struct m_list* list, uint8_t copy, void* data, size_t size);
int m_list_prepend(struct m_list* list, uint8_t copy, void* data, size_t size);
int m_list_generate(struct m_list* list, uint8_t copy, void(*gen_fn)(uint64_t, void*, void**, size_t*), uint64_t n, void* payload);

int m_list_is_empty(struct m_list* list);
int m_list_remove_all(struct m_list* list);
int m_list_remove(struct m_list* list, struct m_elem* elem);
int m_list_remove_safe(struct m_list* list, struct m_elem* elem);
int m_list_remove_first(struct m_list* list);
int m_list_remove_last(struct m_list* list);

int m_list_first(struct m_list* list, struct m_elem** out_first);
int m_list_nth(struct m_list* list, uint64_t n, struct m_elem** out_elem);
int m_list_build_index(struct m_list* list);
int m_list_drop_index(struct m_list* list);
int m_list_last(struct m_list* list, struct m_elem** out_last);

int m_list_map(struct m_list* list, void(*fn)(void*, void*), void* payload);
int m_list_map2(struct m_list* list, void(*fn)(void*, void*, void*), void* payload1, void* payload2);

int m_list_join(struct m_list* list, uint8_t copy, void* data, size_t size);
int m_list_find(struct m_list* list, int(*fn)(void*, void*), void* key, void** output);
int m_list_filter(struct m_list* list, int(*fn)(void*, void*), void* payload);
int m_list_zip(struct m_list* list_a, struct m_list* list_b, void(*fn)(void*, void*, void*), void* payload);

int m_list_equal(struct m_list* list_a, struct m_list* list_b);

int m_list_match_all(struct m_list* list, int(*fn)(void*, void*), void* payload);
int m_list_match_any(struct m_list* list, int(*fn)(void*, void*), void* payload);
int m_list_match_exactly(struct m_list* list, int(*fn)(void*, void*), uint64_t count, void* payload);
int m_list_match_at_least(struct m_list* list, int(*fn)(void*, void*), uint64_t count, void* payload);

int m_list_is_sorted(struct m_list* list, int(*cmp_fn)(void*, void*));
int m_list_sort(struct m_list* list, int(*cmp_fn)(void*, void*, void*), void*);

int m_elem_data(struct m_elem* elem, void** out_data);
int m_elem_next(struct m_elem* elem, struct m_elem** out_next);
int m_elem_prev(struct m_elem* elem, struct m_elem** out_prev);

#endif

