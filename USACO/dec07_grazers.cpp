#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int,int> pi;
typedef multiset<int> ::iterator aauto;

int n,m;
pi a[100005], b[100005];
multiset<int> s;

bool cmp(pi a, pi b){
    return a.second < b.second;
}

int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&a[i].first,&a[i].second);
    }
    for (int i=0; i<m; i++) {
        scanf("%d %d",&b[i].first,&b[i].second);
    }
    sort(a,a+n,cmp);
    sort(b,b+m,cmp);
    int px = n-1, py = m-1;
    long long ret = 0;
    while(px >= 0 || py >= 0){
        if(b[py].second >= a[px].second){
            s.insert(b[py].first);
            py--;
        }
        else{
            aauto it = s.lower_bound(a[px].first);
            if(it != s.end()){
                ret += *it;
                s.erase(it);
            }
            else{
                puts("-1");
                return 0;
            }
            px--;
        }
    }
    printf("%lld",ret);
}