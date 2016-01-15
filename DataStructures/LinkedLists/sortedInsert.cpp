
/*
 Node data structure
 */
struct Node{
    int data;
    struct Node *next;
    struct Node *prev;
};

/*
 Task: Given a sorted doubly linked list, insert the correct element 
 */

/*
 Insert Node in a doubly sorted linked list
 After each insertion, the list should be sorted
 Node is defined as
 struct Node
 {
 int data;
 Node *next;
 Node *prev;
 }
 */

Node* SortedInsert(Node *head,int data){
    
    // initialize new node
    Node* target = new Node();
    target->next = nullptr;
    target->prev = nullptr;
    target->data = data;
    
    if (head == nullptr){
        return target;
    }
    
    Node* cur;
    cur = head;
    
    while (cur != nullptr){
        
        // insertion at head
        if (data <= head->data && cur->prev == nullptr){
            target->next = head;
            head->prev = target;
            return target;
        }
        
        // insertion at tail
        if ( data >= cur->data && cur->next == nullptr ){
            target->prev = cur;
            cur->next = target;
            return head;
        }
        
        // insertion in middle
        if ( data >= cur->data && data <= cur->next->data ){
            Node* tmp = cur->next;
            cur->next = target;
            target->prev = cur;
            target->next = tmp;
            (tmp)->prev = target;
            return head;
        }
        cur = cur->next;
    }
    return head;
}
