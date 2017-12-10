#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 10005;
typedef long long lint;

int n, m, k, deg[MAXN], col[MAXN];
vector<int> gph[MAXN];
queue<int> que;
vector<int> ord;

int main(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<m; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        gph[s].push_back(e);
        gph[e].push_back(s);
    }
    for(int i=1; i<=n; i++){
        deg[i] = gph[i].size();
        k = max(k, deg[i]);
    }
    if(k % 2 == 0) k++;
    for(int i=1; i<=n; i++){
        if(deg[i] < k) que.push(i);
    }
    while(!que.empty()){
        auto x = que.front();
        que.pop();
        ord.push_back(x);
        for(auto &i : gph[x]){
            if(deg[i] == k) que.push(i);
            deg[i]--;
        }
    }
    reverse(ord.begin(), ord.end());
    for(auto &i : ord){
        set<int> s;
        for(auto &j : gph[i]){
            if(col[j]) s.insert(col[j]);
        }
        for(int j=1; j<=k; j++){
            if(s.find(j) == s.end()){
                col[i] = j;
                break;
            }
        }
    }
    printf("%d\n", k);
    for(int i=1; i<=n; i++) printf("%d\n", col[i]);
}
