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

// 21. Merge Two Sorted Lists
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *current = new ListNode(-1, nullptr);
        ListNode *dummy = current;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                current->next = l1;
                l1 = l1->next;
            } else {
                current->next = l2;
                l2 = l2->next;
            }
            current = current->next;
        }
        while (l1) {
            current->next = l1;
            current = current->next;
            l1 = l1->next;
        }
        while (l2) {
            current->next = l2;
            current = current->next;
            l2 = l2->next;
        }
        return dummy->next;
    }
};

// 22. Generate Parentheses
class Solution {
public:
    vector<string> backTrack(string s, int toOpen, int toClose) {
        vector<string> res;
        if (toOpen == 0 && toClose == 0) {
            return {s};
        }
        if (toOpen > 0) {
            vector<string> b = backTrack(s + "(", toOpen - 1, toClose + 1);
            res.insert(res.end(), b.begin(), b.end());
        }
        if (toClose > 0) {
            vector<string> b = backTrack(s + ")", toOpen, toClose - 1);
            res.insert(res.end(), b.begin(), b.end());
        }
        return res;
    }
    vector<string> generateParenthesis(int n) {
        return backTrack("", n, 0);
    }
};

// 23. Merge k Sorted Lists
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *dummy = new ListNode(-1, nullptr), *c = dummy;
        int min = INT_MAX, p = 0;
        while (true) {
            for (int i = 0; i < lists.size(); i++) {
                if (lists[i] && lists[i]->val < min) {
                    min = lists[i]->val;
                    p = i;
                }
            }
            if (min == INT_MAX) {
                break;
            }
            c->next = lists[p];
            c = c->next;
            lists[p] = lists[p]->next;
            min = INT_MAX;
        }
        return dummy->next;
    }
};

// 24. Swap Nodes in Pairs
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
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *res = head->next;
        head->next = swapPairs(head->next->next);
        res->next = head;
        return res;
    }
};

// 25. Reverse Nodes in k-Group
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
    int listLen(ListNode *n) {
        int res = 0;
        while (n) {
            res++;
            n = n->next;
        }
        return res;
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *dummy = new ListNode(-1, nullptr), *prev = dummy;
        dummy->next = head;
        int len = listLen(head);
        for (int i = 0; i < len / k; i++) {
            for (int j = 1; j < k; j++) {
                ListNode *tmp = prev->next;
                prev->next = head->next;
                head->next = head->next->next;
                prev->next->next = tmp;
            }
            prev = head;
            head = head->next;
        }
        return dummy->next;
    }
};

// 26. Remove Duplicates from Sorted Array
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }
        int prev = nums[0], res = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (prev != nums[i]) {
                nums[res++] = nums[i], prev = nums[i];
            }
        }
        return res;
    }
};

// 27. Remove Element
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0) {
            return 0;
        }
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                nums[res] = nums[i];
                res++;
            }
        }
        return res;
    }
};

// 28. Implement strStr()
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.length() == 0) {
            return 0;
        }
        for (int i = 0; i <= int(haystack.length() - needle.length()); i++) {
            int j = i, k = 0;
            while (k < needle.length() && haystack[j] == needle[k]) {
                k++, j++;
            }
            if (k == needle.length()) {
                return i;
            }
        }
        return -1;
    }
};

// 29. Divide Two Integers
class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }
        long dvd = labs(dividend), dvs = labs(divisor), res = 0;
        int sign = dividend > 0 ^ divisor > 0 ? -1 : 1;
        while (dvd >= dvs) {
            long tmp = dvs, m = 1;
            while (tmp << 1 <= dvd) {
                tmp <<= 1;
                m <<= 1;
            }
            dvd -= tmp;
            res += m;
        }
        return sign * res;
    }
};

// 30. Substring with Concatenation of All Words
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if (words.size() == 0 || s.length() == 0) {
            return {};
        }
        unordered_map<string, int> m;
        for (int i = 0; i < words.size(); i++) {
            m[words[i]]++;
        }
        int wordLen = words[0].length();
        vector<int> res;
        for (int i = 0; i < int(s.length() - (words.size() * wordLen)) + 1; i++) {
            unordered_map<string, int>tmp;
            int j = 0;
            for (j = 0; j < words.size(); j++) {
                string str = s.substr(i + j * wordLen, wordLen);
                if (m.find(str) != m.end()) {
                    tmp[str]++;
                    if (tmp[str] > m[str]) {
                        break;
                    }
                } else {
                    break;
                }
            }
            if (j == words.size()) {
                res.push_back(i);
            }
        }
        return res;
    }
};

// 31. Next Permutation
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i, j;
        for (i = nums.size() - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) {
                break;
            }
        }
        if (i < 0) {
            reverse(nums.begin(), nums.end());
        } else {
            for (j = nums.size() - 1; j > i; j--) {
                if (nums[j] > nums[i]) {
                    break;
                }
            }
            swap(nums[i], nums[j]);
            reverse(nums.begin() + i + 1, nums.end());
        }
    }
};

// 32. Longest Valid Parentheses
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> stack;
        int m = 0;
        stack.push(-1);
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                stack.push(i);
            } else {
                stack.pop();
                if (stack.empty()) {
                    stack.push(i);
                } else {
                    m = max(m, (i - stack.top()));
                }
            }
        }
        return m;
    }
};

// 33. Search in Rotated Sorted Array
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            if (nums[left] == target) {
                return left;
            } else if (nums[right] == target) {
                return right;
            }
            int m = (left + right) / 2;
            if (nums[m] == target) {
                return m;
            }
            if (nums[left] > nums[right]) {
                left++, right--;
            } else {
                if (nums[m] > target) {
                    right = m - 1, left++;
                } else {
                    left = m + 1, right--;
                }
            }
        }
        return -1;
    }
};

// 34. Find First and Last Position of Element in Sorted Array
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] > target) {
                right = mid - 1;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                if (nums[left] < target) {
                    left++;
                }
                if (nums[right] > target) {
                    right--;
                }
                if (nums[left] == nums[right]) {
                    return {left, right};
                }
            }
        }
        return {-1, -1};
    }
};

// 35. Search Insert Position
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] >= target) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};

// 36. Valid Sudoku
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool rows[9][9] = {false, false, false, false, false, false, false, false, false};
        bool cols[9][9] = {false, false, false, false, false, false, false, false, false};
        bool blks[9][9] = {false, false, false, false, false, false, false, false, false};
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    continue;
                }
                int c = board[i][j] - '1';
                int p = (i / 3 * 3) + (j / 3);
                if (rows[i][c] || cols[j][c] || blks[p][c]) {
                    return false;
                }
                rows[i][c] = true, cols[j][c] = true, blks[p][c] = true;
            }
        }
        return true;
    }
};

