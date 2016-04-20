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
    int a, b;
    scanf("%d %d",&a,&b);
    int d = b - a;
    while(d && d % 2 == 0) d /= 2;
    for(int i=0; i<5; i++){
        int p, q;
        scanf("%d %d",&p, &q);
        int e = q - p;
        if(d == 0){
            puts(e == 0 ? "Y" : "N");
        }
        else{
            puts(e % d == 0 && e / d > 0 ? "Y" : "N");
        }
    }
}