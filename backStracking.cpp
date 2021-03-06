//第一题，将一系列数字转化为IP地址
class Solution {
    bool check_if_insert(const string& str) {                 //技巧1：将是否满足条件使用一个函数单独写出来；
        if (str.size() == 0 || str.size() > 3) return false;
        if (str.size() > 1 && str[0] == '0') return false;
        int digit = atoi(str.c_str());  //注意不要缺条件；
        if (digit > 255) return false;
        return true;
    }
    void backStracking(string s, int j, vector<string>& strs, string str) {
        if (s.size() == 0) return;                          //首先，如果不满足条件就直接返回；
        if (++j == 4) {                                     //其次，判断条件是否满足，然后进行插入（j就用于这个，将j换个名字，以防冲突）；
            if (check_if_insert(s)) {
                str += s;
                strs.push_back(str);
            }
            return;   
        }
        
        for (int i = 1; i < s.size(); ++i) {    
            string part = s.substr(0, i);
            if (check_if_insert(part))
                backStracking({s.begin() + i, s.end()}, j, strs, str + part + ".");   //回溯法要么就+=之后就-=回到原来状态，要么就直接在参数这里加
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> strs;
        string str;
        backStracking(s, 0, strs, str);
        return strs;
    }
};

//回溯法2：n对括号的所有可能组合方式
class Solution {
    void backStracking(int left, int left_left, int right, vector<string>& res, string tmp) {   //一个一个加上去的，且结果有很多的这种，就要使用回溯
        if (left == 0 && right == 0) {      //首先，如果到达了最后，就添加，这个不需要过滤条件；
            res.push_back(tmp);
            return;
        }
        if (left_left > 0) {                   //其次，有两种情况，加左边还是加右边，以及什么时候加左边什么时候加右边；两边加都可以的情况下，需要都加；
            if (left) backStracking(left - 1, left_left + 1, right,res, tmp + "(");
            backStracking(left, left_left - 1, right - 1, res, tmp + ")");          //在函数调用的时候调整tmp，可以减少回溯变回原来状态的步骤
        }
        else
            backStracking(left - 1, left_left + 1, right,res, tmp + "(");
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string tmp;
        int left = n, left_left = 0, right = n;
        backStracking(left, left_left, right, res, tmp);
        return res;
    }
};

//回溯3：找到集合中加和为target的一组数，允许重复；
class Solution {
    void backStracking(vector<int>& data, int target, int add, int level, vector<int>& tmp, vector<vector<int>>& res) {
        if (add > target) return;                           //退出条件；
        if (add == target) {                                //push_back条件；
            res.push_back(tmp);
            return;
        }
        
        for (int i = level; i < data.size(); ++i) {         //由于每个数都可能加进来，所以使用循环；
            tmp.push_back(data[i]);                 
            backStracking(data, target, add + data[i], i, tmp, res);
            tmp.pop_back();                                 //vector只能使用先push_back然后再pop_back的方法，string可以使用临时字符串；
        }
        
        
    }                                                       //此题保证不重复的做法是，循环是从level开始而不是从0开始；
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> tmp;
        backStracking(candidates, target, 0, 0, tmp, res);
        return res;
    }
};
//上一题的换种问法：数据可以重复，但是结果不可以重复，（上题是结果可以重复，数据不重），那就只能使用先排序和set代替push_back了；
class Solution {
    void backStracking(vector<int>& data, int target, int level, int add, set<vector<int>>& res, vector<int>& tmp) {
        if (add > target) return;
        if (add == target) {
            res.insert(tmp);
            return;
        }
        
        for (int i = level; i < data.size(); ++i) {
            tmp.push_back(data[i]);
            backStracking(data, target, i + 1, add + data[i], res, tmp);
            tmp.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        set<vector<int>> res;
        vector<int> tmp;
        backStracking(candidates, target, 0, 0, res, tmp);
        return {res.begin(), res.end()};
    }
};
//再来一个，1-9这几个数字里选k个，然后加和是n：
class Solution {
    void recursion(vector<vector<int>>& res, vector<int> tmp, int k, int n, int add, int m) {
        if (tmp.size() > k || add > n) return;
        if (tmp.size() == k && add == n) {
            res.push_back(tmp);
            return;
        }
        
        for (int i = m; i < n && i <= 9; ++i) {     //随机选k个，那么就从m开始顺序向后选就可以了，选一个，push_back一个；
            tmp.push_back(i);
            recursion(res, tmp, k, n, add + i, i + 1);  //递归的时候能使用临时值就使用临时值，免得还得回到原来状态；
            tmp.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> tmp;
        recursion(res, tmp, k, n, 0, 1);
        return res;
        
    }
};

//回溯4：获取所有排列：最基本的回溯法；
class Solution {
    void helper(vector<vector<int>>& res, vector<int> tmp, int i) {
        if (i == tmp.size()) {
            res.push_back(tmp);
            return;
        }
        for (int j = i; j < tmp.size(); ++j) {  //必须从i开始，不然可能会取不到0；
            swap(tmp[i], tmp[j]);
            helper(res, tmp, i + 1);
            swap(tmp[i], tmp[j]);
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        helper(result, nums, 0);
        return result;
        
    }
};  

//如果data有重复，但是允许结果有重复，使用set保存结果（因为可能两个数相邻是一样的情况下会造成重复）
class Solution {
    void helper(set<vector<int>>& res, vector<int> tmp, int i) {
        if (i == tmp.size()) res.insert(tmp);
        for (int j = i; j < tmp.size(); ++j) {
            swap(tmp[i], tmp[j]);
            helper(res, tmp, i + 1);
            swap(tmp[i], tmp[j]);
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        set<vector<int>> set;
        helper(set, nums ,0);
        return {set.begin(), set.end()};
    }
};

//回溯法5：利用排列来解题
class Solution {
    void helper(vector<int>& nums, int i, int& res) {
        if (i == nums.size()) {
            res++;
            return;
        }
        
        for (int j = i; j < nums.size(); ++j) {
            swap(nums[i], nums[j]);
            if (nums[i] % (i + 1) == 0 || (i + 1) % nums[i] == 0)   //与排列的差别在于，这个地方满足条件才可以继续向下走，否则就直接回溯；
                 helper(nums, i + 1, res);
            swap(nums[i], nums[j]);
        }
    }
public:
    int countArrangement(int N) {
        int res = 0;
        vector<int> nums;
        nums.reserve(N);
        for (int i = 1; i <= N; ++i)
            nums.push_back(i);
        helper(nums, 0, res);
        return res;
        
    }
};

//回溯法6  递归多少次的题：一组数组，对应手机字母的组合
class Solution {
    void backStracking(const string& digits, vector<string>& const_str, int level, vector<string>& res, string tmp) {
        if (level == digits.size()) {
            res.push_back(tmp);
            return;
        }
        
        int num = digits[level] - '0';
        for (int i = 0; i < const_str[num - 2].size(); ++i) {               //此题是递归的次数也可能需要通过参数传递进来；
            backStracking(digits, const_str, level + 1, res, tmp + const_str[num - 2][i]);
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) return {};              //这里需要注意，如果字符串为空，返回的是{}。而不是{“”}；
        vector<string> const_str{"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"}; //有很多常量，可以定义一个字符串数组；
        vector<string> res;
        string tmp;
        backStracking(digits,const_str, 0, res, tmp);
        return res;
    }
};
//回溯法7  匹配包含点的字符串 //将字符串中的点替换掉之后进行比较
class WordDictionary {
    unordered_set<string> set;
    
