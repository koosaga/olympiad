#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int,int> pi;

pi a[105], b[105];
int p1, p2, n;
int vis[105], vis2[105];

bool solve(pi *a, int size){
    int cpos = 0;
    memset(vis,0,sizeof(vis));
    for(int i=0; i<size; i++){
        int mval = -1e9, mpos = -1;
        for(int j=0; j<size; j++){
            if(vis[j]) continue;
            if(a[j].first <= cpos && a[j].second > mval){
                mval = a[j].second;
                mpos = j;
            }
        }
        if(mpos == -1) return 0;
        cpos += mval;
        vis[mpos] = 1;
    }
    return 1;
}
int main(){
    scanf("%d",&n);
    int sum = 0;
    for(int i=0; i<n; i++){
        char str[105];
        scanf("%s",str);
        int low = 0, cur = 0;
        for(int i=0; str[i]; i++){
            cur += (str[i] == '(' ? 1 : -1);
            low = min(low, cur);
        }
        sum += cur;
    //  printf("%d %d\n",-low, cur);
        if(cur > 0) a[p1++] = pi(-low, cur);
        else b[p2++] = pi(-low + cur, -cur);
    }
    if(sum){
        puts("No");
        return 0;
    }
    sort(a,a+p1);
    sort(b,b+p2);
    int ch = 0;
    if(solve(a,p1) && solve(b,p2)) puts("Yes");
    else puts("No");
}