// 37. Sudoku Solver
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board, 0, 0);
    }

    bool solve(vector<vector<char>>& board, int row, int col) {
        if (9 == row) {
            return true;
        }
        int n_row, n_col;
        if (9 == col + 1) {
            n_row = row + 1, n_col = 0;
        } else {
            n_row = row, n_col = col + 1;
        }
        if (board[row][col] != '.') {
            return solve(board, n_row, n_col);
        }
        char cs[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        for (int i = 0; i < 9; i++) {
            if (in_cell(board, row, col, cs[i]) || in_row(board, row, cs[i]) || in_col(board, col, cs[i])) {
                continue;
            }
            board[row][col] = cs[i];
            if (solve(board, n_row, n_col)) {
                return true;
            }
        }
        board[row][col] = '.';
        return false;
    }

    bool in_cell(vector<vector<char>>& board, int row, int col, char e) {
        int r = row / 3, c = col / 3;
        for (int i = 0; i < 9; i++) {
            if (board[3 * r + i / 3][3 * c + i % 3] == e) {
                return true;
            }
        }
        return false;
    }

    bool in_row(vector<vector<char>>& board, int row, char e) {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == e) {
                return true;
            }
        }
        return false;
    }

    bool in_col(vector<vector<char>>& board, int col, char e) {
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == e) {
                return true;
            }
        }
        return false;
    }
};

// 38. Count and Say
class Solution {
public:
    string countAndSay(int n) {
        if (n == 1) {
            return "1";
        } else if (n == 2) {
            return "11";
        }
        string res = "11";
        for (int i = 3; i <= n; i++) {
            string tmp = "";
            res = res + ' ';
            int c = 1;
            for (int j = 1; j < res.length(); j++) {
                if (res[j] == res[j - 1]) {
                    c++;
                } else {
                    tmp += to_string(c);
                    tmp += res[j - 1];
                    c = 1;
                }
            }
            res = tmp;
        }
        return res;
    }
};

// 39. Combination Sum
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> sub;
        backTrack(res, sub, candidates, 0, target, 0);
        return res;
    }

    void backTrack(vector<vector<int>>& res, vector<int> subset, vector<int>& candidates, int sum, int target, int start_idx) {
        if (sum == target) {
            res.push_back(subset);
            return;
        } else if (sum > target) {
            return;
        }
        for (int i = start_idx; i < candidates.size(); i++) {
            vector<int> sub;
            copy(subset.begin(), subset.end(), back_inserter(sub));
            sub.push_back(candidates[i]);
            backTrack(res, sub, candidates, sum + candidates[i], target, i);
        }
    }
};

// 40. Combination Sum II
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> sub;
        quickSort(candidates, 0, candidates.size() - 1);
        backTrack(res, candidates, sub, target, 0, 0);
        return res;
    }
    void backTrack(vector<vector<int>>& res, vector<int>& can, vector<int> sub, int target, int sum, int start_idx) {
        if (sum == target) {
            res.push_back(sub);
            return;
        } else if (sum > target) {
            return;
        }
        for (int i = start_idx; i < can.size(); i++) {
            if (i > start_idx && can[i] == can[i - 1]) {
                continue;
            }
            vector<int> s;
            copy(sub.begin(), sub.end(), back_inserter(s));
            s.push_back(can[i]);
            backTrack(res, can, s, target, can[i] + sum, i+1);
        }
    }
    void quickSort(vector<int>& v, int left, int right) {
        if (left >= right) {
            return;
        }
        int p = left;
        swap(v[(left + right) / 2], v[right]);
        for (int i = left; i < right; i++) {
            if (v[i] < v[right]) {
                swap(v[p], v[i]);
                p++;
            }
        }
        swap(v[p], v[right]);
        quickSort(v, left, p - 1);
        quickSort(v, p + 1, right);
    }
};

// 41. First Missing Positive
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); i++) {
            m[nums[i]]++;
        }
        for (int i = 1; i <= nums.size() + 1; i++) {
            if (m[i] == 0) {
                return i;
            }
        }
        return 1;
    }
};

// 42. Trapping Rain Water
class Solution {
public:
    int trap(vector<int>& height) {
        int l = 0, r = height.size() - 1, h = 0, res = 0;
        while (l < r) {
            int low = height[height[l] < height[r] ? l++ : r--];
            h = max(h, low);
            res += h - low;
        }
        return res;
    }
};

// 43. Multiply Strings
class Solution {
public:
    string multiply(string num1, string num2) {
        int n = num1.size(), m = num2.size();
        string s(n + m, '0');
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int p = (num1[i] - '0') * (num2[j] - '0') + (s[i + j + 1] - '0');
                s[i + j + 1] = p % 10 + '0';
                s[i + j] += p / 10;
            }
        }
        for (int i = 0; i < m + n; i++) {
            if (s[i] != '0') {
                return s.substr(i);
            }
        }
        return "0";
    }
};

// 44. Wildcard Matching
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();
        int i = 0, j = 0, ast = -1, match;
        while (i < m) {
            if (j < n && p[j] == '*') {
                match = i, ast = j++;
            } else if (j < n && (s[i] == p[j] || p[j] == '?')) {
                i++, j++;
            } else if (ast >= 0) {
                i = ++match, j = ast + 1;
            } else {
                return false;
            }
        }
        while (j < n && p[j] == '*') {
            j++;
        }
        return j == n;
    }
};

// 45. Jump Game II
class Solution {
public:
    int jump(vector<int>& nums) {
        int step = 0, cur = 0, des = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            des = max(des, i + nums[i]);
            if (cur == i) {
                step++, cur = des;
            }
        }
        return step;
    }
};

// 46. Permutations
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> sub;
        backTrack(res, nums, sub);
        return res;
    }
    void backTrack(vector<vector<int>>& res, vector<int> nums, vector<int> sub) {
        if (nums.size() == 0) {
            res.push_back(sub);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            vector<int> n, s;
            copy(nums.begin(), nums.end(), back_inserter(n));
            copy(sub.begin(), sub.end(), back_inserter(s));
            n.erase(n.begin() + i);
            s.push_back(nums[i]);
            backTrack(res, n, s);
        }
    }
};

// 47. Permutations II
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        quickSort(nums, 0, nums.size() - 1);
        do {
            res.push_back(nums);
        } while(nextPerm(nums));
        return res;
    }
    bool nextPerm(vector<int>& nums) {
        int n = nums.size(), i, j;
        for (i = n - 2; i >= 0; i--) {
            if (nums[i + 1] > nums[i]) {
                break;
            }
        }
        if (i < 0) {
            reverse(nums.begin(), nums.end());
            return false;
        } else {
            for (j = n - 1; j > i; j--) {
                if (nums[j] > nums[i]) {
                    break;
                }
            }
            swap(nums[i], nums[j]);
            reverse(nums.begin() + i + 1, nums.end());
            return true;
        }
    }
    void quickSort(vector<int>& n, int left, int right) {
        if (left >= right) {
            return;
        }
        int p = left;
        swap(n[(left + right) / 2], n[right]);
        for (int i = left; i < right; i++) {
            if (n[i] < n[right]) {
                swap(n[i], n[p]), p++;
            }
        }
        swap(n[p], n[right]);
        quickSort(n, left, p - 1);
        quickSort(n, p + 1, right);
    }
};

// 48. Rotate Image
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        for (int i = 0, j = matrix.size() - 1; i < matrix.size() / 2; i++, j--) {
            swap(matrix[i], matrix[j]);
        }
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = i + 1; j < matrix.size(); j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
};

// 49. Group Anagrams
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, int> m;
        vector<vector<string>> res;
        for (string s: strs) {
            string t = s;
            sort(t.begin(), t.end());
            if (m.find(t) != m.end()) {
                res[m[t]].push_back(s);
            } else {
                m[t] = res.size();
                res.push_back({s});
            }
        }
        return res;
    }
};

