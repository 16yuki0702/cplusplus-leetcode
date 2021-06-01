// 1. Two Sum
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); i++) {
            if (m.find(target - nums[i]) != m.end()) {
                return {m[target - nums[i]], i};
            }
            m[nums[i]] = i;
        }
        return {};
    }
};

// 2. Add Two Numbers
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
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return addList(l1, l2, 0);
    }
    ListNode* addList(ListNode* l1, ListNode*l2, int carry) {
        if (!l1 && !l2) {
            if (carry) {
                return new ListNode(carry);
            } else {
                return NULL;
            }
        }
        int val = carry + (l1 ? l1->val : 0) + (l2 ? l2->val : 0);
        ListNode* n = new ListNode(val % 10);
        n->next = addList(l1 ? l1->next : NULL, l2 ? l2->next : NULL, val / 10);
        return n;
    }
};

// 3. Longest Substring Without Repeating Characters
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<int, bool> m;
        int res = 0, idx = 0, marker = 0;
        for (int i = 0; i < s.length(); i++) {
            while (m[s[i]]) {
                m[s[marker]] = false;
                marker++, idx--;
            }
            idx++;
            m[s[i]] = true;
            res = res < idx ? idx : res;
        }
        return res;
    }
};

// 4. Median of Two Sorted Arrays
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> merged;
        int i = 0, j = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] < nums2[j]) {
                merged.push_back(nums1[i]);
                i++;
            } else {
                merged.push_back(nums2[j]);
                j++;
            }
        }
        while (i < nums1.size()) {
            merged.push_back(nums1[i]);
            i++;
        }
        while (j < nums2.size()) {
            merged.push_back(nums2[j]);
            j++;
        }
        int mid = merged.size() / 2;
        if ((merged.size() % 2) == 0) {
            return float(merged[mid - 1] + merged[mid]) / 2;
        } else {
            return float(merged[mid]);
        }
    }
};

// 5. Longest Palindromic Substring
class Solution {
public:
    string findMax(string s, string max, int i, int j) {
        string sub;
        while (i >= 0 && j < s.length() && s[i] == s[j]) {
            sub = s.substr(i, j - i + 1);
            i--, j++;
        }
        return sub.length() > max.length() ? sub : max;
    }

    string longestPalindrome(string s) {
        string max;
        for (int i = 0; i < s.length(); i++) {
            max = findMax(s, max, i, i);
            max = findMax(s, max, i, i + 1);
        }
        return max;
    }
};

// 6. ZigZag Conversion
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) {
            return s;
        }
        vector<string> tmp(numRows, "");
        int d = 1, row = 0;
        for (char c: s) {
            tmp[row].push_back(c);
            row += d;
            if (row == numRows - 1) {
                d = -1;
            } else if (row == 0) {
                d = 1;
            }
        }
        string res;
        for (string c: tmp) {
            res.append(c);
        }
        return res;
    }
};

// 7. Reverse Integer
class Solution {
public:
    int reverse(int x) {
        long res = 0;
        while (x != 0) {
            res = res * 10 + x % 10;
            x /= 10;
            if (abs(res) > INT_MAX) {
                return 0;
            }
        }
        return res;
    }
};

// 8. String to Integer (atoi)
class Solution {
public:
    int myAtoi(string s) {
        bool start = false;
        int sign = 1;
        long res = 0;
        for (char c: s) {
            if ('0' <= c && c <= '9') {
                start = true;
                res = res * 10 + (c - '0');
                if (res > INT_MAX) {
                    break;
                }
            } else if (!start && c == ' ') {
                continue;
            } else if (!start && c == '+') {
                start = true;
            } else if (!start && c == '-') {
                sign = -1;
                start = true;
            } else {
                break;
            }
        }
        res *= sign;
        if (res < INT_MIN) {
            res = INT_MIN;
        } else if (res > INT_MAX) {
            res = INT_MAX;
        }
        return int(res);
    }
};

// 9. Palindrome Number
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        int reverted = 0;
        while (x > reverted) {
            reverted = reverted * 10 + x % 10;
            x /= 10;
        }
        return x == reverted || x == reverted / 10;
    }
};

// 10. Regular Expression Matching
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.length() == 0) {
            return s.length() == 0;
        }
        bool firstMatch = s.length() > 0 && (s[0] == p[0] || p[0] == '.');
        if (p.length() >= 2 && p[1] == '*') {
            return isMatch(s, p.substr(2, p.length()))
                || (firstMatch && isMatch(s.substr(1, s.length()), p));
        }
        return firstMatch && isMatch(s.substr(1, s.length()), p.substr(1, p.length()));
    }
};

// 11. Container With Most Water
class Solution {
public:
    int maxArea(vector<int>& height) {
        int max = 0, left = 0, right = height.size() - 1;
        while (left < right) {
            int x = right - left, y = 0;
            if (height[left] < height[right]) {
                y = height[left];
                left++;
            } else {
                y = height[right];
                right--;
            }
            max = x * y > max ? x * y : max;
        }
        return max;
    }
};

// 12. Integer to Roman
class Solution {
public:
    string intToRoman(int num) {
        string res;
        int m[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        string n[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        for (int i = 0; i < 13; i++) {
            int j = num / m[i];
            num %= m[i];
            while (j > 0) {
                res.append(n[i]);
                j--;
            }
        }
        return res;
    }
};

// 13. Roman to Integer
class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> table = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };
        int res = table[s[s.length() - 1]];
        for (int i = s.length() - 2; i >= 0; i--) {
            res = table[s[i]] < table[s[i + 1]] ? res - table[s[i]] : res + table[s[i]];
        }
        return res;
    }
};

