#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
 
int n,a[105];
int optima = 151;
 
char vis[160][160][160];
 
void f(int pos, int x1, int x2, int x3){
    if(vis[x1][x2][x3] >= pos) return;
    if(max(x1,max(x2,x3)) >= optima || 3 * optima - x1 - x2 - x3 <= 4 * (pos - n)) return;
    vis[x1][x2][x3] = pos;
    if(pos == n) optima = max(x1,max(x2,x3));
    else if(a[pos] == 1){
        f(pos+1,x1+4,x2,x3);
        f(pos+1,x1,x2+4,x3);
        f(pos+1,x1,x2,x3+4);
    }
    else if(a[pos] == 2){
        int p1 = max(x1,max(x2,x3));
        f(pos+1,p1+2,p1+1,p1+1);
         
        p1 = max(x1+1,max(x2+1,x3+2));
        f(pos+1,p1,p1,p1);
         
        p1 = max(x1+3,x2+1);
        f(pos+1,p1,p1,x3);
         
        p1 = max(x1,x2);
        f(pos+1,p1+1,p1+3,x3);
         
        p1 = max(x2+3,x3+1);
        f(pos+1,x1,p1,p1);
         
        p1 = max(x2,x3);
        f(pos+1,x1,p1+1,p1+3);
    }
    else if(a[pos] == 3){
        int p1 = max(x1,max(x2,x3));
        f(pos+1,p1+1,p1+1,p1+2);
         
        p1 = max(x1+2,max(x2+1,x3+1));
        f(pos+1,p1,p1,p1);
         
        p1 = max(x1+1,x2+3);
        f(pos+1,p1,p1,x3);
         
        p1 = max(x1,x2);
        f(pos+1,p1+3,p1+1,x3);
         
        p1 = max(x2+1,x3+3);
        f(pos+1,x1,p1,p1);
         
        p1 = max(x2,x3);
        f(pos+1,x1,p1+3,p1+1);
    }
    else if(a[pos] == 4){
        int p1 = max(x1,max(x2,x3));
        f(pos+1,p1+1,p1+2,p1+1);
         
        p1 = max(x1+1,x2+2);
        f(pos+1,p1,p1+1,x3);
         
        p1 = max(x2+1,x3+2);
        f(pos+1,x1,p1,p1+1);
         
        p1 = max(x1+2,x2+1);
        f(pos+1,p1+1,p1,x3);
         
        p1 = max(x2+2,x3+1);
        f(pos+1,x1,p1+1,p1);
         
        p1 = max(x1+1,max(x2+2,x3+1));
        f(pos+1,p1,p1,p1);
    }
    else if(a[pos] == 6){
        int p1 = max(x1,max(x2+1,x3+1));
        f(pos+1,p1+1,p1+1,p1);
         
        p1 = max(x1+2,x2+1);
        f(pos+1,p1,p1+1,x3);
         
        p1 = max(x2+2,x3+1);
        f(pos+1,x1,p1,p1+1);
    }
    else if(a[pos] == 5){
        int p1 = max(max(x1+1,x2+1),x3);
        f(pos+1,p1,p1+1,p1+1);
         
        p1 = max(x1+1,x2+2);
        f(pos+1,p1+1,p1,x3);
         
        p1 = max(x2+1,x3+2);
        f(pos+1,x1,p1+1,p1);
    }
    else if(a[pos] == 7){
        int p1 = max(x2,x3);
        int p2 = max(x1,x2);
        f(pos+1,x1,p1+2,p1+2);
        f(pos+1,p2+2,p2+2,x3);
    }
}
 
int main(){
    memset(vis,-1,sizeof(vis));
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    f(0,0,0,0);
    printf("%d",optima);
}