#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
typedef pair<int, int> pi;
typedef long long lint;
typedef unsigned long long hash_t;

int n, m, c;
int dfn[MAXN], low[MAXN], piv;
vector<int> bcc[MAXN], cmp[MAXN];
vector<int> gph[MAXN];

void Init(){
    piv = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    for(int i=1; i<=n; i++) cmp[i].clear();
}

void dfs(int x, int p){
    dfn[x] = low[x] = ++piv;
    for(auto &i : gph[x]){
        if(i == p) continue;
        if(dfn[i] == 0){
            dfs(i, x);
            low[x] = min(low[x], low[i]);
        }
        else low[x] = min(low[x], dfn[i]);
    }
}

void color(int x, int p){
    if(p){
        bcc[p].push_back(x);
        cmp[x].push_back(p);
    }
    for(auto &i : gph[x]){
        if(cmp[i].size()) continue;
        if(low[i] >= dfn[x]){
            bcc[++c].push_back(x);
            cmp[x].push_back(c);
            color(i, c);
        }
        else color(i, p);
    }
}

int sz[MAXN], szm[MAXN];

int find_cen(int x){
    int sum = 0;
    for(int i=1; i<bcc[x].size(); i++){
        int p = bcc[x][i];
        int vsum = 1;
        for(auto &j : cmp[p]){
            if(x != j){
                int v = find_cen(j);
                sz[p] = max(sz[p], v);
                vsum += v;
            }
        }
        sum += vsum;
        szm[x] = max(szm[x], vsum);
        sz[p] = max(sz[p], n - vsum);
    }
    szm[x] = max(szm[x], n - sum);
    return sum;
}

void add_factor(int x);
const hash_t prm = 1e9 + 409;
const hash_t prm2 = 1e9 + 433;
const hash_t mgc = 199807161;
const hash_t mgc4 = 949494949;
const hash_t mgc2 = 140043;
const hash_t mgc3 = 98011;

void apply_to_ans(vector<hash_t> &v){
    sort(v.begin(), v.end());
    for(int i=0; i<v.size(); ){
        int e = i;
        while(e < v.size() && v[i] == v[e]) e++;
        for(int j=1; j<e-i; j++){
            add_factor(j + 1);
        }
        i = e;
    }
}

hash_t point_merge(vector<hash_t> &v, hash_t CC){
    sort(v.begin(), v.end());
    hash_t ans = 0;
    auto fu = prm + CC * mgc2 * 2;
    for(int i=0; i<v.size(); i++){
        ans = ans * fu + v[i];
    }
    ans ^= mgc + CC * mgc2;
    return ans;
}

pair<hash_t, int> cdfs(int x){
    vector<hash_t> cyc;
    int rr = 0;
    for(int i=1; i<bcc[x].size(); i++){
        int p = bcc[x][i];
        vector<hash_t> hv;
        int subsz = 1;
        for(auto &j : cmp[p]){
            if(x != j){
                auto ret = cdfs(j);
                hv.push_back(ret.first);
                subsz += ret.second;
            }
        }
        apply_to_ans(hv);
        cyc.push_back(point_merge(hv, subsz));
        rr += subsz;
    }
    auto fu = prm2 + rr * mgc3 * 2;
    hash_t ans = 0;
    for(int i=0; i<cyc.size(); i++){
        ans = ans * fu + cyc[i];
    }
    ans ^= mgc4 + rr * mgc3;
    return make_pair(ans, rr);
}

hash_t Do_root(int r){
    for(int i=1; i<=c; i++){
        bcc[i].clear();
    }
    c = 0;
    dfs(r, -1);
    color(r, 0);
    vector<hash_t> hv;
    int cc = 0;
    for(auto &i : cmp[r]){
        auto k = cdfs(i);
        hv.push_back(k.first);
        cc += k.second;
    }
    apply_to_ans(hv);
    return point_merge(hv, cc + 1);
}

lint ans = 1;
const int mod = 998244353;

void add_factor(int x){
    ans *= x;
    ans %= mod;
}

void print(){
    cout << ans << endl;
}

int main(){
    scanf("%d",&n);
    for(int i=1; i<n; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        gph[s].push_back(e);
        gph[e].push_back(s);
    }
    dfs(1, -1);
    color(1, 0);
    for(auto &i : cmp[1]){
        sz[1] = max(sz[1], find_cen(i));
    }
    for(int i=1; i<=n; i++){
        if(sz[i] < (n + 1)/ 2){
            Init();
            Do_root(i);
            print();
            return 0;
        }
    }
    pi wedge(-1, -1);
    for(int i=1; i<=n; i++){
        if(n % 2 == 0 && sz[i] == n / 2){
            for(auto &j : gph[i]){
                if(sz[j] == n / 2){
                    wedge = pi(i, j);
                }
            }
        }
    }
    if(wedge.first != -1){
        int s = wedge.first;
        int e = wedge.second;
        gph[s].erase(find(gph[s].begin(), gph[s].end(), e));
        gph[e].erase(find(gph[e].begin(), gph[e].end(), s));
        Init();
        hash_t h1 = Do_root(s);
        hash_t h2 = Do_root(e);
        if(h1 == h2) add_factor(2);
        print();
        return 0;
    }
}

