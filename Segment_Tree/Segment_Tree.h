#ifndef SEGMENT_Tree_H_
#define SEGMENT_Tree_H_

class SegTree
{
private:
    const static int MAXM = 10000;
    int a[MAXM+5];
    int st_max[(MAXM<<2)+5];
    int st_min[(MAXM<<2)+5];
    int st_sum[(MAXM<<2)+5];
    int add[(MAXM<<2)+5];
    int change[(MAXM<<2)+5];
public:
    SegTree();
    SegTree(int n);
    void PushUp(int root);

    void Build(int root, int l, int r); // Create a segment tree
    void Update(int root, int l, int r, int ind, int ans);// Single point modification: st[ind] = ans
    void Add(int root, int l, int r, int ind, int ans); // Single point modification: st[ind] += ans
    int QueryMax(int root, int l, int r, int ind, int ans); // Query interval maximum
    int QueryMin(int root, int l, int r, int ind, int ans); // Query interval Minimum value
    int QuerySum(int root, int l, int r, int ind, int ans); // Sum of query interval values

    void Add_PushDown(int root, int l, int r);
    void Update_PushDown(int root, int l, int r);
    void Add_Interval(int root, int l, int r, int ql, int qr, int addv); // Interval added value
    void Update_Interval(int root, int l, int r, int ql, int qr, int addv); // Interval modification
    int Add_Query(int root, int l, int r, int ql, int qr); // Interval query
    int Update_Query(int root, int l, int r, int ql, int qr); // Interval query
};


#endif // SEGMENT_Tree_H_
