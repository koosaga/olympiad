#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef pair<double,lint> pi;
 
priority_queue<pi,vector<pi>,greater<pi> > pq;
 
lint bino[21][21];
 
double p[4];
int n;
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<=20; i++){
        bino[i][0] = 1;
        for(int j=1; j<=i; j++){
            bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
        }
    }
    for(int i=0; i<4; i++){
        scanf("%lf",&p[i]);
    }
    vector<pi> v;
    for(int i=0; i<=n; i++){
        for(int j=0; i+j<=n; j++){
            for(int k=0; i+j+k<=n; k++){
                int l = n-i-j-k;
                lint t = bino[n][i] * bino[n-i][j] * bino[n-i-j][k];
                double prob = pow(p[0],i) * pow(p[1],j) * pow(p[2],k) * pow(p[3],l);
                pq.push(pi(prob,t));
            }
        }
    }
    double ret = 0;
    while(1){
        pi t1 = pq.top();
        pq.pop();
        if(pq.empty() && t1.second == 1) break;
        if(t1.second > 1){
            if(t1.second % 2 == 1){
                pq.push(pi(t1.first, 1));
            }
            ret += (t1.second / 2) * 2.0 * t1.first;
            pq.push(pi(t1.first * 2, t1.second / 2));
        }
        else{
            pi t2 = pq.top();
            pq.pop();
            ret += t1.first + t2.first;
            pq.push(pi(t1.first + t2.first, 1));
            if(t2.second != 1) pq.push(pi(t2.first, t2.second - 1));
        }
    }
    printf("%f\n",ret);
}