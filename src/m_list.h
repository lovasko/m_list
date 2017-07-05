#ifndef M_LIST_H
#define M_LIST_H

#include <stdlib.h>
#include <stdint.h>


typedef struct m_list_elem {
	struct m_list_elem* le_next;
	struct m_list_elem* le_prev;
	void*               le_data;
	size_t              le_size;
} m_list_elem;

typedef struct m_list {
	m_list_elem*  ls_fst;
	m_list_elem*  ls_lst;
	uint64_t      ls_len;
	m_list_elem** ls_idx;
} m_list;

#define M_LIST_OK       0
#define M_LIST_E_NULL   1
#define M_LIST_E_BOUNDS 2

/** Initialise the list.
 *
 * @param[in] list list
 *
 * @return status code
 * @retval M_LIST_E_NULL ls is NULL
 * @retval M_LIST_OK     success
**/
int m_list_init(m_list* list);

/** Get the number of elements in the list.
 *
 * @param[in]  list list
 * @param[out] len  number of elements
 *
 * @return status code
 * @retval M_LIST_E_NULL list and/or len is NULL
 * @retval M_LIST_OK     success
**/
int m_list_length(m_list* list, uint64_t* len);

/** Insert an element into the list.
 *
 * @param[in] list list
 * @param[in] pos  position within the list
 * @param[in] data data to be inserted (can be NULL)
 *
 * @return status code
 * @retval M_LIST_E_NULL   list is NULL
 * @retval M_LIST_E_BOUNDS pos is out of list bounds
 * @retval M_LIST_OK       success
**/
int m_list_insert(m_list* list, uint64_t pos, void* data);

/** Add an element at the end of the list.
 *
 * @param[in] list list
 * @param[in] data data to be added (can be NULL)
 * 
 * @return status code
 * @retval M_LIST_E_NULL   list is NULL
 * @retval M_LIST_E_MEMORY unable to allocate memory (check ERRNO)
 * @retval M_LIST_OK       success
**/
int m_list_append(m_list* list, uint8_t copy, void* data, size_t size);

/** Add an element to the beginning the of the list.
 *
 * @param[in] list list
 * @param[in] data data to be added (can be NULL)
 * 
 * @return status code
 * @retval M_LIST_E_NULL   list is NULL
 * @retval M_LIST_E_MEMORY unable to allocate memory (check ERRNO)
 * @retval M_LIST_OK       success
**/
int m_list_prepend(m_list* list, void* data);

int m_list_generate(m_list* list, uint8_t copy, void(*gen_fn)(uint64_t, void*, void**, size_t*), uint64_t n, void* payload);
int m_list_concat(m_list* list_src, struct m_list* list_dst);

int m_list_remove(m_list* list, m_list_elem* elem);
int m_list_remove_safe(m_list* list, m_list_elem* elem);
int m_list_remove_first(m_list* list);
int m_list_remove_last(m_list* list);

/** Remove all elements from the list.
 *
 * @param[in] list list
 * 
 * @return status code
 * @retval M_LIST_E_NULL list is NULL
 * @retval M_LIST_OK     success
**/
int m_list_remove_all(m_list* list);

/** Get the first element of the list.
 *
 * @param[in]  list list
 * @param[out] fst  first element
 *
 * @return status code
 * @retval M_LIST_E_NULL  list and/or fst are NULL
 * @retval M_LIST_E_EMPTY list is empty
 * @retval M_LIST_OK      success
**/
int m_list_first(m_list* list, m_list_elem** fst);

/** Get the n-th element of the list.
 *
 * @param[in]  list list
 * @param[in]  n    index within the list
 * @param[out] elem n-th element
 *
 * @return status code
 * @retval M_LIST_E_NULL   list and/or elem are NULL
 * @retval M_LIST_E_EMPTY  list is empty
 * @retval M_LIST_E_BOUNDS n is out of list bounds
 * @retval M_LIST_OK       success
**/
int m_list_nth(m_list* list, uint64_t n, m_list_elem** elem);

/** Build an access index that lowers the asymptotical complexity of lookups on
 * the n-th position.
 *
 * @param[in] list list
 * 
 * @return status code
 * @retval M_LIST_E_NULL   list is NULL
 * @retval M_LIST_E_MEMORY unable to allocate memory (check ERRNO)
 * @retval M_LIST_OK       success
**/
int m_list_build_index(m_list* list);

