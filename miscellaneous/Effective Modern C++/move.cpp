#include <iostream>
#include <type_traits>
#include <utility>
#include <queue>

// c++ 11

template <typename T>
struct StructReturnType {
    typedef typename std::remove_reference<T>::type&& type;
};

template <typename T>
typename std::remove_reference<T>::type&& move(T&& param) {
    // typename 在这里用来指示编译器 std::remove_reference<T>::type
    // 是一个类型，并且将其右值引用用于实现移动语义。
    // 这里也是别名声明压倒typedef的优势：支持模板化！而typedef需要结构体来辅助完成同样功能
    // using ReturnType = typename std::remove_reference<T>::type&&;
    return static_cast<typename StructReturnType<T>::type>(param);
    // return static_cast<ReturnType>(param);
}

// c++ 14
template <typename T>
decltype(auto) move(T&& param) {
    using ReturnType = std::remove_reference_t<T>&&;
    return static_cast<ReturnType>(param);
}

// 为什么std::move()不能保证强制转换的后的对象具备可移动的能力
// std::move()
// 实际上没有为对象添加可移动的能力，而是通过转换左值引用为右值引用来改变对象的处理方式。std::move()
// 只是一种标记，用于告诉编译器你希望对对象执行移动操作，而不是复制操作。这个标记并不会使对象本身具备可移动的能力，它依赖于对象的类型和类的实现。

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
private:
    int maxSum = INT_MIN;

public:
    int maxGain(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        
        // 递归计算左右子节点的最大贡献值
        // 只有在最大贡献值大于 0 时，才会选取对应子节点
        int leftGain = max(maxGain(node->left), 0);
        int rightGain = max(maxGain(node->right), 0);

        // 节点的最大路径和取决于该节点的值与该节点的左右子节点的最大贡献值
        int priceNewpath = node->val + leftGain + rightGain;

        // 更新答案
        maxSum = max(maxSum, priceNewpath);

        // 返回节点的最大贡献值
        return node->val + max(leftGain, rightGain);
    }

    int maxPathSum(TreeNode* root) {
        maxGain(root);
        return maxSum;
    }
};
。