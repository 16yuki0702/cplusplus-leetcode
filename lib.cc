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

// 139. Word Break
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> v(s.length() + 1, false);
        v[0] = true;
        for (int i = 0; i < v.size(); i++) {
            if (!v[i]) {
                continue;
            }
            for (int j = 0; j < wordDict.size(); j++) {
                string t = wordDict[j];
                string sub = s.substr(i, t.length());
                if (!t.compare(sub)) {
                    v[i + t.length()] = true;
                }
            }
        }
        return v[s.length()];
    }
};

// 140. Word Break II
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> set;
        vector<string> res;
        set.insert(wordDict.begin(), wordDict.end());
        dfs(s, "", set, res);
        return res;
    }

    void dfs(string s, string sentence, unordered_set<string>& set, vector<string>& res) {
        if (s.empty()) {
            sentence.pop_back();
            res.push_back(sentence);
            return;
        }
        for (int i = 1; i <= s.size(); i++) {
            if (!set.count(s.substr(0, i))) {
                continue;
            }
            dfs(s.substr(i), sentence + s.substr(0, i) + " ", set, res);
        }
    }
};

// 141. Linked List Cycle
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
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next && fast->next->next) {
            slow = slow->next, fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }
        return false;
    }
};

// 142. Linked List Cycle II
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
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next, fast = fast->next->next;
            if (slow == fast) {
                slow = head;
                while (!(slow == fast)) {
                    slow = slow->next, fast = fast->next;
                }
                return slow;
            }
        }
        return nullptr;
    }
};

// 143. Reorder List
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
    void reorderList(ListNode* head) {
        vector<ListNode*> l;
        while (head) {
            l.push_back(head);
            head = head->next;
        }
        int left = 0, right = l.size() - 1;
        while (left < right) {
            l[left++]->next = l[right];
            if (left == right) {
                break;
            }
            l[right--]->next = l[left];
        }
        l[right]->next = nullptr;
    }
};

// 144. Binary Tree Preorder Traversal
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        traverse(res, root);
        return res;
    }
    void traverse(vector<int>& res, TreeNode* r) {
        if (r == nullptr) {
            return;
        }
        res.push_back(r->val);
        traverse(res, r->left);
        traverse(res, r->right);
    }
};

// 145. Binary Tree Postorder Traversal
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        traverse(res, root);
        return res;
    }
    void traverse(vector<int>& res, TreeNode* r) {
        if (r == nullptr) {
            return;
        }
        traverse(res, r->left);
        traverse(res, r->right);
        res.push_back(r->val);
    }
};

// 146. LRU Cache
class DoubleLinkedList {
private:
    int val;
    int key;
    DoubleLinkedList* next;
    DoubleLinkedList* prev;
public:
    DoubleLinkedList(int k, int v) {
        key = k;
        val = v;
        next = nullptr;
        prev = nullptr;
    }
    void setVal(int v) {
        val = v;
    }
    int getVal() {
        return val;
    }
    void setKey(int k) {
        key = k;
    }
    int getKey() {
        return key;
    }
    void setNext(DoubleLinkedList* n) {
        next = n;
    }
    DoubleLinkedList* getNext() {
        return next;
    }
    void setPrev(DoubleLinkedList* p) {
        prev = p;
    }
    DoubleLinkedList* getPrev() {
        return prev;
    }
};

class LRUCache {
private:
    int cap;
    int count;
    map<int, DoubleLinkedList*> m;
    DoubleLinkedList *head;
    DoubleLinkedList *tail;

    void reorder(int k) {
        DoubleLinkedList *tmp = m[k];
        if (tmp == tail) {
            if (tmp == head) {
                return;
            }
            // repoint tail
            tmp->getPrev()->setNext(nullptr);
            tail = tmp->getPrev();

            // repoint head
            tmp->setNext(head);
            head->setPrev(tmp);
            head = tmp;
            return;
        }

        // neither head nor tail
        if (tmp != head) {
            tmp->getPrev()->setNext(tmp->getNext());
            tmp->getNext()->setPrev(tmp->getPrev());

            // put the accessed data to head
            tmp->setNext(head);
            head->setPrev(tmp);
            head = tmp;
        }
    }
public:
    LRUCache(int capacity) {
        cap = capacity;
        head = nullptr;
        tail = nullptr;
        m = {};
        count = 0;
    }
    int get(int k) {
        if (!m[k]) {
            return -1;
        }
        reorder(k);
        return m[k]->getVal();
    }
    void put(int k, int v) {
        // update cached data
        if (m[k]) {
            m[k]->setVal(v);
            reorder(k);
            return;
        }

        // cache new data
        m[k] = new DoubleLinkedList(k, v);
        count++;

        // set first element
        if (head == nullptr) {
            head = tail = m[k];
            return;
        }

        // put new data to head
        DoubleLinkedList *newHead = m[k];
        newHead->setNext(head);
        head->setPrev(newHead);
        head = newHead;

        // delete least accessed data
        if (count > cap) {
            DoubleLinkedList *tmp = tail;

            // set new tail
            tail = tail->getPrev();
            tail->setNext(nullptr);

            m.erase(tmp->getKey());
            delete tmp;
            count = cap;
        }
    }
};
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// 147. Insertion Sort List
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
    ListNode* insertionSortList(ListNode* head) {
        ListNode *dummy = new ListNode(0, head);
        ListNode *pre = dummy, *cur = head;
        while (cur) {
            if (cur->next && cur->next->val < cur->val) {
                while ((pre->next) && (pre->next->val < cur->next->val)) {
                    pre = pre->next;
                }
                ListNode *tmp = pre->next;
                pre->next = cur->next;
                cur->next = cur->next->next;
                pre->next->next = tmp;
                pre = dummy;
            } else {
                cur = cur->next;
            }
        }
        return dummy->next;
    }
};

// 148. Sort List
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
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode *mid = nullptr, *slow = head, *fast = head;
        while (fast && fast->next) {
            mid = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        mid->next = nullptr;
        ListNode* l1 = sortList(head);
        ListNode* l2 = sortList(slow);
        return merge(l1, l2);
    }
    ListNode* merge(ListNode* l1, ListNode *l2) {
        ListNode *dummy = new ListNode(0, nullptr);
        ListNode *c = dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                c->next = l1;
                l1 = l1->next;
            } else {
                c->next = l2;
                l2 = l2->next;
            }
            c = c->next;
        }
        if (l1) {
            c->next = l1;
        }
        if (l2) {
            c->next = l2;
        }
        return dummy->next;
    }
};

// 150. Evaluate Reverse Polish Notation
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        vector<string> stack;
        for (string s : tokens) {
            if (s == "+" || s == "-" || s == "*" || s == "/") {
                int b = stoi(stack.back());
                stack.pop_back();
                int a = stoi(stack.back());
                stack.pop_back();
                if (s == "+") {
                    stack.push_back(to_string(a + b));
                } else if (s == "-") {
                    stack.push_back(to_string(a - b));
                } else if (s == "*") {
                    stack.push_back(to_string(a * b));
                } else if (s == "/") {
                    stack.push_back(to_string(a / b));
                }
            } else {
                stack.push_back(s);
            }
        }
        return stoi(stack.back());
    }
};

// 151. Reverse Words in a String
class Solution {
public:
    string reverseWords(string s) {
        string res, tmp;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s.at(i) == ' ') {
                if (tmp != "") {
                    res = (res == "") ? tmp : res + ' ' + tmp;
                    tmp = "";
                }
                continue;
            }
            tmp = s.at(i) + tmp;
        }
        if (tmp != "") {
            res = (res == "") ? tmp : res + ' ' + tmp;
        }
        return res;
    }
};

// 152. Maximum Product Subarray
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int res = nums[0], l = 0, r = 0, n = nums.size() - 1;
        for (int i = 0; i <= n; i++) {
            l = (l ? l : 1) * nums[i];
            r = (r ? r : 1) * nums[n - i];
            res = max(res, max(l, r));
        }
        return res;
    }
};

// 153. Find Minimum in Rotated Sorted Array
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            if (nums[left] < nums[right]) {
                return nums[left];
            }
            int mid = (left + right) / 2;
            if (nums[left] <= nums[mid]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return nums[left];
    }
};

// 154. Find Minimum in Rotated Sorted Array II
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int m = l + (r - l) / 2;
            if (nums[m] > nums[r]) {
                l = m + 1;
            } else if (nums[m] < nums[r]) {
                r = m;
            } else {
                r--;
            }
        }
        return nums[l];
    }
};

// 155. Min Stack
class MinStack {
private:
    vector<pair<int, int>> s;
public:
    MinStack() {
        s = {};
    }

    void push(int val) {
        s.push_back(
            {
                val,
                s.empty() ? val : min(s.back().second, val)
            }
        );
    }

    void pop() {
        s.pop_back();
    }

    int top() {
        return s.back().first;
    }

    int getMin() {
        return s.back().second;
    }
};
/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

// 160. Intersection of Two Linked Lists
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *t1 = headA, *t2 = headB;
        while (t1 != t2) {
            t1 = t1 ? t1->next : headB;
            t2 = t2 ? t2->next : headA;
        }
        return t1;
    }
};

// 162. Find Peak Element
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int m = (left + right) / 2, mr = m + 1;
            if (nums[m] < nums[mr]) {
                left = mr;
            } else {
                right = m;
            }
        }
        return left;
    }
};

// 164. Maximum Gap
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        qSort(nums, 0, nums.size() - 1);
        int res = 0;
        for (int i = 1; i < nums.size(); i++) {
            res = max(res, nums[i] - nums[i - 1]);
        }
        return res;
    }
    void qSort(vector<int>& nums, int left, int right) {
        if (left >= right) {
            return;
        }
        int p = left;
        swap(nums[(left + right) / 2], nums[right]);
        for (int i = left; i < right; i++) {
            if (nums[i] < nums[right]) {
                swap(nums[p++], nums[i]);
            }
        }
        swap(nums[p], nums[right]);
        qSort(nums, left, p - 1);
        qSort(nums, p + 1, right);
    }
};

// 165. Compare Version Numbers
class Solution {
public:
    int compareVersion(string version1, string version2) {
        int i = 0, j = 0;
        int t1 = 0, t2 = 0;
        while (i < version1.size() || j < version2.size()) {
            while (i < version1.size() && version1.at(i) != '.') {
                t1 = (t1 * 10) + (version1.at(i) - '0');
                i++;
            }
            while (j < version2.size() && version2.at(j) != '.') {
                t2 = (t2 * 10) + (version2.at(j) - '0');
                j++;
            }
            if (t1 < t2) {
                return -1;
            } else if (t1 > t2) {
                return 1;
            }
            i++, j++;
            t1 = 0, t2 = 0;
        }
        return 0;
    }
};

