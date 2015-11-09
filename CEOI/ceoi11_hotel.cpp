#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
typedef multiset<pi> ::iterator aauto;

int n, m, o;

multiset<pi> s;

int c[500005], p[500005];
vector<pi> v, q;
vector<int> match;

int main(){
    scanf("%d %d %d",&n,&m,&o);
    for(int i=0; i<n; i++){
        scanf("%d %d",&c[i],&p[i]);
        s.insert(pi(p[i], c[i]));
    }
    for(int i=0; i<m; i++){
        int val, d;
        scanf("%d %d",&val, &d);
        q.push_back(pi(val, -d));
    }
    sort(q.begin(), q.end());
    reverse(q.begin(), q.end());
    for(int i=0; i<q.size(); i++){
        aauto t = s.lower_bound(pi(-q[i].second, -1e9));
        if(t == s.end()) continue;
        int diff = q[i].first - t->second;
        if(diff < 0) continue;
        s.erase(t);
        match.push_back(diff);
    }
    sort(match.begin(), match.end());
    reverse(match.begin(), match.end());
    long long ret = 0;
    for(int i=0; i<o && i < match.size(); i++){
        ret += max(match[i], 0);
    }
    printf("%lld\n",ret);
}