// 50. Pow(x, n)
class Solution {
public:
    double myPow(double x, int n) {
        long nn = n;
        if (nn == 0) {
            return 1.0;
        }
        if (nn < 0) {
            x = 1 / x, nn = -nn;
        }
        return pow(x, 1.0, nn);
    }
    double pow(double x, double res, long n) {
        if (n == 0) {
            return res;
        }
        if (n & 1 == 1) {
            res *= x;
        }
        return pow(x * x, res, n >> 1);
    }
};

// 51. N-Queens
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<vector<char>> board(n, vector<char>(n, '.'));
        vector<bool> cols(n, false);
        backTrack(res, board, cols, 0, n);
        return res;
    }
    void backTrack(vector<vector<string>>& res, vector<vector<char>>& board, vector<bool>& cols, int r, int n) {
        if (r == n) {
            vector<string> tmp;
            for (vector<char> b: board) {
                tmp.push_back(string(b.begin(), b.end()));
            }
            res.push_back(tmp);
            return;
        }
        for (int c = 0; c < n; c++) {
            if (cols[c] || hasDiagonal(board, r, c, n)) {
                continue;
            }
            cols[c] = true, board[r][c] = 'Q';
            backTrack(res, board, cols, r + 1, n);
            cols[c] = false, board[r][c] = '.';
        }
    }
    bool hasDiagonal(vector<vector<char>>& board, int r, int c, int n) {
        for (int i = r, j = c; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') {
                return true;
            }
        }
        for (int i = r, j = c; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') {
                return true;
            }
        }
        return false;
    }
};

// 52. N-Queens II
class Solution {
public:
    int totalNQueens(int n) {
        int res = 0;
        vector<vector<char>> board(n, vector<char>(n, '.'));
        vector<bool> cols(n, false);
        backTrack(board, cols, res, 0, n);
        return res;
    }
    void backTrack(vector<vector<char>>& board, vector<bool>& cols, int& res, int r, int n) {
        if (r == n) {
            res++;
            return;
        }
        for (int c = 0; c < n; c++) {
            if (cols[c] || hasDiagonal(board, r, c, n)) {
                continue;
            }
            cols[c] = true, board[r][c] = 'Q';
            backTrack(board, cols, res, r + 1, n);
            cols[c] = false, board[r][c] = '.';
        }
    }
    bool hasDiagonal(vector<vector<char>>& board, int r, int c, int n) {
        for (int i = r, j = c; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q') {
                return true;
            }
        }
        for (int i = r, j = c; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q') {
                return true;
            }
        }
        return false;
    }
};

// 53. Maximum Subarray
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int cur = nums[0], res = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            cur = cur < 0 ? nums[i] : cur + nums[i];
            res = max(res, cur);
        }
        return res;
    }
};

// 54. Spiral Matrix
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int top = 0, bottom = matrix.size() - 1, left = 0, right = matrix[0].size() - 1;
        vector<int> res;
        while (top <= bottom && left <= right) {
            for (int i = left; i <= right; i++) {
                res.push_back(matrix[top][i]);
            }
            top++;
            for (int i = top; i <= bottom; i++) {
                res.push_back(matrix[i][right]);
            }
            right--;
            for (int i = right; i >= left; i--) {
                if (top > bottom) {
                    break;
                }
                res.push_back(matrix[bottom][i]);
            }
            bottom--;
            for (int i = bottom; i >= top; i--) {
                if (left > right) {
                    break;
                }
                res.push_back(matrix[i][left]);
            }
            left++;
        }
        return res;
    }
};

// 55. Jump Game
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int cur = 0, des = nums.size() - 1;
        for (int i = 0; i < nums.size(); i++) {
            if (cur < i) {
                return false;
            }
            cur = max(cur, i + nums[i]);
        }
        return cur >= des;
    }
};

// 56. Merge Intervals
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() == 1) {
            return intervals;
        }
        vector<vector<int>> res;
        sort(intervals.begin(), intervals.end());
        res.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            vector<int>& tmp = res.back();
            if (tmp[1] < intervals[i][0]) {
                res.push_back(intervals[i]);
            } else {
                tmp[1] = max(tmp[1], intervals[i][1]);
            }
        }
        return res;
    }
};

// 57. Insert Interval
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        int i = 0;
        for (; i < intervals.size() && intervals[i][0] <= newInterval[1]; i++) {
            if (intervals[i][1] < newInterval[0]) {
                res.push_back(intervals[i]);
            } else {
                newInterval[0] = min(newInterval[0], intervals[i][0]);
                newInterval[1] = max(newInterval[1], intervals[i][1]);
            }
        }
        res.push_back(newInterval);
        res.insert(res.end(), intervals.begin() + i, intervals.end());
        return res;
    }
};

// 58. Length of Last Word
class Solution {
public:
    int lengthOfLastWord(string s) {
        int res = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s[i] != ' ') {
                res++;
            } else if (res > 0) {
                return res;
            }
        }
        return res;
    }
};

// 59. Spiral Matrix II
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        int count = 0, top = 0, bottom = n - 1, left = 0, right = n - 1;
        while (top <= bottom && left <= right) {
            for (int i = left; i <= right; i++) {
                res[top][i] = ++count;
            }
            top++;
            for (int i = top; i <= bottom; i++) {
                res[i][right] = ++count;
            }
            right--;
            for (int i = right; i >= left; i--) {
                if (top > bottom) {
                    break;
                }
                res[bottom][i] = ++count;
            }
            bottom--;
            for (int i = bottom; i >= top; i--) {
                if (left > right) {
                    break;
                }
                res[i][left] = ++count;
            }
            left++;
        }
        return res;
    }
};

// 60. Permutation Sequence
class Solution {
public:
    string getPermutation(int n, int k) {
        string res = "", src = "", des = "";
        int count = 0;
        for (int i = 1; i <= n; i++) {
            src.push_back(i + '0');
            des.push_back('0');
        }
        backTrack(res, src, des, count, k, n, 0);
        return res;
    }
    void backTrack(string& res, string& src, string& des, int& count, int k, int n, int pos) {
        if (pos == n || count >= k) {
            if (++count == k) {
                res = des;
            }
            return;
        }
        for (int i = 0; i < n; i++) {
            if (src[i] == '0') {
                continue;
            }
            des[pos] = src[i];
            src[i] = '0';
            backTrack(res, src, des, count, k, n, pos + 1);
            src[i] = des[pos];
        }
    }
};

// 61. Rotate List
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
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head) {
            return head;
        }
        int count = 0;
        ListNode *tmp = head;
        while (tmp) {
            count++, tmp = tmp->next;
        }
        int p = k % count;
        if (p == 0) {
            return head;
        }
        ListNode *fast = head, *slow = head;
        for (int i = 0; i < p; i++) {
            fast = fast->next;
        }
        while (fast && fast->next) {
            fast = fast->next, slow = slow->next;
        }
        ListNode *res = slow->next;
        slow->next = NULL, fast->next = head;
        return res;
    }
};

// 62. Unique Paths
class Solution {
public:
    int uniquePaths(int m, int n) {
        int path[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                path[i][j] = (i == 0 || j == 0) ? 1 : path[i - 1][j] + path[i][j - 1];
            }
        }
        return path[m - 1][n - 1];
    }
};