    bool backStracking(string& word, int level) {
        if (level == word.size()) 
            return set.find(word) != set.end();
            
        if (word[level] != '.') {
            if (backStracking(word, level + 1)) return true;    //小错误，最开始的没有加{}，导致ifelse匹配出错；
        }
        else {
            for (int i = 0; i < 26; ++i) {              //就是挨个替换；
                word[level] = 'a' + i;
                if (backStracking(word, level + 1)) return true;    //使用返回值的含义是，在递归之后如果需要返回，就直接返回了；
                word[level] = '.';
            }
        }
        return false;
    } 
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        set.insert(word);
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return backStracking(word, 0);
    }
};

//回溯法8，将字符串拆分成一个一个的回文：简单的回溯法，
class Solution {
    bool isPalindrome(const string& s) {
        if (s.size() < 2) return true;
        int i = 0, j = s.size() - 1;
        while (i < s.size()) {
            if (s[i] != s[j]) return false;
            i++, j--;
        }
        return true;
    }
    void backStracking(string s, int level, vector<vector<string>>& res, vector<string>& tmp) {
        if (s.size() == level) {
            res.push_back(tmp);
            return;
        }
        for (int i = level; i < s.size(); ++i) {
            string s_tmp = s.substr(level, i - level + 1);
            if (isPalindrome(s_tmp)) {
                tmp.push_back(s_tmp);
                backStracking(s, i + 1, res, tmp);  //满足条件的才往下走；
                tmp.pop_back();                     //走完之后回溯到原来的状态；
            }
        }
    }
public: 
    vector<vector<string>> partition(string s) {
        if (s.size() == 0) return {};
        vector<vector<string>> res;
        vector<string> tmp;
        backStracking(s, 0, res, tmp);
        return res;
    }
};

//回溯法9：求子集，数据集中有重复，但是结果不能有重复（排序之后不能有重复）
class Solution {
    void generate(set<vector<int>>& res, vector<int>& nums, vector<int> tmp, int i) {
        if (i == nums.size()) {
            res.insert(tmp);
            return;
        }
        generate(res, nums, tmp, i + 1);    //加是一种情况，不加是一种情况；
        tmp.push_back(nums[i]);
        generate(res, nums, tmp, i + 1);
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());     //竟然还需要sort； 结果要求排序后不重复，那就先排序；
        set<vector<int>> res;
        vector<int> tmp;
        generate(res, nums, tmp, 0);
        return {res.begin(), res.end()};
        
    } 
}；
//从一个二维数组中到单词，用过的就不能再用了：二维矩阵第一题
class Solution {
    bool search(vector<vector<char>>& board, vector<vector<int>>& flags ,int i, int j, const string& word, int m) {
        if (m == word.size()) return true;
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || flags[i][j] || board[i][j] != word[m]) return false;     //一并返回false；
        flags[i][j] = true;
        bool res = search(board, flags, i + 1, j , word, m + 1) || search(board, flags, i - 1, j, word, m + 1)
                    || search(board, flags, i, j + 1, word, m + 1) || search(board, flags, i, j - 1, word, m + 1);  //回溯法每个都要走一遍，然后有一个成功了就可以了；
        flags[i][j] = false;
        return res;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.size() == 0) return false;
        vector<vector<int>> flags(board.size(), vector<int>(board[0].size(), 0));   //回溯法操作矩阵，取一个二维标记辅助数组，注意初始化使用括号，而不能使用大括号，大括号不允许缩窄，使得出现不可预料的错误；
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (search(board, flags, i, j, word, 0))
                    return true;
            }
        }
        return false;
    }
};
//求n以内的k个数的组合，排序后不允许重复；
class Solution {
    void recursion(vector<vector<int>>& res, vector<int>& tmp, int n, int m, int k) {
        if (tmp.size() == k) {
            res.push_back(tmp);
            return;
        }
        for (int i = m; i < n; ++i) {
            tmp.push_back(i + 1);
            recursion(res, tmp, n, i + 1, k);   //每个数加或者不加，因为要求排序后无重复，所以遍历的时候，从m开始顺序向后就行了。按全排列的方式是不可以的；
            tmp.pop_back();
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> tmp;
        recursion(res, tmp, n, 0, k);
        return res;
    }
};

//字符串匹配的题，满满的都是技巧；
//技巧1：判断两个是否都为空，那么判断一个就好了，另一个在return上；//和判断树是否都为空一样；
//技巧2：*与前面的字符有关，所以需要考虑后面一个字符，可以先考虑是不是最后一个字符，然后判断下一个字符是不是*；
//技巧3：如果下一个字符是*，那么*可以代表0个，也可以代表无数个，所以代表0个就是第二个数组索引加二，这是第一种情况，还可能是第一个数组对应位置和第二个数组相同时，第一个数组不断加一，而第二个数组不动；
//技巧4：.的匹配就是直接判断是否相等或者其中一个是点；
class Solution {
    bool backTracking(const string& s, const string& p, int level1, int level2) {
        if (level2 == p.size()) return level1 == s.size();
        if (p.size() == level2 + 1) return (level1 == s.size() - 1) && (p[level2] == s[level1] || p[level2] == '.');
        
        if (p[level2 + 1] == '*') {
            return backTracking(s, p, level1, level2 + 2) || 
                ((s[level1] == p[level2] || p[level2] == '.') && s.size() > level1 && backTracking(s, p, level1 + 1, level2));
        }
        return (s[level1] == p[level2] || p[level2] == '.') && backTracking(s, p, level1 + 1, level2 + 1);
    }
public:
    bool isMatch(string s, string p) {
        return backTracking(s, p, 0, 0);
    }
};

//上面的解法比较容易造成思路混乱，这个清楚一点
class Solution {
    bool backStracking(string s, string p) {
        if (p.size() == 0) return s.size() == 0;    //选择检查p是否为空而不是s，是因为即使s为空，那么p也可能是a*，此时也是true;
        if (p.size() > 1 && p[1] == '*') {
            bool condition1 = backStracking(s, p.substr(2));    //*代表0个；
            if (condition1) return true;                        //本来用或的，不用了，就只能用if了；
            if (s.size() == 0) return false;                    //后边会用到s[0]所以需要先判断s.size();
            condition1 = (s[0] == p[0] || p[0] == '.');
            return condition1 && (backStracking(s.substr(1), p));//这个代表是1个及以上的个数；
        }
        return s.size() > 0 && (s[0] == p[0] || p[0] == '.') && backStracking(s.substr(1), p.substr(1)); //只有一个元素，或者下一个元素不为*，都归结到这了
    }
public:
    bool isMatch(string s, string p) {
        return backStracking(s, p);
    }
};

//八皇后的要求是，每行Q的位置不在同一列，斜线位置也不可以；
class Solution {
    bool check(vector<string>& tmp, vector<int>& location, int j) {
        auto it = find(location.begin(), location.end(), location[location.size() - 1]);
        if (it != location.end() - 1) return false;
        
        int last = location.size() - 1;
        for (int i = 0; i < location.size() - 1; ++i) {
            if (abs(location[i] - location[last]) == abs(i - last)) //不能处于斜线位置，那么就需要一个单独的vector来保存以前在哪个位置存储的；
                return false;
        }
        return true;
    }
    void generate(vector<vector<string>>& res, vector<string> tmp, vector<int>& location, int level, int n) {
        if (level == n) {
            res.push_back(tmp);
            return;
        }
        for (int i = 0; i < tmp[level].size(); ++i) {       //矩阵第二题，使用一个for循环挨个处理每一行的思路；
            tmp[level][i] = 'Q';
            location.push_back(i);
            if (check(tmp, location, i))
                generate(res, tmp, location, level + 1, n); //思路就是最简单的回溯法，取完然后放回去就好了；
            tmp[level][i] = '.';
            location.pop_back();
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
       string str(n, '.');
        vector<string> tmp(n, str);
         vector<vector<string>> res;
         vector<int> location;
        generate(res, tmp, location, 0, n);
        return res;
    }
};

//数独求解；
class Solution {
    bool check(vector<vector<char>>& board, int i, int j) {
        for (int m = 0; m < board.size(); ++m) {
            if (m != i && board[m][j] == board[i][j]) return false;
        }
        for (int m = 0; m < board[0].size(); ++m) {
            if (m != j && board[i][j] == board[i][m]) return false;
        }
        int m = i / 3 * 3, n = j / 3 * 3;       //回到3的倍数上去；
        for (int p = 0; p < 3; ++p) {
            for (int q = 0; q < 3; ++q) {
                if (p + m == i && q + n == j) continue;
                if (board[i][j] == board[m + p][n + q])
                    return false;
            }
        }
        return true;
    }
    bool backStracking(vector<vector<char>>& board, int row, int col) { 
        if (row == board.size()) return true;               //矩阵要挨个处理，所以可以采取这种方式；
        if (col == board[0].size())  {
            return backStracking(board, row + 1, 0);        //求的只是一个解，那么只要其返回true，那么各层递归都开始return，即凡是有递归的地方，使用if + return;
        }
        if (board[row][col] != '.') {
            return backStracking(board, row, col + 1);
        }
        else {
            for (int i = 1; i < 10; ++i) {
                board[row][col] = i + '0';
                if (check(board, row, col))     //符合条件的时候向下走；
                    if (backStracking(board, row, col + 1)) return true;
                board[row][col] = '.';          //能走到这，说明不符合条件，那么恢复原来状态；
            }
        }
        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        backStracking(board, 0, 0);
    }
};

//将字符串s根据字典里的字符串组成一个句子（添加空格）//此种解法会超时；
class Solution {
    void backStracking(const string& s, unordered_set<string>& set, int level, vector<string>& res, string tmp) {
        if (level == s.size()) {
            res.push_back({tmp.begin() + 1, tmp.end()});
            return;
        }
        
        for (int i = level + 1; i <= s.size(); ++i) {   //这里出错来着，i既然从level + 1开始，那么边界条件就应该是s.size();
            string str = s.substr(level, i - level);        //比较简单的回溯；
            if (set.find(str) != set.end()) {
                backStracking(s, set, i, res, tmp + " " + str);
            }
        }
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> set;
        for (auto str : wordDict)
            set.insert(str);
        vector<string> res;
        string tmp;
        backStracking(s, set, 0, res, tmp);
        return res;
    }
};
//另一种解法是，遍历字典，字符串太长的话，就遍历字典，然后去比较；
class Solution {
    void backStracking(const string& s, vector<string>& set, int level, vector<string>& res, string tmp) {
        if (level == s.size()) {
            res.push_back({tmp.begin() + 1, tmp.end()});
            return;
        }
        
        for (auto str : set) {
            if (s.size() - level < str.size()) continue;
            string ss = s.substr(level, str.size());
            if (ss == str) {
                backStracking(s, set, level + ss.size(), res, tmp + " " + ss);
            }
        } 
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        vector<string> res;
        string tmp;
        backStracking(s, wordDict, 0, res, tmp);
        return res;
    }
};

//一个二维矩阵里面找多个单词；此题里面有陷阱；
class Solution {
    bool find_helper(vector<vector<char>>& board, vector<vector<int>>& flag, const string& str, int level, int row, int col) {
        if (level == str.size()) return true;
        if (row < 0 || col < 0 || row >= board.size() || col >= board[0].size() || flag[row][col] == 1 || board[row][col] != str[level]) return false;
        flag[row][col] = 1;
        bool res;
        res = find_helper(board, flag, str, level + 1, row + 1, col) || find_helper(board, flag, str, level + 1, row, col + 1) || find_helper(board, flag, str, level + 1, row - 1, col) || find_helper(board, flag, str, level + 1, row, col - 1);
        flag[row][col] = 0;
        return res;
    }
    
    bool helper(vector<vector<char>>& board, const string& str) {
        for (int i = 0; i < board.size(); ++i) {                    //单词可能每个从哪个部位开始，所以需要遍历二维矩阵；
            for (int j = 0; j < board[0].size(); ++j) {
                vector<vector<int>>  flag (board.size(), vector<int>(board[0].size(), 0));  //标志数组每次都要清零，用前定义；
                if (find_helper(board, flag, str, 0 ,i, j))
                    return true;
            }
        }
        return false;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {

        set<string> res;
        for (auto word : words) {
            if (res.find(word) != res.end()) continue;
            if (helper(board, word))
                res.insert(word);
        }
        return {res.begin(), res.end()};
    }
};
