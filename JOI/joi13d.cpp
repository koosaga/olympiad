#include <cstdio>
int n,limit[1000005];
char str[1000005];
 
int isTower(int lim){
    int K=0,O=0,I=0;
    // where can i use i from backward ? limit[lim]+1 ~
    for (int i=0; i<n; i++) {
        if(str[i]=='J' || (str[i]=='I' && i<=limit[lim])) K++;
        if(str[i]=='O' && O<K) O++;
        if(str[i]=='I' && I<O && i>limit[lim]) I++;
    }
    return (K>=lim && O>=lim && I>=lim);
}
 
int bs(int s, int e){
    if(s==e) return s;
    if(isTower((s+e+1)/2)) return bs((s+e+1)/2,e);
    else return bs(s,(s+e+1)/2-1);
}
 
int main(){
    int t=0;
    scanf("%d %s",&n,str);
    for (int i=n-1; i>=0; i--) {
        if(str[i]=='I') limit[t++]=i;
    }
    printf("%d",bs(0,t));
}