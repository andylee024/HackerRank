
struct Node{
     int data;
     struct Node *next;
};

Node* MergeLists(Node *headA, Node* headB){
    
    Node* root;
    Node* master;
    
    // edge case: at least one null pointer
    if ( !(headA && headB) ){
        if ( (headA == nullptr) && (headB == nullptr) ){return nullptr;}
        if ( (headA != nullptr) && (headB == nullptr) ){return headA;}
        if ( (headA == nullptr) && (headB != nullptr) ){return headB;}
    }
    
    // initialize root
    if ( headA->data < headB->data){
        root = headA;
        headA = headA->next;
    }
    else{
        root = headB;
        headB = headB->next;
    }
    master = root;
    
    // merge lists
    while (headA || headB){
        if ( (headA == nullptr) && headB){
            master->next = headB;
            return root;
        }
        
        if ( headA && (headB == nullptr) ){
            master->next = headA;
            return root;
        }
        
        if (headA->data < headB->data){
            master->next = headA;
            master = master->next;
            headA = headA->next;
        }
        
        else{
            master->next = headB;
            master = master->next;
            headB = headB->next;
        }
    }
    return root;
}
