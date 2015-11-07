#include <cstdio>
#include <algorithm>
using namespace std;

int a[100005], n, t;

int trial(int x){
    int p = 0;
    int cnt = 1;
    for (int i=0; i<n; i++) {
        if(a[p] + x <= a[i]){
            p = i;
            cnt++;
        }
    }
    return cnt;
}

int main(){
    scanf("%d %d",&n,&t);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    sort(a,a+n);
    int s = 0, e = 1e9;
    while (s != e) {
        int m = (s+e+1)/2;
        if(trial(m) >= t) s = m;
        else e = m-1;
    }
    printf("%d",s);
}#include <cstdio>
#include <algorithm>
using namespace std;

int a[100005], n, t;

int trial(int x){
    int p = 0;
    int cnt = 1;
    for (int i=0; i<n; i++) {
        if(a[p] + x <= a[i]){
            p = i;
            cnt++;
        }
    }
    return cnt;
}

int main(){
    scanf("%d %d",&n,&t);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    sort(a,a+n);
    int s = 0, e = 1e9;
    while (s != e) {
        int m = (s+e+1)/2;
        if(trial(m) >= t) s = m;
        else e = m-1;
    }
    printf("%d",s);
}