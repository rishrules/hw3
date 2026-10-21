#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void helper_llpivot(Node *&head, Node *&smaller, Node *&larger,Node *&tail_small, Node *&tail_large, int pivot){
    if (head == NULL){
        return;
    }

    Node* current = head;
    head = head->next;
    current->next = NULL;

    if (current->val <= pivot){
        if (smaller == NULL){
            smaller = current;
        }
        else{
            tail_small->next = current;
        }
        tail_small = current;
    }
    else{
        if (larger == NULL){
            larger = current;
        }
        else{
            tail_large->next = current;
        }
        tail_large = current;
    }

    helper_llpivot(head, smaller, larger, tail_small, tail_large, pivot);
}
void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
    smaller = NULL;
    larger = NULL;
    Node* tail_small = smaller;
    Node* tail_large = larger;
    helper_llpivot(head, smaller, larger, tail_small, tail_large, pivot);
}

