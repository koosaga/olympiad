#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
 
vector<int> v[10];
int n,k;
int dp[2005][11];
 
int f(int y, int z){
    if(y == 0) return 0;
    if(z == 10) return -1e9;
    if(~dp[y][z]) return dp[y][z];
    int res = 0;
    for (int i=0; i<=y && i<v[z].size(); i++) {
        res = max(res,f(y-i,z+1) + v[z][i] + i * (i-1));
    }
    return dp[y][z] = res;
}
 
int main(){
    scanf("%d %d",&n,&k);
    for (int i=0; i<n; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        v[y-1].push_back(x);
    }
    memset(dp,-1,sizeof(dp));
    for (int i=0; i<10; i++) {
        sort(v[i].begin(),v[i].end());
        v[i].push_back(0);
        reverse(v[i].begin(),v[i].end());
        for (int j=1; j<v[i].size(); j++) {
            v[i][j] += v[i][j-1];
        }
    }
    printf("%d",f(k,0));
}