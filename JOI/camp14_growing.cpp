#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;

int n, a[300005];
pi p[300005];

struct bit{
    int tree[300005], lim;
    void init(int n){
        lim = n + 1;
    }
    void add(int x, int v){
        x++;
        while(x <= lim){
            tree[x] += v;
            x += x & -x;
        }
    }
    int sum(int x){
        x++;
        int ret = 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
}bit;

int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
        p[i] = pi(a[i],i);
    }
    sort(p,p+n);
    long long ret = 0;
    bit.init(n);
    for (int i=0; i<n; i++) {
        int e = i;
        while (e < n && p[e].first == p[i].first) e++;
        for (int j=i; j<e; j++) {
            bit.add(p[j].second,1);
        }
        for (int j=i; j<e; j++) {
            int q = p[j].second;
            ret += min(q - bit.sum(q-1),(n - 1 - q) - (bit.sum(n) - bit.sum(q)));
        }
        i = e-1;
    }
    printf("%lld",ret);
}