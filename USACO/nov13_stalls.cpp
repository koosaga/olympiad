#include <cstdio>
 
int dx[3000005];
bool occu[3000005];
 
int main(){
    int n, k,x,y,a,b;
    scanf("%d %d",&n,&k);
    while(k--){
        scanf("%d %d %d %d",&x,&y,&a,&b);
        for(int i=1; i<=y; i++){
            int func = (1ll * a * i + b) % n;
            dx[func]+=x;
        }
    }
    int stack = 0;
    for(int i=0; i<n; i++){
        stack += dx[i];
        dx[i] = 0;
        if(!occu[i] && stack){
            occu[i] = 1;
            stack--;
        }
    }
    for(int i=0; i<n; i++){
        if(!occu[i] && stack){
            occu[i] = 1;
            stack--;
        }
    }
    for(int i=0; i<n; i++){
        if(!occu[i]){
            printf("%d",i);
            break;
        }
    }
}