// 63. Unique Paths II
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int r = obstacleGrid.size(), c = obstacleGrid[0].size();
        int dp[r][c];
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                } else if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                } else if (i == 0) {
                    dp[i][j] = dp[i][j - 1];
                } else if (j == 0) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp[r - 1][c - 1];
    }
};

// 64. Minimum Path Sum
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        int dp[r][c];
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = grid[i][j];
                } else if (i == 0) {
                    dp[i][j] = grid[i][j] + dp[i][j - 1];
                } else if (j == 0) {
                    dp[i][j] = grid[i][j] + dp[i - 1][j];
                } else {
                    dp[i][j] = grid[i][j] + (dp[i - 1][j] > dp[i][j - 1] ? dp[i][j - 1] : dp[i - 1][j]);
                }
            }
        }
        return dp[r - 1][c - 1];
    }
};

// 65. Valid Number
class Solution {
public:
    bool isNumber(string s) {
        static regex r(R"_([+-]?(\d+(\.\d*)?|\.\d+)([eE][+-]?\d+)?)_");
        return regex_match(s, r);
    }
};

// 66. Plus One
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> res;
        int tmp = 1;
        for (int i = digits.size() - 1; i >= 0; i--) {
            tmp += digits[i];
            res.push_back(tmp % 10);
            tmp /= 10;
        }
        if (tmp > 0) {
            res.push_back(tmp);
        }
        for (int i = 0, j = res.size() - 1; i < j; i++, j--) {
            swap(res[i], res[j]);
        }
        return res;
    }
};

// 67. Add Binary
class Solution {
public:
    string addBinary(string a, string b) {
        string res;
        for (int i = a.size() - 1, j = b.size() - 1, c = 0; i >= 0 || j >= 0 || c; i--, j--) {
            int x = i >= 0 ? a[i] - '0' : 0;
            int y = j >= 0 ? b[j] - '0' : 0;
            int s = x ^ y ^ c;
            c = (x & y) | (x & c) | (y & c);
            res = to_string(s) + res;
        }
        return res;
    }
};

// 68. Text Justification
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        if (maxWidth == 0) {
            return {""};
        }
        int i = 0, j = 0;
        while (j != words.size()) {
            int len = -1;
            while (j < words.size() && len + words[j].size() + 1 <= maxWidth) {
                len += words[j++].size() + 1;
            }
            int space = maxWidth - len + j - i - 1;
            int k = i;
            while (space) {
                words[k++] += " ", space--;
                if (j != words.size() && (k == j - 1 || k == j)) {
                    k = i;
                }
                if (j == words.size() && k == j) {
                    k = j - 1;
                }
            }
            string line = "";
            for (int l = i; l < j; l++) {
                line += words[l];
            }
            res.push_back(line);
            i = j;
        }
        return res;
    }
};

// 69. Sqrt(x)
class Solution {
public:
    int mySqrt(int x) {
        if (x <= 1) {
            return x;
        }
        int res = x / 2;
        while (true) {
            int tmp = (res + x / res) / 2;
            if (tmp >= res) {
                return res;
            }
            res = tmp;
        }
    }
};

// 70. Climbing Stairs
class Solution {
public:
    int climbStairs(int n) {
        if (n < 3) {
            return n;
        }
        int p1 = 1, p2 = 2, res = 0;
        for (int i = 2; i < n; i++) {
            res = p1 + p2;
            p1 = p2;
            p2 = res;
        }
        return res;
    }
};

// 71. Simplify Path
class Solution {
public:
    string simplifyPath(string path) {
        string res, tmp;
        vector<string> stack;
        stringstream ss(path);
        while (getline(ss, tmp, '/')) {
            if (tmp == "" || tmp == ".") {
                continue;
            }
            if (tmp == ".." && !stack.empty()) {
                stack.pop_back();
            } else if (tmp != "..") {
                stack.push_back(tmp);
            }
        }
        for (string s: stack) {
            res += "/" + s;
        }
        return res.empty() ? "/" : res;
    }
};

// 72. Edit Distance
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            dp[i][0] = i;
        }
        for (int j = 1; j <= n; j++) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
                }
            }
        }
        return dp[m][n];
    }
};

// 73. Set Matrix Zeroes
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int r_len = matrix.size(), c_len = matrix[0].size();
        bool is_first_r = false, is_first_c = false;
        for (int i = 0; i < r_len; i++) {
            for (int j = 0; j < c_len; j++) {
                if (matrix[i][j] == 0) {
                    if (i == 0) {
                        is_first_r = true;
                    }
                    if (j == 0) {
                        is_first_c = true;
                    }
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for (int i = 1; i < r_len; i++) {
            for (int j = 1; j < c_len; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        if (is_first_r) {
            for (int j = 0; j < c_len; j++) {
                matrix[0][j] = 0;
            }
        }
        if (is_first_c) {
            for (int i = 0; i < r_len; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};

// 74. Search a 2D Matrix
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int r_len = matrix.size(), c_len = matrix[0].size();
        if (target < matrix[0][0] || target > matrix[r_len - 1][c_len - 1]) {
            return false;
        }
        int top = 0, bottom = r_len - 1;
        while (true) {
            int mid = (top + bottom) / 2;
            int y = matrix[mid][0];
            if (y == target) {
                return true;
            } else if (y > target) {
                bottom = mid - 1;
            } else if (y < target) {
                top = mid + 1;
            }
            if (top > bottom) {
                break;
            }
        }
        int left = 0, right = c_len - 1;
        while (true) {
            int mid = (left + right) / 2;
            int x = matrix[bottom][mid];
            if (x == target) {
                return true;
            } else if (x > target) {
                right = mid - 1;
            } else if (x < target) {
                left = mid + 1;
            }
            if (left > right) {
                break;
            }
        }
        return false;
    }
};

// 75. Sort Colors
class Solution {
public:
    void sortColors(vector<int>& nums) {
        q_sort(nums, 0, nums.size() - 1);
    }
    void q_sort(vector<int>& nums, int left, int right) {
        if (left >= right) {
            return;
        }
        int j = left;
        swap(nums[(left + right) / 2], nums[right]);
        for (int i = left; i < right; i++) {
            if (nums[i] < nums[right]) {
                swap(nums[i], nums[j]);
                j++;
            }
        }
        swap(nums[j], nums[right]);
        q_sort(nums, left, j - 1);
        q_sort(nums, j + 1, right);
    }
};

// 76. Minimum Window Substring
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> v(128, 0);
        for (char c: t) {
            v[c]++;
        }
        int start = 0, end = 0, counter = t.size();
        int min_s = 0, min_len = INT_MAX;
        while (end < s.size()) {
            if (v[s[end]] > 0) {
                counter--;
            }
            v[s[end]]--;
            end++;
            while (counter == 0) {
                if (end - start < min_len) {
                    min_s = start, min_len = end - start;
                }
                v[s[start]]++;
                if (v[s[start]] > 0) {
                    counter++;
                }
                start++;
            }
        }
        if (min_len != INT_MAX) {
            return s.substr(min_s, min_len);
        }
        return "";
    }
};

// 77. Combinations
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> cur;
        backTrack(res, cur, 1, n, k);
        return res;
    }
    void backTrack(vector<vector<int>>& res, vector<int> cur, int idx, int n, int k) {
        if (cur.size() == k) {
            res.push_back(cur);
            return;
        }
        for (int i = idx; i <= n; i++) {
            vector<int> c = cur;
            c.push_back(i);
            backTrack(res, c, i + 1, n, k);
        }
    }
};

