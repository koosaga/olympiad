#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, a[105];

int chk[10005], sum;

int getsum(int s, int e){
    return chk[e-1] - chk[s];
}

int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i];
        sum += a[i];
        chk[sum] = 1;
    }
    for(int i=1; i<=sum; i++){
        chk[i] += chk[i-1];
    }
    if(sum % 2 == 1){
        puts("no quotation");
        return 0;
    }
    for(int i=100; i; i--){
        if(i * (i+1) > sum) continue;
        int pos = 0, rpos = sum, bad = 0;
        for(int j=i; j; j--){
            if(getsum(pos, pos+j) || getsum(rpos-j, rpos)) bad = 1;
            pos += j;
            rpos -= j;
        }
        if(!bad){
            if(i == 1 && sum != 2){
                break;
            }
            printf("%d", i);
            return 0;
        }
    }
    puts("no quotation");
}