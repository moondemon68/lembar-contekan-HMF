bool pointInsidePolygon(pdd p, pdd c[], int nc) {
    // p point, c polygon points, nc number of polygon points
    pdd center = mp(0,0);
    for (int i=0;i<nc;i++) {
        center = mp(center.x+c[i].x, center.y+c[i].y);
    }
    center = mp(center.x*(1.0/nc), center.y*(1.0/nc));
    bool isInside = 1;
    for (int i=0;i<nc;i++) {
        pdd u;
        u=mp(c[i+1].x-c[i].x,c[i+1].y-c[i].y);
        pdd v1 = mp(center.x-c[i].x, center.y-c[i].y);
        pdd v2 = mp(p.x-c[i].x, p.y-c[i].y);
        if (u.x*v2.y-u.y*v2.x==0) {
            isInside = 1;
            break;
        }
        if ((u.x*v1.y-u.y*v1.x) * (u.x*v2.y-u.y*v2.x)<0) {
            isInside = 0;
            break;
        }
    }
    return isInside;
}