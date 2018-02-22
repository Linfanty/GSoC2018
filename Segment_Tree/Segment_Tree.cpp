#include <iostream>
#include <algorithm>
#include "Segment_Tree.h"

SegTree :: SegTree(){
    a[MAXM+5] = {0};
    st_max[((MAXM)<<2)+5] = {0};
    st_min[((MAXM)<<2)+5] = {0};
    st_sum[((MAXM)<<2)+5] = {0};
    change[(MAXM<<2)+5] = {0};
}

SegTree :: SegTree(int n){
    a[n+5] = {0};
    st_max[((n)<<2)+5] = {0};
    st_min[((n)<<2)+5] = {0};
    st_sum[((n)<<2)+5] = {0};
    change[((n)<<2)+5] = {0};
}


void SegTree :: PushUp(int root) {
    st_max[root] = std::max(st_max[root<<1], st_max[(root<<1)|1]);
    st_min[root] = std::min(st_min[root<<1], st_min[(root<<1)|1]);
    st_sum[root] = st_sum[root<<1] +  st_sum[(root<<1)|1];
}


// Create a segment tree
void SegTree :: Build(int root, int l, int r){
    if(l == r) {
        std::cin >> a[l];
        st_max[root] = a[l];
        st_min[root] = a[l];
        st_sum[root] = a[l];
    }
    else{
        int m = l + ((r-l)>>1);
        Build(root<<1, l, m);
        Build((root<<1)|1 ,m+1, r);
        PushUp(root);
    }
}

// Single point modification: st[ind] = ans
void SegTree :: Update(int root, int l, int r, int ind, int ans){
    if(l == r){
        st_max[root] = st_min[root] = ans;
        st_sum[root] += ans;
        return;
    }
    int m = l + ((r - l)>>1);
    Update(root<<1, l, m, ind, ans);
    Update((root<<1)|1, m+1, r, ind, ans);
    PushUp(root);
}

// Single point modification: st[ind] += ans
void SegTree :: Add(int root, int l, int r, int ind, int ans) {
    if(ind < l || ind > r) return;
    if(l == r) {
        st_max[root] += ans;
        st_sum[root] += ans;
        return;
    }
    int m = l + ((r - l)>>1);
    Update(root<<1, l, m, ind, ans);
    Update((root<<1)|1, m+1, r, ind, ans);
    PushUp(root);
}

// Query interval maximum
int SegTree :: QueryMax(int root,int l,int r,int ql,int qr){
    if(ql > r || qr < l) return -1;
    if(ql <= l && qr >= r) return st_max[root];
    int m = l + ((r - l)>>1);
    int p1 = QueryMax(root<<1, l, m, ql, qr), p2 = QueryMax((root<<1)|1, m + 1, r, ql, qr);
    return std::max(p1, p2);
}

// Query interval Minimum value
int SegTree :: QueryMin(int root,int l,int r,int ql,int qr){
    if(ql > r || qr < l) return -1;
    if(ql <= l && qr >= r) return st_min[root];
    int m = l + ((r - l)>>1);
    int p1 = QueryMin(root<<1, l, m, ql, qr), p2 = QueryMin((root<<1)|1, m + 1, r, ql, qr);
    return std::min(p1, p2);
}

// Sum of query interval values
int SegTree :: QuerySum(int root,int l,int r,int ql,int qr){
    if(ql > r || qr < l) return -1;
    if(ql <= l && qr >= r) return st_sum[root];
    int m = l + ((r - l)>>1);
    int p1 = QuerySum(root<<1, l, m, ql, qr), p2 = QuerySum((root<<1)|1, m + 1, r, ql, qr);
    return p1 + p2;
}


void SegTree :: Add_PushDown(int root, int l, int r){
    if(add[root]){
        add[root<<1] += add[root];
        add[root<<1|1] += add[root];
        int m = l + ((r-l)>>1);
        st_sum[root<<1] += add[root] * (m - l + 1);
        st_sum[root<<1|1] += add[root] * (r - m);
        add[root] = 0;
    }
}

void SegTree :: Update_PushDown(int root, int l, int r){
    if(change[root]){
        int c = change[root];
        change[root<<1] = add[root];
        change[root<<1|1] = add[root];
        int m = l + ((r-l)>>1);
        st_sum[root<<1] = c * (m - l + 1);
        st_sum[root<<1|1] = c * (r - m);
        change[root] = 0;
    }
}

// Interval added value
void SegTree :: Add_Interval(int root, int l, int r, int ql, int qr, int addv){
    if(ql <= l && qr >= r){
        add[root] += addv;
        st_sum[root] += addv*(r - l + 1);
        return;
    }
    Add_PushDown(root, l, r);
    int m = l + ((r - l)>>1);
    if(ql <= m) Add_Interval(root<<1, l, m, ql, qr, addv);
    if(qr >= m+1) Add_Interval(root<<1|1, m + 1, r, ql, qr, addv);
    PushUp(root);
}

// Interval modification
void SegTree :: Update_Interval(int root, int l, int r, int ql, int qr, int addv){
    if(ql <= l && qr >= r){
        add[root] = addv;
        st_sum[root] = addv*(r - l + 1);
        return;
    }
    Update_PushDown(root, l, r);
    int m = l + ((r - l)>>1);
    if(ql <= m) Update_Interval(root<<1, l, m, ql, qr, addv);
    if(qr >= m+1) Update_Interval(root<<1|1, m + 1, r, ql, qr, addv);
    PushUp(root);
}


// Interval query
int SegTree :: Add_Query(int root, int l, int r, int ql, int qr){
    if(ql <= l && qr >= r) return st_sum[root];
    Add_PushDown(root, l, r);
    int m = l + ((r - l)>>1);
    int ans = 0;
    if(ql <= m) ans += Add_Query(root<<1, l, m, ql, qr);
    if(qr >= m + 1) ans += Add_Query(root<<1|1, m + 1, r, ql, qr);

    return ans;
}

// Interval query
int SegTree :: Update_Query(int root, int l, int r, int ql, int qr){
    if(ql <= l && qr >= r) return st_sum[root];
    Update_PushDown(root, l, r);
    int m = l + ((r - l)>>1);
    int ans = 0;
    if(ql <= m) ans += Update_Query(root<<1, l, m, ql, qr);
    if(qr >= m + 1) ans += Update_Query(root<<1|1, m + 1, r, ql, qr);

    return ans;
}
