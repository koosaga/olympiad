#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 3000005;

struct bit{
    int tree[MAXN];
    void add(int x, int v){
        for(int i = x+1; i < MAXN; i += i & -i) tree[i] += v;
    }
    int query(int x){
        int ret = 0;
        for(int i = x+1; i; i -= i & -i) ret += tree[i];
        return ret;
    }
    void clear(){
        memset(tree, 0, sizeof(tree));
    }
}bit;

struct query{
    int x, y, dx, idx;
    bool operator<(const query &q)const{
        return x < q.x;
    }
};

lint solve(vector<int> p){
    int n = sz(p);
    vector<vector<int>> upd(n + 1);
    vector<lint> delta(n + 1);
    vector<pi> point;
    vector<query> event;
    auto AddQuery = [&](int sx, int ex, int sy, int ey, int dx, int idx){
        if(ex>=0&&ey>=0) event.push_back({ex, ey, dx, idx});
        if(sx>=1&&ey>=0) event.push_back({sx-1, ey, -dx, idx});
        if(ex>=0&&sy>=1) event.push_back({ex, sy-1, -dx, idx});
        if(sx>=1&&sy>=1) event.push_back({sx-1, sy-1, +dx, idx});
    };
    for(int i = 0; i < n; i++){
        if(p[i] < i) p[i] += n;
        delta[p[i] - i + 1] += -n+1+2*i;
        point.emplace_back(p[i] - i, p[i]);
        point.emplace_back(p[i] - i + n, p[i] + n);;
        AddQuery(0, p[i] - i + n, p[i] + n + 1, 3 * n - 1, +2, p[i]-i+1);
        AddQuery(p[i] - i, 3 * n - 1, 0, p[i] - 1, -2, p[i]-i+1);
    }
    for(int i = n - 1; i >= 0; i--){
        delta[0] += bit.query(p[i] + n) - bit.query(p[i] - 1);
        bit.add(p[i], 1);
    }
    sort(all(point));
    sort(all(event));
    bit.clear();
    int ptr = 0;
    for(auto &x : event){
        while(ptr < sz(point) && point[ptr].first <= x.x) bit.add(point[ptr++].second, 1);
        delta[x.idx] += x.dx * bit.query(x.y);
    }
    for(int k = 1; k < n; k++){
        delta[k] += delta[k - 1];
    }
    delta.pop_back();
    return 1ll * n * (n - 1) / 2 - *max_element(all(delta));
}

int main(){
    int n;
    scanf("%d %*d",&n);
    vector<pi> a(n);
    vector<int> v;
    for(auto &[x, y] : a){
        scanf("%d %d",&x,&y);
        v.push_back(y);
    }
    sort(all(a));
    sort(all(v));
    vector<int> p(n);
    for(int i = 0; i < n; i++){
        p[i] = lower_bound(all(v), a[i].second) - v.begin();
    }
    cout << solve(p) << endl;
}
