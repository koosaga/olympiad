#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 205;

unsigned read_mask(){
    string s;
    cin >> s;
    s = s + ".";
    unsigned msk = 0;
    for(int i=0; i<s.size(); i++){
        if(s[i] == '.'){
            int pos = i;
            for(int j=i-1; j>=0; j--){
                if(s[j] == '.') break;
                pos = j;
            }
            int ans = 0;
            for(int j=pos; j<i; j++) ans = (ans * 10) + s[j] - '0';
            msk = (msk << 8) | ans;
        }
    }
    return msk;
}

void print_mask(unsigned msk){
    for(int i=0; i<4; i++){
        printf("%u", (msk >> (24 - 8 * i)) & 255);
        if(i < 3) printf(".");
    }
    puts("");
}

unsigned a[1005];
int main(){
    int n;
    cin >> n;
    for(int i=0; i<n; i++) a[i] = read_mask();
    unsigned tot = 0;
    for(int i=31; i>=0; i--){
        int ok = 1;
        for(int j=1; j<n; j++){
            if((a[j] >> i) % 2 != (a[j-1] >> i) % 2){
                ok = 0;
                break;
            }
        }
        if(ok == 0) break;
        else tot |= (1u << i);
    }
    print_mask(a[0] & tot);
    print_mask(tot);
}
