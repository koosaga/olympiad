#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;

struct edg{int s,e,x;};
vector<edg> tree;
vector<pi> graph[200005];

bool cmp(edg a, edg b){return a.x < b.x;}

int n,m,p,q;
char str[2005][2005];
int domain[2005][2005], depth[2005][2005];
int pa[200005][18], val[200005][18], dep[200005];

struct disj{
    int pa[200005], r[200005];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i;
    }
    int find(int x){
        if(pa[x] == x) return x;
        return pa[x] = find(pa[x]);
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        if(r[p] > r[q]) pa[p] = q;
        else pa[q] = p;
        if(r[p] == r[q]) r[q]++;
        return 1;
    }
}disj;

int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};

void dfs(int x, int p, int e, int d){
    pa[x][0] = p;
    val[x][0] = e;
    dep[x] = d;
    for (int i=1; (1<<i) <= dep[x]; i++) {
        pa[x][i] = pa[pa[x][i-1]][i-1];
        val[x][i] = max(val[x][i-1],val[pa[x][i-1]][i-1]);
    }
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i].second == p) continue;
        dfs(graph[x][i].second,x,graph[x][i].first,d+1);
    }
}

int qr(int s, int e){
    if(dep[s] > dep[e]) swap(s,e);
    int ret = 0, dx = dep[e] - dep[s];
    for (int i=0; (1<<i)<=dx; i++) {
        if(dx & (1<<i)){
            ret = max(ret,val[e][i]);
            e = pa[e][i];
        }
    }
    for (int i=17; i>=0; i--) {
        if(pa[s][i] != pa[e][i]){
            ret = max(ret,val[s][i]);
            ret = max(ret,val[e][i]);
            s = pa[s][i];
            e = pa[e][i];
        }
    }
    if(s != e){
        ret = max(ret,val[s][0]);
        ret = max(ret,val[e][0]);
    }
    return ret;
}

vector<edg> cand;
queue<int> qx,qy,qd,qn;

void make_tree(){
    for (int i=1; i<=p; i++) {
        int px,py;
        scanf("%d %d",&px,&py);
        px--;
        py--;
        qx.push(px);
        qy.push(py);
        qd.push(0);
        qn.push(i);
        domain[px][py] = i;
        depth[px][py] = 0;
    }
    while (!qx.empty()) {
        int xf = qx.front();
        int yf = qy.front();
        int df = qd.front();
        int nf = qn.front();
        qx.pop();
        qy.pop();
        qd.pop();
        qn.pop();
        for (int i=0; i<4; i++) {
            if(xf + dx[i] < 0 || xf + dx[i] >= n || yf + dy[i] < 0 || yf + dy[i] >= m){
                continue;
            }
            if(str[xf+dx[i]][yf+dy[i]] == '#') continue;
            if(domain[xf+dx[i]][yf+dy[i]]){
                cand.push_back({domain[xf+dx[i]][yf+dy[i]],nf,depth[xf+dx[i]][yf+dy[i]] + df});
                continue;
            }
            domain[xf+dx[i]][yf+dy[i]] = nf;
            depth[xf+dx[i]][yf+dy[i]] = df+1;
            qx.push(xf + dx[i]);
            qy.push(yf + dy[i]);
            qd.push(df + 1);
            qn.push(nf);
        }
    }
    sort(cand.begin(),cand.end(),cmp);
    for (int i=0; i<cand.size(); i++) {
        if(disj.uni(cand[i].s,cand[i].e)){
            graph[cand[i].s].push_back(pi(cand[i].x,cand[i].e));
            graph[cand[i].e].push_back(pi(cand[i].x,cand[i].s));
        }
    }
    for (int i=1; i<p; i++) {
        if(disj.uni(i,i+1)){
            graph[i].push_back(pi(1e9,i+1));
            graph[i+1].push_back(pi(1e9,i));
        }
    }
}

int main(){
    scanf("%d %d %d %d",&n,&m,&p,&q);
    for (int i=0; i<n; i++) {
        scanf("%s",str[i]);
    }
    disj.init(p);
    make_tree();
    dfs(1,0,0,0);
    for (int i=0; i<q; i++) {
        int s,e;
        scanf("%d %d",&s,&e);
        int ret = qr(s,e);
        if(ret > 1e8) puts("-1");
        else printf("%d\n",ret);
    }
}