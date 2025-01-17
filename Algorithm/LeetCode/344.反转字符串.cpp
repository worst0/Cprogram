/*
 * @lc app=leetcode.cn id=344 lang=cpp
 *
 * [344] 反转字符串
 */

// @lc code=start
class Solution {
public:
    void reverseString(vector<char>& s) {
        if (s.empty()) return ;
        int l = 0, r = s.size() - 1;
        while (l < r) {
            swap(s[l++], s[r--]);
        }
        return ;
    }
};
// @lc code=end

