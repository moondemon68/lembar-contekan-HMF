/**
* Description : find x such that ax = 1 mod m
*/
/* case 1 : when(gcd(a,m) = 1) */
/* use extended euclid : find x such that ax + my = 1 */
/* store x, y, and d as global variables */
/* d = gcd */
void extendedEuclid(int a, int b) {
  if (b == 0) { x = 1; y = 0; d = a; return; }
  /* base case */
  extendedEuclid(b, a % b);
  /* similar as the original gcd */
  int x1 = y;
  int y1 = x - (a / b) * y;
  x = x1;
  y = y1;
}
/* compute the first case inverse modulo*/
int firstInverseModulo(int a, int m){
  /* produces x and y, such that ax + my = 1 */
  /* return a^-1 mod m */
  extendedEuclid(a, m);
  return (x + m)%m;
}
/* case 2 : m is prime */
/* a^(m-1) = 1 mod m */
/* a^(m-2) = a^-1 mod m */
int power(int a,int b){
  int res = 1;
  while (b > 0){
    if (b%2 == 1)
      res *= a;
    b /= 2;
    a *= a;
  }
  return res;
}
int secondInverseModulo(int a,int m){
  return power(a, m-2);
}