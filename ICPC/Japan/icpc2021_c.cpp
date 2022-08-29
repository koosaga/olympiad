#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 505;

struct node{
    int s, e, x;
    bool operator<(const node &nd)const{
        return x > nd.x;
    }
};

int n;
int dist[MAXN][MAXN];
pi trk[MAXN][MAXN];

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<node> pq;
    string s; cin >> s;
    int n = sz(s);
    auto enq = [&](int u, int v, int d, pi t){
        if(dist[u][v] > d){
            dist[u][v] = d;
            trk[u][v] = pi(1e9, 1e9);
            pq.push({u, v, d});
        }
        if(dist[u][v] == d) trk[u][v] = min(trk[u][v], t);
    };
    enq(n, 0, 0, pi(-1, -1));
    auto advance = [&](int pos, int x, int y){
        if(x == 0){
            if(pos < n && s[pos] == '0' + y) return pos + 1;
            return -1;
        }
        if(y == 0) return pos;
        if(x > pos) return -1;
        if(pos + y > n) return -1;
        for(int i = pos; i < pos + y; i++){
            if(s[i - x] != s[i]) return -1;
        }
        return pos + y;
    };
    auto radvance = [&](int pos, int x, int y){
        if(x == 0){
            if(pos > 0 && s[pos - 1] == '0' + y) return pos - 1;
            return -1;
        }
        if(y == 0) return pos;
        if(x > pos - y) return -1;
        if(pos - y < 0) return -1;
        for(int i = pos - y; i < pos; i++){
            if(s[i - x] != s[i]) return -1;
        }
        return pos - y;
    };
    while(sz(pq)){
        auto x = pq.top(); pq.pop();
        if(dist[x.s][x.e] != x.x) continue;
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                int ns = radvance(x.s, i, j);
                int ne = advance(x.e, j, i);
                if(ns != -1 && ne != -1) enq(ns, ne, x.x + 2, pi(i, j));
            }
        }
    }
    assert(dist[0][n] < 1e8);
    string ans; ans.resize(dist[0][n]);
    pi j = pi(0, n);
    for(int i = 0; i < dist[0][n]; i += 2){
        pi prv = trk[j.first][j.second];
        j.first = advance(j.first, prv.first, prv.second);
        j.second = radvance(j.second, prv.second, prv.first);
        ans[i] = prv.first + '0';
        ans[i + 1] = prv.second + '0';
    }
    cout << ans << "\n";
}
