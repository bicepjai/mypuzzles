class FenwickTreeIndexed1
{
    ll *FTree, size;

    public:
    FenwickTreeIndexed1(ll N) {
        size = N+1;
        FTree = new ll[size];
        memset(FTree,0,size * sizeof(ll));
    }

    // add v to value at x
    void increment(ll i, ll v) {
        while(i < size) {
            FTree[i] += v;
            i += (i & -i);
        } 
    }

    // get cumulative sum up to and including x
    ll getCumSum(ll n) {
        ll sum = 0;
        while(n>0) {
            sum += FTree[n];
            n = n - (n & -n);
        } 
        return sum;
    }

    void print() {
        for(int i=1; i<size; i++) {
            cout << FTree[i] << "(" << getCumSum(i) << ") ";
        } cout << endl;
    }
};