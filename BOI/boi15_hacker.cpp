#include <cstdio>
#include <deque>
#include <algorithm>
using namespace std;
 
int a[500005], n;
 
int f(int s, int e){
    if(s <= 0){
        return a[e] + (a[n] - a[s+n-1]);
    }
    return a[e] - a[s-1];
}
 
int px[500005], qx[500005];
deque<int> dq, num;
 
int main(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
        a[i] += a[i-1];
    }
    for (int i=1; i<=n; i++) {
        px[i-1] = f(i - (n-1) / 2,i);
    }
    for (int i=0; i<n+(n-1)/2; i++) {
        if(!num.empty() && num.front() == i - (n+1)/2){
            num.pop_front();
            dq.pop_front();
        }
        while (!dq.empty() && dq.back() > px[i%n]) {
            num.pop_back();
            dq.pop_back();
        }
        dq.push_back(px[i%n]);
        num.push_back(i);
        if(i - (n-1)/2 >= 0){
            qx[i - (n-1)/2] = dq.front();
        }
    }
    printf("%d",*max_element(qx,qx+n));
}