#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
 
int n,a,b,c,m;
vector<pi> graph[100005];
 
int dist[3][100005];
bool vis[100005];
 
priority_queue<pi,vector<pi>,greater<pi> > pq;
 
void dijkstra(int s, int* dist){
    dist[s] = 0;
    memset(vis,0,sizeof(vis));
    pq.push(pi(0,s));
    while (!pq.empty()) {
        pi t = pq.top();
        pq.pop();
        if(vis[t.second]) continue;
        vis[t.second] = 1;
        dist[t.second] = t.first;
        for (auto &i : graph[t.second]){
            pq.push(pi(i.first + t.first,i.second));
        }
    }
}
 
bool is_install[100005];
 
struct rmq{
    int tree[270000], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        memset(tree,0x3f,sizeof(tree));
    }
    void add(int x, int v){
        x += lim;
        tree[x] = min(tree[x],v);
        while(x>1){
            x >>= 1;
            tree[x] = min(tree[2*x],tree[2*x+1]);
        }
    }
    int q(int s, int e){
        s += lim;
        e += lim;
        int ret = 1e9;
        while(s < e){
            if(s%2 == 1) ret = min(ret,tree[s++]);
            if(e%2 == 0) ret = min(ret,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret = min(ret,tree[s]);
        return ret;
    }
}rmq;
 
struct tup{int x,y,z,num;}dists[100005];
bool cmp(tup a, tup b){ return a.x < b.x; }
 
vector<int> tmp;
 
void solve_install(){
    for (int t=0; t<3; t++) {
        for (int i=1; i<=n; i++) {
            tmp.push_back(dist[t][i]);
        }
        sort(tmp.begin(),tmp.end());
        tmp.resize(unique(tmp.begin(),tmp.end()) - tmp.begin());
        for (int i=1; i<=n; i++) {
            dist[t][i] = (int)(lower_bound(tmp.begin(),tmp.end(),dist[t][i]) - tmp.begin()) + 1;
            if(t == 0) dists[i].x = dist[t][i];
            if(t == 1) dists[i].y = dist[t][i];
            if(t == 2) dists[i].z = dist[t][i];
        }
        tmp.clear();
    }
    for (int i=1; i<=n; i++) {
        dists[i].num = i;
    }
    dists[0] = dists[n];
    rmq.init(n);
    sort(dists,dists+n,cmp);
    for (int i=0; i<n; ) {
        int e = i;
        while (e < n && dists[e].x == dists[i].x) e++;
        for (int j=i; j<e; j++) {
            if(rmq.q(0,dists[j].y-1) >= dists[j].z){
                is_install[dists[j].num] = 1;
            }
        }
        for (int j=i; j<e; j++) {
            rmq.add(dists[j].y,dists[j].z);
        }
        i = e;
    }
}
 
int main(){
    scanf("%d %d %d %d %d",&n,&a,&b,&c,&m);
    for (int i=0; i<m; i++) {
        int s,e,x;
        scanf("%d %d %d",&s,&e,&x);
        graph[s].push_back(pi(x,e));
        graph[e].push_back(pi(x,s));
    }
    memset(dist,0x3f,sizeof(dist));
    dijkstra(a,dist[0]);
    dijkstra(b,dist[1]);
    dijkstra(c,dist[2]);
    solve_install();
    int q;
    scanf("%d",&q);
    while (q--) {
        int t;
        scanf("%d",&t);
        puts(is_install[t] ? "YES" : "NO");
    }
}