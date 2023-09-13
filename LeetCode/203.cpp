  
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
         //删除的是头节点
         while(head != nullptr && head->val == val){
             ListNode * tmp = head;
             head = head->next;
             delete tmp;
         }
         //非头节点
         ListNode * cur = head;
         while(cur!= nullptr && cur->next != nullptr){
             if(cur->next->val == val){
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
             }else{
                 cur = cur->next;
             }
         }
             return head;
    }
};