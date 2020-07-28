// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SWERC14B/
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> ii;
 
const int MAXN = 1e4 + 10;
 
vector<ii> grafo[MAXN];
int N,M,processado[MAXN],dist[MAXN][2],menor_caminho;
ll tot;
 
void Dijsktra(int s,int id){
    memset(processado,0,sizeof(processado));
    priority_queue<ii, vector<ii>, greater<ii> > pq;
    pq.push(ii(0,s));
    while(!pq.empty()){
        int d = pq.top().first, v = pq.top().second;
        pq.pop();
        if(processado[v]) continue;
        processado[v] = 1;
        dist[v][id] = d;
        for(ii aresta : grafo[v]){
            if(!processado[aresta.first]) pq.push(ii(aresta.second + d,aresta.first));
        }
    }
}
 
int main(){
    scanf("%d %d",&N,&M);
    
    for(int i = 1;i<=M;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        grafo[u].push_back(ii(v,w));
        grafo[v].push_back(ii(u,w));
    }
 
    Dijsktra(0,0);
    Dijsktra(N-1,1);
 
    menor_caminho = dist[N-1][0];
 
    for(int i = 0;i<N;i++){
        for(ii aresta : grafo[i]){
            int j = aresta.first, peso = aresta.second;
            if(dist[i][0] + peso + dist[j][1]  == menor_caminho) tot += (ll)peso;
        }
    }
 
    printf("%lld\n",2LL*tot);
 
    return 0;
} 
