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
 
vector<int> f(int x, int p){
    vector<int> ret;
    if(p == 1){
        ret.push_back(1);
        return ret;
    }
    if(x > p/2){
        ret = f(x-p/2, p/2);
        for(auto &i : ret) i += p/2;
    }
    else ret = f(x, p/2);
    auto ret2 = ret;
    for(auto &i : ret2){
        if(i > p/2) i -= p/2;
        else i += p/2;
        ret.push_back(i);
    }
    return ret;
}
 
int main(){
    int n, x, mode = 0;
    cin >> n >> x;
    n /= 2;
    if(x > n) x -= n, mode = 1;
    auto t = f(x, n);
    if(mode){
        reverse(t.begin(), t.end());
        for(auto &i : t){
            printf("%d %d ",2*n+1-i, i);
        }
    }
    else{
        for(auto &i : t){
            printf("%d %d ",i, 2*n+1-i);
        }
    }
}