#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;
 
vector<int> a_bit[20];
int n,m,a[20],b[20];
 
void trial_bit(int v){
    int res = 0;
    for (int i=0; i<m; i++) {
        if((v>>i)&1) res += b[i];
    }
    for (int i=0; i<n; i++) {
        if(a[i] == res) a_bit[i].push_back(v);
    }
}
 
bool vis[20][1<<20];
void f(int pos, int v){
    if(pos == n){
        puts("YES");
        exit(0);
    }
    if(vis[pos][v]) return;
    vis[pos][v] = 1;
    for (int i=0; i<a_bit[pos].size(); i++) {
        if((a_bit[pos][i] & ~v) == 0) f(pos+1,v^a_bit[pos][i]);
    }
}
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    for (int i=0; i<m; i++) {
        scanf("%d",&b[i]);
    }
    for (int i=0; i<(1<<m); i++) {
        trial_bit(i);
    }
    f(0,(1<<m)-1);
    puts("NO");
}