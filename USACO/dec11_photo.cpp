#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
 
int idx[5][20005];
int res[20005];
int link[20005];
 
int cmp(int a, int b){
    int res = 0;
    for (int i=0; i<5; i++) {
        if(idx[i][a] < idx[i][b]) res++;
        else res--;
    }
    return res>0;
}
 
int main(){
    map<int,int> mp;
    int n,t;
    scanf("%d",&n);
    for (int i=0; i<5; i++) {
        for (int j=0; j<n; j++) {
            scanf("%d",&t);
            if(i == 0){
                mp[t] = j;
                link[j] = t;
                idx[i][j] = j;
            }
            else{
                idx[i][mp[t]] = j;
            }
        }
    }
    for (int j=0; j<n; j++) {
        res[j] = j;
    }
    sort(res,res+n,cmp);
    for (int i=0; i<n; i++) {
        printf("%d\n",link[res[i]]);
    }
}
소스코드 공개    공개   비공개   맞았을 때만 공개  
