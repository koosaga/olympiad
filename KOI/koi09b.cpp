#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
  
vector<int> ok[30005], rok[30005];
  
int n, m;
int a[30005], b[30005];
  
int sfx[30005][105], mat[30005][105];
  
int ret = 1e9, r1, r2, r3, r4;
  
void cut(int p1, int p2, int q1, int q2){
    int a1 = a[p1];
    int a2 = a[p2] - a[p1];
    int a3 = a[n] - a[p2];
    int b1 = b[q1];
    int b2 = b[q2] - b[q1];
    int b3 = b[m] - b[q2];
    int p = max(abs(a1-b1), max(abs(a2-b2), abs(a3-b3)));
    if(ret > p) tie(ret, r1, r2, r3, r4) = tie(p, p1, p2, q1, q2);
}
  
int main(){
    scanf("%d %d",&n,&m);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
        a[i] += a[i-1];
    }
    for(int i=1; i<=m; i++){
        scanf("%d",&b[i]);
        b[i] += b[i-1];
    }
    for(int i=1; i<n; i++){
        int p = lower_bound(b+1, b+m+1, a[i] - 50) - b;
        for(int j=max(p, 1); j<m && b[j] <= a[i] + 50; j++){
            ok[i].push_back(j);
        }
        p = lower_bound(b+1, b+m+1, - a[n] + a[i] + b[m] - 50) - b;
        for(int j=max(p, 1); j<m && a[n] - a[i] - b[m] + b[j] <= 50; j++){
            rok[i].push_back(j);
        }
    }
    memset(sfx[n+1], -1, sizeof(sfx[n+1]));
    for(int i=n; i; i--){
        for(int j=0; j<=100; j++){
            sfx[i][j] = sfx[i+1][j];
            mat[i][j] = mat[i+1][j];
        }
        for(auto &j : rok[i]){
            int cd = a[n] - a[i] - b[m] + b[j];
            if(cd < -50 || cd > 50) continue;
            if(sfx[i][cd+50] != -1) continue;
            sfx[i][cd + 50] = i;
            mat[i][cd + 50] = j;
        }
    }
    for(int i=1; i<=n; i++){
        for(auto &k : ok[i]){
            for(int j=-50; j<=50; j++){
                int p = sfx[i+1][j+50];
                if(p == -1) continue;
                if(k < mat[i+1][j+50]) cut(i, p, k, mat[i+1][j+50]);
            }
        }
    }
    if(ret > 50){
        puts("-1");
    }
    else printf("%d %d %d\n%d %d %d\n",r1,r2-r1,n-r2,r3,r4-r3,m-r4);
}