// 167. Two Sum II - Input Array Is Sorted
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0, r = numbers.size() - 1;
        while (l < r) {
            if (numbers[l] + numbers[r] == target) {
                return {l + 1, r + 1};
            } else if (numbers[l] + numbers[r] > target) {
                r--;
            } else {
                l++;
            }
        }
        return {};
    }
};

// 168. Excel Sheet Column Title
class Solution {
public:
    string convertToTitle(int columnNumber) {
        string res = "";
        while (columnNumber) {
            res = (char)(((columnNumber - 1) % 26) + 'A') + res;
            columnNumber = (columnNumber - 1) / 26;
        }
        return res;
    }
};

// 169. Majority Element
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count = 0, m = nums[0];
        for (int i = 0; i < nums.size(); i++) {
            if (!count) {
                m = nums[i];
            }
            count += (m == nums[i]) ? 1 : -1;
        }
        return m;
    }
};

// 171. Excel Sheet Column Number
class Solution {
public:
    int titleToNumber(string columnTitle) {
        unsigned int res = 0, digit = 1;
        for (int i = columnTitle.size() - 1; i >= 0; i--, digit *= 26) {
            res += ((int)(columnTitle.at(i) - 'A') + 1) * digit;
         }
        return res;
    }
};

// 172. Factorial Trailing Zeroes
class Solution {
public:
    int trailingZeroes(int n) {
        unsigned int res = 0, d = 5;
        while (n) {
            res += n / 5;
            d *= 5, n /= 5;
        }
        return res;
    }
};

// 174. Dungeon Game
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[m][n - 1] = 1;
        dp[m - 1][n] = 1;
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int hp = min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j];
                dp[i][j] = (hp <= 0 ? 1 : hp);
            }
        }
        return dp[0][0];
    }
};

// 179. Largest Number
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int a, int b){
            return to_string(a) + to_string(b) > to_string(b) + to_string(a);
        });
        string res;
        for (int i = 0; i < nums.size(); i++) {
            res += to_string(nums[i]);
        }
        return res.at(0) == '0' ? "0" : res;
    }
};

// 187. Repeated DNA Sequences
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<string, int> m;
        vector<string> res;
        if (s.size() < 10) {
            return res;
        }
        for (int i = 0; i < s.size() - 9; i++) {
            m[s.substr(i, 10)]++;
        }
        for (pair v : m) {
            if (v.second > 1) {
                res.push_back(v.first);
            }
        }
        return res;
    }
};

// 189. Rotate Array
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        vector<int> res(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++) {
            res[(i + k) % nums.size()] = nums[i];
        }
        nums = res;
    }
};

// 190. Reverse Bits
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for (int i = 0; i < 31; i++, res <<= 1, n >>= 1) {
            res |= (n & 1);
        }
        return res |= (n & 1);
    }
};

// 191. Number of 1 Bits
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        for (int i = 0; i < 32; i++, n >>= 1) {
            res += (n & 1) ? 1 : 0;
        }
        return res;
    }
};

// 198. House Robber
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size(), pre = 0, cur = 0;
        for (int i = 0; i < n; i++) {
            int t = max(pre + nums[i], cur);
            pre = cur;
            cur = t;
        }
        return cur;
    }
};

// 199. Binary Tree Right Side View
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        collect(res, root, 1);
        return res;
    }
    void collect(vector<int> &res, TreeNode *root, int level) {
        if (!root) {
            return;
        }
        if (res.size() < level) {
            res.push_back(root->val);
        }
        collect(res, root->right, level + 1);
        collect(res, root->left, level + 1);
    }
};

// 200. Number of Islands
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1') {
                    res++;
                    check(grid, i, j);
                }
            }
        }
        return res;
    }
    void check(vector<vector<char>>& g, int i, int j) {
        if (i < 0 || i >= g.size() || j < 0 || j >= g[0].size() || g[i][j] == '0') {
            return;
        }
        g[i][j] = '0';
        check(g, i - 1, j);
        check(g, i + 1, j);
        check(g, i, j - 1);
        check(g, i, j + 1);
    }
};

// 201. Bitwise AND of Numbers Range
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int count = 0;
        while (left != right) {
            left >>= 1, right >>= 1, count++;
        }
        return left << count;
    }
};

// 202. Happy Number
class Solution {
public:
    int next(int n) {
        int res = 0;
        while (n >= 10) {
            int t = n % 10;
            res += t * t;
            n /= 10;
        }
        return res + (n * n);
    }
    bool isHappy(int n) {
        int slow = next(n), fast = next(next(n));
        while (slow != fast) {
            slow = next(slow);
            fast = next(next(fast));
        }
        return fast == 1;
    }
};

// 203. Remove Linked List Elements
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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode *fake = new ListNode(-1, head);
        ListNode *cur = fake, *prev = fake;
        while (cur) {
            if (cur->val == val) {
                prev->next = cur->next;
                cur = cur->next;
                continue;
            }
            prev = cur;
            cur = cur->next;
        }
        return fake->next;
    }
};

// 204. Count Primes
class Solution {
public:
    int countPrimes(int n) {
        vector<bool> m(n, true);
        int res = 0;
        for (int i = 2; i < n; i++) {
            if (!m[i]) {
                continue;
            }
            res++;
            if (i > sqrt(n)) {
                continue;
            }
            for (int j = i * i; j < n; j += i) {
                m[j] = false;
            }
        }
        return res;
    }
};

// 205. Isomorphic Strings
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        return normalize(s) == normalize(t);
    }
    string normalize(string s) {
        unordered_map<char, char> m;
        string res = "";
        char mapc = 'a';
        for (int i = 0; i < s.size(); i++) {
            if (!m[s.at(i)]) {
                m[s.at(i)] = mapc++;
            }
            res += m[s.at(i)];
        }
        return res;
    }
};

// 206. Reverse Linked List
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
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        ListNode *h = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return h;
    }
};

// 207. Course Schedule
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> g = buildGraph(numCourses, prerequisites);
        vector<int> degrees = computeIndegrees(g);
        for (int i = 0; i < numCourses; i++) {
            int j = 0;
            for (; j < numCourses; j++) {
                if (!degrees[j]) {
                    break;
                }
            }
            if (j == numCourses) {
                return false;
            }
            degrees[j]--;
            for (int v : g[j]) {
                degrees[v]--;
            }
        }
        return true;
    }

    vector<vector<int>> buildGraph(int n, vector<vector<int>>& p) {
        vector<vector<int>> g(n);
        for (int i = 0; i < p.size(); i++) {
            g[p[i][1]].push_back(p[i][0]);
        }
        return g;
    }

    vector<int> computeIndegrees(vector<vector<int>>& g) {
        vector<int> degrees(g.size(), 0);
        for (vector<int> adj : g) {
            for (int v : adj) {
                degrees[v]++;
            }
        }
        return degrees;
    }
};

// 208. Implement Trie (Prefix Tree)
class TrieNode {
public:
    bool isWord;
    TrieNode *children[26];
    TrieNode() {
        isWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        int c = 0;
        TrieNode *cur = root;
        for (int i = 0; i < word.size(); i++) {
            c = word[i] - 'a';
            if (cur->children[c] == nullptr) {
                cur->children[c] = new TrieNode();
            }
            cur = cur->children[c];
        }
        cur->isWord = true;
    }

    bool search(string word) {
        int c = 0;
        TrieNode *cur = root;
        for (int i = 0; i < word.size(); i++) {
            c = word[i] - 'a';
            cur = cur->children[c];
            if (cur == nullptr) {
                return false;
            }
        }
        return cur->isWord;
    }

    bool startsWith(string prefix) {
        int c = 0;
        TrieNode *cur = root;
        for (int i = 0; i < prefix.size(); i++) {
            c = prefix[i] - 'a';
            cur = cur->children[c];
            if (cur == nullptr) {
                return false;
            }
        }
        return true;
    }
};
/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

// 209. Minimum Size Subarray Sum
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int l = 0, r = 0, sum = 0, res = INT_MAX;
        while (r < nums.size()) {
            sum += nums[r++];
            while (sum >= target) {
                res = min(res, r - l);
                sum -= nums[l++];
            }
        }
        return res == INT_MAX ? 0 : res;
    }
};

// 210. Course Schedule II
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> g = buildGraph(numCourses, prerequisites);
        vector<int> d = computeIndegrees(g);
        vector<int> order;
        for (int i = 0; i < numCourses; i++) {
            int j = 0;
            for (; j < numCourses; j++) {
                if (!d[j]) {
                    order.push_back(j);
                    break;
                }
            }
            if (j == numCourses) {
                return {};
            }
            d[j]--;
            for (int v : g[j]) {
                d[v]--;
            }
        }
        return order;
    }
    vector<vector<int>> buildGraph(int n, vector<vector<int>> p) {
        vector<vector<int>> g(n);
        for (vector<int> v : p) {
            g[v[1]].push_back(v[0]);
        }
        return g;
    }
    vector<int> computeIndegrees(vector<vector<int>>& g) {
        vector<int> d(g.size(), 0);
        for (vector<int> adj : g) {
            for (int v : adj) {
                d[v]++;
            }
        }
        return d;
    }
};

// 211. Design Add and Search Words Data Structure
class TrieNode {
public:
    bool isWord;
    TrieNode *children[26];
    TrieNode() {
        isWord = false;
        memset(children, NULL, sizeof(children));
    }
};

class WordDictionary {
public:
    WordDictionary() {

    }

    void addWord(string word) {
        TrieNode *node = root;
        for (char c : word) {
            if (!node->children[c - 'a']) {
                node->children[c - 'a'] = new TrieNode();
            }
            node = node->children[c - 'a'];
        }
        node->isWord = true;
    }

    bool search(string word) {
        return search(word.c_str(), root);
    }

private:
    TrieNode *root = new TrieNode();

    bool search(const char *word, TrieNode *node) {
        for (int i = 0; word[i] && node; i++) {
            if (word[i] != '.') {
                node = node->children[word[i] - 'a'];
            } else {
                TrieNode *tmp = node;
                for (int j = 0; j < 26; j++) {
                    node = tmp->children[j];
                    if (search(word + i + 1, node)) {
                        return true;
                    }
                }
            }
        }
        return node && node->isWord;
    }
};
/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

