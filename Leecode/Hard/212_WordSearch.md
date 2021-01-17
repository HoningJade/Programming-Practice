#### Description

Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

Example 1:

 Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]

Example 2:


Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 12
board[i][j] is a lowercase English letter.
1 <= words.length <= 3 * $10^4$
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
All the strings of words are unique.

#### Solution

Python 3, two optimizations:

1. 沿着 Trie 的节点回溯。
   将 Trie 与回溯过程一起遍历，即每一步 backtracking(TrieNode)，TrieNode 的深度对应于我们到目前为止匹配的前缀的长度。
2. 在回溯过程中逐渐剪除 Trie 中的节点（剪枝）。
   这个想法的动机是整个算法的时间复杂度取决于 Trie 的大小。对于 Trie 中的叶节点，一旦遍历它（即找到匹配的单词），就不需要再遍历它了。结果，我们可以把它从树上剪下来。逐渐地，这些非叶节点可以成为叶节点以后，因为我们修剪他们的孩子叶节点。在极端情况下，一旦我们找到字典中所有单词的匹配项，Trie 就会变成空的。

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        WORD_KEY = '$'
        
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                # retrieve the next node; If not found, create a empty node.
                node = node.setdefault(letter, {})
            # mark the existence of a word in trie node
            node[WORD_KEY] = word
        
        rowNum = len(board)
        colNum = len(board[0])
        
        matchedWords = []
        
        def backtracking(row, col, parent):    
            
            letter = board[row][col]
            currNode = parent[letter]
            
            # check if we find a match of word
            word_match = currNode.pop(WORD_KEY, False)
            if word_match:
                # also we removed the matched word to avoid duplicates,
                #   as well as avoiding using set() for results.
                matchedWords.append(word_match)
            
            # Before the EXPLORATION, mark the cell as visited 
            board[row][col] = '#'
            
            # Explore the neighbors in 4 directions, i.e. up, right, down, left
            for (rowOffset, colOffset) in [(-1, 0), (0, 1), (1, 0), (0, -1)]:
                newRow, newCol = row + rowOffset, col + colOffset     
                if newRow < 0 or newRow >= rowNum or newCol < 0 or newCol >= colNum:
                    continue
                if not board[newRow][newCol] in currNode:
                    continue
                backtracking(newRow, newCol, currNode)
        
            # End of EXPLORATION, we restore the cell
            board[row][col] = letter
        
            # Optimization: incrementally remove the matched leaf node in Trie.
            if not currNode:
                parent.pop(letter)

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)
        
        return matchedWords    
```

C++

```c++
class TrieNode{
public:
    string word = "";
    vector<TrieNode*> nodes;
    TrieNode():nodes(26, 0){}
};

class Solution {
    int rows, cols;
    vector<string> res;
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        rows = board.size();
        cols = rows ? board[0].size():0;
        if(rows==0 || cols==0) return res;

        //建立字典树的模板
        TrieNode* root = new TrieNode();
        for(string word:words){
            TrieNode *cur = root;
            for(int i=0; i<word.size(); ++i){
                int idx = word[i]-'a';
                if(cur->nodes[idx]==0) cur->nodes[idx] = new TrieNode();
                cur = cur->nodes[idx];
            }
            cur->word = word;
        }

        //DFS模板
        for(int i=0; i<rows; ++i){
            for(int j=0; j<cols; ++j){
                dfs(board, root, i, j);
            }
        }
        return res;
    }

    void dfs(vector<vector<char>>& board, TrieNode* root, int x, int y){
        char c = board[x][y];
        //递归边界
        if(c=='.' || root->nodes[c-'a']==0) return;
        root = root->nodes[c-'a'];
        if(root->word!=""){
            res.push_back(root->word);
            root->word = "";
        }
        
        board[x][y] = '.';
        if(x>0) dfs(board, root, x-1, y);
        if(y>0) dfs(board, root, x, y-1);
        if(x+1<rows) dfs(board, root, x+1, y);
        if(y+1<cols) dfs(board, root, x, y+1);
        board[x][y] = c;
    }  
};
```



#### Note

1. Used Tire (data structure) + backtracking (algorithm)
2. 能够查找前缀的数据结构叫 Trie。和 hashset 比较，Trie 不仅可以检查一个单词，还可以立即找到共享给定前缀的单词。
