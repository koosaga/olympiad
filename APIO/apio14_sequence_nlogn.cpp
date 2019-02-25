#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, int> pi;
const int MAXN = 100005;

struct line{ lint x, y; int cnt, idx; };

struct cht{
    vector<line> v;
    int p = 0;
    void clear(){ v.clear(); p = 0; }
    bool bad(line x, line y, line z){
        return (llf)(x.y - y.y) / (y.x - x.x) >= (llf)(z.y - y.y) / (y.x - z.x);
    }
    void add(line l){
        if(v.size() > p && v.back().x == l.x){
            if(l.y < v.back().y) l = v.back();
            v.pop_back();
        }
        while(v.size() >= p + 2 && bad(v[v.size()-2], v.back(), l)){
            v.pop_back();
        }
        v.push_back(l);
    }
    tuple<lint, int, int> query(lint x){
        while(p + 1 < v.size() && v[p].x * x + v[p].y <= v[p+1].x * x + v[p+1].y) p++;
        return make_tuple(v[p].x * x + v[p].y, v[p].cnt, v[p].idx);
    }
}cht;

int n, k, a[MAXN], trk[MAXN];
pi dp[MAXN];

pi trial(lint l){
    cht.clear();
    for(int i=1; i<=n; i++){
        cht.add({a[i-1], dp[i-1].first - l, dp[i-1].second, i-1});
        lint x; int y, z; 
        tie(x, y, z) = cht.query(2 * (a[i] - a[n]));
        dp[i] = pi(x + 2ll * (a[n] - a[i]) * a[i], y + 1);
        trk[i] = z;
    }
    return dp[n];
}

vector<int> trace(lint l){
    trial(l);
    vector<int> v;
    for(int i=n; i; i=trk[i]){
        v.push_back(i);
    }
    v.push_back(0);
    return vector<int>(v.rbegin(), v.rend());
}

void printv(vector<int> v){
    lint ret = 0;
    for(int i=1; i<v.size(); i++){
        ret += 1ll * (a[v[i]] - a[v[i-1]]) * (a[n] - a[v[i]]);
    }
    printf("%lld\n", ret);
    for(int i=1; i+1<v.size(); i++) printf("%d ", v[i]);
    exit(0);
}

int main(){
    scanf("%d %d",&n,&k); k++;
    for (int i=0; i<n; i++) {
        int t;
        scanf("%d",&t);
        a[i+1] = a[i] + t;
    }
    lint s = 0, e = 1e17;
    while(s != e){
        lint m = (s+e)/2;
        if(trial(2 * m + 1).second <= k) e = m;
        else s = m + 1;
    }
    vector<int> l = trace(2 * s + 1);
    vector<int> r = trace(2 * s - 1);
    if(l.size() == k + 1) printv(l);
    if(r.size() == k + 1) printv(r);
    for(int i=0; i+1<r.size(); i++){
        auto idx = upper_bound(l.begin(), l.end(), r[i]) - l.begin();
        if(l[idx] >= r[i+1] && (i + 1) + (l.size() - idx) == k + 1){
            vector<int> v;
            for(int j=0; j<=i; j++) v.push_back(r[j]);
            for(int j=idx; j<l.size(); j++) v.push_back(l[j]);
            printv(v);
        }
    }
    assert(0);
}

