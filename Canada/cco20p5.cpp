#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define ends fuck
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
const int MAXN = 1000005;
const int MAXT = 2100005;
const int inf = 1e9;

int q;
char buf[10];

struct event{
    int pos, typ, idx;
    bool operator<(const event &e)const{
        return pi(pos, -typ) < pi(e.pos, -e.typ);
    }
};

struct node{
    int l, r, opt;
    node operator+(const node &n)const{
        node ret;
        ret.l = max(l, n.l);
        ret.r = min(r, n.r);
        ret.opt = min({opt, n.opt, n.r - l});
        return ret;
    }
};

struct seg{
    node tree[MAXT];
    int lim;
    void init(int n){
        fill(tree, tree + MAXT, (node){-inf, inf, inf});
        for(lim = 1; lim <= n; lim <<= 1);
    }
    node query(int s, int e){
        s += lim;
        e += lim;
        node retL = (node){-inf, inf, inf};
        node retR = (node){-inf, inf, inf};
        while(s < e){
            if(s%2 == 1) retL = retL + tree[s++];
            if(e%2 == 0) retR = tree[e--] + retR;
            s >>= 1;
            e >>= 1;
        }
        if(s == e) retL = retL + tree[s];
        return retL + retR;
    }
    void upd(int x, node v){
        x += lim;
        tree[x] = v;
        while(x > 1){
            x >>= 1;
            tree[x] = tree[2*x] + tree[2*x+1];
        }
    }
}seg;

vector<event> E;
pi a[MAXN];
bool mark[MAXN];
map<pi, vector<int>> mp;
pi ends[MAXN];

node range_query(int v){
    auto st = lower_bound(all(E), (event){v, 69, -1});
    auto ed = lower_bound(all(E), (event){v + 1, 69, -1});
    return seg.query(st - E.begin(), ed - E.begin() - 1);
}

void solve(){
    seg.init(sz(E));
    priority_queue<pi> Lend;
    priority_queue<pi, vector<pi>, greater<pi>> Rend;
    for(int i=0; i<q; i++){
        if(a[i].first != -1){
            seg.upd(ends[i].first, (node){-inf, a[i].second, inf});
            seg.upd(ends[i].second, (node){a[i].first, inf, inf});
            Lend.emplace(a[i].first, i);
            Rend.emplace(a[i].second, i);
        }
        else{
            int v = a[i].second;
            seg.upd(ends[v].first, (node){-inf, inf, inf});
            seg.upd(ends[v].second, (node){-inf, inf, inf});
            mark[v] = 1;
        }
        while(sz(Lend) && mark[Lend.top().second]) Lend.pop();
        while(sz(Rend) && mark[Rend.top().second]) Rend.pop();
        if(Lend.top().first < Rend.top().first){
            auto q1 = range_query(Lend.top().first);
            auto q2 = range_query(Rend.top().first);
            printf("%d\n", q1.r - q2.l);
        }
        else{
            printf("%d\n", seg.tree[1].opt);
        }
    }
}

int main(){
    scanf("%d",&q);
    for(int i=0; i<q; i++){
        scanf("%s %d %d",buf,&a[i].first,&a[i].second);
        if(*buf == 'A'){
            E.push_back({a[i].first, -1, i});
            E.push_back({a[i].second, +1, i});
            mp[a[i]].push_back(i);
        }
        else{
            int idx = mp[a[i]].back();
            mp[a[i]].pop_back();
            a[i] = pi(-1, idx);
        }
    }
    sort(all(E));
    for(int i=0; i<sz(E); i++){
        if(E[i].typ == -1) ends[E[i].idx].first = i;
        if(E[i].typ == +1) ends[E[i].idx].second = i;
    }
    solve();
}
