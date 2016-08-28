#include <cstdio>
#include <deque>
using namespace std;
 
deque<int> lo,hi;
deque<int> lon, hin;
 
int main(){
    int n,m,c,t;
    int dp = 0;
    scanf("%d %d %d",&n,&m,&c);
    for (int i=0; i<m; i++) {
        scanf("%d",&t);
        while (!lo.empty() && lo.back() >= t) {
            lon.pop_back();
            lo.pop_back();
        }
        while (!hi.empty() && hi.back() <= t) {
            hi.pop_back();
            hin.pop_back();
        }
        lo.push_back(t);
        hi.push_back(t);
        lon.push_back(i);
        hin.push_back(i);
    }
    if(hi.front() - lo.front() <= c) printf("1\n"), dp++;
    for (int i=m; i<n; i++) {
        scanf("%d",&t);
        if(lon.front() == i-m){
            lon.pop_front();
            lo.pop_front();
        }
        if(hin.front() == i-m){
            hin.pop_front();
            hi.pop_front();
        }
        while (!lo.empty() && lo.back() >= t) {
            lon.pop_back();
            lo.pop_back();
        }
        while (!hi.empty() && hi.back() <= t) {
            hi.pop_back();
            hin.pop_back();
        }
        lo.push_back(t);
        hi.push_back(t);
        lon.push_back(i);
        hin.push_back(i);
        if(hi.front() - lo.front() <= c) printf("%d\n",i-m+2),dp++;
    }
    if(!dp) puts("NONE");
}