#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <queue>
#include <bits/stdc++.h>
#include <stack>

using namespace std;

#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define pb push_back
#define ri(a)  scanf("%d",&a)
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

const int MAXN = 200005;

struct edge
{
	int to,c;
};
vector<edge> g[MAXN];
int n,m,x,y;
int sp[MAXN];

void dijkstra(){
	FOR(i,0,n) sp[i]=INF; //inicializa en INF el largo de todos los caminos minimos.
	priority_queue<int> pq;
	int v=0;
	pq.push({0,v});
	while(!pq.empty()){
		v=pq.top().S;
		int dd= -pq.top().F; //mosca con el signo - .
		pq.pop();
		if(dd>sp[v]) continue;
		for(auto e:g[v]){ //relajacion desde el nodo v, a sus vecinos u.
			int u=e.to,c=e.c;
			if(sp[v]+c<sp[u]){
				sp[u]=sp[v]+c;
				pq.push({-sp[u],u}); //mosca con el signo - .
		}
	}
}

int main(){

	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL);

	rii(n,m); rii(x,y);

	FOR(i,0,p){
		riii(a,b,c);
		g[a].pb({b,c});
		g[b].pb({a,c});
	}

	dijkstra();

	
	return 0;
}
