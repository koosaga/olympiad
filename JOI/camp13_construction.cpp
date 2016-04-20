#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;

int n,m,c;
int x[200005], y[200005];

struct point{
    int x,y,num;
};

bool cmp1(point a, point b){return a.x != b.x ? (a.x < b.x) : (a.y < b.y);}
bool cmp2(point a, point b){return a.y != b.y ? (a.y < b.y) : (a.x < b.x);}

struct edge_hori{
    int sx, ex, y;
    int s,e;
};

struct edge_vert{
    int sy, ey, x;
    int s,e;
};

struct kill_hori{
    int y, sx, ex, dx;
};

struct kill_vert{
    int x, sy, ey, dx;
};

bool cmp3(edge_hori a, edge_hori b){return a.y < b.y;}
bool cmp4(edge_vert a, edge_vert b){return a.x < b.x;}
bool cmp5(kill_hori a, kill_hori b){return a.y < b.y;}
bool cmp6(kill_vert a, kill_vert b){return a.x < b.x;}

long long tree[2100000];
int lazy[2100000];

void lazydown(int ps, int pe, int p){
    lazy[2*p] += lazy[p];
    lazy[2*p+1] += lazy[p];
    int pm = (ps+pe)/2;
    tree[2*p] += 1ll * lazy[p] * (pm - ps + 1);
    tree[2*p+1] += 1ll * lazy[p] * (pe - pm);
    lazy[p] = 0;
}

void add(int s, int e, int x, int ps, int pe, int p){
    if(e < ps || pe < s) return;
    if(s <= ps && pe <= e){
        tree[p] += (pe - ps + 1) * x;
        lazy[p] += x;
        return;
    }
    lazydown(ps,pe,p);
    int pm = (ps+pe)/2;
    add(s,e,x,ps,pm,2*p);
    add(s,e,x,pm+1,pe,2*p+1);
    tree[p] = tree[2*p] + tree[2*p+1];
}

long long sum(int s, int e, int ps, int pe, int p){
    if(e < ps || pe < s) return 0;
    if(s <= ps && pe <= e) return tree[p];
    lazydown(ps,pe,p);
    int pm = (ps+pe)/2;
    return sum(s,e,ps,pm,2*p) + sum(s,e,pm+1,pe,2*p+1);
}

vector<edge_hori> eh;
vector<edge_vert> ev;
vector<kill_hori> kh;
vector<kill_vert> kv;

void initialize(){
    point hor[200005];
    point vert[200005];
    scanf("%d %d %d",&n,&m,&c);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&x[i],&y[i]);
    }
    for (int i=0; i<n; i++) {
        hor[i] = {x[i],y[i],i};
        vert[i] = {x[i],y[i],i};
    }
    sort(hor,hor+n,cmp2);
    sort(vert,vert+n,cmp1);
    for (int i=0; i<n-1; i++) {
        if(hor[i].y == hor[i+1].y){
            eh.push_back({hor[i].x,hor[i+1].x,hor[i].y,hor[i].num,hor[i+1].num});
        }
    }
    for (int i=0; i<n-1; i++) {
        if(vert[i].x == vert[i+1].x){
            ev.push_back({vert[i].y,vert[i+1].y,vert[i].x,vert[i].num,vert[i+1].num});
        }
    }
    for (int i=0; i<m; i++) {
        int p,q,r,s;
        scanf("%d %d %d %d",&p,&q,&r,&s);
        kh.push_back({q,p,r,1});
        kh.push_back({s+1,p,r,-1});
        kv.push_back({p,q,s,1});
        kv.push_back({r+1,q,s,-1});
    }
    sort(eh.begin(),eh.end(),cmp3);
    sort(ev.begin(),ev.end(),cmp4);
    sort(kh.begin(),kh.end(),cmp5);
    sort(kv.begin(),kv.end(),cmp6);
}

vector<int> px, py;

