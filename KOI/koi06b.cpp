#include <cstdio>  
   
int cost[6][6]={{100,70,40},{70,50,30},{40,30,20}},n,v[11][11],dp[12][12][1<<12];  
char a[12][12];  
int DEL(int bit, int pos){return bit&(1<<pos)?bit^(1<<pos):bit;}  
   
int f(int x, int y, int bit){  
    if(x==n) return 0;  
    if(y==n) return f(x+1,0,bit);  
    if(dp[x][y][bit]) return dp[x][y][bit];  
    int r=f(x,y+1,DEL(bit,y)),t;  
    if(y+1<n && !(bit&(1<<y)) && !(bit&(1<<(y+1)))){  
        t=f(x,y+2,bit)+cost[a[x][y]-'A'][a[x][y+1]-'A'];  
        if(r<t) r=t;  
    }  
    if(x+1<n && !(bit&(1<<y))){  
        t=f(x,y+1,bit|(1<<y))+cost[a[x][y]-'A'][a[x+1][y]-'A'];  
        if(r<t) r=t;  
    }  
    return dp[x][y][bit]=r;  
}  
   
int main(){  
    scanf("%d",&n);  
    for (int i=0; i<n; i++) scanf("%s",a[i]);  
    printf("%d",f(0,0,0));  
}