#include <cstdio>
#include <algorithm>
using namespace std;
 
int val[3000005], n;
int a[300005], cost[3] = {1,2,5};
 
struct bit{
    int tree[3000005], lim;
    void init(int maxelem){
        lim = maxelem;
        for(int i=1; i<=lim; i++) add(i,1);
    }
    void add(int x, int v){
        while(x <= lim){
            tree[x] += v;
            x += x & -x;
        }
    }
    int kth(int x){
        int pos = 0, ret = 0;
        for(int i=21; i>=0; i--){
            if((pos | (1<<i)) <= lim && tree[pos | (1<<i)] < x){
                pos |= (1<<i);
                x -= tree[pos];
            }
        }
        return pos + 1;
    }
}bit;
 
int main(){
    scanf("%d",&n);
    fill(a,a+n,1);
    for(int i=0; i<3; i++){
        for(int j=0; j<n; j++){
            int t;
            scanf("%d",&t);
            val[a[j]] += cost[i];
            val[a[j]+t] -= cost[i];
            a[j] += t;
        }
    }
    int maxelem = *max_element(a,a+n);
    for(int i=1; i<=maxelem; i++){
        val[i] += val[i-1];
    }
    bit.init(maxelem);
    int q;
    scanf("%d",&q);
    while(q--){
        int t;
        scanf("%d",&t);
        t = bit.kth(t);
        printf("%d\n",val[t]);
        bit.add(t,-1);
    }
}