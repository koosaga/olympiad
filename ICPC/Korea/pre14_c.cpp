#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

void solve2(int n, int m){
    if(n%2 == 0){
        for(int i=0; i<n; i++){
            if(i%2 == 0){
                for(int j=0; j<m; j++){
                    printf("(%d,%d)\n",i,j);
                }
            }
            else{
                for(int j=0; j<m; j++){
                    printf("(%d,%d)\n",i,m-1-j);
                }
            }
        }
    }
    else if(m%2 == 0){
        for(int i=0; i<m; i++){
            if(i%2 == 0){
                for(int j=0; j<n; j++){
                    printf("(%d,%d)\n",j,i);
                }
            }
            else{
                for(int j=0; j<n; j++){
                    printf("(%d,%d)\n",n-1-j,i);
                }
            }
        }
    }
}
void solve(){
    int n, m;
    scanf("%d %d",&n,&m);
    puts("1");
    if(n%2 == 0 || m%2 == 0){
        solve2(n,m);
    }
    else{
        solve2(n-1,m-1);
        for(int i=0; i<m; i++){
            printf("(%d,%d)\n",n-1,i);
        }
        for(int i=n-2; i>=0; i--){
            printf("(%d,%d)\n",i,m-1);
        }
    }
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
}