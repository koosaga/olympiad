#include <cstdio>
#include <vector>
#include <algorithm>
typedef long long lint;
using namespace std;
 
vector<lint> v1, v2;
 
lint a[41], m;
 
void dfs(lint x, int pos, int lim, vector<lint> &v){
    if(pos == lim){
        v.push_back(x);
        return;
    }
    dfs(x + a[pos], pos+1, lim, v);
    dfs(x, pos + 1, lim, v);
}
 
int n;
 
int main(){
    scanf("%d %lld",&n,&m);
    for(int i=0; i<n; i++){
        scanf("%lld",&a[i]);
    }
    dfs(0, 0, n/2, v1);
    dfs(0, n/2, n, v2);
    sort(v2.begin(), v2.end());
    lint ret = 0;
    for(auto &i : v1){
        ret += (int)(upper_bound(v2.begin(), v2.end(), m - i) - v2.begin());
    }
    printf("%lld",ret);
}