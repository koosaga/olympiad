#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
 
int n;

vector <pii> graph[26];

int arr[33][33];
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        int t;
        for(scanf("%d",&t);t--;){
            char str[30] = {0, };
            scanf("%s",str);
            int bit = 0;
            for(int j=0; str[j]; j++){
            	bit |= (1 << (str[j]-'a'));
            }
            for(int j=0; j<n; j++) if(bit & (1 << j)){
            	graph[j].emplace_back(bit, i);
            }
        }
    }
    for(int i=0; i<n; i++){
    	queue<int> q;
    	q.push(i);
    	int bit = 0;
    	vector <int> dist(n, -1);
    	dist[i] = 0;
    	while(!q.empty()){
    		int qf = q.front();
            bit |= (1 << qf);
    		q.pop();
            for (auto &p: graph[qf]){
    			int req = p.first;
    			int pos = p.second;
    			if(dist[pos] != -1) continue;
    			if((bit & req) == req){
    				q.push(pos);
    				dist[pos] = dist[qf] + 1;
    			}
    		}
    	}
    	for(int j=0; j<n; j++)
    		arr[j][i] = dist[j];
    }
    for(int i=0; i<n; i++){
    	for(int j=0; j<n; j++){
    		printf("%d ",arr[i][j]);
    	}
    	puts("");
    }
}