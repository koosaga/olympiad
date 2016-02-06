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
 
lint a, b, c;
 
lint gob(lint p, lint q){
    lint ret = 0;
    while(q){
        if(q&1) ret = (ret + p) % c;
        p <<= 1;
        q >>= 1;
        p %= c;
    }
    return ret;
}
 
int n;
 
int main(){
    cin >> a >> b >> c;
    lint ret = 1;
    while(b){
        if(b&1) ret = gob(ret, a);
        a = gob(a, a);
        b >>= 1;
    }
    cout << ret;
}