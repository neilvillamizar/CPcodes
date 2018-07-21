#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

#define pb push_back
#define ri(x) scanf("%d",&x)
#define rii(x,y) ri(x),ri(y)
#define ms(obj,val) memset(obj,val,sizeof(obj))
#define ms2(obj,val,sz) memset(obj,val,sizeof(obj[0])*sz)
#define FOR(i,f,t) for(int i=f;i<(int)t;i++)
#define FORR(i,f,t) for(int i=f;i>(int)t;i--)

typedef long long ll;
typedef vector<int> vi;

struct Point{
    ll x, y, v;
    int t;
    Point operator +(Point p){return {x+p.x, y+p.y};}
    Point operator -(Point p){return {x-p.x, y-p.y};}
    ll operator *(Point p){return x*p.y-y*p.x;}
    ll operator ^(Point p){return x*p.x+y*p.y;}
    bool operator ==(Point p){return x==p.x && y==p.y;}
    bool operator <(Point p){return y<p.y || (y==p.y && x<p.x);}
};
ll norma2(Point p){
    return p^p;
}
ll dist2(Point p, Point q){
    return norma2(p-q);
}

//***********ORDENAR POR ANGULO CON PIVOTE***********
Point pr;
struct comp{
	// Ordenar por angulo con respecto a pr
};
void initialize(){}
void init_in(){}
void add(vector<Point>&pt, int k, int i){}
void subtract(vector<Point>&pt, int k, int i){}
void update_answer(){}
void LS(vector<Point>& PT, Point P){
    pr=P;
    sort(PT.begin(), PT.end(), comp());
    vector<Point> pt(PT.begin()+1, PT.end());
    int N=pt.size();
    initialize();
    int i1=0, i2=0, j1=0, j2=0;
    while(i1<N && pr<pt[i1]){
        init_in();
        for(;i2<N && (pt[i1]-pr)*(pt[i2]-pr)==0 && pr<pt[i2]; i2++){
            add(pt, 1, i2);
            if(i2<j1) subtract(pt, 2, i2);
            else j1++;
        }
        for(;j1<N && (pt[i1]-pr)*(pt[j1%N]-pr)>0; j1++) add(pt, 2, j1);
        j2=j1;
        for(;j2<N && (pt[i1]-pr)*(pt[j2]-pr)==0; j2++) add(pt, 3, j2);
        update_answer();
        i1=i2;
    }
}
vector<Point> pt;
int N;
int main(){
    vector<Point>PT(pt.begin(), pt.end());
    FOR(i, 0, N) LS(PT, pt[i]);
}
