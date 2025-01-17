/*************************************************************************
	> File Name: oj-256.cpp
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年03月11日 星期四 08时38分42秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;
#define MAX_N 1000

struct Data {
    int a, b;
    bool operator<(const Data &obj) const {
        return a * b < obj.a * obj.b;
    }
};

struct BigInt {
    BigInt(int x) {
        num.push_back(x);
        process_digit();
    }
    BigInt(vector<int> res) : num(res) {}
    void process_digit() {
        for (int i = 0; i < num.size(); i++) {
            if (num[i] < 10) continue;
            if (i + 1 == num.size()) num.push_back(0);
            num[i + 1] += num[i] / 10;
            num[i] %= 10;
        }
        return ;
    }
    
    BigInt operator/(int x) {
        int i = num.size(), temp = 0;
        while (i && temp * 10 + num[i - 1] < x) temp = temp * 10 + num[--i];
        if (!i) return BigInt(0);
        vector<int> res(i);
        while (i) {
            temp = temp * 10 + num[i - 1];
            res[i - 1] = temp / x;
            temp %= x;
            i--;
        }
        return BigInt(res);
    }

    bool operator>(const BigInt &obj) {
        if (num.size() - obj.num.size()) {
            return num.size() > obj.num.size();
        }
        for (int i = num.size() - 1; i >= 0; i--){
            if (num[i] - obj.num[i]) {
                return num[i] > obj.num[i];
            }
            return false;
        }
        return false;
    }

    void operator*=(int x) {
        for (int i = 0; i < num.size(); i++) {
            num[i] *= x;
        }
        process_digit();
        return ;
    }

    vector<int> num;
};

ostream &operator<<(ostream &out, const BigInt &obj) {
    for (int i = obj.num.size() - 1; i >= 0; i--) {
        out << obj.num[i];
    }
    return out;
}

int main() {
    vector<Data> arr;
    int n;
    cin >> n;
    for (int i = 0, a, b; i <= n; i++) {
        cin >> a >> b;
        arr.push_back({a, b});
    }
    sort(arr.begin() + 1, arr.end());
    BigInt p = arr[0].a, ans = 0;
    for (int i = 1; i <= n; i++) {
        if (p / arr[i].b > ans) {
            ans = p / arr[i].b;
        }
        p *= arr[i].a;
    }
    cout << ans << endl;
    return 0;
}
