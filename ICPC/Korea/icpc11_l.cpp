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

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

int main(){
    int t;
    cin >> t;
    while(t--){
        char str[555];
        scanf("%s",str);
        int px = 0, py = 0, d = 0;
        int minx = 0, maxx = 0, miny = 0, maxy = 0;
        for(int i=0; str[i]; i++){
            if(str[i] == 'F'){
                px += dx[d];
                py += dy[d];
            }
            else if(str[i] == 'B'){
                px -= dx[d];
                py -= dy[d];
            }
            else if(str[i] == 'L'){
                d += 3;
                d %= 4;
            }
            else{
                d++;
                d %= 4;
            }
            minx = min(minx, px);
            miny = min(miny, py);
            maxx = max(maxx, px);
            maxy = max(maxy, py);
        }
        printf("%d\n",(maxx - minx) * (maxy - miny));
    }
}