/** Drop the already built access index.
 *
 * This function is a no-op if no index was built.
 * 
 * @param[in] list list
 * 
 * @return status code
 * @retval M_LIST_E_NULL list is NULL
 * @retval M_LIST_OK     success
**/
int m_list_drop_index(m_list* list);

/** Get the last element of the list.
 *
 * @param[in]  list list
 * @param[out] elem last list element
 *
 * @return status code
 * @retval M_LIST_E_NULL  list and/or elem are NULL
 * @retval M_LIST_E_EMPTY list is empty
 * @retval M_LIST_OK      success
**/
int m_list_last(m_list* list, m_list_elem** out_last);

/** Apply a function to all elements of the list.
 *
 * @param[in] list list
 * @param[in] func function
 * @param[in] auxd auxiliary data for the applied function (can be NULL)
 *
 * @return status code
 * @retval M_LIST_E_NULL list and/or func are NULL
 * @retval M_LIST_OK     success
**/
int m_list_map(m_list* list, void(*fn)(void*, void*), void* payload);
int m_list_map_ex(m_list* list, void(*fn)(m_list_elem*, uint64_t, void*), void* payload);
int m_list_map2(m_list* list, void(*fn)(void*, void*, void*), void* payload1, void* payload2);

int m_list_join(m_list* list, uint8_t copy, void* data, size_t size);
int m_list_find(m_list* list, int(*fn)(void*, void*), void* key, void** output);

/** Filter out elements of the list based on a predicate.
 *
 * @param[in] list list
 * @param[in] func predicate function on elements
 * @param[in] aux  user-specified auxiliary data for the predicate
 *
 * @return status code
 * @retval M_LIST_E_NULL list and/or func are NULL
 * @retval M_LIST_OK     success
**/
int m_list_filter(m_list* list, int(*func)(void*, void*), void* aux);

int m_list_zip(m_list* list_a, m_list* list_b, void(*fn)(void*, void*, void*), void* payload);

/** Reverse the order of elements in the list.
 *
 * @param[in] list list
 * 
 * @return status code
 * @retval M_LIST_E_NULL list is NULL
 * @retval M_LIST_OK     success
**/
int m_list_reverse(m_list* list);

int m_list_equal(m_list* list_a, m_list* list_b);

int m_list_match_all(m_list* list, int(*fn)(void*, void*), void* payload);
int m_list_match_any(m_list* list, int(*fn)(void*, void*), void* payload);
int m_list_match_exactly(m_list* list, int(*fn)(void*, void*), uint64_t count, void* payload);
int m_list_match_at_least(m_list* list, int(*fn)(void*, void*), uint64_t count, void* payload);

int m_list_is_sorted(m_list* list, int(*cmp_fn)(void*, void*));

/** Sort the list elements according to a comparator function.
 *
 * The sort is stable and runs in O(nlogn) time, where n is the length of the
 * list. It uses no more than O(1) memory.
 *
 * @param[in] list list
 * @param[in] cmp  comparator function
 * @param[in] auxd auxiliary data for the comparator function
 *
 * @return status code
 * @retval M_LIST_E_NULL list and/or cmp are NULL
 * @retval M_LIST_OK     success
**/
int m_list_sort(m_list* list, int(*cmp)(void*, void*, void*), void* auxd);

/** Access the data stored in the list element.
 *
 * @param[in]  elem list element
 * @param[out] data stored data
 *
 * @return status code
 * @retval M_LIST_E_NULL elem and/or data is NULL
 * @retval M_LIST_OK     success
**/
int m_list_elem_data(m_list_elem* elem, void** data);

/** Advance to the next element in the list.
 *
 * @param[in]  elem list element
 * @param[out] next next element in the list
 *
 * @return status code
 * @retval M_LIST_E_NULL   elem and/or next are NULL
 * @retval M_LIST_E_BOUNDS there are no next elements
 * @retval M_LIST_OK       success
**/
int m_list_elem_next(m_list_elem* elem, m_list_elem** next);

/** Advance to the previous element in the list.
 *
 * @param[in]  elem list element
 * @param[out] prev previous element in the list
 *
 * @return status code
 * @retval M_LIST_E_NULL   elem and/or prev are NULL
 * @retval M_LIST_E_BOUNDS there are no previous elements
 * @retval M_LIST_OK       success
**/
int m_list_elem_prev(m_list_elem* elem, m_list_elem** prev);

#endif
