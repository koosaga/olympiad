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
  
int ccw(pi a, pi b, pi c){
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    lint area = 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
    if(area != 0) return area > 0 ? 1 : -1;
    return 0;
}
  
int b[305][305];
int ret, px, py, pz, n;
pi a[305];
 
int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i].first >> a[i].second;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<n; k++){
                if(ccw(a[i], a[j], a[k]) == -1){
                    b[i][j]++;
                }
            }
        }
    }
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            for(int k=j+1; k<n; k++){
                int tmp;
                if(ccw(a[i], a[j], a[k]) == 1){
                    tmp = n - b[i][j] - b[j][k] - b[k][i];
                }
                else if(ccw(a[i], a[j], a[k]) == -1){
                    tmp = n - b[j][i] - b[k][j] - b[i][k];
                }
                if(tmp > ret){
                    ret = tmp;
                    px = i, py = j, pz = k;
                }
            }
        }
    }
    cout << ret << endl << px + 1 << " " << py + 1 << " " << pz + 1;
}