#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int n, table[2005][2005];
int sx, sy;

void bfs(int a, int b){
    queue<int> x,y;
    int xf = a, yf = b;
    x.push(xf);
    y.push(yf);
    table[xf][yf] = 1;
    while (!x.empty()) {
        xf = x.front();
        yf = y.front();
        x.pop();
        y.pop();
        if(xf && !table[xf-1][yf]){
            x.push(xf-1);
            y.push(yf);
            table[xf-1][yf] = 1;
        }
        if(yf && !table[xf][yf-1]){
            x.push(xf);
            y.push(yf-1);
            table[xf][yf-1] = 1;
        }
        if(xf+1 < sx && !table[xf+1][yf]){
            x.push(xf+1);
            y.push(yf);
            table[xf+1][yf] = 1;
        }
        if(yf+1 < sy && !table[xf][yf+1]){
            x.push(xf);
            y.push(yf+1);
            table[xf][yf+1] = 1;
        }
    }
}
int main(){
    int w,h,n;
    int x1[1005], y1[1005], x2[1005], y2[1005];
    scanf("%d %d %d",&w,&h,&n);
    vector<int> vx,vy;
    for (int i=0; i<n; i++) {
        scanf("%d %d %d %d",&x1[i],&y1[i],&x2[i],&y2[i]);
        vx.push_back(x1[i]);
        vx.push_back(x2[i]);
        vy.push_back(y1[i]);
        vy.push_back(y2[i]);
    }
    vx.push_back(0);
    vy.push_back(0);
    vx.push_back(w);
    vy.push_back(h);
    sort(vx.begin(),vx.end());
    sort(vy.begin(),vy.end());
    vx.resize(unique(vx.begin(),vx.end()) - vx.begin());
    vy.resize(unique(vy.begin(),vy.end()) - vy.begin());
    for (int i=0; i<n; i++) {
        x1[i] = (int)distance(vx.begin(),lower_bound(vx.begin(),vx.end(),x1[i]));
        x2[i] = (int)distance(vx.begin(),lower_bound(vx.begin(),vx.end(),x2[i]));
        y1[i] = (int)distance(vy.begin(),lower_bound(vy.begin(),vy.end(),y1[i]));
        y2[i] = (int)distance(vy.begin(),lower_bound(vy.begin(),vy.end(),y2[i]));
    }
    w = (int)distance(vx.begin(),lower_bound(vx.begin(),vx.end(),w));
    h = (int)distance(vy.begin(),lower_bound(vy.begin(),vy.end(),h));
    for (int i=0; i<n; i++) {
        for (int j=x1[i]; j<x2[i]; j++) {
            table[j][y1[i]]++;
            table[j][y2[i]]--;
        }
    }
    for (int i=0; i<w; i++) {
        int piv = 0;
        for (int j=0; j<h; j++) {
            piv += table[i][j];
            table[i][j] = min(piv,1);
        }
    }
    sx = w, sy = h;
    int r = 0;
    for (int i=0; i<sx; i++) {
        for (int j=0; j<sy; j++) {
            if(!table[i][j]){
                bfs(i,j);
                r++;
            }
        }
    }
    printf("%d",r);
}