// 212. Word Search II
class TrieNode {
public:
    bool isEnd;
    vector<TrieNode*> children;
    TrieNode() {
        isEnd = false;
        children = vector<TrieNode*> (26, nullptr);
    }
};

class Trie {
private:
    TrieNode *root;
public:
    Trie(vector<string>& words) {
        root = new TrieNode();
        for (int i = 0; i < words.size(); i++) {
            addWord(words[i]);
        }
    }
    TrieNode *getRoot() {
        return root;
    }
    void addWord(const string& word) {
        TrieNode *cur = root;
        for (int i = 0; i < word.size(); i++) {
            int c = word[i] - 'a';
            if (cur->children[c] == nullptr) {
                cur->children[c] = new TrieNode();
            }
            cur = cur->children[c];
        }
        cur->isEnd = true;
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie *t = new Trie(words);
        TrieNode *n = t->getRoot();
        set<string> resultSet;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                findWords(board, i, j, n, "", resultSet);
            }
        }
        vector<string> res;
        for (string s : resultSet) {
            res.push_back(s);
        }
        return res;
    }
    void findWords(vector<vector<char>>& b, int i, int j, TrieNode *n, string w, set<string>& res) {
        if (i < 0 || i >= b.size() || j < 0 || j >= b[0].size() || b[i][j] == ' ') {
            return;
        }
        if (n->children[b[i][j] - 'a'] != nullptr) {
            w = w + b[i][j];
            n = n->children[b[i][j] - 'a'];
            if (n->isEnd) {
                res.insert(w);
            }
            char c = b[i][j];
            b[i][j] = ' ';
            findWords(b, i + 1, j, n, w, res);
            findWords(b, i - 1, j, n, w, res);
            findWords(b, i, j + 1, n, w, res);
            findWords(b, i, j - 1, n, w, res);
            b[i][j] = c;
         }
    }
};

// 213. House Robber II
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) {
            return n ? nums[0] : 0;
        }
        return max(robber(nums, 0, n - 2), robber(nums, 1, n - 1));
    }

    int robber(vector<int>& nums, int l, int r) {
        int pre = 0, cur = 0;
        for (int i = l; i <= r; i++) {
            int temp = max(pre + nums[i], cur);
            pre = cur;
            cur = temp;
        }
        return cur;
    }
};

// 215. Kth Largest Element in an Array
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        qSort(nums, 0, nums.size() - 1);
        return nums[nums.size() - k];
    }
    void qSort(vector<int>& nums, int l, int r) {
        if (l >= r) {
            return;
        }
        int p = l;
        swap(nums[(l + r) / 2], nums[r]);
        for (int i = l; i < r; i++) {
            if (nums[i] < nums[r]) {
                swap(nums[i], nums[p++]);
            }
        }
        swap(nums[p], nums[r]);
        qSort(nums, l, p - 1);
        qSort(nums, p + 1, r);
    }
};

// 216. Combination Sum III
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        backTrack(res, {}, 0, k, 1, n);
        return res;
    }

    void backTrack(vector<vector<int>>& res, vector<int> tmp, int sum, int k, int first, int n) {
        if (tmp.size() > k) {
            return;
        } else if (sum == n && tmp.size() == k) {
            res.push_back(tmp);
            return;
        }
        for (int i = first; i <= 9; i++) {
            sum += i;
            int idx = tmp.size();
            tmp.push_back(i);
            backTrack(res, tmp, sum, k, i + 1, n);
            tmp.erase(tmp.begin() + idx);
            sum -= i;
        }
    }
};

// 217. Contains Duplicate
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int, int> m;
        for (int n: nums) {
            if (m[n]) {
                return true;
            }
            m[n]++;
        }
        return false;
    }
};

// 219. Contains Duplicate II
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); i++) {
            if (m.find(nums[i]) != m.end() && (i - m[nums[i]]) <= k) {
                return true;
            }
            m[nums[i]] = i;
        }
        return false;
    }
};

// 220. Contains Duplicate III
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int n = nums.size();
        if (n == 0 || k < 0 || t < 0) {
            return false;
        }
        unordered_map<int, int> buckets;
        for (int i = 0; i < n; ++i) {
            int bucket = nums[i] / ((long)t + 1);
            // For negative numbers, we need to decrement bucket by 1
            // to ensure floor division.
            // For example, -1/2 = 0 but -1 should be put in Bucket[-1].
            // Therefore, decrement by 1.
            if (nums[i] < 0) {
                --bucket;
            }
            if (buckets.find(bucket) != buckets.end()) {
                return true;
            } else {
                buckets[bucket] = nums[i];
                if (buckets.find(bucket - 1) != buckets.end() && (long)nums[i] - buckets[bucket - 1] <= t) {
                    return true;
                }
                if (buckets.find(bucket + 1) != buckets.end() && (long)buckets[bucket + 1] - nums[i] <= t) {
                    return true;
                }
                if (buckets.size() > k) {
                    int key_to_remove = nums[i - k] / ((long)t + 1);
                    if (nums[i - k] < 0) {
                        --key_to_remove;
                    }
                    buckets.erase(key_to_remove);
                }
            }
        }
        return false;
    }
};

// 221. Maximal Square
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), dp = 0, pre;
        vector<int> cur(n, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int t = cur[j];
                if (!i || !j || matrix[i][j] == '0') {
                    cur[j] = matrix[i][j] - '0';
                } else {
                    cur[j] = min(pre, min(cur[j], cur[j - 1])) + 1;
                }
                dp = max(cur[j], dp);
                pre = t;
            }
        }
        return dp * dp;
    }
};

// 222. Count Complete Tree Nodes
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
    int countNodes(TreeNode* root) {
        int res = 0;
        traverse(root, res);
        return res;
    }
    void traverse(TreeNode *r, int& res) {
        if (r == nullptr) {
            return;
        }
        res++;
        traverse(r->left, res);
        traverse(r->right, res);
    }
};

// 223. Rectangle Area
class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int s1 = (ax2 - ax1) * (ay2 - ay1);
        int s2 = (bx2 - bx1) * (by2 - by1);
        if (ax1 >= bx2 || ax2 <= bx1 || ay2 <= by1 || ay1 >= by2) {
            return s1 + s2;
        }
        return s1 - (min(bx2, ax2) - max(ax1, bx1)) * (min(ay2, by2) - max(ay1, by1)) + s2;
    }
};

// 224. Basic Calculator
class Solution {
public:
    int calculate(string s) {
        long res = 0;
        vector<int> signs(2, 1);
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c >= '0') {
                long number = 0;
                while (i < s.size() && s[i] >= '0') {
                    number = 10 * number + s[i++] - '0';
                }
                res += signs.back() * number;
                signs.pop_back();
                i--;
            } else if (c == ')') {
                signs.pop_back();
            } else if (c != ' ') {
                signs.push_back(signs.back() * (c == '-' ? -1 : 1));
            }
        }
        return res;
    }
};

// 225. Implement Stack using Queues
class MyStack {
    queue<int> q;
public:
    MyStack() {}

    void push(int x) {
        q.push(x);
        for (int i = 1; i < q.size(); i++) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        int v = q.front();
        q.pop();
        return v;
    }

    int top() {
        return q.front();
    }

    bool empty() {
        return q.empty();
    }
};
/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

// 226. Invert Binary Tree
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
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        TreeNode *tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

// 227. Basic Calculator II
class Solution {
public:
    int calculate(string s) {
        stack<int> stack;
        char sign = '+';
        long res = 0, tmp = 0;
        for (unsigned int i = 0; i < s.size(); i++) {
            if (isdigit(s[i])) {
                tmp = 10 * tmp + s[i] - '0';
            }
            if (!isdigit(s[i]) && !isspace(s[i]) || i == s.size() - 1) {
                if (sign == '-') {
                    stack.push(-tmp);
                } else if (sign == '+') {
                    stack.push(tmp);
                } else {
                    int num;
                    if (sign == '*') {
                        num = stack.top() * tmp;
                    } else {
                        num = stack.top() / tmp;
                    }
                    stack.pop();
                    stack.push(num);
                }
                sign = s[i];
                tmp = 0;
            }
        }
        while (!stack.empty()) {
            res += stack.top();
            stack.pop();
        }
        return res;
    }
};

// 228. Summary Ranges
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        if (nums.size() == 0) {
            return vector<string>();
        }
        vector<string> res;
        string tmp = to_string(nums[0]);
        bool flag = false;
        int t = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (t + 1 == nums[i]) {
                t = nums[i];
                if (!flag) {
                    tmp = tmp + "->";
                    flag = true;
                }
            } else {
                if (flag) {
                    tmp = tmp + to_string(nums[i - 1]);
                }
                res.push_back(tmp);
                t = nums[i];
                tmp = to_string(nums[i]);
                flag = false;
            }
        }
        if (tmp != "") {
            tmp = flag ? tmp + to_string(t) : tmp;
            res.push_back(tmp);
        }
        return res;
    }
};

// 229. Majority Element II
class Solution {　
public:
    vector<int> majorityElement(vector<int>& nums) {
        int count1 = 0, count2 = 0;
        int tmp1 = -1, tmp2 = -1;
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == tmp1) {
                count1++;
            } else if (nums[i] == tmp2) {
                count2++;
            } else if (count1 == 0) {
                tmp1 = nums[i];
                count1++;
            } else if (count2 == 0) {
                tmp2 = nums[i];
                count2++;
            } else {
                count1--;
                count2--;
            }
        }
        count1 = count2 = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == tmp1) {
                count1++;
            } else if (nums[i] == tmp2) {
                count2++;
            }
        }
        if (count1 > nums.size() / 3) {
            res.push_back(tmp1);
        }
        if (count2 > nums.size() / 3) {
            res.push_back(tmp2);
        }
        return res;
    }
};

// 230. Kth Smallest Element in a BST
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
    int kthSmallest(TreeNode* root, int k) {
        return kth(root, k);
    }
    int kth(TreeNode *r, int& k) {
        if (r == nullptr) {
            return -1;
        }
        int x = kth(r->left, k);
        if (x == -1) {
            return --k == 0 ? r->val : kth(r->right, k);
        } else {
            return x;
        }
    }
};

// 231. Power of Two
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if (n == 1) {
            return true;
        }
        for (long i = 2; i <= n; i *= 2) {
            if (i == n) {
                return true;
            }
        }
        return false;
    }
};

