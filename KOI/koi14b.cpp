#include <cstdio>
#include <algorithm>
#include <deque>
using namespace std;
 
struct x{int s,e,x;}a[500005];
bool cmp(x a, x b){return a.s == b.s ? (a.e > b.e) : (a.s < b.s); }
bool cmp2(x a, x b){return a.x < b.x;}
deque<x> dq;
 
int m,n;
 
int main(){
    int barr = 0;
    scanf("%d %d",&m,&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&a[i].s,&a[i].e);
        a[i].x = i+1;
        if(a[i].s > a[i].e) barr = max(barr,a[i].e);
        if(a[i].s > a[i].e) a[i].e += m;
    }
    sort(a,a+n,cmp);
    for (int i=0; i<n; i++) {
        if (dq.empty() || dq.back().e < a[i].e) dq.push_back(a[i]);
    }
    while(!dq.empty() && dq.front().e <= barr) dq.pop_front();
    sort(dq.begin(),dq.end(),cmp2);
    for (int i=0; i<dq.size(); i++) {
        printf("%d ",dq[i].x);
    }
}