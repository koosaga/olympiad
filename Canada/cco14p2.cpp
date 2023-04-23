#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int,int> pi;

vector<pi> graph[100005];
vector<pi> rev[100005];

int n, m, a, b;
int x[100005], y[100005], l[100005], c[100005];

int sp1[100005], sp2[100005];
bool vis1[100005], vis2[100005];

priority_queue<pi, vector<pi>, greater<pi>> pq;

void dijkstra(int* sp, bool* vis, vector<pi> *graph, int st){
    pq.push(pi(0, st));
    while(!pq.empty()){
        pi t = pq.top();
        pq.pop();
        if(vis[t.second]) continue;
        vis[t.second] = 1;
        sp[t.second] = t.first;
        for(auto &i : graph[t.second]){
            pq.push(pi(i.first + t.first, i.second));
        }
    }
}

vector<pi> v;

int main(){
    scanf("%d %d %d %d",&n,&m,&a,&b);
    for(int i=0; i<m; i++){
        scanf("%d %d %d %d",&x[i],&y[i],&l[i],&c[i]);
        graph[x[i]].push_back(pi(l[i], y[i]));
        rev[y[i]].push_back(pi(l[i], x[i]));
    }
    dijkstra(sp1, vis1, graph, a);
    dijkstra(sp2, vis2, rev, b);
    for(int i=0; i<m; i++){
        if(!vis1[x[i]] || !vis2[y[i]]) continue;
        int tmp = l[i] + sp1[x[i]] + sp2[y[i]];
        v.push_back(pi(tmp, c[i]));
    }
    sort(v.begin(), v.end());
    for(int i=1; i<v.size(); i++){
        v[i].second += v[i-1].second;
    }
    int q;
    scanf("%d",&q);
    while(q--){
        int x;
        scanf("%d",&x);
        auto t = upper_bound(v.begin(), v.end(), pi(x, 1e9));
        if(t == v.begin()) puts("0");
        else t--, printf("%d\n",t->second);
    }
}