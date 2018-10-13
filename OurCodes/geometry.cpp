const double PI 2.0*acos(0.0)

//Definicion de punto con numeros complejos
typedef double T;
typedef complex<T> pt;
#define x real()
#define y imag()

//si usas abs con enteros, devuelve un entero

T sq(pt p){
    return p.x*p.x + p.y*p.y;
}

//Tranformaciones lineales
//Traslada un punto p por un vector v
pt translate(pt v, pt p) { return p+v; } 
//Escala un punto p por un factor factor alrededor de un centro c
pt scale(pt c, double factor, pt p) { return c + (p-c)*factor; }
//Rota un punto p por un angulo a alrededor del origen
pt rot(pt p, double a) { return p * polar(1.0,a); }
//Rota 90 grados
pt perp(pt p) { return {-p.y, p.x}; }
//Transformada lineal general
//Se tienen dos puntos p, q y su tranfo fp, fq y se calcula fr
pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq){
    return fp + (r-p) * (fq-fp) / (q-p);
}

//Productos
T dot(pt v, pt w) { return (conj(v)*w).x; }
T cross(pt v, pt w) { return (conj(v)*w).y; }

bool isPerp(pt v, pt w) { return dot(v,w) == 0; }
double angle(pt v, pt w){
    double cosT = dot(v,w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosT)));
}

//Orientacion: >0 antihorario, =0 colineales, <0 horario
T orient(pt a, pt b, pt c) { return cross(b-a,c-a); }
//Devuelve si x esta en el angulo interno BAC
bool inAngle(pt a, pt b, pt c, pt x){
    assert(orient(a,b,c) != 0);
    if(orient(a,b,c) < 0) swap(b,c);
    return orient(a,b,x) >= 0 && orient(a,c,x) <= 0;
}
//Devuelve el angulo orientado
double orientedAngle(pt a, pt b, pt c){
    if(orient(a,b,c) >= 0) return angle(b-a, c-a);
    else return 2*PI - angle(b-a, c-a);
}

//Devuelve si el poligono p es convexo
bool isConvex(vector<pt> p){
    bool pos = 0, neg = 0;
    for(int i = 0, n = p.size(); i<n; i++){
        int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
        if(o > 0) pos = 1;
        if(o < 0) neg = 1;
    }
    return !(pos && neg);
}

//Polar sort
bool half(pt p){
    assert(p.x != 0 || p.y != 0); //(0,0) no esta definifo
    return p.y > 0 || (p.y == 0 && p.x < 0);
}
//Ordena alrededor de un centro o y desempata los de 
//misma direccion por cercania a o

void polarSort(vector<pt> &v){ //o = (0,0)
    sort(v.begin(), v.end(), [](pt v, pt w) {
        return make_tuple(half(v), 0, sq(v)) < 
            make_tuple(half(w), cross(v,w), sq(w));
    });
}
void polarSort(pt o, vector<pt> &v){
    sort(v.begin(), v.end(), [](pt v, pt w) {
        return make_tuple(half(v-o), 0, sq(v-o)) < 
               make_tuple(half(w-o), cross(v-o,w-o), sq(w-o));
    });
}

