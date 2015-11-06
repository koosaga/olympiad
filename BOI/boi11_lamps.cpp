#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> pi;
 
vector<pi> graph[260000];
bool vis[260000];
char str[506][506];
int n, m;
 
void add_edge(int sx, int sy, int ex, int ey, int d){
    int s = sx * (m+1) + sy;
    int e = ex * (m+1) + ey;
    graph[s].push_back(pi(d,e));
    graph[e].push_back(pi(d,s));
}
 
priority_queue<pi,vector<pi>,greater<pi> > pq;
 
int dijkstra(int p){
    pq.push(pi(0,p));
    while(!pq.empty()){
        pi t= pq.top();
        pq.pop();
        if(vis[t.second]) continue;
        vis[t.second] = 1;
        if(t.second == 0) return t.first;
        for(auto &i : graph[t.second]){
            if(vis[i.second]) continue;
            pq.push(pi(i.first + t.first,i.second));
        }
    }
    return -1;
}
int main(){
    scanf("%d %d",&n,&m);
    if((n + m) % 2){
        puts("NO SOLUTION");
        return 0;
    }
    for(int i=0; i<n; i++){
        scanf("%s",str[i]);
        for(int j=0; j<m; j++){
            if((i+j) % 2 == 0){
                add_edge(i,j,i+1,j+1,str[i][j] == '/');
            }
            else{
                add_edge(i+1,j,i,j+1,str[i][j] != '/');
            }
        }
    }
    printf("%d",dijkstra(n*(m+1) + m));
}