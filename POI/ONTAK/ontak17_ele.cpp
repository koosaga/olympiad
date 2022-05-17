#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

const int MAXN = 100005;
typedef long long ll;

namespace DT{
    using ll = long long;

    bool ge(const ll& a, const ll& b) { return a >= b; }
    bool le(const ll& a, const ll& b) { return a <= b; }
    bool eq(const ll& a, const ll& b) { return a == b; }
    bool gt(const ll& a, const ll& b) { return a > b; }
    bool lt(const ll& a, const ll& b) { return a < b; }
    int sgn(const ll& a) { return a >= 0 ? a ? 1 : 0 : -1; }

    struct pt {
        int x, y;
        pt() { }
        pt(ll _x, ll _y) : x(_x), y(_y) { }
        bool operator<(const pt &p)const{
            return make_pair(x, y) < make_pair(p.x, p.y);
        }
        bool operator>(const pt &p)const{
            return make_pair(x, y) > make_pair(p.x, p.y);
        }

        pt operator-(const pt& p) const {
            return pt(x - p.x, y - p.y);
        }
        ll cross(const pt& p) const {
            return 1ll * x * p.y - 1ll * y * p.x;
        }
        ll cross(const pt& a, const pt& b) const {
            return (a - *this).cross(b - *this);
        }
        ll dot(const pt& p) const {
            return 1ll * x * p.x + 1ll * y * p.y;
        }
        ll dot(const pt& a, const pt& b) const {
            return (a - *this).dot(b - *this);
        }
        ll sqrLength() const {
            return this->dot(*this);
        }
        bool operator==(const pt& p) const {
            return eq(x, p.x) && eq(y, p.y);
        }
    };

    const pt inf_pt = pt(2e9, 2e9);

    struct QuadEdge {
        pt origin;
        QuadEdge* rot = nullptr;
        QuadEdge* onext = nullptr;
        bool used = false;
        QuadEdge* rev() const {
            return rot->rot;
        }
        QuadEdge* lnext() const {
            return rot->rev()->onext->rot;
        }
        QuadEdge* oprev() const {
            return rot->onext->rot;
        }
        pt dest() const {
            return rev()->origin;
        }
    };

    QuadEdge* make_edge(pt from, pt to) {
        QuadEdge* e1 = new QuadEdge;
        QuadEdge* e2 = new QuadEdge;
        QuadEdge* e3 = new QuadEdge;
        QuadEdge* e4 = new QuadEdge;
        e1->origin = from;
        e2->origin = to;
        e3->origin = e4->origin = inf_pt;
        e1->rot = e3;
        e2->rot = e4;
        e3->rot = e2;
        e4->rot = e1;
        e1->onext = e1;
        e2->onext = e2;
        e3->onext = e4;
        e4->onext = e3;
        return e1;
    }

    void splice(QuadEdge* a, QuadEdge* b) {
        swap(a->onext->rot->onext, b->onext->rot->onext);
        swap(a->onext, b->onext);
    }

    void delete_edge(QuadEdge* e) {
        splice(e, e->oprev());
        splice(e->rev(), e->rev()->oprev());
        delete e->rev()->rot;
        delete e->rev();
        delete e->rot;
        delete e;
    }

    QuadEdge* connect(QuadEdge* a, QuadEdge* b) {
        QuadEdge* e = make_edge(a->dest(), b->origin);
        splice(e, a->lnext());
        splice(e->rev(), b);
        return e;
    }

    bool left_of(pt p, QuadEdge* e) {
        return gt(p.cross(e->origin, e->dest()), 0);
    }

    bool right_of(pt p, QuadEdge* e) {
        return lt(p.cross(e->origin, e->dest()), 0);
    }

    template <class T>
        T det3(T a1, T a2, T a3, T b1, T b2, T b3, T c1, T c2, T c3) {
            return a1 * (b2 * c3 - c2 * b3) - a2 * (b1 * c3 - c1 * b3) +
                a3 * (b1 * c2 - c1 * b2);
        }

