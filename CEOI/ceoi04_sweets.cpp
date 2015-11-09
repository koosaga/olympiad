#include <cstdio>
#include <cstring>
const int mod = 2004;

int n, a[11];

int bino(int x, int y){
    if(x < y) return 0;
    int cnt[11] = {}, ret = 1;
    for (int i=1; i<=y; i++) {
        int t = x + 1 - i;
        for (int j=2; j<=y; j++){
            while (t % j == 0) {
                cnt[j]++;
                t /= j;
            }
        }
        t %= mod;
        ret *= t;
        ret %= mod;
    }
    for (int i=2; i<=y; i++) {
        int t = i;
        for (int j=2; j<=y; j++){
            while (t % j == 0) {
                cnt[j]--;
                t /= j;
            }
        }
    }
    for (int i=2; i<=y; i++) {
        while (cnt[i]) {
            ret *= i;
            ret %= mod;
            cnt[i]--;
        }
    }
    return ret;
}

int main(){
    int t,u;
    scanf("%d %d %d",&n,&t,&u);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    a[n++] = u - t;
    int ret = 0;
    for (int i=0; i<(1<<n); i++) {
        int cnt = 0, del = u;
        for (int j=0; j<n; j++) {
            if((i >> j) & 1){
                del -= a[j] + 1;
                cnt++;
            }
        }
        if(cnt % 2 == 0){
            ret += bino(del + n - 1, n-1);
        }
        else{
            ret -= bino(del + n - 1, n-1);
        }
        ret += mod;
        ret %= mod;
    }
    printf("%d",ret);
}