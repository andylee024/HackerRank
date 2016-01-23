Node* Reverse(Node* head){
    if (!head){return nullptr;}
    if (!head->next){return head;}
    
    Node* cur = head;
    Node* tmp1;
    Node* tmp2;
    
    while(cur->next){
        tmp1 = cur->next;
        tmp2 = cur->prev;
        cur->next = tmp2;
        cur->prev = tmp1;
        cur = tmp1;
    }
    cur->next = cur->prev;
    cur->prev = nullptr;
    return cur;
     
}
