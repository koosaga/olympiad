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

int n;

bool ispalin(int x){
    vector<int> v, rev;
    int p = n;
    while(p){
        rev.push_back(p % x);
        v.push_back(p % x);
        p /= x;
    }
    reverse(rev.begin(), rev.end());
    return rev == v;
}

int main(){
    scanf("%d",&n);
    int i;
    for(i=2; i*i<=n; i++){
        if(ispalin(i)) printf("%d\n",i);
    }
    for(;i;i--){
        if(n % i == 0){
            if(i < n / i - 1) printf("%d\n",n / i - 1);
        }
    }
}