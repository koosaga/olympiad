#include <cstdio>
#include <queue>
using namespace std;

priority_queue<int,vector<int>,greater<int> > pq;
long long r;
int main(){
    int n,t,u;
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&t);
        pq.push(t);
    }
    while (pq.size() > 1) {
        t = pq.top();
        pq.pop();
        u = pq.top();
        pq.pop();
        r += (t+u);
        pq.push(t+u);
    }
    printf("%lld",r);
}