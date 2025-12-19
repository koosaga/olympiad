#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int t;
int n, m;
int A[100005], B[100005];

int main(){
    #ifndef LOCAL
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #endif
    
    cin >> t;
    while(t--){
        cin >> n >> m;
        for(int i=1; i<=n; i++) cin >> A[i];
        for(int i=1; i<=m; i++) cin >> B[i];

        priority_queue<int > S, T;
        for(int i=1; i<=n; i++) S.push(A[i]);
        for(int i=1; i<=m; i++) T.push(B[i]);

        while(1){
            if(S.empty()) {
                cout << "Bob\n";
                break;
            }
            int av = S.top(), bv = T.top(); T.pop();
            if(av < bv) T.push(bv-av);
            
            if(T.empty()){
                cout << "Alice\n";
                break;
            }
            av = S.top(); S.pop();
            bv = T.top();
            if(av > bv) S.push(av-bv);
        }
    }
}