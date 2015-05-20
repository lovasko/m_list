#ifndef M_LIST_H
#define M_LIST_H

struct m_list_elem
{
	struct m_list_elem* next;
	struct m_list_elem* prev;
	void* data;
};

struct m_list_head
{
	struct m_list_elem* first;
	struct m_list_elem* last;
	uint32_t size;
}

#define M_LIST_OK 0
#define M_LIST_E_NULL 1

int m_list_size(struct m_list_head* head, uint32_t* out_size);
int m_list_append(struct m_list_head* head, struct m_list_elem* elem);
int m_list_prepend(struct m_list_head* head, struct m_list_elem* elem);
int m_list_clear(struct m_list_head* head);
int m_list_is_empty(struct m_list_head* head, uint8_t* out_is_empty);
int m_list_remove(struct m_list_head* head, struct m_list_elem* elem);
int m_list_remove_safe(struct m_list_head* head, struct m_list_elem* elem);
int m_list_first(struct m_list_head* head, struct m_list_elem** out_first);
int m_list_last(struct m_list_head* head, struct m_list_elem** out_last);
int m_list_map(struct m_list_head* head, void(*)(struct m_list_elem*));

int m_list_data(struct m_list_elem* elem, void** out_data);
int m_list_next(struct m_list_elem* elem, struct m_list_elem** out_next);
int m_list_prev(struct m_list_elem* elem, struct m_list_elem** out_prev);

#endif

