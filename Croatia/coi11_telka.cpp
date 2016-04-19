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
const int day = 86400;
 
lint dx[90000];
 
int parse(char *buf){
    for(int i=0; i<10; i++){
        buf[i] -= '0';
    }
    int h = buf[0] * 10 + buf[1];
    int m = buf[3] * 10 + buf[4];
    int s = buf[6] * 10 + buf[7];
    return 3600 * h + 60 * m + s;
}
 
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        char buf1[22], buf2[22], buf3[22];
        scanf("%s %s %s",buf1,buf2,buf3);
        int st = parse(buf1);
        int ed = parse(buf3);
        if(st <= ed){
            dx[st]++;
            dx[ed+1]--;
        }
        else{
            dx[st]++;
            dx[day]--;
            dx[0]++;
            dx[ed+1]--;
        }
    }
    for(int i=1; i<=day; i++){
        dx[i] += dx[i-1];
    }
    for(int i=1; i<=day; i++){
        dx[i] += dx[i-1];
    }
    int q;
    scanf("%d",&q);
    for(int i=0; i<q; i++){
        char buf1[22], buf2[22], buf3[22];
        scanf("%s %s %s",buf1,buf2,buf3);
        int st = parse(buf1);
        int ed = parse(buf3);
        int len = 0;
        lint ret = 0;
        if(st <= ed){
            ret += dx[ed] - (st ? dx[st-1] : 0);
            len += ed - st + 1;
        }
        else{
            ret += dx[day-1] - (st ? dx[st-1] : 0);
            ret += dx[ed];
            len += ed + 1 + day - st;
        }
        printf("%.10f\n",1.0 * ret / len);
    }
}