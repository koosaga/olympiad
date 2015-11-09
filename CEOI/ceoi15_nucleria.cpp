#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
 
int w, h, n, q;
vector<vector<lint> > dx1, low1, low2, low3, low4;
 
void Trace1(int depth, int px, int py, int d){ 
    if(depth == 0) return;
    if(px == 1 && py == 1){
        dx1[1][1] += 1ll * depth * d;
        return;
    }
    if(px == 1){
        int dx = min(py-1, depth);
        low4[1][py - dx + 1] += d;
        low4[1][py + 1] -= d;
        Trace1(depth - dx, 1, py - dx, d);
        return;
    }
    if(py == 1){
        int dx = min(px-1, depth);
        low3[px - dx + 1][1] += d;
        low3[px + 1][1] -= d;
        Trace1(depth - dx, px - dx, 1, d);
        return;
    }
    int dx = min(px-1, min(py-1, depth));
    low1[px - dx + 1][py - dx + 1] += d;
    low1[px + 1][py + 1] -= d;
    Trace1(depth - dx, px - dx, py - dx, d);
}
 
void Trace2(int depth, int px, int py, int d){
    if(depth == 0) return;
    if(px == 1 && py == h+1){
        dx1[1][h+1] += 1ll * depth * d;
        return;
    }
    if(px == 1){
        int dx = min(h + 1 - py, depth);
        low4[1][py] += d;
        low4[1][py + dx] -= d;
        Trace2(depth - dx, 1, py + dx, d);
        return;
    }
    if(py == h+1){
        int dx = min(px-1, depth);
        low3[px - dx + 1][py] += d;
        low3[px + 1][py] -= d;
        Trace2(depth - dx, px - dx, py, d);
        return;
    }
    int dx = min(depth, min(h + 1 - py, px - 1));
    low2[px - dx + 1][py + dx - 1] += d;
    low2[px+1][py -1] -= d;
    Trace2(depth - dx, px - dx, py + dx, d);
}
 
void Trace3(int depth, int px, int py, int d){
    if(depth == 0) return;
    if(px == w+1 && py == 1){
        dx1[px][py] += 1ll * depth * d;
        return;
    }
    if(px == w+1){
        int dx = min(py - 1, depth);
        low4[px][py - dx + 1] += d;
        low4[px][py + 1] -= d;
        Trace3(depth - dx, px, py - dx, d);
        return;
    }
    if(py == 1){
        int dx = min(w + 1 - px, depth);
        low3[px][py] += d;
        low3[px + dx][py] -= d;
        Trace3(depth - dx, px + dx, py, d);
        return;
    }
    int dx = min(depth, min(w + 1 - px, py - 1));
    low2[px][py] += d;
    low2[px + dx][py - dx] -= d;
    Trace3(depth - dx, px + dx, py - dx, d);
}
 
void Trace4(int depth, int px, int py, int d){
    if(depth == 0) return;
    if(px == w+1 && py == h+1){
        dx1[px][py] += 1ll * depth * d;
        return;
    }
    if(px == w+1){
        int dx = min(h + 1 - py, depth);
        low4[px][py] += d;
        low4[px][py + dx] -= d;
        Trace4(depth - dx, px, py + dx, d);
        return;
    }
    if(py == h+1){
        int dx = min(w + 1 - px, depth);
        low3[px][py] += d;
        low3[px + dx][py] -= d;
        Trace4(depth - dx, px + dx, py, d);
        return;
    }
    int dx = min(depth, min(h + 1 - py, w + 1 - px));
    low1[px][py] += d;
    low1[px + dx][py + dx] -= d;
    Trace4(depth - dx, px + dx, py + dx, d);
}
 
int main(){
    scanf("%d %d",&w,&h);
    dx1.resize(w+2);
    low1.resize(w+2);
    low2.resize(w+2);
    low3.resize(w+2);
    low4.resize(w+2);
    for(int i=0; i<=w+1; i++){
        dx1[i].resize(h+2);
        low1[i].resize(h+2);
        low2[i].resize(h+2);
        low3[i].resize(h+2);
        low4[i].resize(h+2);
    }
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        int x, y, a, b;
        scanf("%d %d %d %d",&x,&y,&a,&b);
        int rad = a / b;
        int radx = max(w-x,x) + 1;
        int rady = max(h-y,y) + 1;
        int mrad = max(radx, rady);
        dx1[max(1,x-rad)][max(1,y-rad)] += a % b + 1ll * max(0,rad - mrad) * b;
        dx1[max(1,x-rad)][min(h+1,y+rad+1)] -= a % b + 1ll * max(0,rad - mrad) * b;
        dx1[min(w+1,x+rad+1)][max(1,y-rad)] -= a % b + 1ll * max(0,rad - mrad) * b;
        dx1[min(w+1,x+rad+1)][min(h+1,y+rad+1)] += a % b + 1ll * max(0,rad - mrad) * b;
        Trace1(min(rad, mrad), x, y, b);
        Trace2(min(rad, mrad), x, y+1, -b);
        Trace3(min(rad, mrad), x+1, y, -b);
        Trace4(min(rad, mrad), x+1, y+1, b);
    }
    for(int i=1; i<=w; i++){
        for(int j=1; j<=h; j++){
            low1[i][j] += low1[i-1][j-1];
            low2[i][j] += low2[i-1][j+1];
            low3[i][j] += low3[i-1][j];
            low4[i][j] += low4[i][j-1];
        }
    }
    for(int i=1; i<=w; i++){
        for(int j=1; j<=h; j++){
            dx1[i][j] += dx1[i][j-1] + low1[i][j] + low2[i][j] + low3[i][j] + low4[i][j];
        }
    }
    for(int i=1; i<=w; i++){
        for(int j=1; j<=h; j++){
            dx1[i][j] += dx1[i-1][j];
        }
    }
    for(int i=1; i<=w; i++){
        for(int j=1; j<=h; j++){
            //printf("%lld ",dx1[i][j]);
            dx1[i][j] = dx1[i-1][j] + dx1[i][j-1] - dx1[i-1][j-1] + dx1[i][j];
        }
        //puts("");
    }
    int q;
    scanf("%d",&q);
    while(q--){
        int sx, sy, ex, ey;
        scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
        lint res = dx1[ex][ey] - dx1[sx-1][ey] - dx1[ex][sy-1] + dx1[sx-1][sy-1];
        res += (ex - sx + 1) * (ey - sy + 1) / 2;
        res /= 1ll * (ex - sx + 1) * (ey - sy + 1);
        printf("%lld\n",res);
    }
}