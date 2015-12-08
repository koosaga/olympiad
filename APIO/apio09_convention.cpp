#include <cstdio>
#include <utility>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
 
set<pi> s;
vector<pi> v,low;
vector<int> res;
 
int n,l[200005],r[200005];
int nxt[200005][18];
 
bool cmp(pi a, pi b){
    return a.second == b.second ? (a.first > b.first) : (a.second < b.second);
}
 
int assign(int s, int e){
    if(s > e) return 0;
    int ps = (*lower_bound(low.begin(),low.end(),pi(s,-1))).second;
    int elem = 1;
    if(ps == n || v[ps].second > e) return 0;
    for (int i=17; i>=0; i--) {
        if(nxt[ps][i] != n && v[nxt[ps][i]].second <= e){
            elem += (1<<i);
            ps = nxt[ps][i];
        }
    }
    return elem;
}
 
void solve1(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&l[i],&r[i]);
        v.push_back(pi(l[i],r[i]));
    }
    sort(v.begin(),v.end(),cmp);
    for (int i=0; i<n; i++) {
        if (!low.empty() && low.back().first >= v[i].first) continue;
        low.push_back(pi(v[i].first,i));
    }
    low.push_back(pi(2e9,n));
    int e = 0;
    for (int i=0; i<n; i++) {
        while(e < n && v[i].second >= v[e].first) e++;
        nxt[i][0] = e;
    }
    nxt[n][0] = n;
    for (int i=1; i<18; i++) {
        nxt[n][i] = n;
        for (int j=n-1; j>=0; j--) {
            nxt[j][i] = nxt[nxt[j][i-1]][i-1];
        }
    }
}
 
int main(){
    solve1();
    s.insert(pi(-1,1e9+1));
    for (int i=0; i<n; i++) {
        set<pi> ::iterator it = s.upper_bound(pi(l[i],1e9+1));
        it--;
        pi tmp = *it;
        if(tmp.second < r[i]) continue;
        int r1 = assign(tmp.first,tmp.second);
        int r2 = assign(tmp.first,l[i]-1) + assign(r[i]+1,tmp.second) + 1;
        if(r1 != r2) continue;
        s.erase(it);
        if(tmp.first <= l[i] - 1){
            s.insert(pi(tmp.first,l[i]-1));
        }
        if(r[i]+1 <= tmp.second){
            s.insert(pi(r[i]+1,tmp.second));
        }
        res.push_back(i+1);
    }
    printf("%d\n",(int)res.size());
    for (int i=0; i<res.size(); i++) {
        printf("%d ",res[i]);
    }
}