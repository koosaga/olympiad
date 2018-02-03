#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int inf = 2e9 + 100;

typedef pair<int, int> pi;

struct seg{
    pi tree[530000];
    int lim;
    void init(vector<pi> &v){
        for(lim = 1; lim <= v.size(); lim <<= 1);
        for(int i=0; i<v.size(); i++){
            tree[i + lim] = pi(-inf, i);
        }
        for(int i=lim-1; i; i--){
            tree[i] = max(tree[2*i], tree[2*i+1]);
        }
    }
    pi query(int s, int e){
        s += lim;
        e += lim;
        pi ret(-inf, -inf);
        while(s < e){
            if(s%2 == 1) ret = max(ret, tree[s++]);
            if(e%2 == 0) ret = max(ret, tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret = max(ret, tree[s]);
        return ret;
    }
    void update(int x, int v){
        x += lim;
        tree[x].first = v;
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x], tree[2*x+1]);
        }
    }
}seg;

int n, t[MAXN], x[MAXN], y[MAXN];
vector<pi> v;
int cur_assoc[MAXN];

bool inside(int i, pi p){
    int dx = x[i] - p.first;
    int dy = y[i] - p.second;
    return 1ll * dx * dx + 1ll * dy * dy < 1ll * y[i] * y[i];
}

int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d %d",&t[i],&x[i],&y[i]);
        if(t[i] == 1) v.push_back(pi(x[i] - y[i], x[i] + y[i]));
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    seg.init(v);
    for(int i=0; i<n; i++){
        if(t[i] == 1){
            auto l = lower_bound(v.begin(), v.end(), pi(x[i] - y[i], x[i] + y[i])) - v.begin();
            cur_assoc[l] = i + 1;
            seg.update(l, x[i] + y[i]);
        }
        else{
            int pos = lower_bound(v.begin(), v.end(), pi(x[i], -2e9 - 5)) - v.begin();
            vector<int> v;
            while(true){
                auto l = seg.query(0, pos - 1);
                if(l.first <= x[i]) break;
                v.push_back(l.second);
                seg.update(l.second, -inf);
            }
            int ans = -1;
            for(auto &j : v){
                if(inside(cur_assoc[j] - 1, pi(x[i], y[i]))){
                    ans = j;
                }
                else{
                    seg.update(j, ::v[j].second);
                }
            }
            if(ans == -1) puts("-1");
            else{
                printf("%d\n", cur_assoc[ans]);
                seg.update(ans, -inf);
            }
        }
    }
}