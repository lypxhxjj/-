//1  遍历数组时的当前值，前面的结果加上当前值，还是从当前值重新开始；
//问题：和最大的最长子串问题：
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int result = INT_MIN, sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (sum > 0) sum += nums[i];
            else sum = nums[i];
            if (result < sum) result = sum;
        }
        return result;
    }
};

//找到三角矩阵中最小路径和，从上到下，所以只可以不变或者大一个数，即f(i, j) += min(f(i + 1, j), f(i + 1, j + 1))
//此题特殊的思路是，从下往上遍历，最后可以不用遍历那个数组了；还有如果不让更改元素的话，额外空间可以拷贝出最后一行，来当做临时空间；
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if (triangle.size() == 0) return 0;
        unsigned size = triangle.size() - 2;
        for (int i = size; i >= 0; --i) {
            for (int j = 0; j < triangle[i].size(); ++j) {
                triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
            }
        }
        return triangle[0][0];
    }
};

class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        int n = triangle.size();
        vector<int> dp(triangle.back());
        for (int i = n - 2; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
            }
        }
        return dp[0];
    }
};

//求一个数组中可以跳着递增的最大子数组的大小；
//思路1 是动态规划，保存一个临时数组，每次都向前遍历找到当前值的大小，最后选出一个最大值来；
//以下的思路是：遍历一遍数组，使用一个辅助数组，如果此时的值大于所有值，就插入到最后，否则的话就更新当前值，思路巧妙，背吧
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tmp;
        for (int num : nums) {
            auto it = lower_bound(tmp.begin(), tmp.end(), num);
            if (it == tmp.end()) tmp.push_back(num);
            else *it = num;
        }
        return tmp.size();
    }
};
