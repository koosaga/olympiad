#include <cstdio>
#include <vector>
#include <utility>
#include <cstring>
#include <queue>
using namespace std;
typedef long long lint;
typedef pair<lint,int> pi;

vector<pi> graph[500005];
priority_queue<pi,vector<pi>,greater<pi> > pq;

bool vis[500005];
int arr[4], fnd[500005];
lint adj[4][4];

void dijk(int s){
    while (!pq.empty()) pq.pop();
    memset(vis,0,sizeof(vis));
    pq.push(pi(0,arr[s]));
    while (!pq.empty()) {
        pi t = pq.top();
        pq.pop();
        if(vis[t.second]) continue;
        vis[t.second] = 1;
        if(fnd[t.second] != -1){
            adj[s][fnd[t.second]] = adj[fnd[t.second]][s] = t.first;
        }
        for (auto &i : graph[t.second]){
            if(vis[i.second]) continue;
            pq.push(pi(t.first + i.first,i.second));
        }
    }
}

lint solve(){
    lint rets = min(adj[0][3] + adj[1][2],adj[0][2] + adj[1][3]);
    rets = min(rets,adj[0][1] + adj[2][3]);
    if(rets > 1e16) return -1;
    return rets;
}

void input(){
    int a,b,c,d,e,n;
    scanf("%d %d %d %d %d %d",&a,&b,&c,&d,&e,&n);
    arr[0] = a;
    arr[1] = a+b;
    arr[2] = a+b+c;
    arr[3] = a+b+c+d;
    memset(fnd,-1,sizeof(fnd));
    for (int i=0; i<4; i++) {
        fnd[arr[i]] = i;
        for (int j=0; j<4; j++) {
            adj[i][j] = 1e17;
        }
    }
    for (int i=0; i<n; i++) {
        int s,e;
        scanf("%d %d",&s,&e);
        s--;
        graph[s].push_back(pi(e-s,e));
        graph[e].push_back(pi(e-s,s));
    }
}

int main(){
    input();
    for (int i=0; i<4; i++) {
        dijk(i);
    }
    printf("%lld\n",solve());
}