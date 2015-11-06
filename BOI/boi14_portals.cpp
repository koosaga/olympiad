#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;
typedef pair<int,int> pi;
typedef pair<int,pi> edge;
 
char str[1005][1005];
int ply[1005][1005];
int pry[1005][1005];
int pux[1005][1005];
int pdx[1005][1005];
 
int r,c;
 
priority_queue<edge,vector<edge>,greater<edge> > pq;
 
int v[1005][1005];
 
void input(){
    scanf("%d %d",&r,&c);
    for (int i=0; i<r; i++) {
        scanf("%s",str[i]);
        for (int j=0; j<c; j++) {
            if(str[i][j] == 'S'){
                pq.push(edge(0,pi(i,j)));
            }
        }
    }
}
 
void make_portal(){
    for (int i=0; i<r; i++) {
        int piv = 0;
        for (int j=0; j<c; j++) {
            if(str[i][j] == '#') piv = j+1;
            pry[i][j] = piv;
        }
    }
    for (int i=0; i<r; i++) {
        int piv = c-1;
        for (int j=c-1; j>=0; j--) {
            if(str[i][j] == '#') piv = j-1;
            ply[i][j] = piv;
        }
    }
    for (int j=0; j<c; j++) {
        int piv = 0;
        for (int i=0; i<r; i++) {
            if(str[i][j] == '#') piv = i+1;
            pdx[i][j] = piv;
        }
    }
    for (int j=0; j<c; j++) {
        int piv = r-1;
        for (int i=r-1; i>=0; i--) {
            if(str[i][j] == '#') piv = i-1;
            pux[i][j] = piv;
        }
    }
}
 
inline void push(int x, int y, int d){
    if(x < 0 || x >= r || y < 0 || y >= c) return;
    if(v[x][y]) return;
    if(str[x][y] == '#') return;
    pq.push(edge(d,pi(x,y)));
}
 
int main(){
    input();
    make_portal();
    while (!pq.empty()) {
        edge c = pq.top();
        pq.pop();
        int x = c.second.first;
        int y = c.second.second;
        int d = c.first;
        if(v[x][y]) continue;
        if(str[x][y] == 'C'){
            printf("%d",d);
            return 0;
        }
        v[x][y] = 1;
        push(x-1,y,d+1);
        push(x,y-1,d+1);
        push(x+1,y,d+1);
        push(x,y+1,d+1);
        // get closest portal position
        int dist = min(abs(ply[x][y] - y),abs(y - pry[x][y]));
        dist = min(dist,min(abs(pux[x][y] - x),abs(pdx[x][y] - x)));
        // closest portals?
        push(x,ply[x][y],d+dist+1);
        push(x,pry[x][y],d+dist+1);
        push(pux[x][y],y,d+dist+1);
        push(pdx[x][y],y,d+dist+1);
    }
}