// 232. Implement Queue using Stacks
class MyQueue {
    stack<int> in;
    stack<int> out;
public:
    MyQueue() {

    }

    void push(int x) {
        in.push(x);
    }

    int pop() {
        int v = peek();
        out.pop();
        return v;
    }

    int peek() {
        if (out.empty()) {
            while (!in.empty()) {
                out.push(in.top());
                in.pop();
            }
        }
        return out.top();
    }

    bool empty() {
        return in.empty() && out.empty();
    }
};
/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

// 234. Palindrome Linked List
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
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) {
            return true;
        }
        ListNode *slow(head), *fast(head);
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        if (fast) {
            slow = slow->next;
        }
        ListNode *pre(NULL), *cur(slow), *next;
        while (cur) {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        while (pre) {
            if (pre->val != head->val) {
                return false;
            }
            pre = pre->next;
            head = head->next;
        }
        return true;
    }
};

// 235. Lowest Common Ancestor of a Binary Search Tree
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if ((root->val > p->val) && (root->val > q->val)) {
            return lowestCommonAncestor(root->left, p, q);
        }
        if ((root->val < p->val) && (root->val < q->val)) {
            return lowestCommonAncestor(root->right, p, q);
        }
        return root;
    }
};

// 236. Lowest Common Ancestor of a Binary Tree
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) {
            return root;
        }
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left && right) {
            return root;
        } else {
            return left ? left : right;
        }
    }
};

// 237. Delete Node in a Linked List
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
    void deleteNode(ListNode* node) {
        ListNode *tmp = node->next;
        *node = *node->next;
        delete tmp;
    }
};

// 238. Product of Array Except Self
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++) {
            res[i] = res[i - 1] * nums[i - 1];
        }
        int tmp = 1;
        for (int i = nums.size() - 1; i >= 1; i--) {
            tmp *= nums[i];
            res[i - 1] *= tmp;
        }
        return res;
    }
};

// 239. Sliding Window Maximum
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> buf;
        vector<int> res;
        for (auto i = 0; i < nums.size(); i++) {
            while (!buf.empty() && nums[i] >= nums[buf.back()]) {
                buf.pop_back();
            }
            buf.push_back(i);
            if (i >= k - 1) {
                res.push_back(nums[buf.front()]);
            }
            if (buf.front() <= i - k + 1) {
                buf.pop_front();
            }
        }
        return res;
    }
};

// 240. Search a 2D Matrix II
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = m ? matrix[0].size() : 0;
        int row = 0, col = n - 1;
        while (row < m && col >= 0) {
            if (matrix[row][col] == target) {
                return true;
            }
            matrix[row][col] > target ? col-- : row++;
        }
        return false;
    }
};

// 242. Valid Anagram
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }
        int m[26] = {};
        for (int i = 0; i < s.size(); i++) {
            m[s.at(i) - 'a']++;
        }
        for (int i = 0; i < t.size(); i++) {
            if (m[t.at(i) - 'a'] == 0) {
                return false;
            }
            m[t.at(i) - 'a']--;
        }
        return true;
    }
};

// 257. Binary Tree Paths
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        recursive(res, root, "");
        return res;
    }
    void recursive(vector<string>& res, TreeNode *r, string p) {
        if (r == nullptr) {
            return;
        }
        p += p != "" ? "->" + to_string(r->val) : to_string(r->val);
        if (r->left == nullptr && r->right == nullptr) {
            res.push_back(p);
            return;
        }
        recursive(res, r->left, p);
        recursive(res, r->right, p);
    }
};

// 258. Add Digits
class Solution {
public:
    int addDigits(int num) {
        int tmp = 0;
        while (true) {
            tmp += num % 10;
            num /= 10;
            if (num == 0) {
                if (tmp < 10) {
                    return tmp;
                }
                num = tmp;
                tmp = 0;
            }
        }
        return -1;
    }
};

// 260. Single Number III
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unordered_map<int, int> m;
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            m[nums[i]]++;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (m[nums[i]] == 1) {
                res.push_back(nums[i]);
            }
        }
        return res;
    }
};

// 263. Ugly Number
class Solution {
public:
    bool isUgly(int n) {
        if (n == 0) {
            return false;
        }
        if (n == 1) {
            return true;
        }
        while (n % 2 == 0) {
            n /= 2;
        }
        while (n % 3 == 0) {
            n /= 3;
        }
        while (n % 5 == 0) {
            n /= 5;
        }
        return n == 1;
    }
};

// 264. Ugly Number II
class Solution {
public:
    int nthUglyNumber(int n) {
        int dp[n];
        dp[0] = 1;
        int a = 0, b = 0, c = 0;
        for (int i = 1; i < n; i++) {
            dp[i] = min({dp[a] * 2, dp[b] * 3, dp[c] * 5});
            if (dp[i] == dp[a] * 2) {
                a++;
            }
            if (dp[i] == dp[b] * 3) {
                b++;
            }
            if (dp[i] == dp[c] * 5) {
                c++;
            }
        }
        return dp[n - 1];
    }
};

// 268. Missing Number
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sum = 0;
        for (int i = 0; i <= nums.size(); i++) {
            sum += i;
        }
        for (int i = 0; i < nums.size(); i++) {
            sum -= nums[i];
        }
        return sum;
    }
};

// 274. H-Index
class Solution {
public:
    int hIndex(vector<int>& citations) {
        if (citations.empty()) {
            return 0;
        }
        int n = citations.size();
        vector<int> m(n + 1, 0);
        for (int i = 0; i < n; i++) {
            if (citations[i] >= n) {
                m[n]++;
            } else {
                m[citations[i]]++;
            }
        }
        int paper = 0;
        for (int i = n; i >= 0; i--) {
            paper += m[i];
            if (paper >= i) {
                return i;
            }
        }
        return -1;
    }
};

// 278. First Bad Version
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);
class Solution {
public:
    int firstBadVersion(int n) {
        int res = 1, l = 1, r = n;
        while (l <= r) {
            int m = l + ((r - l) / 2);
            if (isBadVersion(m)) {
                res = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return res;
    }
};

// 279. Perfect Squares
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        int count = 1;
        while (count * count <= n) {
            int sq = count * count;
            for (int i = sq; i <= n; i++) {
                dp[i] = min(dp[i - sq] + 1, dp[i]);
            }
            count++;
        }
        return dp[n];
    }
};

// 283. Move Zeroes
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i = 0;
        for (int j = 0; j < nums.size(); j++) {
            if (nums[j] != 0) {
                nums[i++] = nums[j];
            }
        }
        for (; i < nums.size(); i++) {
            nums[i] = 0;
        }
    }
};

// 284. Peeking Iterator
/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */
class PeekingIterator : public Iterator {
private:
    int nextVal;
    bool hasNextVal;
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	    // Initialize any member here.
	    // **DO NOT** save a copy of nums and manipulate it directly.
	    // You should only use the Iterator interface methods.
	    hasNextVal = Iterator::hasNext();
      if (hasNextVal) {
          nextVal = Iterator::next();
      }
	}
	
    // Returns the next element in the iteration without advancing the iterator.
	int peek() {
      return nextVal;
	}
	
	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
      int current = nextVal;
      hasNextVal = Iterator::hasNext();
      if (hasNextVal) {
          nextVal = Iterator::next();
      }
      return current;
	}
	
	bool hasNext() const {
	    return hasNextVal;
	}
};

// 287. Find the Duplicate Number
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        qSort(nums, 0, nums.size() - 1);
        for (int i = 0; i < nums.size() - 1; i++) {
            if (nums[i] == nums[i + 1]) {
                return nums[i];
            }
        }
        return -1;
    }
    void qSort(vector<int>& nums, int left, int right) {
        if (left >= right) {
            return;
        }
        int p = left;
        swap(nums[(left + right) / 2], nums[right]);
        for (int i = left; i < right; i++) {
            if (nums[i] < nums[right]) {
                swap(nums[p++], nums[i]);
            }
        }
        swap(nums[p], nums[right]);
        qSort(nums, left, p - 1);
        qSort(nums, p + 1, right);
    }
};

// 290. Word Pattern
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        unordered_map<char, int> m1;
        unordered_map<string, int> m2;
        int i = 1, k = 0;
        for (int j = 0; j < pattern.size(); j++) {
            if (k >= s.size()) {
                return false;
            }
            string tmp = "";
            for (; k < s.size(); k++) {
                if (s.at(k) == ' ') {
                    k++;
                    break;
                }
                tmp += to_string(s.at(k));
            }
            if (!m1[pattern.at(j)] && !m2[tmp]) {
                m1[pattern.at(j)] = m2[tmp] = i++;
            }
            if (m1[pattern.at(j)] != m2[tmp]) {
                return false;
            }
        }
        if (k < s.size()) {
            return false;
        }
        return true;
    }
};

// 292. Nim Game
class Solution {
public:
    bool canWinNim(int n) {
        return n % 4;
    }
};

// 295. Find Median from Data Stream
class MedianFinder {
private:
    priority_queue<long> small, large;
public:
    MedianFinder() {}

    void addNum(int num) {
        small.push(num);
        large.push(-small.top());
        small.pop();
        if (small.size() < large.size()) {
            small.push(-large.top());
            large.pop();
        }
    }

    double findMedian() {
        return small.size() > large.size() ?
            small.top() : (small.top() - large.top()) / 2.0;
    }
};
/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

// 297. Serialize and Deserialize Binary Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
private:
    void serialize(TreeNode *r, ostringstream& o) {
        if (r) {
            o << r->val << ' ';
            serialize(r->left, o);
            serialize(r->right, o);
        } else {
            o << "# ";
        }
    }

    TreeNode* deserialize(istringstream& i) {
        string val;
        i >> val;
        if (val == "#") {
            return nullptr;
        }
        TreeNode *r = new TreeNode(stoi(val));
        r->left = deserialize(i);
        r->right = deserialize(i);
        return r;
    }
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream o;
        serialize(root, o);
        return o.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream i(data);
        return deserialize(i);
    }
};
// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

// 300. Longest Increasing Subsequence
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), res = INT_MIN;
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};

// 303. Range Sum Query - Immutable
class NumArray {
private:
    vector<int> accum;
public:
    NumArray(vector<int>& nums) {
        accum.push_back(0);
        for (int i = 0; i < nums.size(); i++) {
            accum.push_back(accum.back() + nums[i]);
        }
    }

    int sumRange(int left, int right) {
        return accum[right + 1] - accum[left];
    }
};
/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */

