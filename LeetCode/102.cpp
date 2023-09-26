/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
// 循环
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode *>  queue;
        vector<vector<int>> result;
        if(root != nullptr) queue.push(root);
        while(!queue.empty()){
            vector<int> tmp;
            int size = queue.size();
            for(int i = 0;i < size;++i){
                TreeNode* node = queue.front();
                queue.pop();
                tmp.push_back(node->val);
                if(node->left)   queue.push(node->left);     //左
                if(node->right)  queue.push(node->right);   //右
            }
            result.push_back(tmp);
        }
        return result;
    }
};

// 递归
// class Solution {
// public:
//     void func(TreeNode* cur,vector<vector<int>>& result,int depth){
//         if(cur  == nullptr)     return;
//         if (result.size() == depth) result.push_back(vector<int>());
//         result[depth].push_back(cur->val);
//         func(cur->left,result,depth+1);
//         func(cur->right,result,depth+1);
//     }
//     vector<vector<int>> levelOrder(TreeNode* root) {
//         vector<vector<int>> result;
//         int depth = 0;
//         func(root,result,depth);
//         return result;
//     }
// };