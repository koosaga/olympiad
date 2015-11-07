#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
vector<int> v;
int n,k;
 
int a[200005], b[200005], q[200005];
bool flip[200005];
 
struct rmq{
    int tree[1050000], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        memset(tree,-1,sizeof(tree));
    }
    void add(int x, int v){
        if(x < 0) return;
        x += lim;
        tree[x] = v;
        while(x>1){
            x >>= 1;
            tree[x] = max(tree[2*x],tree[2*x+1]);
        }
    }
    int q(int s, int e){
        s += lim;
        e += lim;
        int r = -1;
        while(s < e){
            if(s%2 == 1) r = max(r,tree[s++]);
            if(e%2 == 0) r = max(r,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) r = max(r,tree[s]);
        return r;
    }
}rmq;
 
struct bit{
    int tree[400005], lim;
    void init(int n){
        lim = n+2;
    }
    void add(int x){
        x+=2;
        while(x <= lim){
            tree[x]++;
            x += x & -x;
        }
    }
    int sum(int x){
        x+=2;
        int r = 0;
        while(x){
            r += tree[x];
            x -= x & -x;
        }
        return r;
    }
}bit, bit2;
 
void input(){
    scanf("%d %d",&n,&k);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&a[i],&b[i]);
        if(a[i] > b[i]){
            swap(a[i],b[i]);
            flip[i] = 1;
        }
        v.push_back(a[i]);
        v.push_back(b[i]);
    }
    sort(v.begin(),v.end());
    v.resize(unique(v.begin(),v.end()) - v.begin());
    bit.init((int)v.size());
    rmq.init((int)v.size());
    for (int i=0; i<n; i++) {
        a[i] = (int)(lower_bound(v.begin(),v.end(),a[i]) - v.begin());
        b[i] = (int)(lower_bound(v.begin(),v.end(),b[i]) - v.begin());
    }
    for (int i=0; i<k; i++) {
        scanf("%d",&q[i]);
        q[i] = (int)(upper_bound(v.begin(),v.end(),q[i]) - v.begin()) - 1;
    }
}
 
int table[200005];
 
void solve(){
    for (int i=0; i<k; i++) {
        rmq.add(q[i],i);
    }
    for (int i=0; i<n; i++) {
        table[i] = rmq.q(a[i],b[i]-1);
    }
    for (int i=0; i<k; i++) {
        bit.add(q[i]);
    }
    for (int i=0; i<n; i++) {
        if(table[i] >= 0) flip[i] = 1;
    }
    vector<pi> v2;
    for (int i=0; i<n; i++) {
        v2.push_back(pi(table[i]+1,i));
    }
    sort(v2.begin(),v2.end());
    bit2.init((int)v.size());
    int pt = k-1, cnt = 0;
    for (int i=(int)v2.size()-1; i>=0; i--) {
        while (pt >= v2[i].first) {
            bit2.add(q[pt]);
            cnt++;
            pt--;
        }
        int sum = cnt - bit2.sum(b[v2[i].second] - 1);
        flip[v2[i].second] ^= (sum & 1);
    }
}
 
int main(){
    input();
    solve();
    long long ret = 0;
    for (int i=0; i<n; i++) {
        if(flip[i]) ret += v[b[i]];
        else ret += v[a[i]];
    }
    printf("%lld",ret);
}