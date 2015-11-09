#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
typedef long long lint;
typedef pair<int,int> pi;
const int mod = 1e6;
const int inf = 1e9;
 
int n, x[250005], v[250005];
int cnt[105];
 
struct node{
    int i, j;
    int track;
    double time;
};
 
bool operator<(node a, node b){
    if(fabs(a.time - b.time) > 1e-8 || a.time > 1e8) return a.time < b.time;
    double col1 = x[a.i] + v[a.i] * a.time;
    double col2 = x[b.i] + v[b.i] * b.time;
    return col1 < col2;
}
 
double curr_time;
 
node make_node(int i, int j){
    double t = 1.0 * (x[j] - x[i]) / (v[i] - v[j]);
    if(t < curr_time) t = 1e9;
    return (node){i,j,-1,t};
}
 
struct rmq{
    node tree[530000];
    int lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        fill(tree,tree+530000,(node){inf,inf,inf,1e9});
    }
    void add(int x, node v){
        v.track = x;
        x += lim;
        tree[x] = v;
        while(x > 1){
            x >>= 1;
            tree[x] = min(tree[2*x],tree[2*x+1]);
        }
    }
    node get(int x){
        return tree[x+lim];
    }
}rmq;
 
int main(){
    scanf("%d",&n);
    lint ret = 0;
    for (int i=0; i<n; i++) {
        scanf("%d %d",&x[i],&v[i]);
        for (int j=v[i]+1; j<100; j++) {
            ret += cnt[j];
            ret %= mod;
        }
        cnt[v[i]]++;
    }
    rmq.init(n);
    for (int i=1; i<n; i++) {
        rmq.add(i,make_node(i-1,i));
    }
    printf("%lld\n",ret % 1000000);
    for (int i=0; i < ret && i < 10000; i++) {
        node t = rmq.tree[1];
        printf("%d %d\n",t.i+1,t.j+1);
        curr_time = t.time;
        if(t.track != 1){
            node u = rmq.get(t.track-1);
            rmq.add(t.track - 1,make_node(u.i,t.j));
        }
        if(t.track != n-1){
            node u = rmq.get(t.track+1);
            rmq.add(t.track + 1,make_node(t.i,u.j));
        }
        node u = make_node(t.j,t.i);
        u.time = 1e9;
        rmq.add(t.track,u);
    }
}