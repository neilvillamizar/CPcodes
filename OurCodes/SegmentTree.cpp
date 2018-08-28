#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <queue>
#include <bits/stdc++.h>
#include <stack>
#include <assert.h>

using namespace std;

#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define pb push_back
#define ri(a)  scanf("%d\n",&a)
#define rii(a,b)  scanf("%d %d",&a,&b)
#define riii(a,b,c) scanf("%d %d %d",&a,&b,&c)
#define lri(a) scanf("%lld",&a)
#define lrii(a,b) scanf("%lld %lld",&a,&b)
#define F first
#define S second

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int INF = 0x3f3f3f3f;

/*--------------------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------------------*/

int a[1000000]; //Mosca con el largo del array.
int n;
struct nodost
{
	ll something, anotherSomething; // PONER AQUI LO QUE SE VA A LLEVAR EN CADA NODO
};
nodost nodo[1000000]; //mosca con el largo del  array

nodost merge(nodost l, nodost r){

	nodost resp;

	// PONER AQUI LOS CALCULOS PARA EL MERGE ENTRE DOS SEGMENTOS
	
	return resp;
}

nodost hoja(int l){

	nodost resp;

	resp.something=a[l];         //INICIALIZAR AQUI LO QUE VAS A LLEVAR EN CADA SEGMENTO EN LAS HOJAS.
	resp.anotherSomething=a[l];
	
	return resp;
}

void buildst(int l,int r,ll indexst){ 
	if(l==r){
		nodo[indexst]=hoja(l);
		return;
	}
	ll left=2*indexst, right=2*indexst+1;
	int med= (l+r)/2;
	buildst(l,med,left); 
	buildst(med+1,r,right);
	nodo[indexst]=merge(nodo[left],nodo[right]);
}

void update(int u,int l,int r,ll indexst){ 
	if(l==u && r==u){
		nodo[indexst]=hoja(u);
		return;
	}
	ll left=2*indexst, right=2*indexst+1;
	int med= (l+r)/2;
	if(u<=med)
	update(u,l,med,left); 
	else
	update(u,med+1,r,right);
	nodo[indexst]=merge(nodo[left],nodo[right]);
}

nodost query(ll indexst, int left,int right,int l,int r){

	if (left == l && right == r)
    	return nodo[indexst];
  	
	  int med = (left + right) / 2;
	  if (l > med)
	    return query(2*indexst+1, med+1, right, l, r);
	  if (r <= med)
	    return query(2*indexst, left, med, l, r);
	  	
	  nodost lresp = query(2*indexst, left, med, l, med);
	  nodost rresp = query(2*indexst+1, med+1, right, med+1, r);
	  nodost result=merge(lresp, rresp);

	return result;
}

int main(){

	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL);

	cin>>n;

	FOR(i,1,n+1){ //mosca indexar desde 1
		ri(a[i]);
	}

	//hacer segment tree
	buildst(1,n,1); // intevalo comlpleto (1-n), lo representa el nodo 1

	int m;
	ri(m);

	FOR(i,0,m){
		int x,y,e;
		riii(e,x,y);
		if(e==1){ 
		//resolver query con segment tree
			printf("%d\n", query(1,1,n,x,y).something); //something es lo que quieras devolver del struct hoja 
							//nodo 1, intervalo completo, intervalo de interes
		}else{ //hacer update
			a[x]=y; //mosca actualizar el array 
			update(x,1,n,1); //valor a actualizar, intervalo completo, nodo 1
		}
	}

	return 0;
}