// 78. Subsets
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> cur;
        backTrack(res, nums, cur, 0);
        return res;
    }
    void backTrack(vector<vector<int>>& res, vector<int>&nums, vector<int> cur, int idx) {
        res.push_back(cur);
        for (int i = idx; i < nums.size(); i++) {
            vector<int> c = cur;
            c.push_back(nums[i]);
            backTrack(res, nums, c, i + 1);
        }
    }
};

// 79. Word Search
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (dfs(board, word, i, j)) {
                    return true;
                }
            }
        }
        return false;
    }
    bool dfs(vector<vector<char>>& b, string& w, int i, int j) {
        if (!w.size()) {
            return true;
        }
        if (i < 0 || i >= b.size() || j < 0 || j >= b[0].size() || b[i][j] != w[0]) {
            return false;
        }
        char c = b[i][j];
        b[i][j] = '*';
        string s = w.substr(1);
        bool res = dfs(b, s, i - 1, j) || dfs(b, s, i + 1, j) ||
            dfs(b, s, i, j - 1) || dfs(b, s, i, j + 1);
        b[i][j] = c;
        return res;
    }
};

// 80. Remove Duplicates from Sorted Array II
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
        int p = 2;
        for (int i = p; i < nums.size(); i++) {
            if (nums[p - 2] != nums[i]) {
                nums[p] = nums[i];
                p++;
            }
        }
        return p;
    }
};

// 81. Search in Rotated Sorted Array II
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if (nums.size() == 1) {
            return nums[0] == target;
        };
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            if (nums[l] == target) {
                return true;
            } else if (nums[r] == target) {
                return true;
            }
            int m = (l + r) / 2;
            if (nums[m] == target) {
                return true;
            }
            while ((l < nums.size() - 1 && r > 0) && nums[l] == nums[r]) {
                l++, r--;
            }
            if (nums[l] == target) {
                return true;
            } else if (nums[r] == target) {
                return true;
            }
            if (nums[l] > nums[r]) {
                l = slideLeft(nums, l), r = slideRight(nums, r);
            } else {
                if (nums[m] > target) {
                    l = slideLeft(nums, l), r = m - 1;
                } else {
                    r = slideRight(nums, r), l = m + 1;
                }
            }
        }
        return false;
    }
    int slideLeft(vector<int>& nums, int l) {
        while (l < nums.size() - 1 && nums[l] == nums[l + 1]) {
            l++;
        }
        return ++l;
    }
    int slideRight(vector<int>& nums, int r) {
        while (r > 0 && nums[r] == nums[r - 1]) {
            r--;
        }
        return --r;
    }
};

// 82. Remove Duplicates from Sorted List II
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
    ListNode* deleteDuplicates(ListNode* head) {
        return deleteDup(head, false);
    }
    ListNode* deleteDup(ListNode* head, bool dup) {
        if (head == nullptr) {
            return nullptr;
        }
        while (head->next != 0 && head->val == head->next->val) {
            dup = true, head->next = head->next->next;
        }
        head->next = deleteDup(head->next, false);
        return dup ? head->next : head;
    }
};

// 83. Remove Duplicates from Sorted List
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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *cur = head;
        while (cur && cur->next) {
            if (cur->val == cur->next->val) {
                ListNode *tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        return head;
    }
};

// 84. Largest Rectangle in Histogram
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        stack<int> stack;
        int i = 0, m = 0;
        while (i < heights.size()) {
            if (stack.empty() || heights[i] >= heights[stack.top()]) {
                stack.push(i++);
            } else {
                int t = stack.top();
                stack.pop();
                m = max(m, heights[t] * (stack.empty() ? i : i - stack.top() - 1));
            }
        }
        return m;
    }
};

// 85. Maximal Rectangle
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.size() == 0) {
            return 0;
        }
        int m = 0;
        vector<vector<int>> dp(matrix.size(), vector<int>(matrix[0].size(), 0));
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (matrix[i][j] == '1') {
                    dp[i][j] = (j == 0) ? 1 : dp[i][j - 1] + 1;
                    int width = dp[i][j];
                    for (int k = i; k >= 0; k--) {
                        width = min(width, dp[k][j]);
                        m = max(m, width * (i - k + 1));
                    }
                }
            }
        }
        return m;
     }
};

// 86. Partition List
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
    ListNode* partition(ListNode* head, int x) {
        ListNode *less = new ListNode, *greater = new ListNode;
        ListNode *i = less, * j = greater;
        while (head) {
            if (head->val < x) {
                i->next = head;
                i = i->next;
            } else {
                j->next = head;
                j = j->next;
            }
            head = head->next;
        }
        j->next = nullptr;
        i->next = greater->next;
        return less->next;
    }
};

// 87. Scramble String
class Solution {
public:
    unordered_map<string, bool> m;
    bool isScramble(string s1, string s2) {
        if (s1.size() != s2.size()) {
            return false;
        }
        if (s1 == s2 || s1.size() == 0) {
            return true;
        }
        string key = s1 + "" + s2;
        if (m.find(key) != m.end()) {
            return m[key];
        }
        bool flag = false;
        for (int i = 1; i < s1.size(); i++) {
            if (isScramble(s1.substr(0, i), s2.substr(s1.size() - i, i))
               && isScramble(s1.substr(i, s1.size() - i), s2.substr(0, s1.size() - i))) {
                flag = true;
                break;
            }
            if (isScramble(s1.substr(0, i), s2.substr(0, i))
               && isScramble(s1.substr(i, s1.size() - i), s2.substr(i, s1.size() - i))) {
                flag = true;
                break;
            }
        }
        m[key] = flag;
        return flag;
    }
};

// 88. Merge Sorted Array
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, k = nums1.size() - 1;
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }
    }
};

// 89. Gray Code
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> res;
        for (int i = 0, target = 1 << n; i < target; i++) {
            res.push_back(i ^ (i >> 1));
        }
        return res;
    }
};

// 90. Subsets II
class Solution {
public:
    void qSort(vector<int>& nums, int left, int right) {
        if (left >= right) {
            return;
        }
        int p = left;
        swap(nums[(left + right) / 2], nums[right]);
        for (int i = left; i < right; i++) {
            if (nums[i] < nums[right]) {
                swap(nums[p], nums[i]);
                p++;
            }
        }
        swap(nums[p], nums[right]);
        qSort(nums, left, p - 1);
        qSort(nums, p + 1, right);
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> cur;
        qSort(nums, 0, nums.size() - 1);
        backTrack(res, nums, cur, 0);
        return res;
    }
    void backTrack(vector<vector<int>>& res, vector<int> nums, vector<int>& cur, int start) {
        res.push_back(cur);
        for (int i = start; i < nums.size(); i++) {
            if (i == start || nums[i] != nums[i - 1]) {
                cur.push_back(nums[i]);
                backTrack(res, nums, cur, i + 1);
                cur.pop_back();
            }
        }
    }
};

