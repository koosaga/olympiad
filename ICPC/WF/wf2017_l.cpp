#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 100005;

int n;

struct bit{
    int tree[2 * MAXN];
    void add(int x, int v){
        while(x < 2 * MAXN){
            tree[x] += v;
            x += x & -x;
        }
    }
    int query(int x){
        int ret = 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
}bit;

struct pnt{
    int x, y, idx;
    bool operator<(const pnt &p)const{
        return pi(x, y) < pi(p.x, p.y);
    }
}a[MAXN], b[MAXN];

struct seg{
    int pos, s, e;
    bool operator<(const seg &g)const{
        return pos < g.pos;
    }
};

int ans[MAXN];
vector<int> px, py;

int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].x,&a[i].y);
        px.push_back(a[i].x);
        py.push_back(a[i].y);
        a[i].idx = i;
    }
    for(int i=0; i<n; i++){
        scanf("%d %d",&b[i].x,&b[i].y);
        px.push_back(b[i].x);
        py.push_back(b[i].y);
        b[i].idx = i;
    }
    sort(a, a+n);
    sort(b, b+n);
    sort(px.begin(), px.end());
    sort(py.begin(), py.end());
    px.resize(unique(px.begin(), px.end()) - px.begin());
    py.resize(unique(py.begin(), py.end()) - py.begin());
    for(int i=0; i<n; i++){
        a[i].x = lower_bound(px.begin(), px.end(), a[i].x) - px.begin() + 1;
        a[i].y = lower_bound(py.begin(), py.end(), a[i].y) - py.begin() + 1;
        b[i].x = lower_bound(px.begin(), px.end(), b[i].x) - px.begin() + 1;
        b[i].y = lower_bound(py.begin(), py.end(), b[i].y) - py.begin() + 1;
    }
    int p = 0;
    set<pnt> s;
    for(int i=0; i<n; i++){
        while(p < n && a[p] < b[i]){
            s.insert({a[p].y, a[p].x, a[p].idx});
            p++;
        }
        auto l = s.upper_bound({b[i].y, 98765432, -1});
        if(l == s.begin()){
            puts("syntax error");
            return 0;
        }
        l--;
        ans[l->idx] = b[i].idx;
        s.erase(l);
    }
    sort(a, a+n, [&](const pnt &a, const pnt &b){
        return a.idx < b.idx;
    });
    sort(b, b+n, [&](const pnt &a, const pnt &b){
        return a.idx < b.idx;
    });
    vector<seg> vx, vy;
    for(int i=0; i<n; i++){
        vx.push_back({a[i].y, a[i].x, b[ans[i]].x});
        vx.push_back({b[ans[i]].y, a[i].x, b[ans[i]].x});
        vy.push_back({a[i].x, a[i].y, b[ans[i]].y});
        vy.push_back({b[ans[i]].x, a[i].y, b[ans[i]].y});
    }
    sort(vx.begin(), vx.end());
    sort(vy.begin(), vy.end());
    vector<pi> va, vd;
    for(auto &i : vy){
        va.push_back(pi(i.s, i.pos));
        vd.push_back(pi(i.e + 1, i.pos));
    }
    sort(va.begin(), va.end());
    sort(vd.begin(), vd.end());
    lint ret = 0;
    int p1 = 0, p2 = 0;
    for(auto &i : vx){
        while(p1 < va.size() && va[p1].first <= i.pos) bit.add(va[p1++].second, 1);
        while(p2 < vd.size() && vd[p2].first <= i.pos) bit.add(vd[p2++].second, -1);
        ret += bit.query(i.e) - bit.query(i.s-1);
    }
    if(ret != 4 * n){
        puts("syntax error");
        return 0;
    }
    for(int i=0; i<n; i++) printf("%d\n", ans[i] + 1);
}
