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

int nxt(int x){
    vector<int> v;
    v.push_back(x / 1000);
    v.push_back(x % 10);
    v.push_back((x / 10) % 10);
    v.push_back((x / 100) % 10);
    sort(v.begin(), v.end());
    int ret1 = v[0] * 1000 + v[1] * 100 + v[2] * 10 + v[3];
    reverse(v.begin(), v.end());
    int ret2 = v[0] * 1000 + v[1] * 100 + v[2] * 10 + v[3];
    return ret2 - ret1;
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int u;
        scanf("%d",&u);
        int cnt = 0;
        while(u != 6174){
            cnt++;
            u = nxt(u);
        }
        printf("%d\n",cnt);
    }
}