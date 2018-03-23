#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n,a[100005], b[100005];
int rev[100005], res[100005];

struct fff{
    int tree[132000], lim;
    void init(int n){
        memset(tree,0,sizeof(tree));
        for(lim = 1; lim <=n; lim <<= 1);
    }
    int sum(int x){
        int res = 0;
        while(x){
            res += tree[x];
            x -= x & -x;
        }
        return res;
    }
    void add(int x){
        while(x <= lim){
            tree[x] ++;
            x += x & -x;
        }
    }
}fff;

void calc(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
        rev[a[i]] = i;
    }
    for (int i=0; i<n; i++) {
        scanf("%d",&b[i]);
        res[rev[b[i]]] = i;
    }
    fff.init(n);
    long long ress = 0;
    for (int i=n-1; i>=0; i--) {
        ress += fff.sum(res[i] + 1);
        fff.add(res[i]+1);
    }
    printf("%lld\n",ress);
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        calc();
    }
}