// 14. Longest Common Prefix
class Solution {
public:
    string cmp(string& s1, string& s2) {
        string buff = "";
        for (int i = 0; i < s1.length() && i < s2.length(); i++) {
            if (s1[i] != s2[i]) {
                break;
            }
            buff.push_back(s1[i]);
        }
        return buff;
    }
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 0) {
            return "";
        } else if (strs.size() == 1) {
            return strs[0];
        }
        string p = strs[0];
        for (string v: strs) {
            p = cmp(p, v);
        }
        return p;
    }
};

// 15. 3Sum
class Solution {
public:
    void quickSort(vector<int>& nums, int left, int right) {
        if (left >= right) {
            return;
        }
        int p = left;
        swap(nums[int((left + right) / 2)], nums[right]);
        for (int i = left; i < right; i++) {
            if (nums[i] < nums[right]) {
                swap(nums[i], nums[p]);
                p++;
            }
        }
        swap(nums[p], nums[right]);
        quickSort(nums, left, p - 1);
        quickSort(nums, p + 1, right);
    }
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        quickSort(nums, 0, nums.size() - 1);
        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right) {
                if (left > i + 1 && nums[left] == nums[left - 1]) {
                    left++;
                    continue;
                }
                if (right < nums.size() - 1 && nums[right] == nums[right + 1]) {
                    right--;
                    continue;
                }
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0) {
                    res.push_back({nums[i], nums[left], nums[right]});
                    left++, right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return res;
    }
};

// 16. 3Sum Closest
class Solution {
public:
    void quickSort(vector<int>& nums, int left, int right) {
        if (left >= right) {
            return;
        }
        int p = left;
        swap(nums[int((left + left) / 2)], nums[right]);
        for (int i = left; i < right; i++) {
            if (nums[i] < nums[right]) {
                swap(nums[i], nums[p]);
                p++;
            }
        }
        swap(nums[p], nums[right]);
        quickSort(nums, left, p - 1);
        quickSort(nums, p + 1, right);
    }
    int threeSumClosest(vector<int>& nums, int target) {
        quickSort(nums, 0, nums.size() - 1);
        long res = INT_MAX;
        for (int i = 0; i < nums.size() - 2; i++) {
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == target) {
                    return target;
                } else if (sum > target) {
                    right--;
                } else if (sum < target) {
                    left++;
                }
                res = abs(target - sum) < abs(target - res) ? sum : res;
            }
        }
        return res;
    }
};

// 17. Letter Combinations of a Phone Number
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        if (digits.length() == 0) {
            return res;
        }
        unordered_map<char, string> m = {
            {'1', ""},
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"},
        };
        for (char c: digits) {
            string cs = m[c];
            vector<string> tmp;
            for (char cc: cs) {
                if (res.empty()) {
                    tmp.push_back({cc});
                } else {
                    for (string s: res) {
                        tmp.push_back({s + cc});
                    }
                }
            }
            res = tmp;
        }
        return res;
    }
};

// 18. 4Sum
class Solution {
public:
    void quickSort(vector<int>& nums, int left, int right) {
        if (left >= right) {
            return;
        }
        int p = left;
        swap(nums[(left + right) / 2], nums[right]);
        for (int i = left; i < right; i++) {
            if (nums[i] < nums[right]) {
                swap(nums[i], nums[p]);
                p++;
            }
        }
        swap(nums[p], nums[right]);
        quickSort(nums, left, p - 1);
        quickSort(nums, p + 1, right);
    }
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        if (nums.size() < 4) {
            return res;
        }
        quickSort(nums, 0, nums.size() - 1);
        for (int i = 0; i < nums.size() - 3; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            for (int j = i + 1; j < nums.size() - 2; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }
                int left = j + 1, right = nums.size() - 1;
                while (left < right) {
                    int tmp = nums[i] + nums[j] + nums[left] + nums[right];
                    if (tmp == target) {
                        res.push_back({nums[i], nums[j], nums[left], nums[right]});
                        left++, right--;
                        while (left < right && nums[left] == nums[left - 1]) {
                            left++;
                        }
                        while (left < right && nums[right] == nums[right + 1]) {
                            right--;
                        }
                    } else if (tmp < target) {
                        left++;
                    } else if (tmp > target) {
                        right--;
                    }
                }
            }
        }
        return res;
    }
};

// 19. Remove Nth Node From End of List
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
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummy = new ListNode(-1, head);
        ListNode *slow = dummy, *fast = dummy;
        for (int i = 0; i <= n; i++) {
            fast = fast->next;
        }
        while (fast) {
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;
        return dummy->next;
    }
};

// 20. Valid Parentheses
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c: s) {
            switch (c) {
                case ')':
                    if (st.empty() || st.top() != '(') {
                        return false;
                    }
                    st.pop();
                    break;
                case ']':
                    if (st.empty() || st.top() != '[') {
                        return false;
                    }
                    st.pop();
                    break;
                case '}':
                    if (st.empty() || st.top() != '{') {
                        return false;
                    }
                    st.pop();
                    break;
                default:
                    st.push(c);
            }
        }
        return st.empty();
    }
};
