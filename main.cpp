#include <iostream>
#include "graph.h"

using namespace std;

int main() {
graph G;

    for (int i = 0; i < 9; ++i) {
        G.AddV( 100 - i);
        G.AddV( 50 - i);
        G.AddArc(100 - i, 50 - i);
        G.AddArc(50 - i, 100 - i);
        G.AddArc(100 - i, 100 - i);
        G.AddArc(50 - i, 50 - i);
    }

 //   G.PrintGraph();

    for (int i = 0; i < 9; ++i) {
        G.SubV( 100 - (i % 2));
        G.SubV( 50 - i);
    }

 //   G.PrintGraph();

    for (int i = 0; i < 9; ++i) {
        G.SubArc(100 - i, 100 - i);
    }

 //   G.PrintGraph();

    for (int i = 0; i < 9; ++i) {
        G.AddArc(92 + i, 98 - i);
    }

  //  G.PrintGraph();

    G.SubArc(95, 95);

  //  G.PrintGraph();

    cout <<G.SearchVer(95)<< endl;
    cout <<G.SearchArc(95, 95) << endl;
    cout << G.SearchVer(99) << endl;
    cout << G.SearchVer(92) << endl;
    cout << G.SearchArc(98, 98) << endl;
    cout << G.SearchArc(98, 92) << endl;
    cout << G.SearchArc(92, 98) << endl;

    G.SubV(98);
//    G.SubV( 96);
    G.SubV(97);

    for (int i = 0; i < 5; ++i) {
        G.AddArc(96 - i, 95 - i);
        G.AddArc(96 - i, 96 - i);
    }
    G.SubArc(94, 96);
    G.SubArc(96, 94);
    G.AddArc(96, 92);

    G.AddArc(92, 96);
    G.PrintGraph();

    G.Traversing();
    G.Algoritgm();

/*    for(int i=1; i<11; i++)
        G.AddV(i);*/
 //   G.PrintGraph();

/*    G.AddArc(1, 2);
    G.AddArc(2, 1);
    G.AddArc(2, 3);
    G.AddArc(3, 3);
    G.AddArc(3, 4);
    G.AddArc(4, 1);
    G.AddArc(4, 5);
    G.AddArc(6, 7);
    G.AddArc(7, 6);
    G.AddArc(8, 8);
    G.AddArc(8, 9);
    G.PrintGraph();*/

    G.Traversing();
    G.Algoritgm();

    G.SubArc(92,96);
    for (int i=1;i<5;i++)
        G.AddV(i);

    for (int i=1;i<5;i++)
        for (int j=i+1;j<5;j++)
            G.AddArc(i,j);

    G.AddArc(4,2);
    G.PrintGraph();
    G.Traversing();
    G.Algoritgm();
    return 0;
}
