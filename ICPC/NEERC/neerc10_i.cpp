#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

vector<pi> graph[100005];

int dist0[100005], dist1[100005];
int vis[100005];
queue<int> q,d;

void bfs(int s, int* ret){
    memset(vis,0,sizeof(vis));
    q.push(s);
    d.push(0);
    vis[s] = 1;
    while (!q.empty()) {
        int qf = q.front();
        int df = d.front();
        ret[qf] = df;
        q.pop();
        d.pop();
        for (auto &i : graph[qf]){
            if(!vis[i.second]){
                vis[i.second] = 1;
                q.push(i.second);
                d.push(df+1);
            }
        }
    }
}

vector<int> cur;
vector<pi> upd;

int main(){
    int n, m;
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        int s,e,x;
        scanf("%d %d %d",&s,&e,&x);
        graph[s].push_back(pi(x,e));
        graph[e].push_back(pi(x,s));
    }
    bfs(1,dist0);
    bfs(n,dist1);
    cur.push_back(1);
    printf("%d\n",dist0[n]);
    for(int i=0; i<dist0[n]; i++){
        upd.clear();
        for (auto &i : cur){
            for (auto &j : graph[i]){
                if(dist0[j.second] == dist0[i] + 1 && dist1[j.second] == dist1[i] - 1){
                    upd.push_back(j);
                }
            }
        }
        cur.clear();
        sort(upd.begin(),upd.end());
        printf("%d ",upd[0].first);
        for (auto &i : upd){
            if(i.first == upd[0].first){
                cur.push_back(i.second);
            }
            else break;
        }
        sort(cur.begin(),cur.end());
        cur.resize(unique(cur.begin(),cur.end()) - cur.begin());
    }
}