    bool in_circle(pt a, pt b, pt c, pt d) {
        long double det = -det3<long double>(b.x, b.y, b.sqrLength(), c.x, c.y,
                c.sqrLength(), d.x, d.y, d.sqrLength());
        det += det3<long double>(a.x, a.y, a.sqrLength(), c.x, c.y, c.sqrLength(), d.x,
                d.y, d.sqrLength());
        det -= det3<long double>(a.x, a.y, a.sqrLength(), b.x, b.y, b.sqrLength(), d.x,
                d.y, d.sqrLength());
        det += det3<long double>(a.x, a.y, a.sqrLength(), b.x, b.y, b.sqrLength(), c.x,
                c.y, c.sqrLength());
        if(fabs(det) > 1e18) return det > 0;
        else{

            ll det = -det3<ll>(b.x, b.y, b.sqrLength(), c.x, c.y,
                    c.sqrLength(), d.x, d.y, d.sqrLength());
            det += det3<ll>(a.x, a.y, a.sqrLength(), c.x, c.y, c.sqrLength(), d.x,
                    d.y, d.sqrLength());
            det -= det3<ll>(a.x, a.y, a.sqrLength(), b.x, b.y, b.sqrLength(), d.x,
                    d.y, d.sqrLength());
            det += det3<ll>(a.x, a.y, a.sqrLength(), b.x, b.y, b.sqrLength(), c.x,
                    c.y, c.sqrLength());
            return (det > 0);
        }
    }

    pair<QuadEdge*, QuadEdge*> build_tr(int l, int r, vector<pt>& p) {
        if (r - l + 1 == 2) {
            QuadEdge* res = make_edge(p[l], p[r]);
            return make_pair(res, res->rev());
        }
        if (r - l + 1 == 3) {
            QuadEdge *a = make_edge(p[l], p[l + 1]), *b = make_edge(p[l + 1], p[r]);
            splice(a->rev(), b);
            int sg = sgn(p[l].cross(p[l + 1], p[r]));
            if (sg == 0)
                return make_pair(a, b->rev());
            QuadEdge* c = connect(b, a);
            if (sg == 1)
                return make_pair(a, b->rev());
            else
                return make_pair(c->rev(), c);
        }
        int mid = (l + r) / 2;
        QuadEdge *ldo, *ldi, *rdo, *rdi;
        tie(ldo, ldi) = build_tr(l, mid, p);
        tie(rdi, rdo) = build_tr(mid + 1, r, p);
        while (true) {
            if (left_of(rdi->origin, ldi)) {
                ldi = ldi->lnext();
                continue;
            }
            if (right_of(ldi->origin, rdi)) {
                rdi = rdi->rev()->onext;
                continue;
            }
            break;
        }
        QuadEdge* basel = connect(rdi->rev(), ldi);
        auto valid = [&basel](QuadEdge* e) { return right_of(e->dest(), basel); };
        if (ldi->origin == ldo->origin)
            ldo = basel->rev();
        if (rdi->origin == rdo->origin)
            rdo = basel;
        while (true) {
            QuadEdge* lcand = basel->rev()->onext;
            if (valid(lcand)) {
                while (in_circle(basel->dest(), basel->origin, lcand->dest(),
                            lcand->onext->dest())) {
                    QuadEdge* t = lcand->onext;
                    delete_edge(lcand);
                    lcand = t;
                }
            }
            QuadEdge* rcand = basel->oprev();
            if (valid(rcand)) {
                while (in_circle(basel->dest(), basel->origin, rcand->dest(),
                            rcand->oprev()->dest())) {
                    QuadEdge* t = rcand->oprev();
                    delete_edge(rcand);
                    rcand = t;
                }
            }
            if (!valid(lcand) && !valid(rcand))
                break;
            if (!valid(lcand) ||
                    (valid(rcand) && in_circle(lcand->dest(), lcand->origin,
                                               rcand->origin, rcand->dest())))
                basel = connect(rcand, basel->rev());
            else
                basel = connect(basel->rev(), lcand->rev());
        }
        return make_pair(ldo, rdo);
    }

    vector<tuple<pt, pt, pt>> delaunay(vector<pt> p) {
        sort(p.begin(), p.end(), [](const pt& a, const pt& b) {
                return lt(a.x, b.x) || (eq(a.x, b.x) && lt(a.y, b.y));
                });
        auto res = build_tr(0, (int)p.size() - 1, p);
        QuadEdge* e = res.first;
        vector<QuadEdge*> edges = {e};
        while (lt(e->onext->dest().cross(e->dest(), e->origin), 0))
            e = e->onext;
        auto add = [&p, &e, &edges]() {
            QuadEdge* curr = e;
            do {
                curr->used = true;
                p.push_back(curr->origin);
                edges.push_back(curr->rev());
                curr = curr->lnext();
            } while (curr != e);
        };
        add();
        p.clear();
        int kek = 0;
        while (kek < (int)edges.size()) {
            if (!(e = edges[kek++])->used)
                add();
        }
        vector<tuple<pt, pt, pt>> ans;
        for (int i = 0; i < (int)p.size(); i += 3) {
            ans.push_back(make_tuple(p[i], p[i + 1], p[i + 2]));
        }
        return ans;
    }

