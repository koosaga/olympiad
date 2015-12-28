#include <cstdio>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;
typedef pair<int,int> pi;
 
int n,k,a[1000005];
priority_queue<pi, vector<pi>, greater<pi> > pq;
 
stack<int> s,t;
  
int main(){
    scanf("%d %d",&n,&k);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    rotate(a, max_element(a, a+n), a+n);
    a[n] = a[0];
    for (int i=0; i<=n; i++) {
        if(s.empty() || s.top() >= a[i]){
            s.push(a[i]);
            t.push(i);
        }
        else{
            while (!s.empty() && s.top() < a[i]) {
                int ptop = s.top();
                s.pop();
                t.pop();
                pq.push(pi(i - t.top() - 1, min(s.top(), a[i]) - ptop));
                // first cost로 t만큼 뽕뽑
            }
            s.push(a[i]);
            t.push(i);
        }
    }
    int ret = 0;
    while(!pq.empty()){
        pi t = pq.top();
        pq.pop();
        int change = min(t.second, k / t.first);
        ret += change * 2;
        k -= change * t.first;
    }
    printf("%d",ret);
}