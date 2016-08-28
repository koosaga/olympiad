#include <cstdio>
#include <utility>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int,int> pi;

multiset<int> s;
multiset<int> ::iterator it;

int n;
pi x[100005];

int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&x[i].first,&x[i].second);
    }
    sort(x,x+n);
    for (int i=0; i<n; i++) {
        it = s.upper_bound(x[i].second);
        if(it != s.begin()) s.erase(--it);
        s.insert(x[i].second);
    }
    printf("%d",(int)s.size());
}