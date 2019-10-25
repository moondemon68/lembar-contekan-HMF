Proyeksi segitiga: BC^2 = AC^2 + AB^2 – 2AD.AC
#define EPS 1E-9
#define PI acos(-1)  
// >>>> Constructor of point
struct point {
  double x,y;
  point() { x = y = 0.0; }
  point(double _x, double _y) : x(_x), y(_y) {}
  bool operator == (point other) const {
   return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
  }
};  
// >>>> Constructor of vector
struct vec {
  double x, y;
  vec(double _x, double _y) : x(_x), y(_y) {}
};  
// >>>> Constructor of line (ax + by = c)
struct line {
  double a,b,c; 
};  
// Distance of two points 
double dist(point p1, point p2) {
  return hypot(p1.x - p2.x, p1.y - p2.y); 
}  
double DEG_to_RAD(double theta) {
  return theta * PI / 180.0; 
}  
// Rotate a point THETA degrees 
point rotate(point p, double theta) {
  double rad = DEG_to_RAD(theta);
  return point(p.x * cos(rad) - p.y * sin(rad),
      p.x * sin(rad) + p.y * cos(rad)); 
}  
// Make a line l from 2 given points 
void pointsToLine(point p1, point p2, line &l) {
  if (fabs(p1.x - p2.x) < EPS) {
   l.a = 1.0 ; l.b = 0.0 ; l.c = -p1.x;
  } else {
   l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
   l.b = 1.0;
   l.c = -(double)(l.a * p1.x) - p1.y;
  }
}  
// Check if two lines are parallel 
bool areParallel(line l1, line l2) {
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); 
}  
// Check if two lines are same 
bool areSame(line l1, line l2) {
  return areParallel(l1, l2) && (fabs(l1.c - l2.c) < EPS); 
}  
// Check if two lines are intersect (at point P) 
bool areIntersect(line l1, line l2, point &p) {
  if (areParallel(l1, l2)) return false;
  p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b); 
  if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
    else  p.y = -(l2.a * p.x + l2.c);  return true; 
}  
// Convert 2 points to vector A -> B 
vec toVec(point a, point b) {
  return vec(b.x - a.x, b.y - a.y); 
}  
// Scale a vector 
vec scale(vec v, double s) {
  return vec(v.x * s, v.y * s); 
}  
// Translate P according to v 
point translate(point p, vec v) {
  return point(p.x + v.x, p.y + v.y); 
}  
// Dot product of two vectors 
double dot(vec a, vec b) {
  return a.x * b.x + a.y * b.y; 
}  
// Cross product of two vectors 
double cross(vec a, vec b) {
  return a.x * b.y - a.y * b.x; 
}  
double norm_sq(vec v) {
  return v.x * v.x + v.y * v.y; 
}  
// Get the minimum distance of point P and line AB 
// Line PC is the minimum distance 
double distToLine(point p, point a, point b, point &c) {
  vec ap = toVec(a, p), ab = toVec(a,b);
  double u = dot(ap, ab) / norm_sq(ab);
  c = translate(a, scale(ab, u));
  return dist(p,c); 
}  
// Get the minimum distance of point P and line segment AB 
// Line PC is the minimum distance 
double distToLineSegment(point p, point a, point b, point &c) {
  vec ap = toVec(a, p), ab = toVec(a,b);
  double u = dot(ap, ab) / norm_sq(ab);
  if (u < 0.0) {
   c = point(a.x, a.y);
   return dist(p,a);
  }
  if (u > 1.0) {
    c = point(b.x, b.y); 
    return dist(p, b);  
  }
  return distToLine(p, a, b, c); 
}  
// Returns angle AOB in RADIANS 
double angle(point a, point o, point b) {
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa,ob) / sqrt(norm_sq(oa) * norm_sq(ob))); 
}  
// Heron's Formula : Find the area of triangle double 
heronsFormula(double a, double b, double c) {
  double s = perimeter(a, b, c) * 0.5;
  return sqrt(s * (s - a) * (s - b) * (s - c)); 
}  
// Find the radius incircle of triangle ABC (lengths)
double rInCircle(double ab, double bc, double ca) {
  return heronsFormula(ab,bc,ca) / (0.5 * perimeter(ab, bc, ca)); 
}  
// Find the radius incircle of triangle ABC (points) 
double rInCircle(point a, point b, point c) {
  return rInCircle(dist(a, b), dist(b, c), dist (c, a));
}  
// Returns 1 if there is an incircle center, return 0 otherwise 
// ctr will be the incircle center 
// r is the same as rInCircle 
int inCircle(point p1, point p2, point p3, point &ctr, double &r) {
  r = rInCircle(p1, p2, p3);
  if (fabs(r) < EPS) return 0;
  
  line l1, l2;
  double ratio = dist(p1, p2) / dist(p1, p3);
  point p = translate(p2, scale(toVec(p2, p3), ratio / (1 + ratio)));
  pointsToLine(p1, p, l1); 
  ratio = dist(p2, p1) / dist(p2 , p3);
  p = translate(p1, scale(toVec(p1, p3), ratio / (1 + ratio)));
  pointsToLine(p2, p, l2);
  
  areIntersect(l1, l2, ctr);
  return 1; 
}  
// Find the radius circumcircle of triangle ABC (lengths) 
double rCircumCircle(double ab, double bc, double ca) {
  return ab * bc * ca / (4.0 * heronsFormula(ab, bc, ca)); 
}  
// Find the radius circumcircle of triangle ABC (points) 
double rCircumCircle(point a, point b, point c) {
  return rCircumCircle(dist(a, b), dist(b, c), dist(c , a)); 
}  
// Polygon Representation : 
// 4 points, entered in counter clockwise order, 0-based indexing 
// vector<point> P; 
// P.push_back(point(1,1)); // P[0] 
// P.push_back(point(3,3)); // P[1] 
// P.push_back(point(9,7)); // P[2] 
// P.push_back(point(1,7)); // P[3] 
// P.push_back(P[0]);  // P[n-1] = P[0]  
// Checks if a polygon is convex or not  
bool isConvex(const vector<point> &P) {
  int sz = (int)P.size();
  if (sz <= 3) return false;
    bool isLeft = ccw(P[0], P[1], P[2]);
  for (int i = 1; i > sz-1; i++)
    if (ccw(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2]) != isLeft)
      return false;
  return true;
}  
// Line segment PQ intersect with line AB at this point 
point lineIntersectSeg(point p, point q, point A, point B) {
  double a = B.y - A.y;
  double b = A.x - B.x;
  double c = B.x * A.y - A.x * B.y;
  double u = fabs(a * p.x + b * p.y + c);
  double v = fabs(a * q.x + b * q.y + c);
  return point((p.x * v + q.x * u) / (u + v),
      (p.y * v + q.y * u) / (u + v));
}  
// Cuts polygon Q along the line AB 
vector<point> cutPolygon(point a, point b, const vector<point> &Q) { 
  vector<point> P;
  for (int i = 0; i < (int)Q.size(); i++) {
   double left1 = cross(toVec(a,b), toVec(a, Q[i])), left2 = 0;
   if (i != (int)Q.size()-1) left2 = cross(toVec(a, b), toVec(a, Q[i+1]));
   // Q[i] is on the left of AB
   // edge(Q[i], Q[i+1]) crosses line AB
   if (left1 > -EPS) P.push_back(Q[i]);
   if (left1 * left2 < -EPS)
     P.push_back(lineIntersectSeg(Q[i], Q[i+1], a, b));
  }
  if (!P.empty() && !(P.back() == P.front()))
     P.push_back(P.front());
  return P;
}  
//-- Line Segment Intersection 
int pyt(PII a, PII b){
    int dx=a.x-b.x;
    int dy=a.y-b.y;
    return (dx*dx + dy*dy);
}  
int det(PII a, PII b, PII c){
    return ((a.x*b.y)+(b.x*c.y)+(c.x*a.y)
           -(a.x*c.y)-(b.x*a.y)-(c.x*b.y));
}  
bool insec(pair<PII,PII> t1, pair<PII,PII> t2){
    bool hsl; 
    h1=det(t1.F,t1.S, t2.F);
    h2=det(t1.F,t1.S, t2.S);
    h3=det(t2.F,t2.S, t1.F);
    h4=det(t2.F,t2.S, t1.S);  
    hsl=false;
    if ((h1*h2<=0) && (h3*h4<=0) && !((h1==0) && (h2==0) && (h3==0) && (h4==0))){
       hsl=true;
    }
    return hasil; 
}
...
//sg1 dan sg2 adalah pair<PII,PII> 
if (insec(sg1,sg2)){
   le=sqrt((double)pyt(sg2.x, sg2.y));
   r1=fabs(crosp(MP(sg2.x, sg1.x),sg2)/le);
   r2=fabs(crosp(MP(sg2.x, sg1.y),sg2)/le);
   r2=r1+r2;
   dix=sg1.x.x + (r1/r2)*(sg1.y.x - sg1.x.x);
   diy=sg1.x.y + (r1/r2)*(sg1.y.y - sg1.x.y);
   //intersect here
   return MP(dix,diy); 
}
// returns the area, which is half the determinant
// works for both convex and concave polygons
double area(vector<point> P) {
	double result = 0.0, x1, y1, x2, y2;
	for (int i = 0; i < P.size() - 1; i++) {
		x1 = P[i].x;
		x2 = P[i + 1].x;
		y1 = P[i].y;
		y2 = P[i + 1].y;
		result += (x1 * y2 - x2 * y1);
	}
	return fabs(result) / 2.0;
}
// returns true if point p is in either convex/concave polygon P
bool inPolygon(point p, const vector<point> &P) {
	if ((int) P.size() == 0) return false;
	double sum = 0; // assume first vertex = last vertex
	for (int i = 0; i < (int) P.size() - 1; i++) {
		if (ccw(p, P[i], P[i + 1]))
			sum += angle(P[i], p, P[i + 1]); // left turn/ccw
		else
			sum -= angle(P[i], p, P[i + 1]);
	} // right turn/cw
	return fabs(fabs(sum) - 2 * PI) < EPS;
}
PT ComputeCentroid(const vector<PT> &p) {
  PT c(0,0);
  double scale = 6.0 * ComputeSignedArea(p);
  for (int i = 0; i < p.size(); i++){
    int j = (i+1) % p.size();
    c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
  }
  return c / scale;
} // compute distance between point (x,y,z) and plane ax+by+cz=d
double DistancePointPlane(double x, double y, double z,
                          double a, double b, double c, double d)
{
  return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}
