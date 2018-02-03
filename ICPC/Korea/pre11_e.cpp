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

bool che[10005];

int main(){
    int t;
    che[1] = 1;
    for(int i=2; i<=10000; i++){
        for(int j=2*i; j<=10000; j+=i){
            che[j] = 1;
        }
    }
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        for(int i=n/2; i; i--){
            if(!che[i] && !che[n-i]){
                printf("%d %d\n",i, n-i);
                break;
            }
        }
    }
}