/*************************************************************************
	> File Name: oj-480.cpp
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年09月08日 星期二 20时10分37秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    char s[3];
    int num1, num2, flag;
};

struct Node x[15];

int main() {
    for (int i = 0; cin >> x[i].s; ++i) {
        if (x[i].s[0] == '/') {
            x[i].num1 = 10;
            x[i].num2 = 10;
            x[i].flag = 2;
        } else if (x[i].s[1] == '/') {
            x[i].num1 = x[i].s[0] - '0';
            x[i].num2 = 10;
            x[i].flag = 1;
        } else {
            x[i].num1 = x[i].s[0] - '0';
            x[i].num2 = x[i].s[1] - '0' + x[i].num1;
        }
    }
    int ans = 0;
    for (int i = 0; i < 10; ++i) {
        ans += x[i].num2;
        if (x[i].flag == 1) {
            ans += x[i + 1].num1;
        } else if (x[i].flag == 2) {
            if (x[i + 1].flag == 2) {
                ans += 10 + x[i + 2].num1;
            } else {
                ans += x[i + 1].num2;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
