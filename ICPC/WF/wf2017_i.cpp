#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

int n, m;
int adj[55][55];
char a[55], b[55];

int main(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<n; i++){
        scanf("%s %s",a, b);
        adj[*a - 'a'][*b - 'a'] = 1;
    }
    for(int i=0; i<26; i++) adj[i][i] = 1;
    for(int i=0; i<26; i++){
        for(int j=0; j<26; j++){
            for(int k=0; k<26; k++){
                adj[j][k] |= adj[j][i] & adj[i][k];
            }
        }
    }
    while(m--){
        scanf("%s %s",a, b);
        if(strlen(a) != strlen(b)) puts("no");
        else{
            bool ok = 1;
            for(int i=0; i<strlen(a); i++){
                if(!adj[a[i] - 'a'][b[i] - 'a']) ok = 0;
            }
            puts(ok ? "yes" : "no");
        }
    }
}
