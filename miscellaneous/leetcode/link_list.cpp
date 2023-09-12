

struct node{
    //data
    struct node * next;
};

node* init(int n){
    node* ptr1=nullptr,*ptr2=nullptr;
    while(n>0){
        ptr1=new node();
        ptr1->next=ptr2;
        ptr2=ptr1;
        n--;
    }
    return ptr1;
}
//--------
while(n--){

ptr1=new node(0,ptr1);

}
//--------
node* init(int n){
    node* head = nullptr;
    node** ptr = &head;

    while(n-- > 0) {
        *ptr = new node();
        ptr = &((*ptr)->next);
    }

    return head;
}

