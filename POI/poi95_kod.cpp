#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n,a[100005];
int ret[100005], q[100005];
vector<int> v;

struct bit{
    int tree[100005];
    void add(int x, int v){
        while(x <= n){
            tree[x] += v;
            x += x & -x;
        }
    }
    int kth(int k){
        int ret = 0;
        for(int i=16; i>=0; i--){
            int piv = 1<<i;
            if(ret + piv <= n && tree[ret + piv] < k){
                k -= tree[ret+piv];
                ret += piv;
            }
        }
        ret++;
        return ret;
    }
}bit;

int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        bit.add(i + 1, 1);
        scanf("%d",&q[i]);
    }
    for (int i=n-1; i>=0; i--) {
        q[i] = i - q[i] + 1;
        if(q[i] <= 0 || q[i] > i + 1){
            puts("NIE");
            return 0;
        }
        ret[i] = bit.kth(q[i]);
        bit.add(ret[i],-1);
    }
    for (int i=0; i<n; i++) {
        printf("%d\n",ret[i]);
    }
}

