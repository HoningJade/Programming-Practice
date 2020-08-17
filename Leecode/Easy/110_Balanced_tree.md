#### Description

给定一个二叉树，判断它是否是高度平衡的二叉树。

本题中，一棵高度平衡二叉树定义为：

> 一个二叉树*每个节点* 的左右两个子树的高度差的绝对值不超过1。

#### My Solution

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode *root) {
        if (root) {
            if (!root->left && !root->right) return true;
            else if (!root->left) return (height(root->right) <= 1);
            else if (!root->right) return (height(root->left) <= 1);
            else
                return (height(root->right) - height(root->left) <= 1) &&
                       (height(root->right) - height(root->left) >= -1) && isBalanced(root->right) &&
                       isBalanced(root->left);
        }
        return true;
    }

    int height(TreeNode *node) {
        int temp1 = 1, temp2 = 1;
        if (node->right)
            temp1 += height(node->right);
        if (node->left)
            temp2 += height(node->left);
        return temp1 > temp2 ? temp1 : temp2;
    }
};
```

#### Sample Solution

- 自顶向下递归，时间复杂度：$O(n ^ 2)$，空间复杂度：$O(n)$

```c++
class Solution {
public:
    int height(TreeNode* root) {
        if (root == NULL) {
            return 0;
        } else {
            return max(height(root->left), height(root->right)) + 1;
        }
    }

    bool isBalanced(TreeNode* root) {
        if (root == NULL) {
            return true;
        } else {
            return abs(height(root->left) - height(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right);
        }
    }
};
```

- 好：自底向上的递归, 提前阻断，对于每个节点，函数 $\texttt{height}$ 只会被调用一次, 时间复杂度：$O(n)$，空间复杂度：$O(n)$

  ```c++
  class Solution {
  public:
      int height(TreeNode* root) {
          if (root == NULL) {
              return 0;
          }
          int leftHeight = height(root->left);
          int rightHeight = height(root->right);
          if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1) {
              return -1;
          } else {
              return max(leftHeight, rightHeight) + 1;
          }
      }
  
      bool isBalanced(TreeNode* root) {
          return height(root) >= 0;
      }
  };
  ```

#### Note

1. Use some C++ libraries such as ```max()``` , ```abs()```  can make you program more efficient sometimes.
2. Try to consider 剪支、time & space complexity