// 304. Range Sum Query 2D - Immutable
class NumMatrix {
private:
    vector<vector<int>> m;
    int helper(int i, int j) {
        return i >= 0 && j >= 0 ? m[i][j] : 0;
    }

public:
    NumMatrix(vector<vector<int>>& matrix) {
        m = matrix;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                m[i][j] += (helper(i - 1, j) + helper(i, j - 1)) - helper(i - 1, j - 1);
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return helper(row2, col2) - helper(row1 - 1, col2) - helper(row2, col1 - 1)
            + helper(row1 - 1, col1 - 1);
    }
};
/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */

// 309. Best Time to Buy and Sell Stock with Cooldown
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy = INT_MAX;
        int pfree = 0, last = 0, now = 0, x = 0;
        for (int i = 0; i < prices.size(); i++) {
            x = prices[i];
            now = max(last, x - buy);
            buy = min(buy, x - pfree);
            pfree = last;
            last = now;
        }
        return now;
    }
};

// 315. Count of Smaller Numbers After Self
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<pair<int, int>> v(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            v[i] = make_pair(nums[i], i);
        }
        vector<int> count(nums.size(), 0);
        mergeSort(count, v, 0, nums.size() - 1);
        return count;
    }
    void mergeSort(vector<int>& count, vector<pair<int, int>>& v, int left, int right) {
        if (left >= right) {
            return;
        }
        int mid = left + (right - left) / 2;
        mergeSort(count, v, left, mid);
        mergeSort(count, v, mid + 1, right);
        merge(count, v, left, mid, right);
    }
    void merge(vector<int>& count, vector<pair<int, int>>& v, int left, int mid, int right) {
        vector<pair<int, int>> tmp(right - left + 1);
        int i = left;
        int j = mid + 1;
        int k = 0;
        while (i <= mid && j <= right) {
            if (v[i].first <= v[j].first) {
                tmp[k++] = v[j++];
            } else {
                count[v[i].second] += right - j + 1;
                tmp[k++] = v[i++];
            }
        }
        while (i <= mid) {
            tmp[k++] = v[i++];
        }
        while (j <= right) {
            tmp[k++] = v[j++];
        }
        for (int i = left; i <= right; i++) {
            v[i] = tmp[i - left];
        }
    }
};

// 316. Remove Duplicate Letters
class Solution {
public:
    string removeDuplicateLetters(string s) {
        unordered_map<char, bool> visited;
        unordered_map<char, int> m;
        for (char c : s) {
            m[c]++;
        }
        string result = "";
        for (char c : s) {
            m[c]--;
            if (visited[c]) {
                continue;
            }
            while (!result.empty() && c < result.back() && m[result.back()] > 0) {
                visited[result.back()] = false;
                result.pop_back();
            }
            result += c;
            visited[c] = true;
        }
        return result;
    }
};

// 318. Maximum Product of Word Lengths
class Solution {
public:
    int maxProduct(vector<string>& words) {
        vector<int> m(words.size());
        int res = 0;
        for (int i = 0; i < words.size(); i++) {
            for (char c : words[i]) {
                m[i] |= 1 << (c - 'a');
            }
        }
        for (int i = 0; i < words.size(); i++) {
            for (int j = i + 1; j < words.size(); j++) {
                if (!(m[i] & m[j])) {
                    res = max(res, int(words[i].size() * words[j].size()));
                }
            }
        }
        return res;
    }
};

// 319. Bulb Switcher
class Solution {
public:
    int bulbSwitch(int n) {
        return floor(sqrt(n));
    }
};

// 322. Coin Change
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (coin <= i) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};

// 324. Wiggle Sort II
class Solution {
public:
    int vIndex(int i, int n) {
        return (2 * i + 1) % (n | 1);
    }
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        auto nth = nums.begin() + n / 2;
        nth_element(nums.begin(), nth, nums.end());
        int median = *nth;
        int first = 0, mid = 0, last = n - 1;
        while (mid <= last) {
            if (nums[vIndex(mid, n)] > median) {
                swap(nums[vIndex(first++, n)], nums[vIndex(mid++, n)]);
            } else if (nums[vIndex(mid, n)] < median) {
                swap(nums[vIndex(mid, n)], nums[vIndex(last--, n)]);
            } else {
                ++mid;
            }
        }
    }
};

// 326. Power of Three
class Solution {
public:
    bool isPowerOfThree(int n) {
        while (n % 3 == 0 && n != 0) {
            n /= 3;
        }
        return n == 1;
    }
};

// 328. Odd Even Linked List
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
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        ListNode *dummy = new ListNode(-1, head);
        ListNode *dummy2 = new ListNode(-1, head->next);
        ListNode *cur = dummy->next;
        while (cur && cur->next) {
            ListNode *nex = cur->next;
            if (!nex->next) {
                break;
            }
            cur->next = nex->next;
            nex->next = nex->next->next;
            cur = cur->next;
            nex = nex->next;
        }
        cur->next = dummy2->next;
        return dummy->next;
    }
};

// 331. Verify Preorder Serialization of a Binary Tree
class Solution {
public:
    bool isValidSerialization(string preorder) {
        preorder += ',';
        int cap = 1;
        for (int i = 0; i < preorder.size(); i++) {
            if (preorder.at(i) != ',') {
                continue;
            }
            cap--;
            if (cap < 0) {
                return false;
            }
            if (preorder.at(i - 1) != '#') {
                cap += 2;
            }
        }
        return cap == 0;
    }
};

// 334. Increasing Triplet Subsequence
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n1 = INT_MAX, n2 = INT_MAX;
        for (int x : nums) {
            if (x <= n1) {
                n1 = x;
            } else if (x <= n2) {
                n2 = x;
            } else {
                return true;
            }
        }
        return false;
    }
};

// 337. House Robber III
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
    int rob(TreeNode* root) {
        int l, r;
        return tryRob(root, l, r);
    }
    int tryRob(TreeNode* root, int& l, int& r) {
        if (!root) {
            return 0;
        }
        int ll = 0, lr = 0, rl = 0, rr = 0;
        l = tryRob(root->left, ll, lr);
        r = tryRob(root->right, rl, rr);
        return max(root->val + ll + lr + rl + rr, l + r);
    }
};

// 338. Counting Bits
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> res;
        for (int i = 0; i <= n; i++) {
            int sum = 0;
            int tmp = i;
            while (tmp) {
                sum += tmp & 1;
                tmp >>= 1;
            }
            res.push_back(sum);
        }
        return res;
    }
};

// 342. Power of Four
class Solution {
public:
    bool isPowerOfFour(int n) {
        while (n % 4 == 0 && n != 0) {
            n /= 4;
        }
        return n == 1;
    }
};

// 344. Reverse String
class Solution {
public:
    void reverseString(vector<char>& s) {
        for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }
};

// 345. Reverse Vowels of a String
class Solution {
public:
    bool isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
            || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
    }
    string reverseVowels(string s) {
        int l = 0, r = s.size() - 1;
        while (l < r) {
            while (l < r && !isVowel(s.at(l))) {
                l++;
            }
            while (l < r && !isVowel(s.at(r))) {
                r--;
            }
            if (l < r) {
                swap(s[l], s[r]);
                l++, r--;
            }
        }
        return s;
    }
};

// 347. Top K Frequent Elements
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        unordered_map<int, vector<int>> m2;
        vector<int> rank, res;
        for (int v : nums) {
            m[v]++;
        }
        for (auto it = m.begin(); it != m.end(); it++) {
            if (m2.find(it->second) == m2.end()) {
                rank.push_back(it->second);
            }
            m2[it->second].push_back(it->first);
        }
        qSort(rank, 0, rank.size() - 1);
        for (int i = rank.size() - 1; k > 0; i--) {
            for (int v : m2[rank[i]]) {
                if (k == 0) {
                    break;
                }
                res.push_back(v);
                k--;
            }
        }
        return res;
    }
    void qSort(vector<int>& v, int left, int right) {
        if (left >= right) {
            return;
        }
        int p = left;
        swap(v[(left + right) / 2], v[right]);
        for (int i = left; i < right; i++) {
            if (v[i] < v[right]) {
                swap(v[i], v[p++]);
            }
        }
        swap(v[p], v[right]);
        qSort(v, left, p - 1);
        qSort(v, p + 1, right);
    }
};

// 349. Intersection of Two Arrays
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> m;
        vector<int> res;
        for (int v : nums1) {
            m[v] = 1;
        }
        for (int v : nums2) {
            if (m[v]) {
                res.push_back(v);
                m[v] = 0;
            }
        }
        return res;
    }
};

// 350. Intersection of Two Arrays II
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> m;
        vector<int> res;
        for (int v : nums1) {
            m[v]++;
        }
        for (int v : nums2) {
            if (m[v]) {
                res.push_back(v);
                m[v]--;
            }
        }
        return res;
    }
};

// 355. Design Twitter
class Twitter {
private:
    vector<pair<int, int>> posts;
    unordered_map<int, unordered_map<int, int>> follows;
public:
    Twitter() {

    }

    void postTweet(int userId, int tweetId) {
        posts.push_back(make_pair(userId, tweetId));
    }

    vector<int> getNewsFeed(int userId) {
        vector<int> feed;
        int count = 0;
        for (int i = posts.size() - 1; i >= 0 && count < 10; i--) {
            if (posts[i].first == userId || follows[userId][posts[i].first]) {
                feed.push_back(posts[i].second), count++;
            }
        }
        return feed;
    }

    void follow(int followerId, int followeeId) {
        follows[followerId][followeeId] = 1;
    }

    void unfollow(int followerId, int followeeId) {
        follows[followerId][followeeId] = 0;
    }
};
/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

// 357. Count Numbers with Unique Digits
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) {
            return 1;
        }
        int ans = 10, calc = 9, temp = 9;
        for (int i = 0; i < n - 1; i++) {
            calc *= temp;
            ans += calc;
            temp--;
        }
        return ans;
    }
};

// 371. Sum of Two Integers
class Solution {
public:
    int getSum(int a, int b) {
        int sum = a;
        long mask = 0xFFFFFFFF;
        while (b != 0) {
            sum = a ^ b;
            b = ((a & b) & mask) << 1;
            a = sum;
        }
        return sum;
    }
};

