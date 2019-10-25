// random
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
/* usage: rng() */

// fast io
ios_base::sync_with_stdio(false);
cin.tie(NULL);
cout.tie(NULL);

// magic
#pragma GCC optimize ("O3")

// baca file
ifstream fin("input.txt")
ofstream fout("output.txt")

// fast scan number
void fastscan(int &number) { 
    //variable to indicate sign of input number 
    bool negative = false; 
    register int c; 
    number = 0; 
    c = getchar(); 
    if (c=='-') {  
        negative = true; 
        c = getchar(); 
    } 
    for (; (c>47 && c<58); c=getchar()) 
        number = number *10 + c - 48; 
    if (negative) 
        number *= -1; 
}
