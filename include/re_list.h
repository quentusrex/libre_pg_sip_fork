/**
 * @file re_list.h  Interface to Linked List
 *
 * Copyright (C) 2010 Creytiv.com
 */


/** Linked-list element */
struct le {
	struct le *prev;    /**< Previous element                    */
	struct le *next;    /**< Next element                        */
	struct list *list;  /**< Parent list (NULL if not linked-in) */
	void *data;         /**< User-data                           */
};

/** List Element Initializer */
#define LE_INIT {NULL, NULL, NULL, NULL}


/** Defines a linked list */
struct list {
	struct le *head;  /**< First list element */
	struct le *tail;  /**< Last list element  */
};

/** Linked list Initializer */
#define LIST_INIT {NULL, NULL}


/**
 * Defines the list apply handler
 *
 * @param le  List element
 * @param arg Handler argument
 *
 * @return true to stop traversing, false to continue
 */
typedef bool (re_list_apply_h)(struct le *le, void *arg);

/**
 * Defines the list sort handler
 *
 * @param le1  Current list element
 * @param le2  Next list element
 * @param arg  Handler argument
 *
 * @return true if sorted, otherwise false
 */
typedef bool (re_list_sort_h)(struct le *le1, struct le *le2, void *arg);


void re_list_init(struct list *list);
void re_list_flush(struct list *list);
void re_list_clear(struct list *list);
void re_list_append(struct list *list, struct le *le, void *data);
void re_list_prepend(struct list *list, struct le *le, void *data);
void re_list_insert_before(struct list *list, struct le *le, struct le *ile,
			void *data);
void re_list_insert_after(struct list *list, struct le *le, struct le *ile,
		       void *data);
void re_list_unlink(struct le *le);
void re_list_sort(struct list *list, re_list_sort_h *sh, void *arg);
struct le *re_list_apply(const struct list *list, bool fwd, re_list_apply_h *ah,
		      void *arg);
struct le *re_list_head(const struct list *list);
struct le *re_list_tail(const struct list *list);
uint32_t re_list_count(const struct list *list);


/**
 * Get the user-data from a list element
 *
 * @param le List element
 *
 * @return Pointer to user-data
 */
static inline void *re_list_ledata(const struct le *le)
{
	return le ? le->data : NULL;
}


static inline bool re_list_contains(const struct list *list, const struct le *le)
{
	return le ? le->list == list : false;
}


static inline bool re_list_isempty(const struct list *list)
{
	return list ? list->head == NULL : true;
}


#define LIST_FOREACH(list, le)					\
	for ((le) = re_list_head((list)); (le); (le) = (le)->next)
