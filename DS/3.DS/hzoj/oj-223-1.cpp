/*************************************************************************
	> File Name: oj-223.cpp
	> Author: yanzhiwei
	> Mail: 1931248856@qq.com
	> Created Time: 2021年02月04日 星期四 14时30分16秒
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
#define MAX_N 10000
#define lc(ind) (ind << 1)
#define rc(ind) (ind << 1 | 1)
#define tag(ind) (tree[ind].tag)
#define sum(ind) (tree[ind].sum)
#define cnt(ind) (tree[ind].cnt)

struct node {
    long long sum, tag, cnt;
} tree[(MAX_N << 1) + 5];
int root = 0, cnt = 1;
long long arr[MAX_N + 5];
int getNode() { return cnt++; }

void DOWN(int ind) {
    if (tag(ind)) {
        tag(lc(ind)) += tag(ind);
        tag(rc(ind)) += tag(ind);
        sum(lc(ind)) += tag(ind) * cnt(lc(ind));
        sum(rc(ind)) += tag(ind) * cnt(rc(ind));
        tag(ind) = 0;
    }
    return ;
}

void UP(int ind) {
    sum(ind) = sum(lc(ind)) + sum(rc(ind));
    return ;
}

void build(int ind, int l, int r) {
    cnt(ind) = (r - l + 1);
    tag(ind) = 0;
    if (l == r) {
        sum(ind) = arr[l];
        return ;
    }
    int mid = (l + r) >> 1;
    build(lc(ind), l, mid);
    build(rc(ind), mid + 1, r);
    UP(ind);
    return ;
}

void modify(int ind, int x, int y, long long d, int l, int r) {
    if (x <= l && r <= y) {
        tree[ind].tag += d;
        tree[ind].sum += d * tree[ind].cnt;
        return ;
    }
    DOWN(ind);
    int mid = (l + r) >> 1;
    if (x <= mid) modify(lc(ind), x, y, d, l, mid);
    if (y > mid) modify(rc(ind), x, y, d, mid + 1, r);
    UP(ind);
    return ;
}

long long query(int ind, int x, int y, int l, int r) {
    if (x <= l && r <= y) {
        return sum(ind);
    }
    DOWN(ind);
    int mid = (l + r) >> 1;
    long long ans = 0;
    if (x <= mid) ans += query(lc(ind), x, y, l, mid);
    if (y > mid) ans += query(rc(ind), x, y, mid + 1, r);
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build(root, 1, n);
    for (int i = 0; i < m; i++) {
        long long a, b, c, d;
        cin >> a >> b >> c;
        if (a == 1) {
            cin >> d;
            modify(root, b, c, d, 1, n);
        } else {
            cout << query(root, b, c, 1, n) << endl;
        }
    }
    return 0;
}
