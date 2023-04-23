#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m, k;
vector<int> gph[1000005];
bool vis[1000005];
int edg, vtx;

void dfs(int x){
    if(vis[x]) return;
    vis[x] = 1;
    vtx++;
    for(auto &i : gph[x]){
        edg++;
        dfs(i);
    }
}

int main(){
    cin >> n >> m >> k;
    for(int i=0; i<m; i++){
        int s, e;
        scanf("%d %d",&s,&e);
        gph[s].push_back(e);
        gph[e].push_back(s);
    }
    int ret = 0, los = 0;
    for(int i=1; i<=n; i++){
        if(!vis[i]){
            edg = 0, vtx = 0;
            dfs(i);
            edg /= 2;
            ret += vtx / k;
            if(edg != vtx){
                if(vtx % k == 0){
                    los += vtx / k - 1;
                }
                else{
                    if(vtx >= k) los += vtx / k;
                }
            }
            else{
                if(vtx % k == 0){
                    if(vtx != k) los += vtx / k;
                }
                else{
                    if(vtx >= k) los += vtx / k + 1;
                }
            }
        }
    }
    printf("%d %d",ret * k, los);
}