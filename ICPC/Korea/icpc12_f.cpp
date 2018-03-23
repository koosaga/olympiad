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
typedef pair<lint, int> pi;

int t;

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        vector<int> even, odd;
        char buf[100005];
        scanf("%s",buf);
        int d = 0;
        for(int i=0; buf[i]; i++){
            if(d%2 == 0) even.push_back(d);
            else odd.push_back(d);
            if(buf[i] == 'L') d = (d + 3) % 4;
            else d = (d + 1) % 4;
        }
        int cnt1 = 0, cnt2 = 0;
        for(int i=0; i<odd.size(); i++){
            if(odd[i] != odd[(i+1)%odd.size()]) cnt1++;
        }
        for(int i=0; i<even.size(); i++){
            if(even[i] != even[(i+1)%even.size()]) cnt2++;
        }
        printf("%d\n",(cnt1 <= 2) + (cnt2 <= 2));
    }
}