// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1469
#include <cstdio>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;
#define MAXN 700
set<int> grafo[MAXN];
int idade[MAXN],processado[MAXN],N,M,I;
int main(){
while(scanf("%d %d %d",&N,&M,&I)!= EOF){
for(int i=1;i<=N;i++) grafo[i].clear();
for(int i=1;i<=N;i++) scanf("%d",&idade[i]);
while(M--){
int u,v;
scanf("%d %d",&u,&v);
grafo[v].insert(u);
}
while(I--){
char op;
scanf(" %c",&op);
if(op == 'T'){
int a,b;
scanf("%d %d",&a,&b);
swap(grafo[a],grafo[b]);
for(int i=1;i<=N;i++){
int tem_a = grafo[i].count(a);
int tem_b = grafo[i].count(b);
if(tem_a == tem_b) continue;
if(tem_a){
grafo[i].erase(a);
grafo[i].insert(b);
}
if(tem_b){
grafo[i].erase(b);
grafo[i].insert(a);
}
}
}
else{
int davez;
scanf("%d",&davez);
queue<int> bfs;
for(int i=1;i<=N;i++){
processado[i] = 0;
if(grafo[davez].count(i)) bfs.push(i);
}
processado[davez] = 1;
int resp= MAXN;
while(!bfs.empty()){
int v = bfs.front();
bfs.pop();
if(processado[v]) continue;
processado[v] = 1;
resp = min(resp,idade[v]);
for(set<int>::iterator it = grafo[v].begin();it != grafo[v].end();it++){
int u = *it;
bfs.push(u);
}
}
if(resp== MAXN) printf("*\n");
else printf("%d\n",resp);
}
}
}
return 0;
}
