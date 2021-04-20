/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Alexander Uong
 * Email: uonga@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

struct node{
	int priority_value;
	void* data;

};


/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
	struct dynarray* array;
};





/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq* priority_queue = malloc(sizeof(struct pq));
	priority_queue->array = dynarray_create();
	return priority_queue;

}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	dynarray_free(pq->array);
	free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
 	if (dynarray_size(pq->array) == 0)
		return 1;
	else 
		return 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
	
	struct node* inserted_node = malloc(sizeof(struct node));
	inserted_node->priority_value = priority;
	inserted_node->data = value;
	int inserted_node_index = dynarray_size(pq->array) -1;

	struct node* parent_node;
	int parentindex;

	dynarray_insert(pq->array, inserted_node);
		
	while (inserted_node_index != 0){
		parentindex = ((inserted_node_index-1)/2);
		parent_node = dynarray_get(pq->array, parentindex);

		if (parent_node->priority_value > inserted_node->priority_value){
			dynarray_set(pq->array, parentindex, inserted_node);
			dynarray_set(pq->array, inserted_node_index, parent_node);
	
			inserted_node_index = parentindex;

		}else{
			break;	
		}

	}

	
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	struct node* first = dynarray_get(pq->array,0);
	return first->data;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	struct node*  n =  dynarray_get(pq->array,0);
	return n->priority_value;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
	
	void* first_value = dynarray_get(pq->array,0);

	dynarray_set(pq->array, 0, dynarray_get(pq->array, dynarray_size(pq->array)-1)); 
	dynarray_remove(pq->array, dynarray_size(pq->array)-1);

	struct node* left_child;
	struct node* right_child;
	int index_left;
	int index_right;
	
	struct node* curr = dynarray_get(pq->array, 0); 
	if (dynarray_size(pq->array) > 0){
		int i = 0;
		while (i < dynarray_size(pq->array)){
			int index_left = 2*i+1;
			int index_right = 2*i+2;

		if (index_left < dynarray_size(pq->array)-1 && index_right < dynarray_size(pq->array)-1){
			left_child = dynarray_get(pq->array, index_left);
			right_child = dynarray_get(pq->array, index_right);
			if (left_child->priority_value < right_child->priority_value){
				dynarray_set(pq->array, index_left, curr);
				dynarray_set(pq->array, i, left_child); 
				i = index_left;
			}else if (right_child->priority_value < left_child->priority_value){
                                dynarray_set(pq->array, index_right, curr);
                                dynarray_set(pq->array, i, right_child);
 				i = index_right;
		
			}

		}

		if (index_left < dynarray_size(pq->array)-1 && index_right > dynarray_size(pq->array)-1){
                        left_child = dynarray_get(pq->array, index_left);
                        right_child = dynarray_get(pq->array, index_right);
			if (left_child->priority_value < curr->priority_value){
				dynarray_set(pq->array, index_left, curr);
				dynarray_set(pq->array, i, left_child);
                        	i = index_left;
			}


		}
		
                if (index_right < dynarray_size(pq->array)-1 && index_left > dynarray_size(pq->array)-1){
                        left_child = dynarray_get(pq->array, index_left);
                        right_child = dynarray_get(pq->array, index_right);
                        if (right_child->priority_value < curr->priority_value){
				dynarray_set(pq->array, index_right, curr);
                        	dynarray_set(pq->array, i, right_child);
                        	i = index_right;
			}

		}

		
		
		}

	}

		
	return first_value;


}