        bool in_triangle(pt a, pt b, pt c, pt d){
        if((b - a).cross(c - a) < 0) swap(b, c);
        if((b - a).cross(d - a) < 0) return 0;
        if((c - b).cross(d - b) < 0) return 0;
        if((a - c).cross(d - c) < 0) return 0;
        return 1;
    }


}

struct edge{
    int s, e; lint x;
    bool operator<(const edge &e)const{
        return x < e.x;
    }
};

struct disj{
    int pa[MAXN];
    void init(int n){
        iota(pa, pa + n, 0);
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p); q = find(q);
        if(p == q) return 0;
        pa[q] = p; return 1;
    }
}disj;
namespace GGD{

    int n;
    pi a[100005];

    bool cmp(pi a, pi b){return a.second < b.second;}
    lint dist(pi x, pi y){return 1ll*(y.second - x.second) * (y.second - x.second) + 1ll*(y.first - x.first) * (y.first - x.first);}

    lint closest(int s, int e){
        if(s == e-2){
            return min(min(dist(a[s],a[s+1]),dist(a[s+1],a[s+2])),dist(a[s],a[s+2]));
        }
        if(s == e-1){
            return dist(a[s],a[e]);
        }
        int m = (s+e)/2;
        lint res = min(closest(s,m),closest(m+1,e));

        vector<pi> strip;
        for (int i=s; i<=e; i++) {
            if(1ll * abs(a[i].first - a[m].first) * abs(a[i].first - a[m].first) < res){
                strip.push_back(a[i]);
            }
        }
        sort(strip.begin(),strip.end(),cmp);
        for (int i=0; i<strip.size(); i++) {
            for (int j=i+1; j<strip.size() &&
                1ll*    (strip[j].second - strip[i].second) * (strip[j].second - strip[i].second) < res; j++){
                res = min(res,dist(strip[j],strip[i]));
            }
        }
        return res;
    }

    lint getdist(vector<DT::pt> v){
        n = sz(v);
        for (int i=0; i<n; i++) {
            a[i] = pi(v[i].x, v[i].y);
        }
        sort(a,a+n);
        return closest(0, n - 1);
    }

};

vector<int> gph[MAXN];
int col[MAXN];

lint dist(DT::pt a, DT::pt b){
    lint dx = b.x - a.x;
    lint dy = b.y - a.y;
    return dx*dx+dy*dy;
}



void dfs(int x, int c, int p = -1){
    col[x] = c;
    for(auto &i : gph[x]){
        if(i != p) dfs(i, 3-c, x);
    }
}

int main(){
    int n;
    scanf("%d",&n);
    vector<DT::pt> a(n);
    map<DT::pt, int> mp;
    int cnt = 0;
    for(auto &i : a){
        scanf("%d %d",&i.x,&i.y);
        mp[i] = cnt++;
    }
    vector<edge> v;
    auto dt = DT::delaunay(a);
    for(int i=0; i<sz(dt); i++){
        auto [x, y, z] = dt[i];
        auto edges = {make_pair(x, y), make_pair(x, z), make_pair(y, z)};
        for(auto &[x, y] : edges){
            v.push_back({mp[x], mp[y], dist(x,y)});
        }
    }
    sort(all(v));
    disj.init(n);
    for(int i=0; i<sz(v); i++){
        if(disj.uni(v[i].s, v[i].e)){
            gph[v[i].s].push_back(v[i].e);
            gph[v[i].e].push_back(v[i].s);
        }
    }
    dfs(0, 1);
    {
    vector<DT::pt> v[2];
    for(int i = 0; i < n; i++){
        v[col[i] - 1].push_back(a[i]);
    }
    printf("%lld\n", min(GGD::getdist(v[0]), GGD::getdist(v[1])));
    for(int i = 0; i < 2; i++){
        printf("%d\n", sz(v[i]));
        for(int j = 0; j < n; j++){
            if(col[j] == i + 1) printf("%d ", j + 1);
        }
        puts("");
    }
    }
}

