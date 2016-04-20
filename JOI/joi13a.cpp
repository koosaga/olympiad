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
 
int a[100005], n;
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    for(int i=0; i<n; i++){
        a[i] ^= 1 - a[i+1];
        if(i) a[i] += a[i-1];
    }
    a[n-1] = a[n-2];
    int e = 0, ret = 0;
    for(int i=0; i<n-1; i++){
        while(e < n-1 && a[e] - (i ? a[i-1] : 0) <= 2) e++;
        ret = max(ret, e - i + 1);
    }
    printf("%d",ret);
}