// 374. Guess Number Higher or Lower
/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */
class Solution {
public:
    int guessNumber(int n) {
        int left = 1, right = n;
        while (true) {
            int mid = left + ((right - left) / 2);
            int g = guess(mid);
            if (g == 0) {
                return mid;
            } else if (g == -1) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
    }
};

// 376. Wiggle Subsequence
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        vector<int> up(nums.size(), 0);
        vector<int> down(nums.size(), 0);
        up[0] = down[0] = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i - 1]) {
                up[i] = down[i - 1] + 1;
                down[i] = down[i - 1];
            } else if (nums[i] < nums[i - 1]) {
                down[i] = up[i - 1] + 1;
                up[i] = up[i - 1];
            } else {
                up[i] = up[i - 1];
                down[i] = down[i - 1];
            }
        }
        return max(up[nums.size() - 1], down[nums.size() - 1]);
    }
};

// 377. Combination Sum IV
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned int> res(target + 1);
        res[0] = 1;
        for (int i = 1; i <= target; i++) {
            for (int x : nums) {
                if (i >= x) {
                    res[i] += res[i - x];
                }
            }
        }
        return res[target];
    }
};

// 378. Kth Smallest Element in a Sorted Matrix
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int low = matrix[0][0], high = matrix[n - 1][n - 1] + 1;
        int mid = 0, count = 0, tmp = 0;
        while (low < high) {
            mid = low + (high - low) / 2;
            tmp = n - 1;
            count = 0;
            for (int i = 0; i < n; i++) {
                while (tmp >= 0 && matrix[i][tmp] > mid) {
                    tmp--;
                }
                count += tmp + 1;
            }
            if (count < k) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }
};

// 380. Insert Delete GetRandom O(1)
class RandomizedSet {
private:
    vector<int> nums;
    unordered_map<int, int> m;
public:
    RandomizedSet() {}

    bool insert(int val) {
        if (m.find(val) != m.end()) {
            return false;
        }
        nums.emplace_back(val);
        m[val] = nums.size() - 1;
        return true;
    }

    bool remove(int val) {
        if (m.find(val) == m.end()) {
            return false;
        }
        int last = nums.back();
        m[last] = m[val];
        nums[m[val]] = last;
        nums.pop_back();
        m.erase(val);
        return true;
    }

    int getRandom() {
        return nums[rand() % nums.size()];
    }
};
/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

// 382. Linked List Random Node
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
private:
    vector<int> v;
public:
    Solution(ListNode* head) {
        while (head) {
            v.push_back(head->val);
            head = head->next;
        }
    }

    int getRandom() {
        return v[random() % v.size()];
    }
};
/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */

// 384. Shuffle an Array
class Solution {
private:
    vector<int> nums;
public:
    Solution(vector<int>& nums) {
        this->nums = nums;
    }

    vector<int> reset() {
        return nums;
    }

    vector<int> shuffle() {
        vector<int> res(nums);
        for (int i = 0; i < res.size(); i++) {
            int pos = rand() % (res.size() - i);
            swap(res[i + pos], res[i]);
        }
        return res;
    }
};
/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */

// 386. Lexicographical Numbers
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> res(n);
        int cur = 1;
        for (int i = 0; i < n; i++) {
            res[i] = cur;
            if (cur * 10 <= n) {
                cur *= 10;
            } else {
                if (cur >= n) {
                    cur /= 10;
                }
                cur += 1;
                while (cur % 10 == 0) {
                    cur /= 10;
                }
            }
        }
        return res;
    }
};

// 389. Find the Difference
class Solution {
public:
    char findTheDifference(string s, string t) {
        int res = 0;
        for (char c : s) {
            res ^= c;
        }
        for (char c : t) {
            res ^= c;
        }
        return res;
    }
};

// 392. Is Subsequence
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0;
        while (i < s.size()) {
            while (j < t.size() && s.at(i) != t.at(j)) {
                j++;
            }
            if (j == t.size()) {
                break;
            }
            i++, j++;
        }
        return i == s.size() && j <= t.size();
    }
};

// 393. UTF-8 Validation
class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int count = 0;
        for (int c : data) {
            if (count == 0) {
                if ((c >> 5) == 0b110) {
                    count = 1;
                } else if ((c >> 4) == 0b1110) {
                    count = 2;
                } else if ((c >> 3) == 0b11110) {
                    count = 3;
                } else if ((c >> 7) == 0b1) {
                    return false;
                }
            } else {
                if ((c >> 6) != 0b10) {
                    return false;
                }
                count--;
            }
        }
        return count == 0;
    }
};

// 394. Decode String
class Solution {
public:
    string decodeString(const string& s, int& i) {
        string res;
        while (i < s.length() && s[i] != ']') {
            if (!isdigit(s[i])) {
                res += s[i++];
            } else {
                int n = 0;
                while (i < s.length() && isdigit(s[i])) {
                    n = n * 10 + s[i++] - '0';
                }
                i++;
                string t = decodeString(s, i);
                i++;
                while (n-- > 0) {
                    res += t;
                }
            }
        }
        return res;
    }
    string decodeString(string s) {
        int i = 0;
        return decodeString(s, i);
    }
};

// 395. Longest Substring with At Least K Repeating Characters
class Solution {
public:
    int longestSubstring(string s, int k) {
        if (s.size() == 0 || k > s.size()) {
            return 0;
        }
        if (k == 0) {
            return s.size();
        }
        unordered_map<char, int> m;
        for (int i = 0; i < s.size(); i++) {
            m[s[i]]++;
        }
        int idx = 0;
        while (idx < s.size() && m[s[idx]] >= k) {
            idx++;
        }
        if (idx == s.size()) {
            return s.size();
        }
        int left = longestSubstring(s.substr(0, idx), k);
        int right = longestSubstring(s.substr(idx + 1), k);
        return max(left, right);
    }
};

// 397. Integer Replacement
class Solution {
private:
    int res = 0;
public:
    int integerReplacement(int n) {
        if (n == 1) {
            return res;
        }
        if (n == 3) {
            res += 2;
            return res;
        }
        if (n == INT_MAX) {
            return 32;
        }
        if (n & 1) {
            res++;
            if ((n + 1) % 4 == 0) {
                integerReplacement(n + 1);
            } else {
                integerReplacement(n - 1);
            }
        } else {
            res++;
            integerReplacement(n / 2);
        }
        return res;
    }
};

// 398. Random Pick Index
class Solution {
private:
    unordered_map<int, vector<int>> m;
public:
    Solution(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            m[nums[i]].push_back(i);
        }
    }

    int pick(int target) {
        int idx = rand() % m[target].size();
        return m[target][idx];
    }
};
/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */

// 402. Remove K Digits
class Solution {
public:
    string removeKdigits(string num, int k) {
        if (num.length() <= k) {
            return "0";
        }
        if (k == 0) {
            return num;
        }
        string res = "";
        stack<char> s;
        s.push(num[0]);
        for (int i = 1; i < num.length(); i++) {
            while (k > 0 && !s.empty() && num[i] < s.top()) {
                k--;
                s.pop();
            }
            s.push(num[i]);
            if (s.size() == 1 && num[i] == '0') {
                s.pop();
            }
        }
        while (k && !s.empty()) {
            k--;
            s.pop();
        }
        while (!s.empty()) {
            res.push_back(s.top());
            s.pop();
        }
        reverse(res.begin(), res.end());
        if (res.length() == 0) {
            return "0";
        }
        return res;
    }
};

// 404. Sum of Left Leaves
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
    int sumOfLeftLeaves(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        if (root->left && !root->left->left && !root->left->right) {
            return root->left->val + sumOfLeftLeaves(root->right);
        }
        return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
    }
};

// 405. Convert a Number to Hexadecimal
class Solution {
private:
    const string HEX = "0123456789abcdef";
public:
    string toHex(int num) {
        if (num == 0) {
            return "0";
        }
        string res;
        int count = 0;
        while (num && count++ < 8) {
            res = HEX[num & 0xf] + res;
            num >>= 4;
        }
        return res;
    }
};

// 406. Queue Reconstruction by Height
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        auto comp = [](const vector<int>& p1, const vector<int>& p2) {
            return p1[0] > p2[0] || p1[0] == p2[0] && p1[1] < p2[1];
        };
        sort(people.begin(), people.end(), comp);
        vector<vector<int>> res;
        for (auto &p : people) {
            res.insert(res.begin() + p[1], p);
        }
        return res;
    }
};

// 409. Longest Palindrome
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> m;
        for (char c : s) {
            m[c]++;
        }
        int count = 0;
        for (auto v : m) {
            if (v.second % 2 != 0) {
                count++;
            }
        }
        if (count > 1) {
            return s.length() - count + 1;
        }
        return s.length();
    }
};

// 412. Fizz Buzz
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> res;
        for (int i = 1; i <= n; i++) {
            if (i % 3 == 0 && i % 5 == 0) {
                res.push_back("FizzBuzz");
            } else if (i % 3 == 0) {
                res.push_back("Fizz");
            } else if (i % 5 == 0) {
                res.push_back("Buzz");
            } else {
                res.push_back(to_string(i));
            }
        }
        return res;
    }
};

// 413. Arithmetic Slices
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        if (nums.size() < 3) {
            return 0;
        }
        int count = 0;
        for (int i = 0; i < nums.size() - 2; i++) {
            int diff = nums[i + 1] - nums[i];
            for (int j = i + 2; j < nums.size(); j++) {
                if (nums[j] - nums[j - 1] == diff) {
                    count++;
                } else {
                    break;
                }
            }
        }
        return count;
    }
};

// 414. Third Maximum Number
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long v1 = LONG_MIN, v2 = LONG_MIN, v3 = LONG_MIN;
        for (int n : nums) {
            if (n == v1 || n == v2 || n == v3) {
                continue;
            }
            if (n >= v1) {
                v3 = v2;
                v2 = v1;
                v1 = n;
            } else if (n >= v2) {
                v3 = v2;
                v2 = n;
            } else if (n >= v3) {
                v3 = n;
            }
        }
        if (v3 != LONG_MIN) {
            return v3;
        } else if (v1 != LONG_MIN) {
            return v1;
        } else {
            return v2;
        }
    }
};

// 415. Add Strings
class Solution {
public:
    string addStrings(string num1, string num2) {
        string l, s;
        if (num1.length() >= num2.length()) {
            l = num1, s = num2;
        } else {
            l = num2, s = num1;
        }
        string res;
        int i = s.length() - 1, j = l.length() - 1;
        bool carry = false;
        while (i >= 0) {
            int v1 = s[i--] - '0', v2 = l[j--] - '0';
            int sum = carry ? v1 + v2 + 1 : v1 + v2;
            carry = sum >= 10 ? true : false;
            res = char((sum % 10) + '0') + res;
        }
        while (j >= 0) {
            int v = l[j--] - '0';
            int sum = carry ? v + 1 : v;
            carry = sum >= 10 ? true : false;
            res = char((sum % 10) + '0') + res;
        }
        return carry ? '1' + res : res;
    }
};

