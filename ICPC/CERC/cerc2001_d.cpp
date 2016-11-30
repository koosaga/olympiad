#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
 
struct node{int zero, one, term;}trie[800005];
int piv;
 
char morse[26][5] = {"01","1000","1010","100","0","0010","110","0000","00","0111","101","0100","11","10","111","0110","1101","010","000","1","001","0001","011","1001","1011","1100"};
int len[26] = {2,4,4,3,1,4,3,4,2,4,3,4,2,2,3,4,4,3,3,1,3,4,3,4,4,4};
 
char str[10005], str2[25];
char str3[10000][100];
int n, length;
 
vector<int> graph[10005];
int dp[10005];
 
void init(){
	for (int i=0; i<800005; i++) {
		trie[i] = {0,0,0};
		if(i < 10005) graph[i].clear();
	}
	memset(dp,-1,sizeof(dp));
	memset(str3,0,sizeof(str3));
	length = piv = 0;
}
 
void mk_trie(){
	for (int i=0; i<n; i++) {
		int pt = 0;
		for (int j=0; str3[i][j]; j++) {
			if(str3[i][j] == '0'){
				if(trie[pt].zero == 0) trie[pt].zero = ++piv;
				pt = trie[pt].zero;
			}
			if(str3[i][j] == '1'){
				if(trie[pt].one == 0) trie[pt].one = ++piv;
				pt = trie[pt].one;
			}
		}
		trie[pt].term++;
	}
}
 
int f(int x){
	if(x > length) return 0;
	if(x == length) return 1;
	if(~dp[x]) return dp[x];
	int res = 0;
	for (int i=0; i<graph[x].size(); i++) {
		res += f(x + graph[x][i]);
	}
	return dp[x] = res;
}
 
void solve(){
	init();
	scanf("%s %d",str,&n);
	for (int i=0; str[i]; i++) {
		str[i] = (str[i] == '.' ? '0' : '1');
		length++;
	}
	for (int i=0; i<n; i++) {
		scanf("%s",str2);
		char *pt = str3[i];
		for (int j=0; str2[j]; j++) {
			for (int k=0; k<len[str2[j]-'A']; k++) {
				*pt = morse[str2[j]-'A'][k];
				pt++;
			}
		}
	}
	mk_trie();
	for (int i=0; i<length; i++) {
		int pt = 0, j = 0;
		do{
			if(str[i+j] == '0') pt = trie[pt].zero;
			else pt = trie[pt].one;
			j++;
			for(int k=0; k<trie[pt].term; k++) graph[i].push_back(j);
		}while(pt && i+j < length);
	}
	printf("%d\n",f(0));
}
 
int main(){
	int t;
	scanf("%d",&t);
	while (t--) {
		solve();
	}
}