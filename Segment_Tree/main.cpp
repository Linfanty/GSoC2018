#include <iostream>
#include "Segment_Tree.h"

using namespace std;

int main()
{
    SegTree Stree;
    int n; // The number of nodes
    int ind, ans; // Change the value of node ind to ans
    int a, b; // Query interval

    cin >> n;
    Stree.Build(1, 1, n); // Create a segment tree
    // At this point you need to enter the value of each point

    int t; // T group to modify or query
    cin >> t;
    while( t-- )
    {
        string command;
        cin >> command;

        if( command == "Update") // Single point modification: st[ind] = ans
        {
            cin >> ind >> ans;
            Stree.Update(1, 1, n, ind, ans);
        }
        else if( command == "Add") // The ind node adds ans
        {
            cin >> ind >> ans;
            Stree.Add(1, 1, n, ind, ans);
        }
        else if( command == "Sub") // The ind node reduces ans
        {
            cin >> ind >> ans;
            Stree.Add(1, 1, n, ind, -ans);
        }
        else if( command == "QueryMax") // Query interval maximum value
        {
            cin >> a >> b;
            cout << Stree.QueryMax(1, 1, n, a, b) << endl;// Corresponds to a single point of change in the query
        }
        else if( command == "QueryMin") // Query interval Minimum value

        {
            cin >> a >> b;
            cout << Stree.QueryMin(1, 1, n, a, b) << endl;// Corresponds to a single point of change in the query
        }
        else if( command == "QuerySum") // Sum of query interval values
        {
            cin >> a >> b;
            cout << Stree.QuerySum(1, 1, n, a, b) << endl;// Corresponds to a single point of change in the query
        }
    }

    return 0;
}
