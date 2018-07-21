#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

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

vi bordes(string &S){
    int n=S.size();
    vi T(n+1, -1);
    FOR(i, 1, n+1){
        int pos=T[i-1];
        while(pos!=-1 && S[i-1]!=S[pos]) pos=T[pos];
        T[i]=pos+1;
    }
    return T;
}
vi KMP(string &S, string &K){
    int n=S.size(), m=K.size();
    vi T=bordes(K), matches;
    int j=0;
    FOR(i, 0, n){
        while(j!=-1 && (j==m || S[i]!=K[j]))
            j=T[j];
        j++;
        if(j==m) matches.pb(i+1-m);
    }
    return matches;
}


int main(){

}
