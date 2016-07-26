#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int mod1 = 1e9 + 409;
const int mod2 = 1e9 + 433;
 
int n, m;
string s[205];
int com[205][205];
 
struct adj{
    lint adj[205][205];
    void init(){
        memset(adj, 0x3f, sizeof(adj));
    }
};
 
adj gob(adj a, adj b){
    adj c;
    c.init();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<n; k++){
                c.adj[i][j] = min(c.adj[i][j], a.adj[i][k] + b.adj[k][j]);
            }
        }
    }
    return c;
}
 
lint h1[100005], h2[100005], p1[100005], p2[100005];
char t[100005];
int l, ps[205];
 
lint query(int s, int l){
    int e = s + l - 1;
    lint v1 = h1[e] - (s ? h1[s-1] : 0) * p1[e - s + 1];
    lint v2 = h2[e] - (s ? h2[s-1] : 0) * p2[e - s + 1];
    v1 = v1 % mod1 + mod1;
    v2 = v2 % mod2 + mod2;
    v1 %= mod1, v2 %= mod2;
    return v1 * mod2 + v2;
}
 
void make_hash(){
    p1[0] = p2[0] = 1;
    for(int i=1; i<=l; i++){
        p1[i] = p1[i-1] * 257 % mod1;
        p2[i] = p2[i-1] * 257 % mod2;
    }
    for(int i=0; i<l; i++){
        h1[i] = (i ? h1[i-1] : 0) * 257 + t[i];
        h2[i] = (i ? h2[i-1] : 0) * 257 + t[i];
        h1[i] %= mod1;
        h2[i] %= mod2;
    }
}
 
int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++){
        cin >> s[i];
        for(int j=0; j<s[i].size(); j++){
            t[l++] = s[i][j];
        }
        ps[i] = s[i].size() + (i ? ps[i-1] : 0);
    }
    make_hash();
    if(m == 1){
        int ret = 1e9;
        for(int i=0; i<n; i++){
            ret = min(ret, (int)s[i].size());
        }
        cout << ret;
        return 0;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int l = min(s[i].size(), s[j].size());
            if(i == j) l--;
            int ps1 = (i ? ps[i-1] : 0), ps2 = (j ? ps[j-1] : 0);
            while(l > 0 && query(ps1 + s[i].size() - l, l) != query(ps2, l)){
                l--;
            }
            com[i][j] = s[j].size() - l;
        }
    }
    adj ret, piv;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            piv.adj[i][j] = com[i][j];
        }
    }
    ret = piv;
    int p = m-2;
    while(p){
        if(p&1) ret = gob(ret, piv);
        piv = gob(piv, piv);
        p >>= 1;
    }
    lint dap = 1e18;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            dap = min(dap, ret.adj[i][j] + (int)s[i].size());
        }
    }
    cout << dap;
}