#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
typedef long long lint;
typedef pair<int,int> pi;
 
vector<int> vx, vy;
 
int n, sx, sy, bx, by;
 
struct mir{int x,y,d;};
struct seg{int s,e,x;};
 
vector<pi> px[100005], py[100005];
 
mir a[100005];
vector<seg> vx1, vy1, vx2, vy2;
 
bool inside(int s, int m, int e){
    if(s > e) swap(s,e);
    return s < m && m < e;
}
int get_new(int x, int y, int d){
    if(d == 0){
        auto t = upper_bound(px[x].begin(),px[x].end(),pi(y,1e9));
        if(t == px[x].end()) return -1;
        return t->second;
    }
    if(d == 1){
        auto t = upper_bound(py[y].begin(),py[y].end(),pi(x,1e9));
        if(t == py[y].end()) return -1;
        return t->second;
    }
    if(d == 2){
        auto t = lower_bound(px[x].begin(),px[x].end(),pi(y,-1));
        if(t == px[x].begin()) return -1;
        return (--t)->second;
    }
    if(d == 3){
        auto t = lower_bound(py[y].begin(),py[y].end(),pi(x,-1));
        if(t == py[y].begin()) return -1;
        return (--t)->second;
    }
    return -1;
}
 
bool vis[100005][4];
 
void get_segs(int px, int py, int d, vector<seg> &x, vector<seg> &y){
    memset(vis,0,sizeof(vis));
    while(1){
        int np = get_new(px, py, d);
        if(np == -1){
            if(d == 0){
                if(px == sx && inside(py,sy,n+5)) break;
                y.push_back({py,n+5,px});
            }
            if(d == 1){
                if(py == sy && inside(px,sx,n+5)) break;
                x.push_back({px,n+5,py});
            }
            if(d == 2){
                if(px == sx && inside(py,sy,0)) break;
                y.push_back({0,py,px});
            }
            if(d == 3){
                if(py == sy && inside(px,sx,0)) break;
                x.push_back({0,px,py});
            }
            break;
        }
        else{
            if(d == 0){
                if(px == sx && inside(py,sy,a[np].y)) break;
                y.push_back({py,a[np].y,px});
            }
            if(d == 1){
                if(py == sy && inside(px,sx,a[np].x)) break;
                x.push_back({px,a[np].x,py});
            }
            if(d == 2){
                if(px == sx && inside(py,sy,a[np].y)) break;
                y.push_back({a[np].y,py,px});
            }
            if(d == 3){
                if(py == sy && inside(px,sx,a[np].x)) break;
                x.push_back({a[np].x,px,py});
            }
            if(a[np].d == 0){
                d ^= 1;
            }
            else{
                d ^= 3;
            }
            if(vis[np][d]) break;
            vis[np][d] = 1;
            px = a[np].x;
            py = a[np].y;
        }
    }
}
 
bool cmp(seg a, seg b){
    return a.x == b.x ? (a.s == b.s ? (a.e < b.e) : (a.s < b.s)) : a.x < b.x;
}
 
void sort_segment(vector<seg> &s){
    vector<seg> upd;
    sort(s.begin(), s.end(), cmp);
    for(int i=0; i<s.size();){
        int e = i;
        while(e < s.size() && s[e].x == s[i].x) e++;
        int seg_st = -1, seg_ed = -1;
        for(int j=i; j<e; j++){
            if(seg_ed < s[j].s){
                if(~seg_ed){
                    upd.push_back({2 * seg_st + 1,2 * seg_ed - 1,2 * s[j].x});
                }
                seg_st = s[j].s;
                seg_ed = s[j].e;
            }
            seg_ed = max(seg_ed,s[j].e);
        }
        upd.push_back({2 * seg_st + 1,2 * seg_ed - 1,2 * s[i].x});
        i = e;
    }
    s.clear();
    s = upd;
}
 
struct bit{
    int tree[200500], lim;
    void init(int n){
        lim = n+2;
        memset(tree,0,sizeof(tree));
    }
    void add(int x, int v){
        x += 2;
        while(x <= lim){
            tree[x] += v;
            x += x & -x;
        }
    }
    int sum(int x){
        x += 2;
        int ret= 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
    int range_sum(int s, int e){
        return sum(e) - sum(s-1);
    }
}bit;
 
struct sweeper{int pos, dest, dx;};
 
vector<sweeper> sweep;
vector<seg> query;
 
lint solve(vector<seg> &vx, vector<seg> &vy){
    long long ret = 0;
    sweep.clear();
    query.clear();
    for (auto &i : vx){
        sweep.push_back({i.s,i.x,1});
        sweep.push_back({i.e+1,i.x,-1});
    }
    sort(sweep.begin(),sweep.end(),[&](const sweeper &a, const sweeper &b){return a.pos < b.pos;});
    for (auto &i : vy){
        query.push_back(i);
    }
    sort(query.begin(),query.end(),cmp);
    bit.init(2*n + 20);
    int px = 0, py = 0;
    for(int i=0; i<2*n+20; i++){
        while(px < sweep.size() && sweep[px].pos == i){
            bit.add(sweep[px].dest,sweep[px].dx);
            px++;
        }
        while(py < query.size() && query[py].x == i){
            ret += bit.range_sum(query[py].s,query[py].e);
            py++;
        }
    }
    return ret;
}
 
int main(){
    scanf("%d %d %d",&n,&bx,&by);
    vx.push_back(-2e9);
    vy.push_back(-2e9);
    vx.push_back(bx);
    vy.push_back(by);
    vx.push_back(0);
    vy.push_back(0);
    for(int i=0; i<n; i++){
        char str[5];
        scanf("%d %d %s",&a[i].x,&a[i].y,str);
        if(str[0] == '/') a[i].d = 0;
        else a[i].d = 1;
        vx.push_back(a[i].x);
        vy.push_back(a[i].y);
    }
    sort(vx.begin(),vx.end());
    sort(vy.begin(),vy.end());
    vx.resize(unique(vx.begin(),vx.end()) - vx.begin());
    vy.resize(unique(vy.begin(),vy.end()) - vy.begin());
    sx = (int)(lower_bound(vx.begin(),vx.end(),0) - vx.begin());
    sy = (int)(lower_bound(vy.begin(),vy.end(),0) - vy.begin());
    bx = (int)(lower_bound(vx.begin(),vx.end(),bx) - vx.begin());
    by = (int)(lower_bound(vy.begin(),vy.end(),by) - vy.begin());
    for(int i=0; i<n; i++){
        a[i].x = (int)(lower_bound(vx.begin(),vx.end(),a[i].x) - vx.begin());
        a[i].y = (int)(lower_bound(vy.begin(),vy.end(),a[i].y) - vy.begin());
        px[a[i].x].push_back(pi(a[i].y,i));
        py[a[i].y].push_back(pi(a[i].x,i));
    }
    for(int i=0; i<n+3; i++){
        sort(px[i].begin(),px[i].end());
        sort(py[i].begin(),py[i].end());
    }
    get_segs(sx,sy,0,vx1,vy1);
    for(int i=0; i<4; i++){
        get_segs(bx,by,i,vx2,vy2);
    }
    sort_segment(vx1);
    sort_segment(vx2);
    sort_segment(vy1);
    sort_segment(vy2);
    printf("%lld",solve(vx1, vy2) + solve(vx2, vy1));
}