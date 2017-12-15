
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class LinkedListNode {
public:
   int val;
   LinkedListNode *next;

   LinkedListNode(int node_value)
   {
      val = node_value;
      next = NULL;
   }
};

LinkedListNode* _insert_node_singlylinkedlist(LinkedListNode *head, int val)
{
   if(head == NULL)
   {
      head = new LinkedListNode(val);
   }
   else
   {
      LinkedListNode *end = head;
      while(end->next != NULL)
      {
         end = end->next;
      }
      LinkedListNode *node = new LinkedListNode(val);
      end->next = node;
   }
   return head;
}

void print_sll(LinkedListNode **_list)
{
   LinkedListNode* _current = *_list;
   cout << "list: ";
   while( _current != NULL)
   {
      cout << _current->val << " ";
      _current = _current->next;
   }
   cout << endl;
}

void removeAll(int val, LinkedListNode **list) {
    if (list == NULL)
    {
        return;
    }
    else
    {

        // single element in the list
        if((*list) != NULL && (*list)->next == NULL)
        {
            if((*list)->val == val)
            {
               *list = NULL;
            }
            return;
        }

        LinkedListNode *current = *list;
        LinkedListNode *prev = NULL;

        while (current->next != NULL) {
            // cout << "in while " << current->val << endl;
            if (current->val == val)
            {
                // if the list val is to be removed,
                // list pointer should be updated
                if (prev == NULL)
                {
                     // cout << "updating list head" << endl;
                     *list = (current->next);
                }
                // it its not list pointer, meaning prev
                // exists and the links have to updated
                else
                {
                     // cout << "removing element " << endl;
                     prev->next = current->next;
                }
                // clean up on the LinkedListNode thats removed

            }
            else
            {
               // when some values are removed the prev pointer doesnt change
               // cout << "updating prev " << endl;
               prev = current;
            }

            // print_sll(list);

            current = current->next;
        }

        // handling the last node
        if (current != NULL && current->val == val)
        {
            if(prev != NULL)
            {
               prev->next = NULL;
            }
        }

        print_sll(list);
    }
}

int main()
{
   int _val;
   cin >> _val;

   int _list_size;
   int _list_item;
   LinkedListNode* _list = NULL;
   cin >> _list_size;

   int _list_i;
   for(_list_i = 0; _list_i < _list_size; _list_i++)
   {
      cin >> _list_item;
      _list = _insert_node_singlylinkedlist(_list, _list_item);
   }

   cout << "removing " << _val << " from list " << endl;
   print_sll(&_list);
   cout << "--------------" << endl;

   removeAll(_val, &_list);

   cout << "--------------" << endl;
   print_sll(&_list);

   return 0;
}
