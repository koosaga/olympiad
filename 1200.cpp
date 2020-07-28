// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1200
#include <iostream>
#include <string>
#include <set>
#include <queue>
#define endl '\n'
using namespace std;
queue<char> fila;
struct node{
	char key;
	struct node *left, *right;
};
struct node *newNode(char item){
	struct node *temp = new node;
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}
struct node* insert(struct node* node, char key){
	if (node == NULL) return newNode(key);
	if (key < node-> key) node->left = insert(node->left, key);
	else if (key > node->key) node->right = insert(node->right, key);
	return node;
}
void prefixa(struct node *root){
	if (root != NULL){
		fila.push(root->key);
		prefixa(root->left);
		prefixa(root->right);
	}
}
void infixa(struct node *root){
	if (root != NULL){
		infixa(root->left);
		fila.push(root->key);
		infixa(root->right);
	}
}
void posfixa(struct node *root){
	if (root != NULL){
		posfixa(root->left);
		posfixa(root->right);
		fila.push(root->key);
	}
}
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	set<char> busca;
	string operacao;
	char op;
	string insere = "I", procura = "P", inf = "INFIXA", pre = "PREFIXA", pos = "POSFIXA";
	struct node *raiz = NULL;
	cin >> operacao >> op;
	raiz = insert(raiz,op);
	while(cin >> operacao){
		//cout << "Operacao : " << operacao << endl;
		if (operacao == insere){
			cin >> op;
			//cout << "Op : " << op << endl;
			busca.insert(op);
			insert(raiz,op);
		}
		if (operacao == procura){
			cin >> op;
			if (busca.count(op)) cout << op << " existe" << endl;
			else cout << op << " nao existe" << endl;
		}
		if (operacao == inf){
			infixa(raiz);
			cout << fila.front();
			fila.pop();
			while(!fila.empty()){
				cout << " " << fila.front();
				fila.pop();
			}
			cout << endl;
		}
		if (operacao == pre){
			prefixa(raiz);
			cout << fila.front();
			fila.pop();
			while(!fila.empty()){
				cout << " " << fila.front();
				fila.pop();
			}
			cout << endl;
		}
		if (operacao == pos){
			posfixa(raiz);
			cout << fila.front();
			fila.pop();
			while(!fila.empty()){
				cout << " " << fila.front();
				fila.pop();
			}
			cout << endl;
		}
	}
	return 0;
}
