#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 205;
const int mod = 1e9 + 7;

vector<pi> gph[MAXN];
vector<pi> rev[MAXN];

struct node{
    int s, e, state;
    lint dist;
    bool operator<(const node &n)const{
        return dist > n.dist;
    }
};

lint dp[205][205][5];
int c2i[256];
int n, m, s, t;

int main(){
    {
        string s = "<>()[]{}";
        for(int i = 0; i < 8; i++) c2i[s[i]] = i;
    }
    scanf("%d %d %d %d",&n,&m,&s,&t);
    memset(dp, 0x3f, sizeof(dp));
    for(int i = 0; i < m; i++){
        int x, y; char s[7];
        scanf("%d %d %s",&x,&y,s);
        x--; y--;
        int j = c2i[s[0]];
        gph[x].emplace_back(j, y);
        rev[y].emplace_back(j, x);
    }
    priority_queue<node> pq;
    auto enq = [&](int s, int e, int state, lint d){
        if(dp[s][e][state] > d){
            dp[s][e][state] = d;
            pq.push({s, e, state, d});
        }
    };
    for(int i = 0; i < n; i++){
        enq(i, i, 0, 0);
    }
    while(sz(pq)){
        auto x = pq.top(); pq.pop();
        if(dp[x.s][x.e][x.state] != x.dist) continue;
        if(x.state){
            for(auto &[i, v] : gph[x.e]){
                if(i == 2 * x.state - 1){
                    enq(x.s, v, 0, x.dist + 1);
                }
            }
        }
        else{
            for(int i = 0; i < n; i++){
                enq(x.s, i, 0, x.dist + dp[x.e][i][0]);
                enq(i, x.e, 0, x.dist + dp[i][x.s][0]);
            }
            for(auto &[i, v] : rev[x.s]){
                if(i % 2 == 0) enq(v, x.e, i / 2 + 1, x.dist + 1);
            }
        }
    }
    lint ans = dp[s-1][t-1][0];
    if(ans > 1'000'000'000'000'000'000L) ans = -1;
    cout << ans << endl;
}
