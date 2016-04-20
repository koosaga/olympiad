#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
typedef long long lint;
 
int x[150005], y[150005], n;
  
int h;
long long res;
  
struct rmq{
    pi tree[530000];
    int lim;
    void init(int n, int *a){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=0; i<n; i++){
            tree[i+lim] = pi(a[i],i);
        }
        for(int i=lim-1; i; i--){
            tree[i] = min(tree[2*i],tree[2*i+1]);
        }
    }
    int q(int s, int e){
        s += lim;
        e += lim;
        pi t(1e9,1e9);
        while(s < e){
            if(s%2 == 1) t = min(t,tree[s++]);
            if(e%2 == 0) t = min(t,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) t = min(t,tree[s]);
        return t.second;
    }
}rmq;
 
priority_queue<lint> pq;
 
lint f(int s, int e){
    if(s >= e) return 0;
    int pos = rmq.q(s,e-1);
    int ph = h;
    h = y[pos];
    lint f1 = f(s, pos);
    lint f2 = f(pos+1, e);
    pq.push(min(f1, f2));
    h = ph;
    return max(f1, f2) + 1ll * (x[e] - x[s]) * (y[pos] - ph);
}
  
int main(){
    scanf("%d",&n);
    n/=2;
    for (int i=0; i<n; i++) {
        scanf("%*d %*d %d %d",&x[i],&y[i]);
    }
    rmq.init(n,y);
    pq.push(f(0, n-1));
    int k;
    scanf("%d",&k);
    lint ret = 0;
    for(int i=0; i<k && !pq.empty(); i++){
        ret += pq.top();
        pq.pop();
    }
    printf("%lld",ret);
}