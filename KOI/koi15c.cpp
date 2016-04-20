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
const int oo = 1e9;
  
struct rect{ int s, e, x, h, t; };
bool cmp(rect a, rect b){return a.e < b.e;}
  
rect a[3005];
int n, w;
int dp[3005][3005];
int low[6005];
  
bool cross(int p, int q){
    return (a[p].h + a[q].h <= w || a[q].s >= a[p].e);
}
  
vector<int> v;
int pmax[2][3005][3005];
  
int main(){
    scanf("%d %d",&n,&w);
    for(int i=0; i<n; i++){
        scanf("%d %d %d %d %d",&a[i].t,&a[i].s,&a[i].e,&a[i].h,&a[i].x);
    }
    a[n++] = {oo, oo, 0, 0, 0};
    a[n++] = {oo, oo, 0, 0, 1};
    for(int i=0; i<n; i++){
        v.push_back(a[i].s);
        v.push_back(a[i].e);
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    for(int i=0; i<n; i++){
        a[i].s = lower_bound(v.begin(), v.end(), a[i].s) - v.begin();
        a[i].e = lower_bound(v.begin(), v.end(), a[i].e) - v.begin();
    }
    sort(a, a+n, cmp);
    int p = 0;
    for(int i=0; i<v.size(); i++){
        while(p < n && a[p].e <= i) p++;
        low[i] = p;
    }
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(a[i].t == a[j].t || !cross(i, j)){
                dp[i][j] = -1e9;
            }
            else{
                int p = min(low[a[i].s]-1, i-1);
                if(p >= 0) dp[i][j] = max(dp[i][j], pmax[a[i].t][p][j]);
                p = min(low[a[j].s]-1, i-1);
                if(p >= 0) dp[i][j] = max(dp[i][j], pmax[a[j].t][p][i]);
            }
            pmax[a[i].t][i][j] = (i ? pmax[a[i].t][i-1][j] : -oo);
            pmax[a[i].t][i][j] = max(pmax[a[i].t][i][j], dp[i][j] + a[i].x);
            pmax[!a[i].t][i][j] = (i ? pmax[!a[i].t][i-1][j] : -oo);
            // pmax(t, i, j) == Max (dp[k][j] + a[k].x) (k <= i, a[k].t == t)
        }
    }
    printf("%d",dp[n-2][n-1]);
}