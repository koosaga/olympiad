#include <cstdio>
#include <cstring>
using namespace std;

void solve(){
    char s[105];
    scanf("%s",s);
    int l = (int)strlen(s);
    for (int i=0; i<l; i++) {
        s[i] -= '0';
        if(i) s[i] ^= s[i-1];
    }
    int r = 0;
    for (int i=0; i<l; i++) {
        if(s[i]) r += (1<<(l-i-1));
    }
    printf("%d\n",r);
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        solve();
    }
}