// 91. Decode Ways
class Solution {
public:
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') {
            return 0;
        }
        int pre = 1, cur = 1;
        for (int i = 2; i <= s.size(); i++) {
            if (s[i - 1] == '0') {
                if (s[i - 2] == '1' || s[i - 2] == '2') {
                    cur = pre;
                } else {
                    return 0;
                }
            } else {
                int n = atoi(s.substr(i - 2, 2).c_str());
                int tmp = cur;
                cur = cur + (n >= 11 && n <= 26 ? pre : 0);
                pre = tmp;
            }
        }
        return cur;
    }
};

// 92. Reverse Linked List II
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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode *dummy = new ListNode(), *pre = dummy, *cur;
        dummy->next = head;
        for (int i = 0; i < left - 1; i++) {
            pre = pre->next;
        }
        cur = pre->next;
        for (int i = 0; i < right - left; i++) {
            ListNode *tmp = pre->next;
            pre->next = cur->next;
            cur->next = cur->next->next;
            pre->next->next = tmp;
        }
        return dummy->next;
    }
};

// 93. Restore IP Addresses
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        if (s.empty()) {
            return vector<string>();
        }
        vector<string> res;
        for (int a = 1; a <= 3; a++) {
            for (int b = 1; b <= 3; b++) {
                for (int c = 1; c <= 3; c++) {
                    for (int d = 1; d <= 3; d++) {
                        if (a + b + c + d == s.length()) {
                            int A = stoi(s.substr(0, a));
                            int B = stoi(s.substr(a, b));
                            int C = stoi(s.substr(a + b, c));
                            int D = stoi(s.substr(a + b + c, d));
                            if (A <= 255 && B <= 255 && C <= 255 && D <= 255) {
                                string r = to_string(A) + "." + to_string(B) + "." +
                                    to_string(C) + "." + to_string(D);
                                if (r.length() == s.length() + 3) {
                                    res.push_back(r);
                                }
                            }
                        }
                    }
                }
            }
        }
        return res;
    }
};

// 94. Binary Tree Inorder Traversal
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        traversal(res, root);
        return res;
    }
    void traversal(vector<int>& res, TreeNode* root) {
        if (!root) {
            return;
        }
        traversal(res, root->left);
        res.push_back(root->val);
        traversal(res, root->right);
    }
};

// 95. Unique Binary Search Trees II
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
    vector<TreeNode*> generateTrees(int n) {
        return recursion(1, n);
    }
    vector<TreeNode*> recursion(int start, int end) {
        if (start > end) {
            return vector<TreeNode*>(1, nullptr);
        }
        vector<TreeNode*> res;
        for (int i = start; i <= end; i++) {
            vector<TreeNode*> left = recursion(start, i - 1);
            vector<TreeNode*> right = recursion(i + 1, end);
            for (int j = 0; j < left.size(); j++) {
                for (int k = 0; k < right.size(); k++) {
                    res.push_back(new TreeNode(i, left[j], right[k]));
                }
            }
        }
        return res;
    }
};

// 96. Unique Binary Search Trees
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1, dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }
        return dp[n];
    }
};

// 97. Interleaving String
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.length() + s2.length() != s3.length()) {
            return false;
        }
        vector<vector<bool>> dp(s1.length() + 1);
        for (int i = 0; i <= s1.length(); i++) {
            dp[i] = vector<bool>(s2.length() + 1, false);
        }
        dp[0][0] = true;
        for (int i = 0; i <= s1.length(); i++) {
            for (int j = 0; j <= s2.length(); j++) {
                if ((i < s1.size()) && (s3[i + j] == s1[i])) {
                    dp[i + 1][j] = dp[i][j] || dp[i + 1][j];
                }
                if ((j < s2.size()) && (s3[i + j] == s2[j])) {
                    dp[i][j + 1] = dp[i][j] || dp[i][j + 1];
                }
            }
        }
        return dp[s1.length()][s2.length()];
    }
};

// 98. Validate Binary Search Tree
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
    bool isValidBST(TreeNode* root) {
        return validate(root, nullptr, nullptr);
    }
    bool validate(TreeNode* n, TreeNode* min, TreeNode* max) {
        if (!n) {
            return true;
        }
        if (min && min->val >= n->val) {
            return false;
        }
        if (max && max->val <= n->val) {
            return false;
        }
        return validate(n->left, min, n) && validate(n->right, n, max);
    }
};

// 99. Recover Binary Search Tree
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
    void recoverTree(TreeNode* root) {
        TreeNode *prev = nullptr, *first = nullptr, *next = nullptr;
        recover(root, prev, first, next);
        swap(first->val, next->val);
    }
    void recover(TreeNode* root, TreeNode* &prev, TreeNode* &first, TreeNode* &next) {
        if (!root) {
            return;
        }
        recover(root->left, prev, first, next);
        if (prev && root->val < prev->val) {
            if (!first) {
                first = prev;
            }
            next = root;
        }
        prev = root;
        recover(root->right, prev, first, next);
    }
};

// 100. Same Tree
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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) {
            return true;
        }
        if ((!p && q) || (p && !q) || (p->val != q->val)) {
            return false;
        }
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

// 101. Symmetric Tree
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
    bool isSymmetric(TreeNode* root) {
        return isSym(root->left, root->right);
    }
    bool isSym(TreeNode* left, TreeNode* right) {
        if (!left && !right) {
            return true;
        }
        if ((!left || !right) || left->val != right->val) {
            return false;
        }
        return isSym(left->right, right->left) && isSym(left->left, right->right);
    }
};

// 102. Binary Tree Level Order Traversal
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        traversal(res, root, 1);
        return res;
    }
    void traversal(vector<vector<int>>& res, TreeNode* root, int level) {
        if (!root) {
            return;
        }
        if (res.size() < level) {
            res.push_back(vector<int>());
        }
        res[level - 1].push_back(root->val);
        traversal(res, root->left, level + 1);
        traversal(res, root->right, level + 1);
    }
};

// 103. Binary Tree Zigzag Level Order Traversal
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> list, res;
        traversal(list, root, 1);
        for (int i = 0; i < list.size(); i++) {
            res.push_back(vector<int>());
            vector<int> tmp = list[i];
            if (i % 2 == 0) {
                for (int j = 0; j < tmp.size(); j++) {
                    res[i].push_back(tmp[j]);
                }
            } else {
                for (int j = tmp.size() - 1; j >= 0; j--) {
                    res[i].push_back(tmp[j]);
                }
            }
        }
        return res;
    }
    void traversal(vector<vector<int>>& list, TreeNode* root, int level) {
        if (!root) {
            return;
        }
        if (list.size() < level) {
            list.push_back(vector<int>());
        }
        list[level - 1].push_back(root->val);
        traversal(list, root->left, level + 1);
        traversal(list, root->right, level + 1);
    }
};

// 104. Maximum Depth of Binary Tree
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
    int maxDepth(TreeNode* root) {
        return root ? max(maxDepth(root->left) + 1, maxDepth(root->right) + 1) : 0;
    }
};

// 105. Construct Binary Tree from Preorder and Inorder Traversal
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder, inorder, 0, 0, inorder.size() - 1);
    }
    TreeNode* build(vector<int>& pre, vector<int>& in, int pre_start, int in_start, int in_end) {
        if (pre_start > pre.size() - 1 || in_start > in_end) {
            return nullptr;
        }
        TreeNode* r = new TreeNode(pre[pre_start]);
        int index = 0;
        for (int i = in_start; i <= in_end; i++) {
            if (r->val == in[i]) {
                index = i;
                break;
            }
        }
        r->left = build(pre, in, pre_start + 1, in_start, index - 1);
        r->right = build(pre, in, pre_start + index - in_start + 1, index + 1, in_end);
        return r;
    }
};

