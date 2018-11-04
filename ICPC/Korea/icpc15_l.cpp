#include <cstdio>
#include <algorithm>
using namespace std;

int n, m, a[105];

int get(int* a, int l){
    int ret = 0;
    for(int i=0; i<l; i++){
        ret = ret * 10 + a[i];
    }
    return ret;
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int s, e, ret = 0;
        scanf("%d %d",&n,&m);
        for(int i=0; i<m; i++){
            scanf("%d",&a[i]);
        }
        s = get(a, m);
        for(int i=0; i<m; i++){
            scanf("%d",&a[i]);
        }
        e = get(a, m);
        for(int i=0; i<n; i++){
            scanf("%d",&a[i]);
        }
        for(int i=0; i<n; i++){
            int t = get(a, m);
            if(s <= t && t <= e) ret++;
            rotate(a, a+1, a+n);
        }
        printf("%d\n",ret);
    }
}