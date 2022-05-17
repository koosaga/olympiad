#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;
const int mod = 1e9 + 7;
 
int n, p[MAXN], dep[MAXN], cnt[MAXN];
vector<int> gph[MAXN];

int sz[MAXN], rev[MAXN];
int din[MAXN], dout[MAXN], chn[MAXN], piv;

void hld(int x){
    din[x] = ++piv;
    rev[din[x]] = x;
    if(sz(gph[x])){
        chn[gph[x][0]] = chn[x];
        hld(gph[x][0]);
        for(int i = 1; i < sz(gph[x]); i++){
            chn[gph[x][i]] = gph[x][i];
            hld(gph[x][i]);
        }
    }
    dout[x] = piv;
}

struct bit{
    int tree[MAXN];
    void add(int x, int v){
        x += 2;
        for(int i = x; i < MAXN; i += i & -i) tree[i] += v;
    }
    int query(int x){
        x += 2;
        int ret = 0;
        for(int i = x; i; i -= i & -i) ret += tree[i];
        return ret;
    }
}bit;

set<int> cnd;

pi forward(int x){
    int y = x;
    while(true){
        int nxt = chn[x];
        auto ll = cnd.lower_bound(din[x]);
        while(ll != cnd.begin()){
            ll--;
            if(*ll < din[nxt]) break;
            x = rev[*ll + 1];
            if(bit.query(din[x]) != bit.query(din[p[x]])){
                return pi(x, dep[y] - dep[x]);
            }
            else ll = cnd.erase(ll);
        }
        x = chn[x];
        if(x == 0) break;
        if(bit.query(din[x]) == bit.query(din[p[x]])){
            x = p[x];
        }
        else break;
    }
    return pi(x, dep[y] - dep[x]);
}

void witness(int v){
    if(v == -1) return;
    if(cnd.find(din[v]) != cnd.end()) cnd.erase(din[v]);
    if(bit.query(din[v]) != bit.query(din[v] + 1)) cnd.insert(din[v]);
}

void add_until(int s, int e, int x){
    if(s == -1) return;
    if(e == -1) e = 0;
    while(chn[s] != chn[e]){
        bit.add(din[chn[s]], +x);
        bit.add(din[s] + 1, -x);
        witness(s);
        s = p[chn[s]];
    }
    bit.add(din[e], +x);
    bit.add(din[s] + 1, -x);
    witness(p[e]);
    witness(s);
}

int main(){
    scanf("%d",&n);
    p[0] = -1;
    for(int i = 1; i <= n; i++){
        scanf("%d",&p[i]);
        dep[i] = dep[p[i]] + 1;
        gph[p[i]].push_back(i);
    }
    for(int i = n; i; i--){
        sz[i]++;
        if(~p[i]) sz[p[i]] += sz[i];
        sort(all(gph[i]), [&](const int &a, const int &b){
            return sz[a] > sz[b];
        });
    }
    hld(0);
    for(int i = 0; i <= n; i++){
        if(dep[i] % 2 == 1){
            bit.add(din[i], +1);
            bit.add(din[i] + 1, -1);
        }
        if(i) cnd.insert(din[i]);
    }
    for(int i = 1; i <= n; i++){
        int ans = 0;
        if(dep[i] % 2){
            int j = i;
            if(bit.query(din[p[j]]) == 0){
                tie(j, ans) = forward(p[j]);
                ans++;
            }
            add_until(p[i], p[j], 1);
        }
        else{
            int j = i;
            if(bit.query(din[p[j]]) == 1){
                tie(j, ans) = forward(p[j]);
                ans++;
            }
            add_until(p[i], p[j], -1);
        }
        printf("%d\n", ans);
    }
}

