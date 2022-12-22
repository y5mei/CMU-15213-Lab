/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * @author ywmei
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /*if malloc returned NULL (failed), return NULL */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    if (q) {
        list_ele_t *curr = q->head;
        while (curr) {
            q->head = q->head->next;
            free(curr->value); // free string by free the staring char ptr
            free(curr);
            curr = q->head;
        }
    }
    /* Free queue structure */
    free(q);
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    /* if q is NULL, return false*/
    if (!q)
        return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    /* if the memory allocation failed, return false*/
    if (!newh)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    char *deepCopyString = malloc(sizeof(char) * (strlen(s) + 1));
    if (!deepCopyString) {
        free(newh);
        return false;
    }
    strcpy(deepCopyString, s);
    /* What if either call to malloc returns NULL? */
    newh->value = deepCopyString;
    newh->next = q->head;
    q->head = newh;
    if (!q->tail)
        q->tail = q->head; // if q's size if 1, head and tail are the same;
    (q->size)++;
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* if q is NULL, return false*/
    if (!q)
        return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    /* if the memory allocation failed, return false*/
    if (!newh)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    char *deepCopyString = malloc(sizeof(char) * (strlen(s) + 1));
    if (!deepCopyString) {
        free(newh);
        return false;
    }
    strcpy(deepCopyString, s);
    /* What if either call to malloc returns NULL? */
    newh->value = deepCopyString;
    newh->next = NULL;
    if (!q->head) {
        q->head = newh;
        q->tail = newh;
    } else {
        q->tail->next = newh;
        q->tail = newh;
    }
    (q->size)++;
    return true;
}

size_t min(size_t a, size_t b) {
    return (a > b) ? b : a;
}
/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. */
    if (!q || !q->head)
        return false;
    list_ele_t *oldhead = q->head;
    if (buf) {
        // if `buf` is non-NULL, copy all chars to buf up to bufsize -1
        size_t n = min(strlen(q->head->value), bufsize - 1);
        strncpy(buf, q->head->value, n);
        buf[n] = '\0';
    }
    q->head = q->head->next;
    (q->size)--;
    free(oldhead->value);
    free(oldhead);
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q || !q->head)
        return 0;
    return q->size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */
    if (!q || !q->head)
        return;
    list_ele_t *prev = NULL;
    list_ele_t *curr = q->head;
    q->tail = curr;
    while (curr) {
        list_ele_t *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    q->head = prev;
}