// 106. Construct Binary Tree from Inorder and Postorder Traversal
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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return build(inorder, postorder, 0, inorder.size() - 1, 0, inorder.size() - 1);
    }
    TreeNode* build(vector<int>& in, vector<int>& post, int in_start, int in_end, int post_start, int post_end) {
        if (in_start > in_end) {
            return nullptr;
        }
        TreeNode* t = new TreeNode(post[post_end]);
        int idx = 0;
        for (int i = in_start; i <= in_end; i++) {
            if (in[i] == post[post_end]) {
                idx = i;
                break;
            }
        }
        int left_size = idx - in_start;
        t->left = build(in, post, in_start, idx - 1, post_start, post_start + left_size -1);
        t->right = build(in, post, idx + 1, in_end, post_start + left_size, post_end - 1);
        return t;
    }
};

// 107. Binary Tree Level Order Traversal II
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        int h = 0;
        height(root, h, 0);
        while (h != 0 && res.size() < h) {
            res.push_back(vector<int>());
        }
        traverse(res, root, h);
        return res;
    }
    void height(TreeNode* r, int& h, int current) {
        if (r == nullptr) {
            return;
        }
        h = (++current > h) ? current : h;
        height(r->left, h, current);
        height(r->right, h, current);
    }
    void traverse(vector<vector<int>>& res, TreeNode* r, int h) {
        if (r == nullptr) {
            return;
        }
        h--;
        traverse(res, r->left, h);
        traverse(res, r->right, h);
        res[h].push_back(r->val);
    }
};

// 108. Convert Sorted Array to Binary Search Tree
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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return build(nums, 0, nums.size() - 1);
    }
    TreeNode* build(vector<int>& nums, int left, int right) {
        if (left > right) {
            return nullptr;
        }
        int m = (left + right) / 2;
        TreeNode* t = new TreeNode(nums[m]);
        t->left = build(nums, left, m - 1);
        t->right = build(nums, m + 1, right);
        return t;
    }
};

// 109. Convert Sorted List to Binary Search Tree
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
    TreeNode* sortedListToBST(ListNode* head) {
        vector<int> list;
        while (head) {
            list.push_back(head->val);
            head = head->next;
        }
        return build(list, 0, list.size() - 1);
    }
    TreeNode* build(vector<int>& list, int left, int right) {
        if (left > right) {
            return nullptr;
        }
        int m = (left + right) / 2;
        TreeNode* t = new TreeNode(list[m]);
        t->left = build(list, left, m - 1);
        t->right = build(list, m + 1, right);
        return t;
    }
};

// 110. Balanced Binary Tree
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
    bool isBalanced(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        if (!isBalanced(root->left) || !isBalanced(root->right)) {
            return false;
        }
        return abs(height(root->left) - height(root->right)) <= 1;
    }
    int height(TreeNode* r) {
        return (r == nullptr) ? 0 : max(height(r->left), height(r->right)) + 1;
    }
};

// 111. Minimum Depth of Binary Tree
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
    int minDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        if (root->left != nullptr && root->right != nullptr) {
            return 1 + min(minDepth(root->left), minDepth(root->right));
        }
        return 1 + max(minDepth(root->left), minDepth(root->right));
    }
};

// 112. Path Sum
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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            return false;
        } else if (root->left == nullptr && root->right == nullptr) {
            return root->val == targetSum;
        }
        return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
    }
};

// 113. Path Sum II
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
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> res;
        traverse(res, vector<int>(), root, targetSum);
        return res;
    }
    void traverse(vector<vector<int>>& res, vector<int> tmp, TreeNode* r, int sum) {
        if (r == nullptr) {
            return;
        }
        tmp.push_back(r->val);
        if (r->left == nullptr && r->right == nullptr) {
            if (r->val == sum) {
                res.push_back(tmp);
            }
            return;
        }
        traverse(res, tmp, r->left, sum - r->val);
        traverse(res, tmp, r->right, sum - r->val);
    }
};

// 114. Flatten Binary Tree to Linked List
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
    void flatten(TreeNode* root) {
        while (root) {
            if (root->left) {
                flatten(root->left);
                TreeNode* right = root->right;
                root->right = root->left;
                root->left = nullptr;
                while (root->right) {
                    root = root->right;
                }
                root->right = right;
            }
            root = root->right;
        }
    }
};

class Solution {
public:
    void flatten(TreeNode* root) {
        while (root) {
            if (root->left) {
                TreeNode* pre = root->left;
                while (pre->right) {
                    pre = pre->right;
                }
                pre->right = root->right;
                root->right = root->left;
                root->left = nullptr;
            }
            root = root->right;
        }
    }
};

// 115. Distinct Subsequences
class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<vector<unsigned int>> dp(n + 1, vector<unsigned int>(m + 1));
        for (int j = 0; j <= m; j++) {
            dp[0][j] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (t[i - 1] == s[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1];
                } else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
        return dp[n][m];
    }
};

// 116. Populating Next Right Pointers in Each Node
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/
class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) {
            return root;
        }
        if (root->left) {
            root->left->next = root->right;
            if (root->next) {
                root->right->next = root->next->left;
            }
            connect(root->left);
            connect(root->right);
        }
        return root;
    }
};

// 117. Populating Next Right Pointers in Each Node II
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/
class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) {
            return root;
        }
        Node* c = root, *dummy = new Node(0, nullptr, nullptr, nullptr);
        for (Node* p = dummy; c != nullptr; c = c->next) {
            if (c->left) {
                p->next = c->left;
                p = p->next;
            }
            if (c->right) {
                p->next = c->right;
                p = p->next;
            }
        }
        connect(dummy->next);
        dummy->next = nullptr;
        delete dummy;
        return root;
    }
};

// 118. Pascal's Triangle
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if (numRows == 1) {
            return vector<vector<int>>{{1}};
        } else if (numRows == 2) {
            return vector<vector<int>>{{1}, {1, 1}};
        }
        vector<vector<int>> res = {{1}, {1, 1}};
        while (res.size() < numRows) {
            int row_size = res.size() + 1, prev = res.size() - 1;
            vector<int> tmp(row_size, 1);
            for (int i = 1; i < row_size - 1; i++) {
                tmp[i] = res[prev][i - 1] + res[prev][i];
            }
            res.push_back(tmp);
        }
        return res;
    }
};

// 119. Pascal's Triangle II
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if (rowIndex == 0) {
            return vector<int>{1};
        } else if (rowIndex == 1) {
            return vector<int>{1, 1};
        }
        vector<int> prev = {1, 1};
        while (prev.size() <= rowIndex) {
            vector<int> next(prev.size() + 1, 1);
            for (int i = 1; i < prev.size(); i++) {
                next[i] = prev[i - 1] + prev[i];
            }
            prev = next;
        }
        return prev;
    }
};

// 120. Triangle
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if (triangle.size() == 1) {
            return triangle[0][0];
        }
        for (int i = triangle.size() - 2; i >= 0; i--) {
            for (int j = 0; j < triangle[i].size(); j++) {
                triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
            }
        }
        return triangle[0][0];
    }
};

