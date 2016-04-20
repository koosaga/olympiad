#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
 
int n, a[100005], l;
priority_queue<pi,vector<pi>,greater<pi> > pq;
 
int main(){
    scanf("%d %d",&n,&l);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
    }
    for (int i=1; i<=n; i++) {
        if(a[i] > a[i-1] && a[i] > a[i+1]){
            pq.push(pi(l - a[i],i));
        }
    }
    int ret = 0;
    while (!pq.empty()) {
        pi t = pq.top();
        pq.pop();
        ret = max(ret,t.first);
        a[t.second] = 0;
        if(t.second > 1 && a[t.second-1] > a[t.second-2]){
            pq.push(pi(l - a[t.second-1] + t.first,t.second-1));
        }
        if(t.second < n && a[t.second+1] > a[t.second + 2]){
            pq.push(pi(l - a[t.second+1] + t.first,t.second + 1));
        }
    }
    printf("%d\n",ret);
}