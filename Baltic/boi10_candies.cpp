#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
using namespace std;
typedef bitset<100> bits;
 
int n, a[105];
bool knap[700005];
bits bs[700005];
 
const int offset = 700000;
bool knap2[2][1400005];
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    int sum = 0;
    knap[0] = 1;
    bs[0] = 0;
    for(int i=1; i<=offset; i++){
        bs[i].set();
    }
    for(int i=0; i<n; i++){
        sum += a[i];
        for(int j=sum; j>=a[i]; j--){
            if(knap[j - a[i]]){
                bits tmp = bs[j - a[i]];
                tmp.set(i,1);
                bs[j] &= tmp;
                knap[j] = 1;
            } 
        }
    }
    int ret = 1e9, retp = -1;
    for(int i=0; i<n; i++){
        int cnt = 0;
        for(int j=0; j<=sum; j++){
            if(knap[j] && bs[j].test(i)){
                cnt++;
            }
        }
        if(ret > cnt) {
            ret = cnt;
            retp = i;
        }
    }
    printf("%d ",a[retp]);
    for(int i=retp; i<n-1; i++){
        a[i] = a[i+1];
    }
    n--;
    sum = 0;
    knap2[1][offset] = 1;
    for(int i=0; i<n; i++){
        sum += a[i];
        for(int j=offset-sum; j<=offset+sum; j++){
            knap2[i%2][j] |= knap2[(i+1)%2][j];
            if(j + a[i] <= 2 * offset) knap2[i%2][j] |= knap2[(i+1)%2][j + a[i]];
            if(j >= a[i]) knap2[i%2][j] |= knap2[(i+1)%2][j - a[i]];
        }
    }
    for(int i=offset+1; ; i++){
        if(!knap2[(n+1)%2][i]){
            printf("%d",i-offset);
            return 0;
        }
    }
}