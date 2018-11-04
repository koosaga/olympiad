#include <cstdio>
#include <algorithm>
using namespace std;

int che[1005];

int main(){
    for(int i=2; i<=1000; i++){
        if(che[i]) continue;
        for(int j=i*i; j<=1000; j+=i){
            che[j] = 1;
        }
    }
    int t;
    scanf("%d",&t);
    while(t--){
        int x;
        scanf("%d",&x);
        int f = 0;
        for(int i=2; i<=x; i++){
            if(che[i]) continue;
            for(int j=i; j<=x-i-j; j++){
                if(che[j]) continue;
                int k = x - i - j;
                if(!che[k]){
                    f = 1;
                    printf("%d %d %d\n",i,j,k);
                    break;
                }
            }
            if(f) break;
        }
        if(!f) puts("-1");
    }
}