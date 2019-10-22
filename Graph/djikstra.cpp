void Djikstra(vector<pii> a[]){
    priority_queue<pii, vector<pii>, greater<pii> > pq;

    vector<int> dist(n+2,inf);
    dist[s] = 0;
    pq.push(mp(dist[s],s));
    while(!pq.empty()){
        int u = pq.top().ss;
        pq.pop();

        for(int j=0; j<a[u].size(); j++){
            int v = a[u][j].ff;
            int weight = a[u][j].ss;
            if(dist[v] > dist[u]+weight){
                //cout << v << " => " << dist[u]+weight << "\n";
                dist[v] = dist[u]+weight;
                pq.push(mp(dist[v],v));
            }
        }
    }

    for(int i=1;i<=n;i++){
        cout << i << " => " << dist[i] << "\n";
        // if dist[i] is still inf, then it is not connected to s
    }

}
