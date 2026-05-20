#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

struct edg{int s,e,x;};
edg a[305];

int n;
vector<int> v;
int dp[2][605][605];
int obstacle[605][605];

void solve(){
    memset(dp,0,sizeof(dp));
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d %d",&a[i].s,&a[i].e,&a[i].x);
        v.push_back(a[i].s);
        v.push_back(a[i].e);
    }
    v.push_back(-1);
    v.push_back(1e9);
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    sort(a,a+n,[&](const edg &a, const edg &b){return a.x > b.x;});
    for(int i=0; i<n; i++){
        a[i].s = (int)(lower_bound(v.begin(), v.end(), a[i].s) - v.begin());
        a[i].e = (int)(lower_bound(v.begin(), v.end(), a[i].e) - v.begin());
    }
    for(int i=0; i<v.size(); i++){
        for(int j=i; j<v.size(); j++){
            obstacle[i][j] = n;
            for(int k=0; k<n; k++){
                if(i <= a[k].s && a[k].e <= j){
                    obstacle[i][j] = k;
                    break;
                }
            }
        }
    }
    for(int i=n-1; i>=0; i--){
        for(int j=0; j<v.size(); j++){
            for(int k=j; k<v.size(); k++){
                if(obstacle[j][k] == i){
                    dp[i%2][j][k] = 1e9;
                    for(int l=a[i].s; l<=a[i].e; l++){
                        dp[i%2][j][k] = min(dp[i%2][j][k], dp[(i+1)%2][j][l-1] + dp[(i+1)%2][l+1][k] + a[i].x);
                    }
                }
                else dp[i%2][j][k] = dp[(i+1)%2][j][k];
            }
        }
    }
    printf("%d\n",dp[0][0][v.size()-1]);
}


int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
        v.clear();
    }
}