void coord_compression(){
    for(auto i : eh){
        px.push_back(i.sx);
        px.push_back(i.ex);
        py.push_back(i.y);
    }
    for(auto i : ev){
        py.push_back(i.sy);
        py.push_back(i.ey);
        px.push_back(i.x);
    }
    for(auto i : kh){
        py.push_back(i.y);
        px.push_back(i.sx);
        px.push_back(i.ex);
    }
    for(auto i : kv){
        px.push_back(i.x);
        py.push_back(i.sy);
        py.push_back(i.ey);
    }
    sort(px.begin(),px.end());
    sort(py.begin(),py.end());
    px.resize(unique(px.begin(),px.end()) - px.begin());
    py.resize(unique(py.begin(),py.end()) - py.begin());
    for(auto &i : eh){
        i.sx = (int)(lower_bound(px.begin(),px.end(),i.sx) - px.begin());
        i.ex = (int)(lower_bound(px.begin(),px.end(),i.ex) - px.begin());
        i.y = (int)(lower_bound(py.begin(),py.end(),i.y) - py.begin());
    }
    for(auto &i : ev){
        i.sy = (int)(lower_bound(py.begin(),py.end(),i.sy) - py.begin());
        i.ey = (int)(lower_bound(py.begin(),py.end(),i.ey) - py.begin());
        i.x = (int)(lower_bound(px.begin(),px.end(),i.x) - px.begin());
    }
    for(auto &i : kh){
        i.sx = (int)(lower_bound(px.begin(),px.end(),i.sx) - px.begin());
        i.ex = (int)(lower_bound(px.begin(),px.end(),i.ex) - px.begin());
        i.y = (int)(lower_bound(py.begin(),py.end(),i.y) - py.begin());
    }
    for(auto &i : kv){
        i.sy = (int)(lower_bound(py.begin(),py.end(),i.sy) - py.begin());
        i.ey = (int)(lower_bound(py.begin(),py.end(),i.ey) - py.begin());
        i.x = (int)(lower_bound(px.begin(),px.end(),i.x) - px.begin());
    }
}

struct edge{int s,e,x;};
bool cmp7(edge a, edge b){return a.x < b.x;}

vector<edge> ret_edge;

void graph_retrieval(){
    memset(tree,0,sizeof(tree));
    memset(lazy,0,sizeof(lazy));
    int p1 = 0, p2 = 0;
    while (p1 < eh.size() && p2 < kh.size()) {
        if(eh[p1].y < kh[p2].y){
            if(sum(eh[p1].sx,eh[p1].ex,0,(int)px.size()-1,1) == 0){
                ret_edge.push_back({eh[p1].s,eh[p1].e,px[eh[p1].ex] - px[eh[p1].sx]});
            }
            p1++;
        }
        else{
            add(kh[p2].sx,kh[p2].ex,kh[p2].dx,0,(int)px.size()-1,1);
            p2++;
        }
    }
    while (p1 < eh.size()) {
        ret_edge.push_back({eh[p1].s,eh[p1].e,px[eh[p1].ex] - px[eh[p1].sx]});
        p1++;
    }
    memset(tree,0,sizeof(tree));
    memset(lazy,0,sizeof(lazy));
    p1 = 0, p2 = 0;
    while (p1 < ev.size() && p2 < kv.size()) {
        if(ev[p1].x < kv[p2].x){
            if(sum(ev[p1].sy,ev[p1].ey,0,(int)py.size()-1,1) == 0){
                ret_edge.push_back({ev[p1].s,ev[p1].e,py[ev[p1].ey] - py[ev[p1].sy]});
            }
            p1++;
        }
        else{
            add(kv[p2].sy,kv[p2].ey,kv[p2].dx,0,(int)py.size()-1,1);
            p2++;
        }
    }
    while (p1 < ev.size()) {
        ret_edge.push_back({ev[p1].s,ev[p1].e,py[ev[p1].ey] - py[ev[p1].sy]});
        p1++;
    }
}

struct disj{
    int pa[200005], r[200005];
    void init(int n){
        for(int i=0; i<=n; i++){
            pa[i] = i;
        }
    }
    int find(int x){
        if(pa[x] == x) return x;
        return pa[x] = find(pa[x]);
    }
    bool uni(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y) return 0;
        if(r[x] < r[y]) pa[y] = x;
        else pa[x] = y;
        if(r[x] == r[y]) r[x]++;
        return 1;
    }
}disj;

vector<int> ret;
vector<long long> psum;

void tree_retrieval(){
    disj.init(n);
    sort(ret_edge.begin(),ret_edge.end(),cmp7);
    for(edge i : ret_edge){
        if(disj.uni(i.s,i.e)){
            ret.push_back(i.x);
            psum.push_back(i.x + (psum.empty() ? 0 : psum.back()));
        }
    }
}

inline long long get_sum(int x){
    if(x == 0) return 0;
    return psum[x-1];
}

void process_query(){
    while (c--) {
        int b,k;
        scanf("%d %d",&b,&k);
        k = min(k,n);
        if(k + ret.size() < n) puts("-1");
        else{
            auto x = upper_bound(ret.begin(),ret.end(),b);
            int cnt = (int)(x - ret.begin());
            if(cnt + k < n){
                printf("%lld\n",get_sum(n-k) + 1ll * b * k);
            }
            else{
                printf("%lld\n",get_sum(cnt) + 1ll * (n - cnt) * b);
            }
        }
    }
}

int main(){
    initialize();
    coord_compression();
    graph_retrieval();
    tree_retrieval();
    process_query();
}