// 416. Partition Equal Subset Sum
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int n : nums) {
            sum += n;
        }
        if (sum & 1) {
            return false;
        }
        vector<int> dp(sum / 2 + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = sum / 2; j >= nums[i]; j--) {
                dp[j] = dp[j] || dp[j - nums[i]];
            }
        }
        return dp[sum / 2];
    }
};

// 419. Battleships in a Board
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) {
            return 0;
        }
        int row = board.size(), col = board[0].size();
        int res = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (board[i][j] == 'X') {
                    if (i > 0 && board[i - 1][j] == 'X') {
                        continue;
                    }
                    if (j > 0 && board[i][j - 1] == 'X') {
                        continue;
                    }
                    res++;
                }
            }
        }
        return res;
    }
};

// 424. Longest Repeating Character Replacement
class Solution {
public:
    int characterReplacement(string s, int k) {
        int res = 0, maxf = 0;
        unordered_map<int, int> m;
        for (int i = 0; i < s.length(); i++) {
            maxf = max(maxf, ++m[s[i]]);
            if (res - maxf < k) {
                res++;
            } else{
                m[s[i - res]]--;
            }
        }
        return res;
    }
};

// 429. N-ary Tree Level Order Traversal
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> res;
        traversal(res, root, 1);
        return res;
    }
    void traversal(vector<vector<int>>& res, Node* root, int level) {
        if (!root) {
            return;
        }
        if (res.size() < level) {
            res.push_back({});
        }
        res[level - 1].push_back(root->val);
        for (auto c : root->children) {
            traversal(res, c, level + 1);
        }
    }
};

// 430. Flatten a Multilevel Doubly Linked List
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/
class Solution {
public:
    Node* flatten(Node* head) {
        stack<Node*> s;
        Node* h = head;
        while (head) {
            if (head->child) {
                if (head->next) {
                    s.push(head->next);
                }
                head->next = head->child;
                head->child = nullptr;
                head->next->prev = head;
            } else if (!head->next && !s.empty()) {
                head->next = s.top();
                head->next->prev = head;
                s.pop();
            }
            head = head->next;
        }
        return h;
    }
};

// 434. Number of Segments in a String
class Solution {
public:
    int countSegments(string s) {
        int res = 0;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == ' ' && s[i - 1] != ' ') {
                res++;
            }
        }
        return s.size() > 0 && s[s.size() - 1] != ' ' ? res + 1 : res;
    }
};

// 437. Path Sum III
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
    int pathSum(TreeNode* root, int targetSum) {
        if (!root) {
            return 0;
        }
        return traverse(root, targetSum) +
            pathSum(root->left, targetSum) +
            pathSum(root->right, targetSum);
    }
    int traverse(TreeNode* root, long sum) {
        if (!root) {
            return 0;
        }
        return (root->val == sum) +
            traverse(root->left, sum - root->val) +
            traverse(root->right, sum - root->val);
    }
};

// 441. Arranging Coins
class Solution {
public:
    int arrangeCoins(int n) {
        int res = 0, s = 1;
        while (n >= s) {
            n -= s++, res++;
        }
        return res;
    }
};

// 442. Find All Duplicates in an Array
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        for (int n : nums) {
            nums[abs(n) - 1] = -nums[abs(n) - 1];
            if (nums[abs(n) - 1] > 0) {
                res.push_back(abs(n));
            }
        }
        return res;
    }
};

// 443. String Compression
class Solution {
public:
    int compress(vector<char>& chars) {
        if (chars.size() < 2) {
            return chars.size();
        }
        int i = 0, j = 0;
        while (i < chars.size()) {
            chars[j] = chars[i];
            int count = 0;
            while (i < chars.size() && chars[i] == chars[j]) {
                count++, i++;
            }
            if (count == 1) {
                j++;
            } else {
                string s = to_string(count);
                for (char c : s) {
                    chars[++j] = c;
                }
                j++;
            }
        }
        return j;
    }
};

// 445. Add Two Numbers II
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
        vector<int> n1, n2;
        while (l1) {
            n1.push_back(l1->val);
            l1 = l1->next;
        }
        while (l2) {
            n2.push_back(l2->val);
            l2 = l2->next;
        }
        int i = n1.size() - 1, j = n2.size() - 1;
        int sum = 0, carry = 0;
        ListNode *head = nullptr, *p = nullptr;
        for ( ; i >= 0 || j >= 0 || carry > 0; i--, j--) {
            sum = carry;
            if (i >= 0) {
                sum += n1[i];
            }
            if (j >= 0) {
                sum += n2[j];
            }
            carry = sum / 10;
            p = new ListNode(sum % 10);
            p->next = head;
            head = p;
        }
        return head;
    }
};

// 448. Find All Numbers Disappeared in an Array
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int len = nums.size();
        for (int i = 0; i < len; i++) {
            int n = abs(nums[i]) - 1;
            nums[n] = nums[n] > 0 ? -nums[n] : nums[n];
        }
        vector<int> res;
        for (int i = 0; i < len; i++) {
            if (nums[i] > 0) {
                res.push_back(i + 1);
            }
        }
        return res;
    }
};

// 449. Serialize and Deserialize BST
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) {
            return "";
        }
        return to_string(root->val) + "-" + serialize(root->left) + serialize(root->right);
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        string item;
        TreeNode* r = nullptr;
        while (getline(ss, item, '-')) {
            r = insert(r, stoi(item));
        }
        return r;
    }
private:
    TreeNode* insert(TreeNode* r, int v) {
        if (!r) {
            return new TreeNode(v);
        }
        if (v <= r->val) {
            r->left = insert(r->left, v);
        } else {
            r->right = insert(r->right, v);
        }
        return r;
    }
};
// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;

// 450. Delete Node in a BST
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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) {
            return root;
        } else if (root->val > key) {
            root->left = deleteNode(root->left, key);
        } else if (root->val < key) {
            root->right = deleteNode(root->right, key);
        } else {
            if (!root->right) {
                return root->left;
            } else if (!root->left) {
                return root->right;
            } else {
                root->val = findMin(root->right);
                root->right = deleteNode(root->right, root->val);
            }
        }
        return root;
    }
private:
    int findMin(TreeNode* r) {
        while (r->left) {
            r = r->left;
        }
        return r->val;
    }
};

// 451. Sort Characters By Frequency
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> m;
        vector<string> bucket(s.size() + 1, "");
        string res;
        for (char c : s) {
            m[c]++;
        }
        for (auto& it : m) {
            char c = it.first;
            int n = it.second;
            bucket[n].append(n, c);
        }
        for (int i = s.size(); i > 0; i--) {
            if (!bucket[i].empty()) {
                res.append(bucket[i]);
            }
        }
        return res;
    }
};

// 453. Minimum Moves to Equal Array Elements
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int m = INT_MAX;
        for (int n : nums) {
            m = min(m, n);
        }
        int res = 0;
        for (int n : nums) {
            res += n - m;
        }
        return res;
    }
};

// 454. 4Sum II
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        map<int, int> m;
        for (int k : nums3) {
            for (int l : nums4) {
                m[k + l]++;
            }
        }
        int res = 0;
        for (int i : nums1) {
            for (int j : nums2) {
                res += m[-(i + j)];
            }
        }
        return res;
    }
};

// 455. Assign Cookies
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        qSort(g, 0, g.size() - 1);
        qSort(s, 0, s.size() - 1);
        int i = 0, j = 0;
        while (i < g.size() && j < s.size()) {
            if (s[j] >= g[i]) {
                i++;
            }
            j++;
        }
        return i;
    }
    void qSort(vector<int>& v, int left, int right) {
        if (left >= right) {
            return;
        }
        int p = left;
        swap(v[(left + right) / 2], v[right]);
        for (int i = left; i < right; i++) {
            if (v[i] < v[right]) {
                swap(v[i], v[p++]);
            }
        }
        swap(v[p], v[right]);
        qSort(v, left, p - 1);
        qSort(v, p + 1, right);
    }
};

// 459. Repeated Substring Pattern
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int i = 1, j = 0, n = s.size();
        vector<int> dp(n + 1, 0);
        while (i < s.size()) {
            if (s[i] == s[j]) {
                dp[++i] = ++j;
            } else if (j == 0) {
                i++;
            } else {
                j = dp[j];
            }
        }
        return dp[n] && dp[n] % (n - dp[n]) == 0;
    }
};

// 461. Hamming Distance
class Solution {
public:
    int hammingDistance(int x, int y) {
        int z = x ^ y;
        int res = 0;
        while (z > 0) {
            res += z & 1;
            z >>= 1;
        }
        return res;
    }
};

// 462. Minimum Moves to Equal Array Elements II
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int n = nums.size(), res = 0;
        qSort(nums, 0, n - 1);
        int m = nums[n / 2];
        for (int i = 0; i < n; i++) {
            res += abs(nums[i] - m);
        }
        return res;
    }
    void qSort(vector<int>& v, int l, int r) {
        if (l >= r) {
            return;
        }
        int p = l;
        swap(v[(l + r) / 2], v[r]);
        for (int i = l; i < r; i++) {
            if (v[i] < v[r]) {
                swap(v[p++], v[i]);
            }
        }
        swap(v[p], v[r]);
        qSort(v, l, p - 1);
        qSort(v, p + 1, r);
    }
};

// 463. Island Perimeter
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int res = 0, n = grid.size(), m = grid[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!grid[i][j]) {
                    continue;
                }
                if ((j > 0 && !grid[i][j - 1]) || j == 0) {
                    res++;
                }
                if ((i > 0 && !grid[i - 1][j]) || i == 0) {
                    res++;
                }
                if ((j < m - 1 && !grid[i][j + 1]) || j == m - 1) {
                    res++;
                }
                if ((i < n - 1 && !grid[i + 1][j]) || i == n - 1) {
                    res++;
                }
            }
        }
        return res;
    }
};

// 476. Number Complement
class Solution {
public:
    int findComplement(int num) {
        unsigned int mask = ~0;
        while (mask & num) {
            mask <<= 1;
        }
        return ~mask & ~num;
    }
};

