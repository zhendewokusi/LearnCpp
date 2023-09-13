/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        //设置一个虚拟头节点
        ListNode * dummyNode = new ListNode(0);
        ListNode * cur = dummyNode;
        int carryNum = 0;
        while(l1 || l2){
            int val1 = l1 ? l1->val : 0 ;
            int val2 = l2 ? l2->val : 0 ;
            cur->next = new ListNode((val1+val2+carryNum)%10,nullptr);
            cur = cur->next;
            carryNum = (val1 + val2 + carryNum ) / 10;

            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        if(carryNum != 0) cur-> next = new ListNode(carryNum);
        return dummyNode->next;
    }
};
