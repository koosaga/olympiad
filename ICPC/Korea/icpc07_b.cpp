#include <cstdio>
#include <cstring>
#include <unordered_set>
using namespace std;
  
const int p = 409;
  
char str[200005];
long long hf[200005], pw[200005];
int n;
  
bool f(int x){
    unordered_set<long long> s;
    for (int i=x-1; i<n; i++) {
        long long h = (hf[i] - (i >= x ?hf[i-x] * pw[x] : 0));
        if(s.find(h) != s.end()) return 1;
        s.insert(h);
    }
    return 0;
}
  
int main(){
    scanf("%s",str);
    n = strlen(str);
    hf[0] = str[0], pw[0] = 1;
    for (int i=1; i<n; i++) {
        pw[i] = pw[i-1] * p;
        hf[i] = hf[i-1] * p + str[i];
    }
    int s = 0, e = n;
    while (s != e) {
        int m = (s+e+1)/2;
        if(f(m)) s = m;
        else e = m-1;
    }
    printf("%d",s);
}