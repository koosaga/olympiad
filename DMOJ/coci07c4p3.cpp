// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c4p3
#include <bits/stdc++.h>
using namespace std;
vector<string> cjt;
int main(){
	string s;
	cin >> s;
	int n = s.size();
	for(int i = 0;i + 1 < n;i++){
		for(int j = i+1;j + 1<n;j++){
			string s1,s2,s3,s4;
			for(int k = 0;k<=i;k++) s1.push_back(s[k]);
			for(int k = i+1;k<=j;k++) s2.push_back(s[k]);
			for(int k = j+1;k<n;k++) s3.push_back(s[k]);
			reverse(s1.begin(),s1.end());
			reverse(s2.begin(),s2.end());
			reverse(s3.begin(),s3.end());
			s4 = s1 + s2 + s3;
			cjt.push_back(s4);
		}
	}
	sort(cjt.begin(),cjt.end());
	cout << cjt[0] << endl;
	return 0;
}