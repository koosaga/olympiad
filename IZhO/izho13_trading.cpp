#include <cstdio>
#include <algorithm>
#include <set>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
multiset<int> s;
 
pi ins[300005], del[300005];
int n,m;
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        int s,e,x;
        scanf("%d %d %d",&s,&e,&x);
        ins[i] = pi(s,x-s);
        del[i] = pi(e,x-s);
    }
    sort(ins,ins+m);
    sort(del,del+m);
    int p1 = 0, p2 = 0;
    for (int i=1; i<=n; i++) {
        int mv = p1;
        while (mv < m && ins[mv].first == i) {
            mv++;
        }
        for (int j=p1; j<mv; j++) {
            s.insert(ins[j].second);
        }
        p1 = mv;
        auto x = s.end();
        if(x == s.begin()) printf("0 ");
        else printf("%d ",*(--x) + i);
        mv = p2;
        while (mv < m && del[mv].first == i) {
            mv++;
        }
        for (int j=p2; j<mv; j++) {
            s.erase(s.find(del[j].second));
        }
        p2 = mv;
    }
     
}