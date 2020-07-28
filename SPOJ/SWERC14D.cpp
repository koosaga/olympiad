// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SWERC14D/
#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 1e4 + 10;
 
vector<int> G[MAXN];
int match[MAXN],vis[MAXN],iteracao,N,M;
 
int bpm(int v){
    if(vis[v] == iteracao) return 0;
    vis[v] = iteracao;
    for(int u : G[v]){
        if(match[u] == -1 || bpm(match[u])){
            match[u] = v;
            return 1;
        }
    }
    return 0;
}
 
int main(){
    cin >> N >> M;
    memset(match,-1,sizeof(match));
    for(int i = 1;i<=M;i++){
        int u,v;
        cin >> u >> v;
        G[u].push_back(v);
    }
    for(int i = 0;i<N;i++){
        iteracao++;
        if(bpm(i) == 0){
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    return 0;
} 
