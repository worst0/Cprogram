/*************************************************************************
	> File Name: test.cpp
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年11月09日 星期一 19时58分13秒
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
#define MOD 100003
#define MAX_N 1000000
#define MAX_M 1000000

struct Edge {
    int v, next;
};

struct Node {
    int now, dist;
    bool operator<(const struct Node &b) const {
        return this->dist > b.dist;
    }
};

int head[MAX_N + 5], cnt[MAX_N + 5], dist[MAX_N + 5];
int n, m, mcnt;
Edge e[MAX_M + 5];
priority_queue<Node> que;

inline void addEdge(int u, int v) {
    e[++mcnt].v = v;
    e[mcnt].next = head[u];
    head[u] = mcnt;
    return ;
}

int main() {
    memset(dist, 0x3f, sizeof(dist));
    memset(head, -1, sizeof(head));
    cin >> n >> m;
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        addEdge(a, b);
        addEdge(b, a);
    }
    que.push((Node){1, 0});
    dist[1] = 0;
    cnt[1] = 1;
    while (!que.empty()) {
        Node tmp = que.top();
        que.pop();
        if (tmp.dist > dist[tmp.now]) {
            continue;
        }
        int u = tmp.now;
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                cnt[v] = cnt[u];
                que.push((Node){v, dist[v]});
            } else if (dist[v] == dist[u] + 1) {
                cnt[v] += cnt[u];
                cnt[v] %= MOD;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << cnt[i] << endl;
    }
    return 0;
}
