#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
char str[76][76];
bitset<76> bs[76];
int n, ret;
int chk[105], rchk[105];
 
void bktk(int x, int d, bitset<76> bst){
     if(ret <= d) return;
    if(x == n){
        if(bst.count() == n && ret > d){
            ret = d;
            for(int i=0; i<n; i++){
                chk[i] = rchk[i];
            }
        }
        return;
    }
    bktk(x+1, d, bst);
    if(d < 5){
        rchk[x] = 1;
        bktk(x+1, d+1, bst | bs[x]);
        rchk[x] = 0;
    }
}
 
int main(){
    int t, p = 0;
    while(~scanf("%d",&n)){
        for(int i=0; i<n; i++){
            bs[i] = 0;
            cin >> str[i];
            for(int j=0; j<n; j++){
                if(str[i][j] == '1'){
                    bs[i].set(j);
                }
            }
            bs[i].set(i);
        }
        memset(chk, 0, sizeof(chk));
        ret = 10;
        bitset<76> none;
        bktk(0, 0, none);
        printf("Case %d: %d", ++p, ret);
        for(int i=0; i<n; i++){
            if(chk[i]) printf(" %d", i+1);
        }
        puts("");
    }
}