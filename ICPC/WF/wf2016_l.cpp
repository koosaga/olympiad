#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
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

int n;
pi a[1000005];
vector<pi> v1, v2;

int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first, &a[i].second);
        if(a[i].first <= a[i].second) v1.push_back(a[i]);
        else v2.push_back(a[i]);
    }
    sort(v1.begin(), v1.end());
    lint ret = 0, curlev = 0;
    for(auto &i : v1){
        if(curlev < i.first){
            ret += i.first - curlev;
            curlev = i.first;
        }
        curlev += i.second - i.first;
    }
    sort(v2.begin(), v2.end(), [&](const pi &a, const pi &b){
        return a.second > b.second;
    });
    for(auto &i : v2){
        curlev -= i.first;
        if(curlev < 0){
            ret -= curlev;
            curlev = 0;
        }
        curlev += i.second;
    }
    cout << ret;
}