#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

int n, m;
vector<int> gph[MAXN];
int chk[MAXN];
int cnt = 0;

void solve(int x, int p, int parentHasIt = 0){
    assert(parentHasIt == 0 || chk[x] == 0);
    if(chk[x]) parentHasIt = 1;
    int leeway = 0;
    for(auto &i : gph[x]){
        if(i != p){
            if(!chk[i]) leeway++;
        }
    }
    if(leeway >= parentHasIt) cnt++;
    for(auto &i : gph[x]){
        if(i != p){
            int newLeeway = leeway - (chk[i] == 0);
            if(newLeeway == 0 && parentHasIt){
                if(!chk[i]) solve(i, x, 1);
            }
            else solve(i, x, 0);
        }
    }
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 0; i < n-1; i++){
        int s, e; scanf("%d %d",&s,&e);
        gph[s].push_back(e);
        gph[e].push_back(s);
    }
    while(m--){
        int x; scanf("%d",&x);
        chk[x] = 1;
    }
    solve(1, 0);
    cout << cnt << endl;
}
