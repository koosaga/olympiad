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
 
const int offset = 1001;
 
bool pan[2005][2005];
int dist[2005][2005];
int dx[4] = {0,1,0,-1}, dy[4] = {1,0,-1,0};
 
queue<int> qx, qy;
 
int n, s;
lint ret[2];
 
void line(int x){
    if(x >= s) return;
    // 
    ret[0] += s/2 - x/2;
    ret[1] += (s-1)/2 - (x-1)/2;
}
 
void area(int x){
    for(int i=x+1; i<=s; i++){
        ret[i&1] += (i - x + 1);
    }
}
 
int main(){
    scanf("%d %d",&n,&s);
    for(int i=0; i<n; i++){
        int x, y;
        scanf("%d %d",&x,&y);
        x += offset;
        y += offset;
        pan[x][y] = 1;
    }
    memset(dist,0x3f,sizeof(dist));
    dist[offset][offset] = 0;
    qx.push(offset);
    qy.push(offset);
    while(!qx.empty()){
        int xf = qx.front();
        int yf = qy.front();
        qx.pop(), qy.pop();
        for(int i=0; i<4; i++){
            if(xf + dx[i] < 0 || yf + dy[i] < 0 || xf + dx[i] > 2 * offset || yf + dy[i] > 2 * offset){
                continue;
            }
            if(pan[xf+dx[i]][yf+dy[i]]) continue;
            if(dist[xf + dx[i]][yf + dy[i]] > dist[xf][yf] + 1){
                qx.push(xf + dx[i]);
                qy.push(yf + dy[i]);
                dist[xf + dx[i]][yf + dy[i]] = dist[xf][yf] + 1;
            }
        }
    }
    for(int i=0; i<=2*offset; i++){
        for(int j=0; j<=2*offset; j++){
            if(dist[i][j] <= s) ret[dist[i][j]&1]++;
        }
    }
    for(int i=1; i<2*offset; i++){
        line(dist[0][i]);
        line(dist[2*offset][i]);
        line(dist[i][0]);
        line(dist[i][2*offset]);
    }
    area(dist[0][0]);
    area(dist[0][2*offset]);
    area(dist[2*offset][0]);
    area(dist[2*offset][2*offset]);
    cout << ret[0] << " " << ret[1];
}