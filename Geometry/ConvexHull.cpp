#include <bits/stdc++.h>
#define x first
#define y second
#define pb push_back
#define mp make_pair
#define pdd pair<double,double>
#define LL long long
#define INF 1e8

using namespace std;

pdd p[100115],c[100115],P0;

double triangleArea(pdd a,pdd b, pdd c) {
    return (a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y));
}

double sqDist(pdd a,pdd b) {
    return ((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

bool cmp(pdd a,pdd b) {
    double d=triangleArea(P0,a,b);
    if (d<0) return 0;
    return !(d==0&&sqDist(P0,a)>sqDist(P0,b));
} 

bool normal(pdd a,pdd b) {
    if (a.x==b.x) {
        return a.y<b.y;
    } else {
        return a.x<b.x;
    }
}

bool same(pdd a,pdd b) {
    return a.x==b.x && a.y==b.y;
}

void nosame(int &np) {
    sort (p,p+np,normal);
    np=unique(p,p+np,same)-p;
}

void convexhull(int &np, int &nc) {
    int pos=0,j;
    for (int i=1;i<np;i++) {
        if (p[i].y<p[pos].y || (p[i].y==p[pos].y && p[i].x<p[pos].x)) pos=i;
    }
    swap(p[0],p[pos]);
    P0 = p[0];
    sort(&p[1],&p[np],cmp);
    for (int i=0;i<3;i++) {
        c[i]=p[i];
    }
    for (int i=j=3;i<np;i++) {
        while (triangleArea(c[j-2],c[j-1],p[i])<0) j--;
        c[j++]=p[i];
    }
    nc=j;
}

int main () {
    int np,nc;
    cin >> np;
    for (int i=0;i<np;i++) cin >> p[i].x >> p[i].y;
    nosame(np);
    convexhull(np,nc);
    sort (c,c+nc,cmp);
    c[nc]=c[0];
    // c contains points that form the convex hull, sorted counterclockwise
    for (int i=0;i<nc;i++) cout << c[i].x << " " << c[i].y << endl;
    return 0;
}