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

struct edge
{
	int to,c;
};
vector<edge> g[200000];
int n,p,x,y;


int main(){

	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL);

	rii(n,p); rii(x,y);

	FOR(i,0,p){
		riii(a,b,c);
		g[a].pb({b,c});
		g[b].pb({a,c});
	}

	
	return 0;
}
