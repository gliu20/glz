#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct linkedlist {
    Node *head;
} LinkedList;


LinkedList *createList () {
    const int size = sizeof(LinkedList);
    
    LinkedList *list = malloc(size);
    list->head = NULL;
    
    return list;
    
}

Node *createNode (int data) {
    const int size = sizeof(Node);
    
    Node *node = malloc(size);
    
    node->data = data;
    node->next = NULL;
    
    return node;
}


void printList (LinkedList *list) {
    Node *node = list->head; 
    
    printf("LinkedList:");
    
    while (node != NULL) {
        printf(" %d",node->data);
        node = node->next;
    }
    
    printf("\n");
}



void deleteNode (LinkedList *list, Node *currNode) {
    Node *nextNode = list->head; 
    Node *prevNode = NULL;
    
    // case with deleting the firstNode
    // to delete we get rid of the currNode
    if (list->head == currNode) {
        // save nextNode for pointing the head to
        nextNode = nextNode->next;
        
        free(list->head);
        list->head = nextNode;
    }
    
    // this handles everything including the case with
    // deleting the last node
    while (nextNode != NULL) {
        // pointers to the nodes match so we can delete the previous node
        if (nextNode == currNode) {
            if (prevNode != NULL) {
                // point prevNode to the currNode's next
                // which is where the list continues
                prevNode->next = currNode->next;
            }
            
            free(currNode);
            
            break;
        }
        
        prevNode = nextNode;
        nextNode = nextNode->next;
    }
    
}

int deleteAllNodes (LinkedList *list) {
    int deleteCount = 0;
    while (list->head != NULL) {
        deleteNode(list, list->head);
        deleteCount++;
    }
    return deleteCount;
}

void deleteList (LinkedList *list) {
    deleteAllNodes(list);
    free(list);
}

void insertNodeAfter (LinkedList *list, Node *prevNode, Node *nodeToAdd) {
    // if prevNode is NULL we do insertAtFront
    // if prevNode is tail, we do insertAtBack
    // otherwise we do regular insert
    Node *nextNode = prevNode == NULL ? list->head : prevNode->next;
    
    // list is empty or prevNode is NULL
    // so we want to insert at head.
    if (list->head == NULL || prevNode == NULL) {
        list->head = nodeToAdd;
    }
    
    if (prevNode != NULL) {
        prevNode->next = nodeToAdd;
    }
    
    // set next pointer as long as nodeToAdd exists
    if (nodeToAdd != NULL) {
        nodeToAdd->next = nextNode;
    }
}

void insertIntoOrderedList (LinkedList *list, Node *nodeToAdd, bool useIncreasingOrder) {
    
    Node *prevNode = list->head;
    Node *currNode = list->head->next;
    
    bool didInsert = false;
    
    // special case firstNode
    if (useIncreasingOrder ? 
        prevNode->data >= nodeToAdd->data : 
        prevNode->data <= nodeToAdd->data) {
        
        // do insert at front
        insertNodeAfter(list, NULL, nodeToAdd);
        didInsert = true;
    }
    

    while (currNode != NULL && !didInsert) {
        if (useIncreasingOrder ? 
            currNode->data >= nodeToAdd->data : 
            currNode->data <= nodeToAdd->data) {
            
                
            //printf("Insert after %d\n", prevNode->data);
            insertNodeAfter(list, prevNode, nodeToAdd);
            didInsert = true;
        }
        
        
        prevNode = currNode;
        currNode = currNode->next;
    }
    
    if (!didInsert) {
        insertNodeAfter(list, prevNode, nodeToAdd);
    }
}


int main(int argc, char **argv)
{
    LinkedList *list = createList();
    
    Node *head = createNode(1);
    Node *test1 = createNode(1);
    Node *test2 = createNode(2);
    Node *test3 = createNode(3);
    Node *test4 = createNode(4);
    Node *test5 = createNode(5);
    Node *test6 = createNode(6);
    Node *test0 = createNode(0);
    
    list->head = head;
    
    
    printList(list);
    insertIntoOrderedList(list, test3, true);
    printList(list);
    insertIntoOrderedList(list, test2, true);
    printList(list);
    insertIntoOrderedList(list, test5, true);
    printList(list);
    insertIntoOrderedList(list, test4, true);
    printList(list);
    
    insertIntoOrderedList (list, test6, true);
    printList(list);
    insertIntoOrderedList (list, test0, true);
    printList(list);
    insertIntoOrderedList (list, test1, true);
    printList(list);
    
    deleteList(list);
    
	return 0;
}
