#include <stdio.h>
 
int n;
char str[1000005];
int fail[1000005];
 
int main(){
    scanf("%d %s",&n,str);
    int p = 0;
    for(int i=1; i<n; i++){
        while(p && str[p] != str[i]) p = fail[p];
        if(str[p] == str[i]) p++;
        fail[i+1] = p;
    }
    printf("%d",n - fail[n]);
}