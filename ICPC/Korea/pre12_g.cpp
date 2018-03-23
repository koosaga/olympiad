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
        char str[51];
        int hi = 0;
        scanf("%s",str);
        for(int j=0; str[j]; j++){
            hi += (str[j] == '(') - (str[j] == ')');
            if(hi < 0){
                break;
            }
        }
        if(hi == 0) puts("YES");
        else puts("NO");
    }
}