#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;
const int MAXN = 300005;

int trie[MAXN][100], piv;
int sub[MAXN], S[MAXN], T[MAXN];

void dfs(int x, int y){
    if(y == 3) T[x] = sub[x] * 600;
    if(y == 2) S[x] = sub[x] * 8;
    for(int i = 0; i < 100; i++){
        if(trie[x][i]){
            dfs(trie[x][i], y + 1);
            T[x] = max(T[x], T[trie[x][i]]);
            S[x] = max(S[x], S[trie[x][i]]);
        }
    }
}

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        int s; cin >> s;
        int p = 0;
        for(int j = 0; j < 3; j++){
            sub[p]++;
            if(!trie[p][s % 100]){
                trie[p][s % 100] = ++piv;
            }
            p = trie[p][s % 100];
            s /= 100;
        }
        sub[p]++;
    }
    dfs(0, 0); 
    S[0] = T[0] = sub[0] = 0;

    int dap = 0;
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            if(i != j){
                vector<int> v;
                int ret = S[trie[0][i]] + T[trie[0][j]];
                for(int k = 0; k < 100; k++){
                    if(i != k && j != k) v.push_back(sub[trie[0][k]]);
                }
                sort(all(v));
                reverse(all(v));
                for(int i = 0; i < 3; i++) ret += v[i];
                dap = max(dap, ret);
            }
        }
    }
    cout << dap * 500 << "\n";
}
