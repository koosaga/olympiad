#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int B = 1000;
 
char buck[1005][2005];
int len[1005];
 
char buf[1000005];
 
int n, m;
 
pi back(){
    int p = 1004;
    while(!len[p]){
        p--;
    }
    return pi(p, len[p]);
}
 
pi get(int x){
    int p = 0;
    while(1){
        if(x <= len[p]){
            break;
        }
        x -= len[p++];
    }
    return pi(p, x-1);
}
 
void reinit(){
    int p = 0;
    for(int i=0; i<1005; i++){
        for(int j=0; j<len[i]; j++){
            buf[p++] = buck[i][j];
        }
        len[i] = 0;
    }
    for(int i=0; i<n; i++){
        buck[i/B][len[i/B]++] = buf[i];
    }
}
 
int main(){
    scanf("%d %d %s",&n,&m,buf);
    for(int i=0; i<n; i++){
        buck[i/B][len[i/B]++] = buf[i];
    }
    for(int i=0; i<m; i++){
        if(i%B == B-1){
            reinit();
        }
        char buf[5];
        scanf("%s",buf);
        if(*buf == 'a'){
            int a, b;
            scanf("%d %d",&a,&b);
            pi pa = get(a);
            char c = buck[pa.first][pa.second];
            for(int i=pa.second; i<len[pa.first]-1; i++){
                buck[pa.first][i] = buck[pa.first][i+1];
            }
            len[pa.first]--;
            pi pb;
            if(b == n) pb = back();
            else pb = get(b);
            for(int i=len[pb.first]; i>pb.second; i--){
                buck[pb.first][i] = buck[pb.first][i-1];
            }
            buck[pb.first][pb.second] = c;
            len[pb.first]++;
        }
        else{
            int t;
            scanf("%d",&t);
            pi r = get(t);
            printf("%c\n",buck[r.first][r.second]);
        }
    }
}