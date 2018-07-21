#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
using namespace std;

#define pb push_back
#define ri(x) scanf("%d",&x)
#define rii(x,y) ri(x),ri(y)
#define ms(obj,val) memset(obj,val,sizeof(obj))
#define ms2(obj,val,sz) memset(obj,val,sizeof(obj[0])*sz)
#define FOR(i,f,t) for(int i=f;i<(int)t;i++)
#define FORR(i,f,t) for(int i=f;i>(int)t;i--)
#define EPS 1e-28
#define PI 2*acos(0.0)
#define y1 fdsadfa
typedef long long ll;
typedef vector<int> vi;
typedef pair <int, int> ii;

const int MAXAL = 258;
struct node{
	node* nxt[MAXAL];
	bool end;
	int c;
	node* p;
	node* sl;
	node* ol;
	int idx;
	node(): end(false), c(0), p(NULL), sl(NULL), ol(NULL), idx(-1){
		ms(nxt, 0);
	}
};
typedef node* trie;
trie root = new node();
//tener cuidado con strings repetidos
void add(trie root, const string& s, int k){
	trie t = root;
	FOR(i, 0, s.size()){
		int v = (int) s[i]; // mapear caracteres a numeros segun alfabeto
		if(!t->nxt[v]){
			trie son = new node();
			son->c = v;
			son->p = t;
			t -> nxt[v] = son;
		}
		t = t->nxt[v];
		if(i == (int)s.size()-1){
			t->end = true;
			t->idx = k;
		}
	}
}
void buildLinks(trie root){
	queue<trie> q;
	q.push(root);
	while(!q.empty()){
		trie t = q.front(); q.pop();
		trie w = t->p;
		if(w){
			w = w->sl;
			while(w && !w->nxt[t->c]) w = w->sl;
			t->sl  = w ? w->nxt[t->c] : root;
			t->end = t->end || t->sl->end;
			t->ol = (t->sl->idx == -1) ? t->sl->ol : t->sl;
		}
		FOR(c, 0, MAXAL) if(t->nxt[c]) q.push(t->nxt[c]); 
	}
}
bool check(trie root, string &T){
	int n = T.size();
	trie x = root;
	FOR(i, 0, n){
		int v = (int) T[i]; // mapear caracter a numero
		while(x && !x->nxt[v])
			x = x->sl;
		x = x ? x->nxt[v] : root;
		if(x->end) return true;
	}
	return false;
}
// Primer ocurrencia del final de un string
// Calcular todas y ver cual es mejor si 
// se necesita la primera
ii first_ocurrence(string& T){
	int n = T.size();
	trie x = root;
	FOR(i, 0, n){
		int v = T[i];
		while(x && !x->nxt[v])
			x = x-> sl;
		x = x ? x->nxt[v] : root;
		if(x->idx != -1) return {i, x->idx};
		if(x->ol && x->ol->idx != -1) return {i, x->ol->idx};
	}
	return {-1, -1};
}
set<int> subString(trie root, string& T){
	int n = T.size();
	trie x = root;
	set<int> ans;
	FOR(i, 0, n){
		int v = (int) T[i]; // mapear caracter a numero
		while(x && !x->nxt[v])
			x = x->sl;
		x = x ? x->nxt[v] : root;
		trie y = x;
		while(y){
			if(y->idx != -1) ans.insert(y->idx);
			y = y -> ol;
		}
	}
	return ans;
}

int main(){

}


