#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long lint;

int a[1000005], n;

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0; i<n; i++){
            scanf("%d",&a[i]);
        }
        sort(a, a+n);
        int m1 = a[0], m2 = a[0], ret = 0;
        for(int i=1; i<n-1; i++){
            if(m1 < m2){
                ret = max(ret, a[i] - m1);
                m1 = a[i];
            }
            else{
                ret = max(ret, a[i] - m2);
                m2 = a[i];
            }
        }
        ret = max(ret, a[n-1] - m1);
        ret = max(ret, a[n-1] - m2);
        printf("%d\n",ret);
    }

}