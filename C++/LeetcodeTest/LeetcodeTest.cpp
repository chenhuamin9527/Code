// LeetcodeTest.cpp: 定义应用程序的入口点。
//

#include "LeetcodeTest.h"
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ans = 0;
        string str = to_string(n);
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == '1') ans++;
        }
        return ans;
    }
};
int main()
{
    Solution solution;
    uint32_t n = 0x00000000000000000000000000001011;
    cout << solution.hammingWeight(n);
	return 0;
}
