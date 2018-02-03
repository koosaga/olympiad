#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){ 
        int n;
        scanf("%d",&n);
        int sa = 0, sb = 0, sa2 = 0, sb2 = 0, tot = 0;
        for(int i=0; i<n; i++){
            int a, b;
            scanf("%d %d",&a,&b);
            sa += a;
            sb += b;
            sa2 += a;
            sb2 += b;
            int ret = min(max(sa2, sb2), max(sa, sb));
            if(sa <= (sa + sb + 1) / 2 && (sa + sb + 1) / 2 <= sa2){
                ret = min(ret, (sa + sb + 1) / 2);
            }
            tot = max(tot, ret);
            if(sa > 0) sa--;
            else if(sb > 0) sb--;
            if(sb2 > 0) sb2--;
            else if(sa2 > 0) sa2--;
        }
        printf("%d\n", tot-1);
    }
}
