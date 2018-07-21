int N;
vector<int> G[MAXN];

int A[MAXN], ST[4*MAXN], ST_N;
// ... SEGMENt TREE
int H[MAXN], sz[MAXN];
int anc[MAXN][MAXLOG]; //-1
int cN, cI[MAXN], cH[MAXN], posA[MAXN];
// ms(anc, -1);
// ms(cH, -1);
// cN = ST_N = 0
// pre_dfs(raiz);
// dfs_HLD(raiz);
// STB();
void dfs_HLD(int u){
	if(cH[cN] == -1) cH[cN] = u;
	cI[u] = cN;
	A[ST_N] = ...;
	posA[u] = ST_N++;
	int sc = -1;
	FOR(i, 0, G[u].size()){
		int v = G[u][i];
		if(v == anc[u][0]) continue;
	   	if(sc == -1 || sz[v] > sz[sc]){
			sc = v;
		}
	}
	if(sc == -1) return;
	dfs_HLD(sc);
	FOR(i,0,G[u].size()){
		int v = G[u][i];
		if(v == anc[u][0] || v == sc) continue;
		cN++;
		dfs_HLD(v);
	}
}
void pre_dfs(int u, int p = -1){
	anc[u][0] = p;
	if(p != -1) H[u] = H[p] + 1;
	else H[u] = 0;
	sz[u] = 1;
	FOR(i, 1, MAXLOG)
		if(anc[u][i-1] != -1)
			anc[u][i] = anc[anc[u][i-1]][i-1];
	FOR(i,0,G[u].size()){
		int v=G[u][i];
		if(p != v){
			pre_dfs(v,u);
			sz[u] += sz[v];
		}
	}
}
int LCA(int u,int v){
	if(H[v] < H[u]) swap(v,u);
	FORR(i,MAXLOG-1,-1)
		if(anc[v][i] != -1 && H[anc[v][i]] >= H[u])
			v = anc[v][i];
	if(v == u) return v;
	FORR(i,MAXLOG-1,-1)
		if(anc[v][i] != anc[u][i])
			v = anc[v][i], u = anc[u][i];
	return anc[v][0];
}
// u (el mas bajo), va subiendo hasta v
// en A los nodos mas altos van primero
tipoRet HLDQ(int u, int v){
	if(u==v) return STQ(posA[u], posA[u]+1);
	int uC, vC = cI[v];// neutro
	tipoRet ret = neutro;
	while(true){
		uC = cI[u];
		if(uC == vC){
			ret = merge(ret, STQ(posA[v], posA[u]+1)); // cuidado si es con arcos
			break;
		}
		ret = merge(ret, STQ(posA[cH[uC]], posA[u]+1));
		u = cH[uC];
		u = anc[u][0];
	}
	return ret;
}