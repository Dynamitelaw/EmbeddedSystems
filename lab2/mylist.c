// Jose Rubianes (jer2201)
// CS3157 Advanced Programming
// Lab 3: Part 1

#include "mylist.h"

#include <stdlib.h> 


/*
 * Create a node that holds the given data pointer,
 * and add the node to the front of the list.
 *
 * Note that this function does not manage the lifetime of the object
 * pointed to by 'data'.
 * 
 * It returns the newly created node on success and NULL on failure.
 */
struct Node *addFront(struct List *list, void *data)
{
	//Instantiate Node struct
	struct Node * newNode = malloc(sizeof(struct Node));
	if (newNode == NULL) {
  		return NULL;
	} 

	//Populate newNode
	newNode->data = data;
	newNode->next = list->head;

	//Change head location
	list->head = newNode;

	return newNode;
}


/*
 * Create a node that holds the given data pointer,
 * and add the node to the back of the list.
 *
 * Note that this function does not manage the lifetime of the object
 * pointed to by 'data'.
 * 
 * It returns the newly created node on success and NULL on failure.
 */
struct Node *addBack(struct List *list, void *data)
{
	if (list->head == 0)
	{
		struct Node * newNode = addFront(list, data);
		list->tail = newNode;
		return newNode;
	}
	else
	{
		struct Node * newNode = addAfter(list, list->tail, data);
		list->tail = newNode;
		return newNode;
	}
}


/*
 * Traverse the list, calling f() with each data item.
 */
void traverseList(struct List *list, void (*f)(void *))
{
	struct Node * currentNode;
	currentNode = list->head;

	while (currentNode)
	{
		f(currentNode->data);
		currentNode = currentNode->next;
	}
}

/*
 * Traverse the list, comparing each data item with 'dataSought' using
 * 'compar' function.  ('compar' returns 0 if the data pointed to by
 * the two parameters are equal, non-zero value otherwise.)
 *
 * Returns the first node containing the matching data, 
 * NULL if not found.
 */
struct Node *findNode(struct List *list, const void *dataSought, int (*compar)(const void *, const void *))
{
	struct Node * currentNode;
	currentNode = list->head;

	while (currentNode)
	{
		if (compar(currentNode->data, dataSought))
		{
			return currentNode;
		}
		currentNode = currentNode->next;
	}

	return NULL;
}

/*
 * Flip the sign of the double value pointed to by 'data' by
 * multiplying -1 to it and putting the result back into the memory
 * location.
 */
void flipSignDouble(void *data)
{
	double * pDouble = (double *) data;
	*pDouble = -1 * (*pDouble);
}

/*
 * Compare two double values pointed to by the two pointers.
 * Return 0 if they are the same value, 1 otherwise.
 */
int compareDouble(const void *data1, const void *data2)
{
	return (*((double *) data1) == *((double *) data2));
}

/*
 * Remove the first node from the list, deallocate the memory for the
 * node, and return the 'data' pointer that was stored in the node.
 * Returns NULL is the list is empty.
 */
void *popFront(struct List *list)
{
	//Get head node
	struct Node * headNode;
	headNode = list->head;

	if (!(headNode))
	{
		return NULL;
	}

	//Get data
	void * returnData = headNode->data;

	//Remove and deallocate head node
	list->head = headNode->next;
	free(headNode);

	return returnData;
}

/*
 * Remove all nodes from the list, deallocating the memory for the
 * nodes.  You can implement this function using popFront().
 */
void removeAllNodes(struct List *list)
{
	while(popFront(list));
}

/*
 * Create a node that holds the given data pointer,
 * and add the node right after the node passed in as the 'prevNode'
 * parameter.  If 'prevNode' is NULL, this function is equivalent to
 * addFront().
 *
 * Note that prevNode, if not NULL, is assumed to be one of the nodes
 * in the given list.  The behavior of this function is undefined if
 * prevNode does not belong in the given list.
 *
 * Note that this function does not manage the lifetime of the object
 * pointed to by 'data'.
 * 
 * It returns the newly created node on success and NULL on failure.
 */
struct Node *addAfter(struct List *list, struct Node *prevNode, void *data)
{
	//Instantiate Node struct
	struct Node * newNode = malloc(sizeof(struct Node));
	if (newNode == NULL) {
  		return NULL;
	} 

	//Populate newNode
	newNode->data = data;

	//Insert node
	if (prevNode)
	{
		//Add node after specified location
		newNode->next = prevNode->next;
		prevNode->next = newNode;
	}
	else
	{
		//Add node to the front of the list
		newNode->next = list->head;
		list->head = newNode;
	}

	return newNode;
}

/* 
 * Reverse the list.
 */
void reverseList(struct List *list)
{
	struct Node *previous = NULL;
	struct Node *current = list->head;
	struct Node *next;

	while (current) 
	{
		//Change next pointer backwards
		next = current->next;
		current->next = previous;

		//Move to next node
		previous = current;
		current = next;
	}

	list->head = previous;
}