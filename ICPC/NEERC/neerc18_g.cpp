#include <bits/stdc++.h>
using namespace std;
int a[7];

int main(){
    int tc; cin >> tc;
    while(tc--){
        int n; cin >> n;
        for(int i=0; i<7; i++) cin >> a[i];
        int cnt = count(a, a + 7, 1);
        int dap = 1e9;
        for(int i=0; i<7; i++){
            if(a[i]){
                int dvs = n / cnt;
                int rem = n % cnt;
                int ret = 7 * dvs;
                if(rem == 0){
                    int lst = 0;
                    for(int j=0; j<7; j++){
                        if(a[(i+j)%7]){
                            lst = j;
                        }
                    }
                    ret += lst - 7;
                }
                else{
                    for(int j=0; j<7; j++){
                        if(a[(i+j)%7]){
                            rem--;
                            if(rem == 0){
                                ret += j;
                                break;
                            }
                        }
                    }
                }
                dap = min(dap, ret);
            }
        }
        cout << dap + 1<< endl;
    }
}