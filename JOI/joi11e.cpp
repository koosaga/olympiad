#include <cstdio>
#include <algorithm>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;
typedef pair<int,int> pi;
typedef long long lint;
 
pi a[300005];
int n;
 
vector<pi> av;
 
bool cmp(pi a, pi b){return a.second < b.second;}
 
int link[300005];
int cnta[300005];
int idxa[300005];
 
bool f(int x){
    if(x == 0) return 1;
    for (int i=0; i<n; i++) {
        idxa[i] = av[i].first;
        cnta[i] = 1;
    }
    int sm_bound = x-1;
    int cnt = x;
    lint sum = 0;
    for (int i=0; i<x; i++) {
        sum += idxa[i];
    }
    for (int i=0; i<n; i++) {
        lint obj = 1ll * x * a[i].second;
        if(sum <= obj) return 1;
        int loc = link[i];
        idxa[loc] = 0;
        cnta[loc] = 0;
        if(loc <= sm_bound){
            cnt--;
            sum -= a[i].first;
        }
        while(cnt < x){
            sum += idxa[sm_bound+1];
            cnt += cnta[sm_bound+1];
            sm_bound++;
            if(sm_bound >= n) return 0;
        }
    }
    return 0;
}
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&a[i].first,&a[i].second);
    }
    sort(a,a+n,cmp);
    for (int i=0; i<n; i++) {
        av.push_back(pi(a[i].first,i));
    }
    sort(av.begin(),av.end());
    for (int i=0; i<n; i++) {
        link[av[i].second] = i;
    }
    int s = 0, e = n;
    while (s != e) {
        int m = (s+e+1)/2;
        if(f(m)) s = m;
        else e = m-1;
    }
    printf("%d",s);
}