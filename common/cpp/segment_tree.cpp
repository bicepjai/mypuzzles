class SegmentTree
{
    ll *STree, *Lazy, size;

    public:
    SegmentTree(ll N) {
        ll x = (ll)(ceil(log2(N)))+1;
        size = 2*(ll)pow(2,x);
        STree = new ll[size];
        Lazy = new ll[size];
        memset(STree,-1,size * sizeof(ll));
        memset(Lazy,0,size * sizeof(ll));
    }
    void buildST(ll s, ll e, ll *array) {
        _buildST(1, s, e, array);
    }

    void printST() {
        for(int n=0; n<10; n++) {
            cout << STree[n] << " " << endl;
        }       
    }

    void updateST(ll node, ll s, ll e, ll i, ll j, ll value) {
        if(Lazy[node] != 0) { // This node needs to be updated
            STree[node] += Lazy[node]; // Update it
             
            if(s != e) {
            Lazy[node*2] += Lazy[node]; // Mark child as Lazy
            Lazy[node*2+1] += Lazy[node]; // Mark child as Lazy
            }
             
            Lazy[node] = 0; // Reset it
        }
        if(s > e || s > j || e < i) // Current segment is not within range [i, j]
            return;
        if(s >= i && e <= j) { // Segment is fully within range
            STree[node] += value;
             
            if(s != e) { // Not leaf node
                Lazy[node*2] += value;
                Lazy[node*2+1] += value;
            }
            return;
        }
         
        updateST(node*2, s, (s+e)/2, i, j, value); // Updating left child
        updateST(1+node*2, 1+(s+e)/2, e, i, j, value); // Updating right child
         
        STree[node] = max(STree[node*2], STree[node*2+1]); // Updating root with max value
    }
    
    private:
    void _buildST(ll node, ll s, ll e, ll *array) {
        if (s > e) return;

        if (s==e){
            STree[node] = array[s];
            return;
        }
        ll m = (s+e)/2;
        _buildST(2*node,s,m,array);
        _buildST(2*node+1,1+m,e,array);

        STree[node] = STree[2*node] + STree[2*node+1];
    }

    private:
    ll _queryST(ll node, ll s, ll e, ll i, ll j) {
        if(s > e || s > j || e < i) return LLONG_MIN; // Out of range
         
        if(Lazy[node] != 0) { // This node needs to be updated
         STree[node] += Lazy[node]; // Update it
             
         if(s != e) {
             Lazy[node*2] += Lazy[node]; // Mark child as Lazy
             Lazy[node*2+1] += Lazy[node]; // Mark child as Lazy
         }
             
         Lazy[node] = 0; // Reset it
        }
         
        if(s >= i && e <= j) // Current segment is totally within range [i, j]
            return STree[node];
        ll m = (s+e)/2;
        ll q1 = _queryST(node*2, s, m, i, j); // Query left child
        ll q2 = _queryST(1+node*2, 1+m, e, i, j); // Query right child

        if (q1==LLONG_MIN)
            return q2;
        if (q2==LLONG_MIN)
            return q1;

        ll res = q1 + q2; // Return final result
        return res; 
    } 

};
