#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
pi a[305];
int n,s;
 
bool dp[305][100005], tra[305][100005];
vector<int> ret;
 
void track(int i, int j){
    if(i <= 0) return;
    if(tra[i][j]){
        ret.push_back(a[i].second);
        track(i-1,j - a[i].first);
        return;
    }
    track(i-1,j);
}
 
int main(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i].first);
        a[i].second = i;
        s += a[i].first;
    }
    sort(a+1,a+n+1);
    reverse(a+1,a+n+1);
    dp[0][0] = 1;
    for (int i=1; i<=n; i++) {
        for (int j=0; j<=s; j++) {
            if(j >= a[i].first){
                dp[i][j] |= dp[i-1][j - a[i].first];
                if(dp[i][j]) tra[i][j] = 1;
            }
            dp[i][j] |= dp[i-1][j];
        }
    }
    pi mx(0,0);
    for (int i=1; i<=n; i++) {
        for (int j=s/2+1; j<=s/2 + a[i].first && j <= s; j++) {
            if(dp[i][j]) mx = max(mx,pi(j,i));
        }
    }
    track(mx.second,mx.first);
    printf("%d\n",(int)ret.size());
    for (int i=0; i<ret.size(); i++) {
        printf("%d ",ret[i]);
    }
}