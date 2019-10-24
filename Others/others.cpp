// random
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
/* usage: rng() */

// fast io
ios_base::sync_with_stdio(false);
cin.tie(NULL);
cout.tie(NULL);

// magic
#pragma GCC optimize ("O3")