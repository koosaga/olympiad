#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int,int> pi;

int n;
pi a[1000005];
int up[1000005];
int dp2[1000005];

void track(int x){
    if(x == 0) return;
    track(up[x]);
    printf("%d ",x - up[x]);
    for (int i=up[x]+1; i<=x; i++) {
        printf("%d ",a[i].second);
    }
    puts("");
}

int dp_max[1000005], max_pos[1000005];

int trial(int x){
    for (int i=1; i<n; i++) {
        dp_max[i] = dp_max[i-1];
        max_pos[i] = max_pos[i-1];
        dp2[i] = -1e9;
        if(i - a[i].first < 0) continue;
        int dp_val = dp_max[i - a[i].first];
        int track = max_pos[i - a[i].first];
        if(dp_max[i] > dp_val + 1 || track < i - x) continue;
        dp2[i] = dp_val + 1;
        up[i] = track;
        dp_max[i] = dp_val + 1;
        max_pos[i] = i;
    }
    dp2[n] = -1e9;
    for (int j=n-x; j<=n - a[n].first; j++) {
        if(dp2[n] < dp2[j] + 1){
            dp2[n] = dp2[j] + 1;
            up[n] = j;
        }
    }
    return dp2[n];
}

int main(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i].first);
        a[i].second = i;
    }
    sort(a+1,a+n+1);
    int t = trial(n);
    printf("%d\n",t);
    int s = a[n].first, e = n;
    while (s != e) {
        int m = (s+e)/2;
        if(trial(m) == t) e = m;
        else s = m+1;
    }
    // printf("%d\n",s);
    trial(s);
    track(n);
}