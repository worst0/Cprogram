/*************************************************************************
	> File Name: cdd-102.cpp
	> Author: yanzhiwei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年11月22日 星期日 20时22分41秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <queue>
#include <stack>
#include <map>
using namespace std;

int main() {
    int t, n, p, m;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) {
        scanf("%d%d%d", &n, &p, &m);
        cout <<  (n <= 1 ? 0 : 2 * n - 3) << endl;
    }

    return 0;
}
