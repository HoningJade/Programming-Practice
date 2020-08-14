#### Description

给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。

说明：不允许修改给定的链表。

###### 示例 1：

输入：head = [3,2,0,-4], pos = 1
输出：tail connects to node index 1
解释：链表中有一个环，其尾部连接到第二个节点。

<img src="C:\Users\SURFACE\AppData\Roaming\Typora\typora-user-images\image-20200814210402736.png" alt="image-20200814210402736" style="zoom:25%;" />

###### 示例 2：

输入：head = [1,2], pos = 0
输出：tail connects to node index 0
解释：链表中有一个环，其尾部连接到第一个节点。

<img src="C:\Users\SURFACE\AppData\Roaming\Typora\typora-user-images\image-20200814210419489.png" alt="image-20200814210419489" style="zoom:25%;" />

###### 示例 3：

输入：head = [1], pos = -1
输出：no cycle
解释：链表中没有环。

<img src="C:\Users\SURFACE\AppData\Roaming\Typora\typora-user-images\image-20200814210437262.png" alt="image-20200814210437262" style="zoom:25%;" />

#### Solution

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *fast = head, *slow = head;
        while(true) {
            if(!fast || !fast->next) return NULL;
            slow = slow->next;
            fast = fast->next->next;
            if(fast == slow) break; 
        }
        fast = head;
        while(fast != slow){
            slow = slow->next;
            fast = fast->next;
        }
        return fast;
    }
};
```



#### Note

Use Floyd Algorithm, fast and slow pointer to transform the problem into a “追击问题”
