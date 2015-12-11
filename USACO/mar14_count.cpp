#include <cstdio>  
#include <queue>  
#include <vector>  
#include <cstring>  
#include <algorithm>  
using namespace std;  
   
int a[505],n,sum;  
vector<int> res;  
   
int freq[505];  
   
vector<int> v;  
   
int f(int pos){  
    int ret = 0;  
    for (int i=pos; i<=n; i++) {  
        ret += min(pos-1,v[i]);  
    }  
    return ret;  
}  
   
   
bool check(int pos){  
    v.clear();  
    for (int i=0; i<n+1; i++) {  
        if(i != pos) v.push_back(a[i]);  
    }  
    sort(v.begin(),v.end());  
    v.push_back(0);  
    reverse(v.begin(),v.end());  
    int sum[505] = {};  
    for (int i=1; i<=n; i++) {  
        sum[i] = sum[i-1] + v[i];  
    }  
    for (int i=1; i<=n; i++) {  
        if(sum[i] > i * (i-1) + f(i+1)) return 0;  
    }  
    return 1;  
}  
int main(){  
    scanf("%d",&n);  
    for (int i=0; i<n+1; i++) {  
        scanf("%d",&a[i]);  
        sum += a[i];  
    }  
    for (int i=0; i<n+1; i++) {  
        if((sum - a[i])%2 == 1) continue;  
        if(a[i] > n-1) continue;  
        if(sum - a[i] > n*(n-1)) continue;  
        else{  
            if(check(i)) res.push_back(i+1);  
        }  
    }  
    printf("%d\n",(int)res.size());  
    for (int i=0; i<res.size(); i++) {  
        printf("%d\n",res[i]);  
    }  
}