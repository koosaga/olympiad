#include <cstdio>
#include <algorithm>
using namespace std;

int a[1000005], n;
int dt[1000005];

int main(){
    scanf("%d",&n);
    for (int i=1; i<n; i++) {
        scanf("%d",&a[i]);
    }
    long long ret = 0;
    int mp = 0, st_pos = -1;
    for (int i=0; i<n; i++) {
        if(mp < a[i] - 2){
            puts("0");
            return 0;
        }
        if(mp == a[i] - 2){
            if(st_pos != -1){
                puts("0");
                return 0;
            }
            st_pos = i;
        }
        mp = max(mp,a[i]);
        dt[i] = mp + 1;
        ret += dt[i];
    }
    if(st_pos != -1){
        int edp = st_pos;
        for (int i=st_pos; i>=0; i--) {
            if(a[i] == a[st_pos] - 2) edp = i;
        }
        printf("%d",st_pos - edp);
        return 0;
    }
    for (int i=1; i<n; i++) {
        if(dt[i] >= a[i]) ret--;
    }
    printf("%lld",ret);
}