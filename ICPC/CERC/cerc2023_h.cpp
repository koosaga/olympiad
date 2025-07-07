#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

map<string, vector<string>> adj;
string brak;

void dfs(string x) {
	brak += "0";
	cout << x << endl;
	for (auto &y : adj[x])
		dfs(y);
	brak += "1";
}

void dfs2(string x) {
	if (sz(adj[x]) == 0)
		return;
	cout << x << ":";
	for (auto &z : adj[x])
		cout << " " << z;
	cout << endl;
	for (auto &z : adj[x])
		dfs2(z);
}
int main() {
	string s;
	cin >> s;
	string dummy;
	getline(cin, dummy);

	if (s == "ENCODE") {
		// Parse written by Gemini 2.5 Pro

		// Set to store all unique employee names for the first part of the output
		set<string> all_employees;

		// Set to store employees who are reports. This helps in finding the CEO,
		// who is the only manager that is not a report to anyone.
		set<string> reports;

		string line;
		// Read all management structure lines from standard input until EOF.
		while (getline(cin, line) && !line.empty()) {
			stringstream ss(line);
			string manager, report_name;

			// The manager's name is everything before the colon.
			getline(ss, manager, ':');
			all_employees.insert(manager);

			// The remaining names on the line are the direct reports.
			while (ss >> report_name) {
				adj[manager].push_back(report_name);

				all_employees.insert(report_name);
				reports.insert(report_name);
			}
		}
		// Find the CEO. The CEO is the only manager who does not appear in the 'reports' set.
		string ceo;
		for (const auto &pair : adj) {
			const string &manager = pair.first;
			if (reports.find(manager) == reports.end()) {
				ceo = manager;
				break;
			}
		}
		dfs(ceo);
		cout << brak << endl;
	} else {
		vector<string> vect;
		while (true) {
			string s;
			cin >> s;
			if (s[0] == '0') {
				int p = 0;
				vector<string> stk;
				for (auto &x : s) {
					if (x == '0') {
						stk.push_back(vect[p++]);
					} else {
						auto cur = stk.back();
						stk.pop_back();
						if (sz(stk) > 0) {
							adj[stk.back()].push_back(cur);
						} else {
							dfs2(cur);
						}
					}
				}
				return 0;
			} else {
				vect.push_back(s);
			}
		}
	}
}