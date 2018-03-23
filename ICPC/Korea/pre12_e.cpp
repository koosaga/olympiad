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

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int a, b;
        scanf("%d %d",&a,&b);
        printf("%.1f\n",b / 2.0 + 1.0 * (a-1) * (a+1) / (3.0 * a));
    }
}