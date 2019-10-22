ll minSpanningTree(vector<pll> a[]){

    ll mst = 0;

    priority_queue<pll, vector<pll>, greater<pll> > pq;

    // create a vector key and initialize all of it to inf
    vector<ll> key(n+2,inf);

    // to store a parent which in turn store MST (optional)
    vector<ll> parent(n+2,-1);

    // To keep track of vertices included in MST
    vector<bool> inMST(n+2,false);

    pq.push(mp(0,s));
    key[s] = 0;
    while(!pq.empty()){
        int u = pq.top().ss;
        pq.pop();

        // include vertex u to the MST
        inMST[u] = true;

        for(int j=0; j<a[u].size();j++){
            int v = a[u][j].ff;
            int weight = a[u][j].ss;

            // if v is not yet in MST and weight of (u,v) is smaller
            // than the current key of v
            if(inMST[v] == false && key[v] > weight){
                // update the key[v]
                key[v] = weight;
                pq.push(mp(key[v],v));
                parent[v] = u;
            }
        }
    }

    // print edges of MST using parent array
    for (int i=1;i<=n;i++){
        cout << i << " => " << parent[i] << " => " << key[i] << "\n";
        mst += key[i];
    }
    return mst;
}
