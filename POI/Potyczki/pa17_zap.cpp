#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int MAXN = 200005;

int n, m;
lint a[MAXN], ans[MAXN];
pi p[MAXN];

set<pi> s;

struct node{
    pi l, r;
    lint calc_event()const{
        int x = l.first, y = r.first;
        return (a[y] - a[x] + y - x - 1) / (y - x);
    }
    bool operator<(const node &n)const{
        return calc_event() > n.calc_event();
    }
};

priority_queue<node> pq;
lint sum[MAXN];

void make_event(pi l, pi r){
    pq.push((node){l, r});
}

pi foo(pi x){
    int q = (x.second - x.first + 1);
    lint ret = q * a[x.first];
    ret -= sum[x.second] - (x.first ? sum[x.first - 1] : 0);
    return pi(ret, 1ll * q * (q - 1) / 2);
}

pi fuck;

lint cost(lint d){
    return fuck.first + d * fuck.second;
}

void ERASE(pi x){
    fuck.first -= foo(x).first;
    fuck.second -= foo(x).second;
    s.erase(x);
}

void INSERT(pi x){
    fuck.first += foo(x).first;
    fuck.second += foo(x).second;
    s.insert(x);
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i=1; i<=n; i++){
        scanf("%lld",&a[i]);
        sum[i] = sum[i-1] + a[i];
    }
    for(int i=0; i<m; i++){
        scanf("%lld",&p[i].first);
        p[i].second = i;
    }
    sort(p, p + m);
    for(int i=0; i<=n; i++){
        INSERT(pi(i, i));
        if(i) make_event(pi(i-1, i-1), pi(i, i));
    }
    for(int i=0; i<m; i++){
        while(sz(pq) && pq.top().calc_event() <= p[i].first){
            auto x = pq.top(); pq.pop();
            if(!s.count(x.l) || !s.count(x.r)) continue;
            ERASE(x.l);
            ERASE(x.r);
            pi p(x.l.first, x.r.second);
            INSERT(p);
            auto it = s.find(p);
            if(it != s.begin()) make_event(*prev(it), *it);
            if(next(it) != s.end()) make_event(*it, *next(it));
        }
        ans[p[i].second] = cost(p[i].first);
    }
    for(int i=0; i<m; i++) printf("%lld\n", ans[i]);
}
