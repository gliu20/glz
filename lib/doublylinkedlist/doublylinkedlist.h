// need a string list implementation
// need a string general tree implementation

typedef struct stringNode {
    char data;
    struct stringNode *next;
    struct stringNode *prev;
} StringNode;

typedef struct doublyLinkedList {
    stringNode *head;
} DoublyLinkedList;
