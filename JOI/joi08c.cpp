#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

priority_queue<int,vector<int>,greater<int> > pq;

int a[2001];
int b[510000],piv;

int main(){
    int n,res = 0,m;
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
    }
    for (int i=0; i<=n; i++) {
        for (int j=i; j<=n; j++) {
            pq.push(a[i]+a[j]);
        }
    }
    while (!pq.empty()) {
        if(!piv || b[piv-1] != pq.top()){
            b[piv++] = pq.top();
        }
        pq.pop();
    }
    for (int i=0; i<piv; i++) {
        if(m < b[i]) break;
        int* pt = upper_bound(b,b+piv,m-b[i]) - 1;
        res = max(res, b[i] + *pt);
    }
    printf("%d",res);
}