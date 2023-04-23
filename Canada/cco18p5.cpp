#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 1000005;
const int MAXT = 2100000;

struct seg{
    pi tree[MAXT];
    int lim;
    void init(int n, int *a){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=0; i<n; i++) tree[i + lim] = pi(a[i], i);
        for(int i=lim-1; i; i--) tree[i] = max(tree[2*i], tree[2*i+1]);
    }
    void upd(int x, int v){
        x += lim;
        tree[x] = pi(v, x - lim);
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x], tree[2*x+1]);
        }
    }
    pi query(int s, int e){
        s += lim;
        e += lim;
        pi ret(0, 0);
        while(s < e){
            if(s%2 == 1) ret = max(ret, tree[s++]);
            if(e%2 == 0) ret = max(ret, tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret = max(ret,tree[s]);
        return ret;
    }
}seg;

int n, k, q, a[MAXN];
pi mxq[MAXN];
int ans[MAXN];
priority_queue<pi> pq;

int query() {
    while(!pq.empty() && ans[pq.top().second] != pq.top().first){
        pq.pop();
    }
    return pq.top().first;
}

void update(int x, int p){
    seg.upd(x, p);
    mxq[x / k] = seg.query((x / k) * k, min(n, (x / k + 1) * k) - 1);
    for(auto &i : {x/k - 1, x/k, x/k+1}){
        int st = max(mxq[i].second - k + 1, 0);
        int ed = min(mxq[i].second + k - 1, n-1);
        ans[i] = mxq[i].first + 
            max(seg.query(st, mxq[i].second-1).first,
                    seg.query(mxq[i].second+1, ed).first);
        pq.push(pi(ans[i], i));
    }
}

int main(){
    scanf("%d %d %d",&n,&k,&q);
    for(int i=0; i<n; i++) scanf("%d",&a[i]);
    seg.init(n, a);
    for(int i=0; i<(n+k-1)/k; i++){
        mxq[i] = seg.query(i * k, min((i + 1) * k, n) - 1);
        int st = max(mxq[i].second - k + 1, 0);
        int ed = min(mxq[i].second + k - 1, n-1);
        ans[i] = mxq[i].first + 
            max(seg.query(st, mxq[i].second-1).first,
                    seg.query(mxq[i].second+1, ed).first);
        pq.push(pi(ans[i], i));
    }
    int ans = query();
    printf("%d\n", ans);
    while(q--){
        int x, p; scanf("%d %d",&x,&p);
        x--;
        update(x, p);
        ans = query();
        printf("%d\n", ans);
    }
}

