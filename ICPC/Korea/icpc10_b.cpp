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

int f(int x, int l){
    if(l == 0) return 1;
    if(l == 1) return 0;
    int ret = 0;
    for(int i=0; i<l; ){
        int e = i;
        while(e < l && (x >> e) % 2 == (x >> i) % 2){
            e++;
        }
        if(e == i+1){
            i++;
            continue;
        }
        if(f((x & ((1<<i) - 1)) | ((x >> e) << i), l - e + i)) return 1;
        i = e;
    }
    return 0;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        char str[55];
        scanf("%s",str);
        int bit = 0;
        for(int i=0; str[i]; i++){
            bit |= ((str[i] - 'a') << i);
        }
        printf("%d\n",f(bit, strlen(str)));
    }
}