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

double mp[256];

int main(){
    mp['C'] = 12.01;
    mp['H'] = 1.008;
    mp['O'] = 16;
    mp['N'] = 14.01;
    int t;
    scanf("%d",&t);
    while(t--){
        char str[105];
        double ret = 0;
        scanf("%s",str);
        for(int i=0; str[i]; i++){
            int e = i+1;
            while(str[e] && str[e] <= '9' && str[e] >= '0'){
                e++;
            }
            if(i == e-1){
                ret += mp[str[i]];
            }
            else{
                int t = 0;
                for(int j=i+1; j<e; j++){
                    t = t * 10 + str[j] - '0';
                }
                ret += t * mp[str[i]];
                i = e-1;
            }
        }
        printf("%.3f\n",ret);
    }
}