#include <cstdio>
#include <map>
#include <queue>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
typedef map<int,bool> mp;
 
priority_queue<pi,vector<pi>,greater<pi> > pq;
mp viable;
 
int n,k,a[100005];
 
int main(){
    scanf("%d %d",&n,&k);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    for (int i=n-1; i; i--) {
        a[i] -= a[i-1];
        pq.push(pi(a[i],i));
        viable[i] = 1;
    }
    int res = 0;
    for (int i=0; i<k; i++) {
        int p = pq.top().second;
        pq.pop();
        if(viable.count(p) == 0){
            i--;
            continue;
        }
        res += a[p];
        viable.erase(viable.find(p));
        mp::iterator it = viable.upper_bound(p);
        int x = 0, cont = 0;
        if(it != viable.end()){
            x += a[(*it).first];
            viable.erase((*it).first);
        }
        else cont = 1;
        it = viable.upper_bound(p);
        if(it != viable.begin()){
            it--;
            x += a[(*it).first];
            viable.erase((*it).first);
        }
        else cont = 1;
        if(cont) continue;
        viable[p] = 1;
        a[p] = x - a[p];
        pq.push(pi(a[p],p));
    }
    printf("%d",res);
}