/*************************************************************************
	> File Name: cd-61.cpp
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年11月12日 星期四 10时20分01秒
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
#include <unordered_set>
using namespace std;
#define MAX_N 100000

int matrix[MAX_N + 5][MAX_N + 5];
int n, area, lef, rig, up, dow;

unordered_set<string> se;

int solve() {
    scanf("%d", &n);
    for (int i = 0, x1,y1,x2,y2; i < n; ++i) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        matrix[x1][y1] += 1, matrix[x2][y2] += 1;
        if (i == 0) {
            lef = x1, rig = x2, dow = y1, up = y2;
        } else {
            lef = min(x1, lef), rig = max(x2, rig);
            dow = min(y1, dow), up = max(y2, up);
        }
        area += (x2 - x1) * (y2 - y1);
    }

    if (matrix[lef][dow] != 1 ||
        matrix[lef][up] != 1 ||
        matrix[rig][dow] != 1 ||
        matrix[rig][up] != 1 ){
        return false;        
    }
    

    return area == (rig - lef) * (up - dow);
}

int main() {
    int ans = solve();
    cout << (ans ? "Yes" : "No") << endl;
    return 0;
}
