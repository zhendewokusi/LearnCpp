    void addAtIndex(int index, int val) {
        //如果index不在范围内
        if(index < 0 || index > _size) return;

        ListNode * tmp = _dummyHead;
        while(index--){
            tmp = tmp->next;
        }
        tmp->next = new ListNode(val,tmp->next);
        _size++;
    }
    
    void deleteAtIndex(int index) {
        if(index < 0 || index >= _size) return;

        ListNode * tmp = _dummyHead;
        while(index--){
            tmp = tmp->next;
        }
        ListNode * delenode = tmp->next;
        tmp->next = tmp->next->next;
        delete delenode;
    }
