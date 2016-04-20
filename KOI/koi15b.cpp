#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long hsh;
const hsh mod1 = 1e9 + 513;
const hsh mod2 = 1e9 + 531;
  
int n, m;
char str1[1505], str2[1505];
int psum1[1505][26], psum2[1505][26];
  
vector<hsh> hs;
vector<hsh> hs2;
  
hsh make_hsh(int* a){
    hsh t1 = 0;
    for(int i=0; i<26; i++){
        t1 *= 1505ll;
        t1 += a[i];
    }
    return t1;
}
  
bool trial(int l){
    if(l == 0) return 1;
    hs.clear();
    for(int i=0; i<=n-l; i++){
        int hshOp[26] = {};
        for(int j=0; j<26; j++){
            hshOp[j] = psum1[i+l][j] - psum1[i][j];
        }
        hs.push_back(make_hsh(hshOp));
    }
    sort(hs.begin(), hs.end());
    for(int i=0; i<=m-l; i++){
        int hshOp[26] = {};
        for(int j=0; j<26; j++){
            hshOp[j] = psum2[i+l][j] - psum2[i][j];
        }
        hsh p = make_hsh(hshOp);
        if(*lower_bound(hs.begin(), hs.end(), p) == p) return 1;
    }
    return 0;
}
  
int main(){
    scanf("%s %s",str1+1,str2+1);
    n = (int)strlen(str1+1);
    m = (int)strlen(str2+1);
    for(int i=1; i<=n; i++){
        psum1[i][str1[i]-'a']++;
        for(int j=0; j<26; j++){
            psum1[i][j] += psum1[i-1][j];
        }
    }
    for(int i=1; i<=m; i++){
        psum2[i][str2[i]-'a']++;
        for(int j=0; j<26; j++){
            psum2[i][j] += psum2[i-1][j];
        }
    }
    int p = min(n, m);
    while(!trial(p)) p--;
    printf("%d",p);
}