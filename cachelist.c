/****************************************************************************/
/*!
\file   cachelist.c
\author Cole Schwinghammer
\par    email: c.schwinghammer\@digipen.edu
\par    DigiPen login: c.schwinghammer
\par    Course: CS180
\par    Project #2
\date   10/19/2020
\brief  
    This file contains code that will manipulate a link list. This file
    contains the following functions.
      
    Functions include:
    
       + make_node
					Function that will make a node
					
			 + c1_dump
			    Prints out the list.
					
			 + c1_add_end
				  Adds a new node to the end of the list.
					
			 + c1_add_front
			    Adds a new node to the front of the list.
					
			 + c1_remove
			    Searches for the first node with that value and deletes it.
			 
			 + cl_insert_before
			    Searches for the first node with a value and adds a new node befor
					it.
					
			 + c1_insert_after
			    Searches for the first node with a value and adds a new node after
					it.
					
			 + c1_find
			    Searches for the first node with a value and records how many
					comparisons there were.
					
			 + c1_destroy
			    Frees the entire list.
    
*/
/****************************************************************************/

#include <stdio.h>     /* printf          */
#include <stdlib.h>    /* malloc, exit    */
#include <string.h>    /* strncpy         */
#include "cachelist.h" /* cachelist stuff */


/*!************************************************************************
\brief
	Makes a new node
	
\param value
	The value in our node.
	
\param label
	The label in our node.
	
\return 
	new node
**************************************************************************/
static cl_node *make_node(int value, const char *label)
{
  cl_node *node = (cl_node *)malloc(sizeof(cl_node));
  if (!node)
  {
    printf("Can't allocate new node.\n");
    exit(1);
  }

  node->value = value;
  node->next = NULL;

    /* Be sure not to overwrite memory */
  strncpy(node->label, label, LABEL_SIZE - 1);
  node->label[LABEL_SIZE - 1] = 0;
  
  return node;
}

/*!************************************************************************
\brief
	Prints out the whole list.
	
\param list
	Our list of nodes.
	
\return 
	nothing
**************************************************************************/
void cl_dump(const cl_node *list)
{
  printf("==================\n");
  while (list)
  {
    printf("%4i: %s\n", list->value, list->label);
    list = list->next;    
  }
}

/*!************************************************************************
\brief
	Adds a new node to the end of the list

\param list
	Our list of nodes.
	
\param value
	The value in our node.
	
\param label
	The label in our node.
	
\return 
	The head of our list.
**************************************************************************/
cl_node *cl_add_end(cl_node *list, int value, const char *label)
{
	cl_node *newNode = make_node(value, label);
	
	if (list == NULL)
	{
		list = newNode;
	}
	else 
	{
		cl_node *temp = list;
		
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}
	return list;
}
/*!************************************************************************
\brief
	Adds a new node to the front of the list

\param list
	Our list of nodes.
	
\param value
	The value in our node.
	
\param label
	The label in our node.
	
\return 
	The head of our list.
**************************************************************************/
cl_node *cl_add_front(cl_node *list, int value, const char *label)
{
	cl_node *newNode = make_node(value, label);
	
	if (list == NULL)
	{
		list = newNode;
	}
	else
	{
		newNode->next = list;
      
		list = newNode;
	}
  return list;
}

/*!************************************************************************
\brief
	Searches the list for a value and deletes that node.

\param list
	Our list of nodes.
	
\param search_value
	The value to search for.
	
\return 
	The head of our list.
**************************************************************************/
cl_node *cl_remove(cl_node *list, int search_value)
{
	if (list == NULL)
	{
		return NULL;
	}
	cl_node *curr = list;
	cl_node *prev = NULL;

	while (curr->next && curr->value != search_value)
	{
		prev = curr;
		curr = curr->next;
	}
	
	if (curr->value == search_value)
	{
		if (prev == NULL)
		{
			list = list->next;
		}
		else if (curr->next)
		{
			prev->next = curr->next;
		}
		else
		{
			prev->next = NULL;
		}

		free(curr);
	}

	return list;
}

/*!************************************************************************
\brief
	Searches the list for a value and inserts a new node before that.

\param list
	Our list of nodes.
	
\param search_value
	The value to search for.	
	
\param value
	The value in our node.
	
\param label
	The label in our node.
	
\return 
	The head of our list.
**************************************************************************/
cl_node *cl_insert_before(cl_node *list, int search_value, int value, const char *label)
{
	cl_node *curr = list;
	cl_node *prev = NULL;

	while (curr->next && curr->value != search_value)
	{
		prev = curr;
		curr = curr->next;
	}
	
	if (curr->value == search_value)
	{
		if (prev == NULL)
		{
			cl_node *newNode = make_node(value, label);
			newNode->next = list;
			list = newNode;
		}
		else
		{
			cl_node *newNode = make_node(value, label);
			prev->next = newNode;
			newNode->next = curr;
		}
	}
	
  return list;
}

/*!************************************************************************
\brief
	Searches the list for a value and inserts a new node after that.

\param list
	Our list of nodes.
	
\param search_value
	The value to search for.	
	
\param value
	The value in our node.
	
\param label
	The label in our node.
	
\return 
	The head of our list.
**************************************************************************/
void cl_insert_after(cl_node *list, int search_value, int value, const char *label)
{
	cl_node *curr = list;
	cl_node *prev = NULL;

	while (curr->next)
	{
		prev = curr;
		curr = curr->next;
		if (prev->value == search_value)
		{
			break;
		}
	}
	
	if (prev->value == search_value)
	{
		cl_node *newNode = make_node(value, label);
		prev->next = newNode;
		newNode->next = curr;
	}
	else if (curr->value == search_value)
	{
		cl_node *newNode = make_node(value, label);
		curr->next = newNode;
	}
	
}

/*!************************************************************************
\brief
	Searches the list for a value and keeps track of the comparisons.

\param list
	Our list of nodes.
	
\param search_value
	The value to search for.	
	
\param cache
	Checks if the node will be cached.
	
\param compares
	Keeps track of how many comparisons there are.
	
\return 
	The head of our list.
**************************************************************************/
cl_node *cl_find(cl_node *list, int search_value, bool cache, int *compares)
{
  cl_node *curr = list;
	cl_node *prev = NULL;
	*compares = 0;

	while (curr && curr->value != search_value)
	{
		++(*compares);
		prev = curr;
		curr = curr->next;
	}
	
	if (curr->value == search_value)
	{
		++(*compares);

		if (curr->next && prev)
		{
			if (cache)
			{
				prev->next = curr->next;
				curr->next = list;
				list = curr;
			}
		}
		else if (curr && prev)
		{
			if (cache)
			{
				prev->next = NULL;
				curr->next = list;
				list = curr;
			}
		}
	}

	return list;
}

/*!************************************************************************
\brief
	Frees the whole list.

\param list
	Our list of nodes.
	
\return 
	nothing.
**************************************************************************/
void cl_destroy(cl_node **list)
{
	while (*list)
	{
		cl_node *temp = (*list)->next;
		free(*list);
		*list = temp;
	}
}
