#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 1000005;
const int MAXM = 5000005;

int m;
vector<int> gph[MAXM];
vector<int> rev[MAXM];
vector<int> dfn;
bool vis[MAXM];
int cmp[MAXM];

void dfs(int x){
    vis[x] = 1;
    for(auto &i : gph[x]) if(!vis[i]) dfs(i);
    dfn.push_back(x);
}

void rdfs(int x, int c){
    cmp[x] = c;
    for(auto &i : rev[x]) if(!cmp[i]) rdfs(i, c);
}

void get_scc(int n){
    for(int i=0; i<n; i++){
        if(!vis[i]){
            dfs(i);
        }
    }
    reverse(dfn.begin(), dfn.end());
    int c = 0;
    for(auto &i : dfn){
        if(!cmp[i]){
            rdfs(i, ++c);
        }
    }
}

int NOT(int x){
    if(x >= m) return x - m;
    return x + m;
}

void make_clause(int s, int e){
    if(s < 0) assert(0 <= (~s) && (~s) < m);
    else assert(0 <= s && s < m);
    if(e < 0) assert(0 <= (~e) && (~e) < m);
    else assert(0 <= e && e < m);
    if(s < 0) s = NOT(~s);
    if(e < 0) e = NOT(~e);
    gph[s].push_back(e);
    gph[NOT(e)].push_back(NOT(s));
    rev[e].push_back(s);
    rev[NOT(s)].push_back(NOT(e));
//  printf("%d %d %d\n", m, s, e);
}

bool satisfy(vector<bool> &ans){
    get_scc(2*m);
    for(int i=0; i<ans.size(); i++){
        if(cmp[i] == cmp[NOT(i)]) return false;
        if(cmp[i] > cmp[NOT(i)]) ans[i] = 1;
    }
    return true;
}

int n;
int trie[MAXN][2], piv;
vector<int> v[MAXN], w[MAXN];
int wb[MAXN];
char buf[MAXN];
vector<string> ans;

int main(){
    freopen("binary.in", "r", stdin);
    freopen("binary.out", "w", stdout);
    scanf("%d",&n);
    vector<int> tmp;
    for(int i=0; i<n; i++){
        scanf("%s",buf);
        ans.push_back(buf);
        int l = strlen(buf);
        int pos = find(buf, buf + l, '?') - buf;
        if(pos == l){
            int p = 0;
            for(int j=0; j<l; j++){
                if(!trie[p][buf[j] - '0']){
                    trie[p][buf[j] - '0'] = ++piv;
                }
                p = trie[p][buf[j] - '0'];
            }
            v[p].push_back(i);
            tmp.push_back(i);
        }
        else{
            buf[pos] = '0';
            int p = 0;
            for(int j=0; j<l; j++){
                if(!trie[p][buf[j] - '0']){
                    trie[p][buf[j] - '0'] = ++piv;
                }
                p = trie[p][buf[j] - '0'];
            }
            v[p].push_back(~i);
            buf[pos] = '1';
            p = 0;
            for(int j=0; j<l; j++){
                if(!trie[p][buf[j] - '0']){
                    trie[p][buf[j] - '0'] = ++piv;
                }
                p = trie[p][buf[j] - '0'];
            }
            v[p].push_back(i);
        }
    }
    m = n + piv;
    for(int i=1; i<=piv; i++){
        w[i].resize(v[i].size());
        wb[i] = n + i - 1;
        for(int j=0; j<w[i].size(); j++){
            w[i][j] = m++;
        }
    }
    for(auto &i : tmp) make_clause(~i, i);
    for(int i=1; i<=piv; i++){
        if(trie[i][0]) make_clause(wb[i], wb[trie[i][0]]);
        if(trie[i][1]) make_clause(wb[i], wb[trie[i][1]]);
        if(w[i].size()){
            make_clause(wb[i], w[i][0]);
            make_clause(wb[i], ~v[i][0]);
            for(int j=0; j+1<w[i].size(); j++){
                make_clause(w[i][j], w[i][j+1]);
                make_clause(w[i][j], ~v[i][j+1]);
            }
            if(trie[i][0]) make_clause(w[i].back(), wb[trie[i][0]]);
            if(trie[i][1]) make_clause(w[i].back(), wb[trie[i][1]]);
            for(int j=0; j<w[i].size(); j++){
                make_clause(v[i][j], w[i][j]);
            }
        }
    }
    vector<bool> ret(ans.size());
    if(!satisfy(ret)){
        puts("NO");
    }
    else{
        puts("YES");
        for(int i=0; i<ans.size(); i++){
            for(auto &j : ans[i]){
                if(j == '?'){
                    j = (int)ret[i] + '0';
                }
            }
            puts(ans[i].c_str());
        }
    }
}
