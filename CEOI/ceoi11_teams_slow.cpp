#include <cstdio>
#include <algorithm>
#include <deque>
#include <cstring>
using namespace std;
typedef pair<int,int> pi;

int n;
pi a[1000005];
int up[1000005];
int dp2[1000005];

struct rmq{
    int lim;
    pi tree[2100005];
    void init(int n){
        fill(tree,tree+2100005,pi(-2,-1));
        for(lim = 1; lim <= n; lim <<= 1);
    }
    void add(int x, pi v){
        x += lim;
        tree[x] = max(tree[x],v);
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x],tree[2*x+1]);
        }
    }
    pi q(int s, int e){
        s += lim;
        e += lim;
        pi ret(-2,-1);
        while(s < e){
            if(s%2 == 1) ret = max(ret,tree[s++]);
            if(e%2 == 0) ret = max(ret,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret = max(ret,tree[s]);
        return ret;
    }
}rmq;

void track(int x){
    if(x == 0) return;
    track(up[x]);
    printf("%d ",x - up[x]);
    for (int i=up[x]+1; i<=x; i++) {
        printf("%d ",a[i].second);
    }
    puts("");
}

int trial(int x){
    rmq.init(n);
    rmq.add(0,pi(0,0));
    for (int i=1; i<=n; i++) {
        pi t = rmq.q(max(i-x,0),i - a[i].first);
        dp2[i] = t.first + 1;
        up[i] = t.second;
        rmq.add(i,pi(dp2[i],i));
    }
    return dp2[n];
}

int main(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i].first);
        a[i].second = i;
    }
    sort(a+1,a+n+1);
    int t = trial(n);
    printf("%d\n",t);
    int s = 0, e = n;
    while (s != e) {
        int m = (s+e)/2;
        if(trial(m) == t) e = m;
        else s = m+1;
    }
    trial(s);
    track(n);
}