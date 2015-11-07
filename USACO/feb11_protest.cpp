#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
 
pi b[100005];
int n,a[100005],dp[100005];
int mod = 1e9 + 9;
 
struct bit{
    int tree[131073], lim;
    void init(int n){
        n++;
        for(lim = 1; lim <= n; lim <<= 1);
    }
    void add(int x, int v){
        x++;
        while(x <= lim){
            tree[x] += v;
            tree[x] %= mod;
            x += x & -x;
        }
    }
    int sum(int x){
        x++;
        int r = 0;
        while (x){
            r += tree[x];
            r %= mod;
            x -= x & -x;
        }
        return r;
    }
}bit;
 
int main(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
    }
    for (int i=0; i<=n; i++) {
        if(i) a[i] += a[i-1];
        b[i] = pi(a[i],i);
    }
    bit.init(n+1);
    sort(b,b+n+1);
    dp[0] = 1;
    for (int i=0; i<=n; i++) {
        int pos = b[i].second;
        dp[pos] += bit.sum(pos);
        bit.add(pos,dp[pos]);
    }
    printf("%d",dp[n]);
}