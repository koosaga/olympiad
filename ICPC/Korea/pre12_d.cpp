#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

int f[100],i;

int main(){
    f[1] = 1;
    for(i=2; i<=50; i++){
        f[i] = f[i-1] + f[i-2];
        if(f[i] > 1e9) break;
    }
    int t;
    scanf("%d",&t);
    while(t--){
        int x;
        scanf("%d",&x);
        int stk[105], sz = 0;
        for(int j=i; j; j--){
            if(x >= f[j]){
                stk[sz++] = f[j];
                x -= f[j];
            }
        }
        for(int i=sz-1; i>=0; i--){
            printf("%d ",stk[i]);
        }
        puts("");
    }
}