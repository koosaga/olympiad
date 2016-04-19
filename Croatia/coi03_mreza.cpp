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
 
struct trap{
    int sx, ex, sy, ey, px, py;
}pref[8005], suff[8005];
 
int a, b, n;
char str[8005];
int dx[256], dy[256];
 
inline bool mid(int s, int x, int e){if(s>e)swap(s,e);return s<=x&&x<=e;}
 
int main(){
    dx['R'] = 1;
    dx['L'] = -1;
    dy['U'] = 1;
    dy['D'] = -1;
    cin >> a >> b >> n >> (str+1);
    for(int i=1; i<=n; i++){
        pref[i] = pref[i-1];
        pref[i].px += dx[str[i]];
        pref[i].py += dy[str[i]];
        pref[i].sx = min(pref[i].sx, pref[i].px);
        pref[i].ex = max(pref[i].ex, pref[i].px);
        pref[i].sy = min(pref[i].sy, pref[i].py);
        pref[i].ey = max(pref[i].ey, pref[i].py);
    }
    for(int i=n; i; i--){
        for(int j=i; j<=n; j++){
            suff[i].px += dx[str[j]];
            suff[i].py += dy[str[j]];
            suff[i].sx = min(suff[i].sx, suff[i].px);
            suff[i].ex = max(suff[i].ex, suff[i].px);
            suff[i].sy = min(suff[i].sy, suff[i].py);
            suff[i].ey = max(suff[i].ey, suff[i].py);
        }
    }
    int ret = 1e9, rs = 0, re = 0;
    for(int i=1; i<=n; i++){
        for(int j=i; j<=n; j++){
            int ex = pref[i-1].px + suff[j+1].px;
            int ey = pref[i-1].py + suff[j+1].py;
            if(!mid(0, pref[i-1].sx, a) || !mid(0, pref[i-1].sy, b) || 
                !mid(0, pref[i-1].ex, a) || !mid(0, pref[i-1].ey, b) ||
                !mid(0, pref[i-1].px + suff[j+1].sx, a) || !mid(0, pref[i-1].py + suff[j+1].sy, b) ||
                !mid(0, pref[i-1].px + suff[j+1].ex, a) || !mid(0, pref[i-1].py + suff[j+1].ey, b)){
                continue;
            }
            if(ret > abs(a - ex) + abs(b - ey)){
                ret = abs(a - ex) + abs(b - ey);
                rs = i;
                re = j;
            }
        }
    }
    cout << rs << " " << re;
}