#include <cstdio>

int m,n,a[20005];
int cnt[1005], cnt2[1005];

int trial(int x){
    cnt[a[x-1]]++;
    cnt2[a[x-1]]--;
    cnt2[a[2*x-2]]++;
    cnt2[a[2*x-1]]++;
    int canput = 0;
    for (int i=m; i>=0; i--) {
        canput -= cnt[i];
        if(canput < 0) return 0;
        canput += cnt2[i];
    }
    return 1;
}

int main(){
    scanf("%d %d",&m,&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    int s = 0;
    for (int i=1; 2*i-1<=n; i++) {
        if(trial(i)) s = i;
    }
    printf("%d",s);
}