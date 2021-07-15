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
