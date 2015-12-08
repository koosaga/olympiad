#include <cstdio>
#include <utility>
#include <vector>
 
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
 
int s,e;
lint la[100005],lb[100005];
int label[100005];
void insert(lint p, lint q, int piv){
    la[e] = p;
    lb[e] = q;
    label[e] = piv;
    while(s+1<e && (lb[e-1] - lb[e-2]) * (la[e] - la[e-1]) <= (la[e-2] - la[e-1])* (lb[e-1] - lb[e])){
        la[e-1] = la[e];
        lb[e-1] = lb[e];
        label[e-1] = label[e];
        e--;
    }
    e++;
}
pi query(lint x){
    while(s+1<e && lb[s+1] - lb[s] >= x * (la[s] - la[s+1])) s++;
    return pi(la[s]*x+lb[s],label[s]);
}
 
int n,k;
lint dp[2][100005],a[100005];
int track[205][100005];
 
int main(){
    int t;
    scanf("%d %d",&n,&k);
    for (int i=0; i<n; i++) {
        scanf("%d",&t);
        a[i+1] = a[i] + t;
    }
    for (int t=0; t<=k; t++) {
        s = e = 0;
        insert(0,0,0);
        for (int i=1; i<=n; i++) {
            pi x = query(a[i]);
            track[t][i] = x.second;
            dp[t%2][i] = x.first + a[i] * (a[n] - a[i]);
            insert(a[i],dp[!(t%2)][i]-a[n]*a[i], i);
        }
    }
    printf("%lld\n",dp[k%2][n]);
    vector<int> res;
    int pos2 = n;
    for(int pos1 = k; pos1; pos1--){
        res.push_back(track[pos1][pos2]);
        pos2 = track[pos1][pos2];
    }
    while (!res.empty()) {
        printf("%d ",res.back());
        res.pop_back();
    }
}