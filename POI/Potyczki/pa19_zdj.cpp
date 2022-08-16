#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 300005;

int dp[MAXN];
vector<int> gph[MAXN];
int idx[MAXN];
priority_queue<int> pq[MAXN];

void dfs(int x){
    for(auto &y : gph[x]){
        dfs(y);
        if(sz(pq[idx[x]]) < sz(pq[idx[y]])){
            swap(idx[x], idx[y]);
        }
        while(sz(pq[idx[y]])){
            int z = pq[idx[y]].top();
            pq[idx[y]].pop();
            pq[idx[x]].push(z);
        }
    }
    int z = 1;
    if(sz(pq[idx[x]])) z += pq[idx[x]].top(), pq[idx[x]].pop();
    if(sz(pq[idx[x]])) z += pq[idx[x]].top(), pq[idx[x]].pop();
    pq[idx[x]].push(z);
}

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    iota(idx, idx + n + 1, 0);
    for(int i = 2; i <= n; i++){
        int p;
        cin >> p;
        gph[p].push_back(i);
    }
    dfs(1);
    cout << pq[idx[1]].top() << "\n";
}
