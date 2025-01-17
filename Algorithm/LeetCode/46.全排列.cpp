/*
 * @lc app=leetcode.cn id=46 lang=cpp
 *
 * [46] 全排列
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        result.clear();
        path.clear();
        vector<bool> used(nums.size(), false);
        backtarcking(nums, used);
        return result;
    }
private:
    vector<vector<int>> result;
    vector<int> path;

    void backtarcking(vector<int>&nums, vector<bool>&used) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return ;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] == true) {
                continue;
            }
            path.push_back(nums[i]);
            used[i] = true;
            backtarcking(nums, used);
            used[i] = false;
            path.pop_back();
        }
        return ;
    }
    
};
// @lc code=end

