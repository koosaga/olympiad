#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long lint;
 
int a[100005], n;
lint sum;
 
lint f(lint a, lint b){
    return min(a,min(b,sum - a - b));
}
 
bool trial(lint x){
    int pt = 0;
    lint box = 0;
    while (box < x && pt < n) {
        box += a[pt++];
    }
    int mid = pt;
    lint box2 = 0;
    while (box2 < x && mid < n) {
        box2 += a[mid++];
    }
    if(f(box,box2) >= x) return 1;
    for (int i=0; i<n; i++) {
        box -= a[i];
        while (box < x && pt < n) {
            box += a[pt];
            box2 -= a[pt++];
        }
        while (box2 < x && mid < n) {
            box2 += a[mid++];
        }
        if(f(box,box2) >= x) return 1;
        if(mid == n && box2 < x) return 0;
    }
    return 0;
}
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
        sum += a[i];
    }
    lint s = 0, e = sum / 3;
    while (s != e) {
        lint m = (s+e+1)/2;
        if(trial(m)) s = m;
        else e = m-1;
    }
    printf("%lld",s);
}