#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
int a[5005],b[5005];
int x,y;
 
int check(int p){
    int piv = p, res = 0;
    for (int i=0; i<x; i++) {
        if(b[piv] == a[i]){
            piv++;
            res++;
        }
    }
    return res;
}
int main(){
    int res = 0;
    scanf("%d %d",&x,&y);
    for (int i=0; i<x; i++) {
        scanf("%d",&a[i]);
    }
    for (int i=0; i<y; i++) {
        scanf("%d",&b[i]);
    }
    for (int i=0; i<y; i++) {
        res = max(res,check(i));
    }
    printf("%d",res);
}