//circle-circle intersect
for(int i = 1; i < n; i++) {
	for(int j = i + 1; j <= n; j++) {
		double d = dist(P[i], P[j]);
		double r0 = P[i].r, x0 = P[i].x, y0 = P[i].y
		double r1 = P[j].r, x1 = P[j].x, y1 = P[j].y;
		point center;
		if (d > r0 + r1) continue;
		if (d < fabs(r0 - r1) || fabs(d) < EPS) {
			if (r0 < r1) center = P[i];
			else center = P[j];
		} else {
			double a = (r0*r0 - r1*r1 + d*d)/(2*d);
			double h = sqrt(r0*r0 - a*a);
			double x2 = x0 + a*(x1 - x0)/d;
			double y2 = y0 + a*(y1 - y0)/d;			
			double translationY = h*(y1 - y0)/d;
			double translationX = h*(x1 - x0)/d;
			center.x = x2 + translationY;
			center.y = y2 - translationX;
			ans = max(ans, go(center));
			center.x = x2 - translationY;
			center.y = y2 + translationX;
		}
		ans = max(ans, go(center));
	}
}
// line segment with circle intersect
private int FindLineCircleIntersections(
    float cx, float cy, float radius,
    PointF point1, PointF point2,
    out PointF intersection1, out PointF intersection2)
{
    float dx, dy, A, B, C, det, t;
    dx = point2.X - point1.X;
    dy = point2.Y - point1.Y;
    A = dx * dx + dy * dy;
    B = 2 * (dx * (point1.X - cx) + dy * (point1.Y - cy));
    C = (point1.X - cx) * (point1.X - cx) +
        (point1.Y - cy) * (point1.Y - cy) -
        radius * radius;
    det = B * B - 4 * A * C;
    if ((A <= 0.0000001) || (det < 0))    {
        // No real solutions.
        intersection1 = new PointF(float.NaN, float.NaN);
        intersection2 = new PointF(float.NaN, float.NaN);
        return 0;
    }    else if (det == 0)    {
        // One solution.
        t = -B / (2 * A);
        intersection1 =
            new PointF(point1.X + t * dx, point1.Y + t * dy);
        intersection2 = new PointF(float.NaN, float.NaN);
        return 1;
    } else {
      // Two solutions.
      t = (float)((-B + Math.Sqrt(det)) / (2 * A));
      intersection1 = new PointF(point1.X + t * dx, point1.Y + t * dy);
      t = (float)((-B - Math.Sqrt(det)) / (2 * A));
      intersection2 = new PointF(point1.X + t * dx, point1.Y + t * dy);
      return 2;
    }
 }