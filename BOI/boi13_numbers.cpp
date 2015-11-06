#include <cstdio>
#include <algorithm>
typedef long long lint;
 
lint piv;
lint pow[20];
 
lint dp[20][11][11][2];
 
lint naive_calc(int d, int p1, int p2, int isroot){
    if(d == -1) return 1;
    if(dp[d][p1][p2][isroot]) return dp[d][p1][p2][isroot];
    lint ret = 0;
    for (int i=0; i<10; i++) {
        if(isroot && i ==0) continue;
        if(i != p1 && i != p2){
            ret += naive_calc(d-1,p2,i,0);
        }
    }
    return dp[d][p1][p2][isroot]=ret;
}
 
lint buho_calc(int d, int p1, int p2, int isroot){
    if(d == -1) return 1;
    lint ret = 0;
    for (int i=0; i<10; i++) {
        if(isroot && i == 0) continue;
        if((piv / pow[d]) % 10 < i) break;
        if(i != p1 && i != p2){
            if((piv / pow[d])%10 == i){
                ret += buho_calc(d-1,p2,i,0);
                break;
            }
            else ret += naive_calc(d-1,p2,i,0);
        }
    }
    return ret;
}
 
lint f(lint x){
    if(x == -1) return 0;
    piv = x;
    lint ret = 0;
    int i, lim = (int)(std::lower_bound(pow,pow+19,x+1) - pow);
     
    for (i=0; i<lim; i++) {
        ret += naive_calc(i-1,10,10,1);
    }
    ret += buho_calc(lim-1,10,10,1);
    return ret;
}
 
int main(){
    lint a,b;
    pow[0] = 1;
    for(int i=1; i<19; i++) pow[i] = pow[i-1] * 10;
    scanf("%lld %lld",&a,&b);
    printf("%lld",f(b) - f(a-1));
}