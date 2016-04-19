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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
int n, a[1005];
bool vis[1005];
int main(){
    cin >> n;
    for(int i=1; i<=n; i++) cin >> a[i];
    vector<vector<int>> ret;
    for(int i=1; i<=n; i++){
        if(a[i] != i && !vis[i]){
            int p = i;
            vector<int> tmp;
            do{
                vis[a[p]] = 1;
                tmp.push_back(p);
                p = a[p];
            }while(p != i);
            ret.push_back(tmp);
        }
    }
    if(ret.size() >= 2){
        vector<int> sol[2];
        for(auto &i : ret){
            for(auto &j : i){
                sol[0].push_back(j);
            }
        }
        for(int i=ret.size()-1; i>=0; i--){
            sol[1].push_back(ret[i][0]);
        }
        ret.clear();
        ret.push_back(sol[0]);
        ret.push_back(sol[1]);
    }
    printf("%d\n",ret.size());
    for(auto &sol : ret){
        printf("%d: ",sol.size());
        for(auto &j : sol){
            printf("%d ",j);
        }
        puts("");
    }
}