// 121. Best Time to Buy and Sell Stock
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0, p = 0;
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] - prices[p] > res) {
                res = prices[i] - prices[p];
            } else {
                p = prices[p] < prices[i] ? p : i;
            }
        }
        return res;
    }
};

// 122. Best Time to Buy and Sell Stock II
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy = 0, sell = 0, res = 0, n = prices.size();
        while (buy < n && sell < n) {
            while (buy + 1 < n && prices[buy] > prices[buy + 1]) {
                buy++;
            }
            sell = buy;
            while (sell + 1 < n && prices[sell] < prices[sell + 1]) {
                sell++;
            }
            res += prices[sell] - prices[buy];
            buy = sell + 1;
        }
        return res;
    }
};

// 123. Best Time to Buy and Sell Stock III
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy1 = INT_MIN, buy2 = INT_MIN, sell1 = 0, sell2 = 0;
        for (int i = 0; i < prices.size(); i++) {
            buy1 = max(buy1, -prices[i]);
            sell1 = max(sell1, buy1 + prices[i]);
            buy2 = max(buy2, sell1 - prices[i]);
            sell2 = max(sell2, buy2 + prices[i]);
        }
        return sell2;
    }
};

// 124. Binary Tree Maximum Path Sum
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
    int maxPathSum(TreeNode* root) {
        int m = INT_MIN;
        traverse(root, m);
        return m;
    }
    int traverse(TreeNode* root, int& m) {
        if (root == nullptr) {
            return 0;
        }
        int l = traverse(root->left, m);
        int r = traverse(root->right, m);
        int t = max(root->val, max(max(root->val + l, root->val + r), root->val + l + r));
        m = (m < t) ? t : m;
        return max(root->val, max(root->val + l, root->val + r));
    }
};

// 125. Valid Palindrome
class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while (left <= right) {
            while (!isTarget(s[left]) && left < right) {
                left++;
            }
            while (!isTarget(s[right]) && left < right) {
                right--;
            }
            if (toLower(s[left]) != toLower(s[right])) {
                return false;
            }
            left++, right--;
        }
        return true;
    }
    bool isTarget(char c) {
        return (('A' <= c && c <= 'Z') ||
                ('a' <= c && c <= 'z') ||
                ('0' <= c && c <= '9')) ? true : false;
    }
    char toLower(char c) {
        return ('A' <= c && c <= 'Z') ? c + 32 : c;
    }
};

// 128. Longest Consecutive Sequence
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        int res;
        for (int i = 0; i < nums.size(); i++) {
            if (s.count(nums[i] - 1)) {
                continue;
            }
            int tmp = nums[i] + 1;
            while (s.count(tmp)) {
                tmp++;
            }
            res = max(res, tmp - nums[i]);
        }
        return res;
    }
};

// 129. Sum Root to Leaf Numbers
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
    int sumNumbers(TreeNode* root) {
        return traverse(root, 0);
    }
    int traverse(TreeNode* r, int prev) {
        if (r == nullptr) {
            return 0;
        }
        int next = (10 * prev) + r->val;
        if (r->left == nullptr && r->right == nullptr) {
            return next;
        }
        return traverse(r->left, next) + traverse(r->right, next);
    }
};

// 130. Surrounded Regions
class Solution {
public:
    void dfs(vector<vector<char>>& b, int i, int j, int m, int n) {
        if (i >= m || i < 0 || j >= n || j < 0) {
            return;
        }
        if (b[i][j] == 'O') {
            b[i][j] = 'V';
            dfs(b, i + 1, j, m, n);
            dfs(b, i - 1, j, m, n);
            dfs(b, i, j + 1, m, n);
            dfs(b, i, j - 1, m, n);
        }
    }
    void solve(vector<vector<char>>& board) {
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O' &&
                   (i == 0 || j == 0 || i == m - 1 || j == n - 1)) {
                    dfs(board, i, j, m, n);
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                } else if (board[i][j] == 'V') {
                    board[i][j] = 'O';
                }
            }
        }
    }
};

// 131. Palindrome Partitioning
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> tmp;
        partition(s, 0, tmp, res);
        return res;
    }
    void partition(string& s, int start, vector<string>&tmp, vector<vector<string>>& res) {
        int n = s.length();
        if (start == n) {
            res.push_back(tmp);
        } else {
            for (int i = start; i < n; i++) {
                if (isPalindrome(s, start, i)) {
                    tmp.push_back(s.substr(start, i - start + 1));
                    partition(s, i + 1, tmp, res);
                    tmp.pop_back();
                }
            }
        }
    }
    bool isPalindrome(string& s, int l, int r) {
        while (l < r) {
            if (s[l++] != s[r--]) {
                return false;
            }
        }
        return true;
    }
};

// 132. Palindrome Partitioning II
class Solution {
public:
    int minCut(string s) {
        vector<int> dp(s.length(), INT_MAX);
        for (int i = 0; i < s.length(); i++) {
            dp[i] = isPalindrome(s, 0, i) ? 0 : dp[i - 1] + 1;
            for (int j = i; j > 0; j--) {
                if (dp[i] == 1) {
                    break;
                }
                dp[i] = isPalindrome(s, j, i) ? min(dp[i], dp[j - 1] + 1) : dp[i];
            }
        }
        return dp[s.length() - 1];
    }
    bool isPalindrome(string& s, int l, int r) {
        while (l < r) {
            if (s[l++] != s[r--]) {
                return false;
            }
        }
        return true;
    }
};

// 133. Clone Graph
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }

    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/
class Solution {
public:
    unordered_map<Node*, Node*> c;
    Node* cloneGraph(Node* node) {
        if (node == nullptr) {
            return node;
        }
        if (c.find(node) == c.end()) {
            c[node] = new Node(node->val, {});
            for (Node* n : node->neighbors) {
                c[node]->neighbors.push_back(cloneGraph(n));
            }
        }
        return c[node];
    }
};

// 134. Gas Station
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int sum(0), total(0), res(0);
        for (int i = 0; i < gas.size(); i++) {
            sum += gas[i] - cost[i], total += gas[i] - cost[i];
            if (sum < 0) {
                res = i + 1;
                sum = 0;
            }
        }
        return total >= 0 ? res : -1;
    }
};

// 135. Candy
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> left(n, 1), right(n, 1);
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                left[i] = left[i - 1] + 1;
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                right[i] = right[i + 1] + 1;
            }
        }
        int res = 0;
        for (int i = 0; i < n; i++) {
            res += max(left[i], right[i]);
        }
        return res;
    }
};

// 136. Single Number
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            res ^= nums[i];
        }
        return res;
    }
};

// 137. Single Number II
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int n = nums.size();
        long res(0);
        int p(0), t(0);
        for (int i = 0; i < 32; i++) {
            t = 0;
            for (int j = 0; j < n; j++) {
                t += nums[j] & 1;
                nums[j] >>= 1;
            }
            t %= 3;
            res = res + (t * pow(2, p));
            p++;
        }
        return res;
    }
};

// 138. Copy List with Random Pointer
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        map<Node*, Node*> m;
        Node* p = head;
        while (p) {
            m[p] = new Node(p->val);
            p = p->next;
        }
        p = head;
        while (p) {
            m[p]->next = m[p->next];
            m[p]->random = m[p->random];
            p = p->next;
        }
        return m[head];
    }
};
