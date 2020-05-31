/*************************************************************************
	> File Name: EP31.cpp
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年05月30日 星期六 14时10分49秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;
#define max_n 8
#define max_m 200

int f[2][max_m + 5];
int w[max_n + 5] = {1, 2, 5, 10, 20, 50, 100, 200};

int main() {
    for (int k = 0; k < max_n; ++k) {
        int i = k % 2;
        f[i][0] = 1;
        for (int j = 1; j <= max_m; ++j) {
            f[i][j] = f[i ^ 1][j];
            if (j >= w[k]) f[i][j] += f[i][j - w[k]];
        }
    }
    cout << f[(max_n - 1) % 2][max_m] << endl;
    return 0;
}
