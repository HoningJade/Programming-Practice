#### Description

给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。

本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

示例:

给定的有序链表： [-10, -3, 0, 5, 9],

一个可能的答案是：[0, -3, 9, -10, null, 5], 它可以表示下面这个高度平衡二叉搜索树：

      0
     / \
    -3   9
     /   /
    -10  5

#### My Solution

```c++
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
class Solution {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        if(!head) return nullptr;
        ListNode *fast = head, *slow = head, *temp;
        while (fast && fast->next){
            temp = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        auto nt = new TreeNode(slow->val);
        if(slow != head) {
            temp->next = nullptr;
            nt->left = sortedListToBST(head);
        }
        if(slow->next) nt->right = sortedListToBST(slow->next);
        return nt;
    }
};
```

#### Sample Solution

-  分治，时间复杂度：$O(nlogn)$，其中 *n* 是链表的长度; 空间复杂度: *O*(log*n*)

  ```c++
  class Solution {
  public:
      ListNode* getMedian(ListNode* left, ListNode* right) {
          ListNode* fast = left;
          ListNode* slow = left;
          while (fast != right && fast->next != right) {
              fast = fast->next;
              fast = fast->next;
              slow = slow->next;
          }
          return slow;
      }
  
      TreeNode* buildTree(ListNode* left, ListNode* right) {
          if (left == right) {
              return nullptr;
          }
          ListNode* mid = getMedian(left, right);
          TreeNode* root = new TreeNode(mid->val);
          root->left = buildTree(left, mid);
          root->right = buildTree(mid->next, right);
          return root;
      }
  
      TreeNode* sortedListToBST(ListNode* head) {
          return buildTree(head, nullptr);
      }
  };
  ```

- 分治 + 中序遍历优化: 方法一的时间复杂度的瓶颈在于寻找中位数节点。由于**构造出的二叉搜索树的中序遍历结果就是链表本身**，因此我们可以将分治和中序遍历结合起来，减少时间复杂度。时间复杂度：*O*(*n*); 空间复杂度：O*(log*n)

  ```c++
  class Solution {
  public:
      int getLength(ListNode* head) {
          int ret = 0;
          for (; head != nullptr; ++ret, head = head->next);
          return ret;
      }
  
      TreeNode* buildTree(ListNode*& head, int left, int right) {
          if (left > right) {
              return nullptr;
          }
          int mid = (left + right + 1) / 2;
          TreeNode* root = new TreeNode();
          root->left = buildTree(head, left, mid - 1);
          root->val = head->val;
          head = head->next;
          root->right = buildTree(head, mid + 1, right);
          return root;
      }
  
      TreeNode* sortedListToBST(ListNode* head) {
          int length = getLength(head);
          return buildTree(head, 0, length - 1);
      }
  }; 
  ```

  此外需要证明：对于任意的有序链表，我们的构造方法得到的二叉搜索树一定是平衡的。显然，如果二叉搜索树的左右子树都是平衡的，并且它们的高度差不超过 1，那么该二叉搜索树就是平衡的。

#### Note

1. 用分治法+递归思想
2. 用快慢指针求链表中位的指针的方法：初始时，快指针 $\textit{fast}$和慢指针 $\textit{slow}$ 均指向链表的左端点 $\textit{left}$。我们将快指针 $\textit{fast}$ 向右移动两次的同时，将慢指针 $\textit{slow}$ 向右移动一次，直到快指针到达边界（即快指针到达右端点或快指针的下一个节点是右端点）。此时，慢指针对应的元素就是中位数。
4. 二叉搜索树的中序遍历结果就是递增序列链表本身