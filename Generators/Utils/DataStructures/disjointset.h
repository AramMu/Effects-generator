#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>

class DisjointSet {
public:
    DisjointSet();
    DisjointSet(int size);

    bool merge (int u, int v);
    int find (int x);
    std::vector <std::vector <int> > getArray();
private:
    std::vector <int> mParent;
    std::vector <int> mRank;
};

#endif // DISJOINTSET_H
