#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5005;

vector<int> gph[MAXN];
int n;

void dfs(int x, int p, int d){
    if(d % 2 == 0) printf("%d\n", x);
    for(auto &i : gph[x]){
        if(i != p){
            dfs(i, x, d + 1);
        }
    }
    if(d % 2 == 1) printf("%d\n", x);
}

int main(){
    cin >> n;
    for(int i=1; i<n; i++){
        int s, e;
        cin >> s >> e;
        gph[s].push_back(e);
        gph[e].push_back(s);
    }
    dfs(1, 0, 0);
}

