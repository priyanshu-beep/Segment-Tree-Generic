#include <vector>


template<class T, class U>
class SegmentTree
{
public:

    // SegmentTree parametersised constructor
    // vecor data is 0 base indexed
    SegmentTree(std::vector<T> &data, T (*combine)(T &obj1, T &obj2));

    // query in the range l to r
    // 1 based indexing
    T query(int l, int r);

    // point update on position pos
    void update(int pos, U val);

    // range update on the range [beg, ind]
    void update(int beg, int ind, U val);

    // clear the segment tree
    void clear();

private:

    // strores segment tree size
    int segTreeSize;

    // stores the data of segment tree
    std::vector<T> st;

    // if(clazy[node] == false) no work is pending on node
    // if(clazy[node] == true) lazy update is to be done in future
    std::vector<bool> cLazy;

    // stores the lazy value
    std::vector<U> lazy;

    // a function combine that specifies how the result of left and right child of a node
    // should be used to generate the value of current node.
    T (*combine)(T &obj1, T &obj2);

    // query helper function
    T queryHelper(int node, int L, int R, int i, int j);

    // this fuction is to be handled appropriately for lazy updates
    void propagate(int node, int L, int R);

    // function to build the segment tree
    void buildTree(int node, int L, int R, std::vector<T> &data);

    // update helper function
    void updateHelper(int node, int L, int R, int i, int j, U val);
};

template<class T, class U>
SegmentTree<T, U>::SegmentTree(std::vector<T> &data, T (*combine)(T &obj1, T &obj2))
{
    this->combine = combine;
    segTreeSize = data.size();

    st.resize(4 * segTreeSize + 1);
    cLazy.assign(4 * segTreeSize + 1, false);
    lazy.resize(4 * segTreeSize + 1);
    buildTree(1, 1, segTreeSize, data);
}

template<class T, class U>
void SegmentTree<T, U>::clear()
{
    segTreeSize = 0;
    st.clear();
    cLazy.clear();
    lazy.clear();
}

template<class T, class U>
void SegmentTree<T, U>::buildTree(int node, int L, int R, std::vector<T> &data)
{
    if (L == R) {
        st[node] = data[L - 1];
        return;
    }
    int mid = (L + R) / 2;
    buildTree(node * 2, L, mid, data);
    buildTree(node * 2 + 1, mid + 1, R, data);
    st[node] = combine(st[node * 2], st[node * 2 + 1]);
}

// handle propgate appriopriately
template<class T, class U>
void SegmentTree<T, U>::propagate(int node, int L, int R)
{
    if (L != R)
    {
        cLazy[node * 2] = 1;
        cLazy[node * 2 + 1] = 1;
        lazy[node * 2] = lazy[node];
        lazy[node * 2 + 1] = lazy[node];
    }
    st[node] = lazy[node];
    lazy[node] = 0;
    cLazy[node] = 0;
}

template<class T, class U>
T SegmentTree<T, U>::queryHelper(int node, int L, int R, int i, int j)
{
    if (cLazy[node])
        propagate(node, L, R);

    if (j < L || i > R) return T();
    if (i <= L && R <= j) return st[node];

    int mid = (L + R) / 2;
    T left = queryHelper(node * 2, L, mid, i, j);
    T right = queryHelper(node * 2 + 1, mid + 1, R, i, j);
    return combine(left, right);
}

template<class T, class U>
void SegmentTree<T, U>::updateHelper(int node, int L, int R, int i, int j, U val)
{
    if (cLazy[node])
        propagate(node, L, R);
    if (j < L || i > R)
        return;
    if (i <= L && R <= j)
    {
        cLazy[node] = true;
        lazy[node] = val;
        propagate(node, L, R);
        return;
    }
    int mid = (L + R) / 2;
    updateHelper(node * 2, L, mid, i, j, val);
    updateHelper(node * 2 + 1, mid + 1, R, i, j, val);

    st[node] = combine(st[node * 2], st[node * 2 + 1]);
}

template<class T, class U>
T SegmentTree<T, U>::query(int l, int r)
{
    if (l > segTreeSize || r > segTreeSize || l < 1 || r < 1 || l > r)
        return T();

    return queryHelper(1, 1, segTreeSize, l, r);
}

template<class T, class U>
void SegmentTree<T, U>::update(int pos, U val)
{
    if (pos > segTreeSize || pos < 1)
        return;

    updateHelper(1, 1, segTreeSize, pos, pos, val);
}

template<class T, class U>
void SegmentTree<T, U>::update(int beg, int ind, U val)
{
    if (beg > segTreeSize || ind > segTreeSize || beg < 1 || ind < 1 || beg > ind)
        return;

    updateHelper(1, 1, segTreeSize, beg, ind, val);
}
