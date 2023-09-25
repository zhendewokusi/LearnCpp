#include <stack>
#include <vector>
#include <algorithm>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};
/*------------------------------------前序遍历-----------------------------------*/
// 递归法
// class Solution {
// public:
//     vector<int> preorderTraversal(TreeNode* root) {
//         vector<int> result;
//         recursion(root,result);
//         return result;
//     }
//     void recursion(TreeNode* node,vector<int>& container){
//         if(node == nullptr) return;
//         container.push_back(node->val);
//         recursion(node->left,container);
//         recursion(node->right,container);
//     }
// };

// 迭代法
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> result;
    if (root == nullptr)
        return result;
    stack<TreeNode*> stack;
    stack.push(root);
    while (!stack.empty()) {
        TreeNode* node = stack.top();
        stack.pop();
        if (node->right)
            stack.push(node->right);
        if (node->left)
            stack.push(node->left);
        result.push_back(node->val);
    }
    return result;
}
/*------------------------------------中序遍历-----------------------------------*/
// 递归法
// class Solution {
// public:
//     vector<int> inorderTraversal(TreeNode* root) {
//         vector<int> result;
//         recursion(root, result);
//         return result;
//     }
//     void recursion(TreeNode* node,vector<int>& container){
//         if(node == nullptr) return;
//         recursion(node->left,container);
//         container.push_back(node->val);
//         recursion(node->right,container);
//     }
// };

// 迭代法
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    if (root == nullptr)
        return result;
    stack<TreeNode*> stack;
    TreeNode* node = root;
    while (!stack.empty() || node != nullptr) {
        if (node != nullptr) {
            stack.push(node);
            node = node->left;
        }
        // 左子节点为空
        else {
            node = stack.top();
            stack.pop();
            result.push_back(node->val);
            node = node->right;
        }
    }
    return result;
}

/*------------------------------------后序遍历-----------------------------------*/
// 递归法
// class Solution {
// public:
    // vector<int> postorderTraversal(TreeNode* root) {
        // vector<int> result;
        // recursion(root, result);
        // return result;
    // }
    // void recursion(TreeNode* node,vector<int>& container){
        // if(node == nullptr) return;
        // recursion(node->left,container);
        // recursion(node->right,container);
        // container.push_back(node->val);
    // }
// };

// 迭代法
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        if(root == nullptr) return result;
        stack<TreeNode *>  stack;
        stack.push(root);
        while(!stack.empty()){
            TreeNode* node = stack.top();
            stack.pop();
            result.push_back(node->val);
            if(node->left) stack.push(node->left);
            if(node->right) stack.push(node->right);
        }
        reverse(result.begin(),result.end());
        return result;
    }