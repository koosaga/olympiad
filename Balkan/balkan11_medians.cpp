#include <cstdio>
  
struct bit{
    int tree[270000], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
    }
    void add(int x){
        printf("%d ",x);
        while(x <= lim){
            tree[x]++;
            x += x & -x;
        }
    }
    int sum(int x){
        int res = 0;
        while(x){
            res += tree[x];
            x -= x & -x;
        }
        return res;
    }
}bit;
  
int v[200005];
int main(){
    int n,t;
    scanf("%d",&n);
    bit.init(2*n);
    int lo = 1, hi = 2*n-1;
    scanf("%d",&t);
    bit.add(t);
    v[t] = 1;
    for (int i=1; i<n; i++) {
        scanf("%d",&t);
        int cnt = 0;
        if(!v[t]){
            v[t] = 1;
            bit.add(t);
            cnt++;
        }
        while(bit.sum(t) < i+1){
            while(v[lo]) lo++;
            v[lo] = 1;
            bit.add(lo);
            cnt++;
        }
        while(cnt < 2){
            while(v[hi]) hi--;
            v[hi] = 1;
            bit.add(hi);
            cnt++;
        }
    }
}