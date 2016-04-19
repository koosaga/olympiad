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
 
int m, n;
int a[100005];
map<int, int> mp;
int ret = 1e9;
vector<int> res;
 
int main(){
    scanf("%d %d",&m,&n);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
        mp[a[i] / m]++;
    }
    sort(a, a+n, [&](const int &a, const int &b){
        return a % m < b % m;
    });
    int p = 0;
    for(int i=0; i<m; i++){
        while(p < n && a[p] % m == i){
            mp[a[p] / m]--;
            if(mp[a[p] / m] == 0){
                mp.erase(a[p] / m);
            }
            mp[a[p] / m - 1]++;
            p++;
        }
        if(ret > mp.size()){
            ret = mp.size();
            res.clear();
        }
        if(ret == mp.size()){
            res.push_back(i+1);
        }
    }
    sort(res.begin(), res.end());
    printf("%d\n",ret);
    for(auto &i : res){
        printf("%d ",i);
    }
}