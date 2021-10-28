#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
const int MAXV = 1000005;

vector<int> merge(vector<int> l, vector<int> r){
    vector<int> ret;
    for(auto &i : l) ret.push_back(i);
    for(auto &i : r) ret.push_back(i);
    assert(sz(ret) == 6);
    sort(all(ret));
    ret.resize(3);
    return ret;
}

vector<int> gen(int x){
    vector<int> ret(3, 1e9);
    fill(ret.begin(), ret.begin() + min(x, 3), 0);
    return ret;
}

struct node{
    node *l, *r;
    vector<int> minv;
    node(){
        l = r = NULL;
        minv = gen(0);
    }
    node(int n){
        l = r = NULL;
        minv = gen(n);
    }
};

void upd(int pos, int s, int e, int v, node *p){
    if(s == e){
        p->minv[0] = v;
        p->minv[1] = p->minv[2] = 1e9;
        return;
    }
    int m = (s + e) / 2;
    if(pos <= m){
        if(!p->l) p->l = new node(m-s+1);
        upd(pos, s, m, v, p->l);
    }
    else{
        if(!p->r) p->r = new node(e-m);
        upd(pos, m+1, e, v, p->r);
    }
    auto l = (p->l ? p->l->minv : gen(m - s + 1));
    auto r = (p->r ? p->r->minv : gen(e - m));
    p->minv = merge(l, r);
}

vector<int> qry(int s, int e, int ps, int pe, node *p){
    if(e < ps || pe < s) return gen(0);
    if(p == NULL) return gen(min(e,pe)-max(s,ps) + 1);
    if(s <= ps && pe <= e) return p->minv;
    int pm = (ps + pe) / 2;
    auto l = qry(s, e, ps, pm, p->l);
    auto r = qry(s, e, pm+1, pe, p->r);
    return merge(l, r);
}

int n, q, a[MAXN];
int low[MAXV];
node *root[MAXV];

vector<pi> factorize(int x){
    vector<pi> v;
    while(x > 1){
        int l = low[x];
        int c = 0;
        while(x % l == 0){
            x /= l;
            c++;
        }
        v.emplace_back(l, c);
    }
    return v;
}

char buf[69];

int main(){
    for(int i = 2; i < MAXV; i++){
        if(!low[i]){
            for(int j = i; j < MAXV; j += i){
                if(!low[j]) low[j] = i;
            }
        }
    }
    scanf("%d %d",&n,&q);
    for(int i = 2; i < MAXV; i++){
        root[i] = new node(n);
    }
    for(int i = 0; i < n; i++){
        scanf("%d",&a[i]);
        auto f = factorize(a[i]);
        for(auto &[x, y] : f){
            upd(i, 0, n - 1, y, root[x]);
        }
    }
    while(q--){
        scanf("%s", buf);
        if(*buf == 'U'){
            int i, x; scanf("%d %d",&i,&x);
            i--;
            auto f = factorize(a[i]);
            for(auto &[x, y] : f){
                upd(i, 0, n - 1, 0, root[x]);
            }
            a[i] = x;
            f = factorize(a[i]);
            for(auto &[x, y] : f){
                upd(i, 0, n - 1, y, root[x]);
            }
        }
        else{
            int l, r, k;
            scanf("%d %d %d",&l,&r,&k);
            l--; r--;
            map<int, int> mp;
            for(int i = l; i <= l + k; i++){
                auto f = factorize(a[i]);
                for(auto &[x, y] : f){
                    auto ans = qry(l, r, 0, n - 1, root[x]);
                    if(ans[k] < 1e8) mp[x] = ans[k];
                }
            }
            lint ret = 1;
            for(auto &[x, y] : mp){
                for(int i = 0; i < y; i++) ret = ret * x;
            }
            printf("%lld\n", ret);
        }
    }
}