// 477. Total Hamming Distance
class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        if (nums.size() <= 0) {
            return 0;
        }
        int res = 0;
        for (int i = 0; i < 32; i++) {
            int setCount = 0;
            for (int j = 0; j < nums.size(); j++) {
                if (nums[j] & (1 << i)) {
                    setCount++;
                }
            }
            res += setCount * (nums.size() - setCount);
        }
        return res;
    }
};

// 485. Max Consecutive Ones
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int res = 0, tmp = 0;
        for (int n : nums) {
            if (n == 0) {
                tmp = 0;
                continue;
            }
            res = max(res, ++tmp);
        }
        return res;
    }
};

// 491. Increasing Subsequences
class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> tmp;
        recursive(res, nums, tmp, 0);
        return res;
    }
    void recursive(vector<vector<int>>& res, vector<int>& nums, vector<int> tmp, int start) {
        if (tmp.size() > 1) {
            res.push_back(tmp);
        }
        unordered_set<int> h;
        for (int i = start; i < nums.size(); i++) {
            if ((tmp.empty() || tmp.back() <= nums[i]) && h.find(nums[i]) == h.end()) {
                tmp.push_back(nums[i]);
                recursive(res, nums, tmp, i + 1);
                tmp.pop_back();
                h.insert(nums[i]);
            }
        }
    }
};

// 492. Construct the Rectangle
class Solution {
public:
    vector<int> constructRectangle(int area) {
        int a = sqrt(area);
        while (area % a) {
            a--;
        }
        return {area / a, a};
    }
};

// 494. Target Sum
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int res = 0;
        recursive(nums, target, 0, 0, res);
        return res;
    }

    void recursive(vector<int>& nums, int target, int i, int tmp, int& res) {
        if (i >= nums.size()) {
            if (target == tmp) {
                res++;
            }
            return;
        }
        recursive(nums, target, i + 1, tmp + nums[i], res);
        recursive(nums, target, i + 1, tmp + -nums[i], res);
    }
};

// 495. Teemo Attacking
class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        int res = 0;
        for (int i = 0; i < timeSeries.size() - 1; i++) {
            if (timeSeries[i + 1] - timeSeries[i] < duration) {
                res += timeSeries[i + 1] - timeSeries[i];
            } else {
                res += duration;
            }
        }
        return res + duration;
    }
};

// 496. Next Greater Element I
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> m;
        stack<int> s;
        for (int n : nums2) {
            while (!s.empty() && s.top() < n) {
                m[s.top()] = n;
                s.pop();
            }
            s.push(n);
        }
        vector<int> res;
        for (int n : nums1) {
            res.push_back(m.count(n) ? m[n] : -1);
        }
        return res;
    }
};

// 498. Diagonal Traverse
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<int> res;
        for (int s = 0; s <= m + n - 2; s++) {
            for (int x = 0; x <= s; x++) {
                int i = x;
                int j = s - i;
                if (s % 2 == 0) {
                    swap(i, j);
                }
                if (i >= m || j >= n) {
                    continue;
                }
                res.push_back(mat[i][j]);
            }
        }
        return res;
    }
};

// 500. Keyboard Row
class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        vector<int> dict(26);
        vector<string> rows = {"QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"};
        for (int i = 0; i < rows.size(); i++) {
            for (auto c : rows[i]) {
                dict[c - 'A'] = 1 << i;
            }
        }
        vector<string> res;
        for (auto w : words) {
            int r = 7;
            for (char c : w) {
                r &= dict[toupper(c) - 'A'];
                if (r == 0) {
                    break;
                }
            }
            if (r) {
                res.push_back(w);
            }
        }
        return res;
    }
};

// 501. Find Mode in Binary Search Tree
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
private:
    int max = 0, cur = 0, pre = INT_MIN;
public:
    vector<int> findMode(TreeNode* root) {
        vector<int> res;
        recursive(root, res);
        return res;
    }
    void recursive(TreeNode* r, vector<int>& res) {
        if (!r) {
            return;
        }
        recursive(r->left, res);
        if (pre == r->val) {
            cur++;
        } else {
            cur = 1;
        }
        if (cur > max) {
            res.clear();
            max = cur;
            res.push_back(r->val);
        } else if (cur == max) {
            res.push_back(r->val);
        }
        pre = r->val;
        recursive(r->right, res);
    }
};

// 504. Base 7
class Solution {
public:
    string convertToBase7(int num) {
        int x = abs(num);
        string res;
        do {
            res = to_string(x % 7) + res;
        } while (x /= 7);
        return (num >= 0 ? "" : "-") + res;
    }
};

// 506. Relative Ranks
class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        vector<int> c = score;
        qSort(c, 0, c.size() - 1);
        unordered_map<int, int> rank;
        for (int i = 0; i < c.size(); i++) {
            rank[c[i]] = i + 1;
        }
        vector<string> res;
        for (int i = 0; i < score.size(); i++) {
            int v = score[i];
            if (rank[v] == 1) {
                res.push_back("Gold Medal");
            } else if (rank[v] == 2) {
                res.push_back("Silver Medal");
            } else if (rank[v] == 3) {
                res.push_back("Bronze Medal");
            } else {
                res.push_back(to_string(rank[v]));
            }
        }
        return res;
    }
    void qSort(vector<int>& v, int left, int right) {
        if (left >= right) {
            return;
        }
        int p = left;
        swap(v[(left + right) / 2], v[right]);
        for (int i = left; i < right; i++) {
            if (v[i] > v[right]) {
                swap(v[p++], v[i]);
            }
        }
        swap(v[p], v[right]);
        qSort(v, left, p - 1);
        qSort(v, p + 1, right);
    }
};

// 508. Most Frequent Subtree Sum
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
    vector<int> findFrequentTreeSum(TreeNode* root) {
        unordered_map<int, int> m;
        vector<int> res;
        recursive(m, root);
        int max = 0;
        for (auto v : m) {
            if (v.second < max) {
                continue;
            } else if (v.second > max) {
                res.clear();
                max = v.second;
            }
            res.push_back(v.first);
        }
        return res;
    }
    int recursive(unordered_map<int, int>& m, TreeNode* root) {
        if (!root) {
            return 0;
        }
        int sum = root->val + recursive(m, root->left) + recursive(m, root->right);
        m[sum]++;
        return sum;
    }
};

// 509. Fibonacci Number
class Solution {
public:
    int fib(int n) {
        if (n == 0) {
            return n;
        }
        vector<int> dp(n + 1, 0);
        dp[0] = 0, dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};

// 513. Find Bottom Left Tree Value
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
    int findBottomLeftValue(TreeNode* root) {
        int res = root->val, max = 0;
        recursive(root, 1, max, res);
        return res;
    }
    void recursive(TreeNode* r, int depth, int& max, int& res) {
        if (r == nullptr) {
            return;
        }
        if (r->left && depth > max) {
            max = depth, res = r->left->val;
        } else if (r->right && depth > max) {
            max = depth, res = r->right->val;
        }
        recursive(r->left, depth + 1, max, res);
        recursive(r->right, depth + 1, max, res);
    }
};

// 515. Find Largest Value in Each Tree Row
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
    vector<int> largestValues(TreeNode* root) {
        vector<int> res;
        recursive(root, 1, res);
        return res;
    }
    void recursive(TreeNode* r, int level, vector<int>& res) {
        if (r == nullptr) {
            return;
        }
        if (res.size() < level) {
            res.push_back(INT_MIN);
        }
        res[level - 1] = r->val > res[level - 1] ? r->val : res[level - 1];
        recursive(r->left, level + 1, res);
        recursive(r->right, level + 1, res);
    }
};

// 516. Longest Palindromic Subsequence
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        string t = s;
        reverse(t.begin(), t.end());
        int dp[n + 1][n + 1];
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
            dp[0][i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[n][n];
    }
};

// 518. Coin Change 2
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int dp[5001] = {1};
        for (auto c : coins) {
            for (auto i = c; i <= amount; i++) {
                dp[i] += dp[i - c];
            }
        }
        return dp[amount];
    }
};

// 520. Detect Capital
class Solution {
public:
    bool detectCapitalUse(string word) {
        for (int i = 1; i < word.size(); i++) {
            if ((isUpper(word[1]) != isUpper(word[i])) ||
                (!isUpper(word[0]) && isUpper(word[i]))) {
                return false;
            }
        }
        return true;
    }
    bool isUpper(char c) {
        return 'A' <= c && c <= 'Z';
    }
};

// 525. Contiguous Array
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> m;
        m[0] = -1;
        int sum = 0, res = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i] == 0 ? -1 : 1;
            if (m.find(sum) != m.end()) {
                if (res < i - m[sum]) {
                    res = i - m[sum];
                }
            } else {
                m[sum] = i;
            }
        }
        return res;
    }
};

// 530. Minimum Absolute Difference in BST
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
    int getMinimumDifference(TreeNode* root) {
        int prev = INT_MAX, res = INT_MAX;
        recursive(root, prev, res);
        return res;
    }
    void recursive(TreeNode* r, int& prev, int& res) {
        if (r == nullptr) {
            return;
        }
        recursive(r->left, prev, res);
        res = min(res, abs(r->val - prev));
        prev = r->val;
        recursive(r->right, prev, res);
    }
};

// 532. K-diff Pairs in an Array
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        for (auto n : nums) {
            m[n]++;
        }
        int res = 0;
        for (auto v : m) {
            if (k == 0) {
                if (v.second > 1) {
                    res++;
                }
            } else {
                if (m.find(v.first + k) != m.end()) {
                    res++;
                }
            }
        }
        return res;
    }
};

// 535. Encode and Decode TinyURL
class Solution {
private:
    unordered_map<string, string> ltos;
    unordered_map<string, string> stol;
    uint64_t hash(const string& s) {
        uint64_t h = 0x811c9dc5;
        uint64_t p = 0x1000193;
        for (int i = 0; i < s.size(); i++) {
            uint8_t v = s[i];
            h = h ^ v;
            h *= p;
        }
        return h;
    }
public:

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        ltos[longUrl] = "http://tinyurl.com/" + to_string(hash(longUrl));
        stol[ltos[longUrl]] = longUrl;
        return ltos[longUrl];
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return stol[shortUrl];
    }
};
// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));

// 538. Convert BST to Greater Tree
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
    TreeNode* convertBST(TreeNode* root) {
        int sum = 0;
        recursive(root, sum);
        return root;
    }
    void recursive(TreeNode* r, int& sum) {
        if (r == nullptr) {
            return;
        }
        recursive(r->right, sum);
        sum += r->val;
        r->val = sum;
        recursive(r->left, sum);
    }
};
