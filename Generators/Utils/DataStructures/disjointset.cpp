#include "disjointset.h"
#include <cassert>

DisjointSet::DisjointSet() {}

DisjointSet::DisjointSet(int size) :
    mParent(size),
    mRank (size, 1)
{
    for (int i = 0; i < mParent.size(); ++i) {
        mParent[i] = i;
    }
}

bool DisjointSet::merge (int u, int v) {
    assert (u >= 0 && u < mParent.size() && v >= 0 && v < mParent.size());
    u = find(u);
    v = find(v);
    if (u == v) {
        return false;
    }
    if (mRank[u] < mRank[v]) {
        int t = u;
        u = v;
        v = t;
    }
    if (mRank[u] == mRank[v]) {
        ++mRank[u];
    }
    mParent[v] = u;
    mRank[v] = 0;
    return true;
}

int DisjointSet::find (int x) {
    if (x == mParent[x]) {
        return x;
    }
    return mParent[x] = find(mParent[x]);
}

std::vector <std::vector <int> > DisjointSet::getArray() {
    std::vector <std::vector <int> > res (mParent.size());
    for (int i = 0; i < mParent.size(); ++i) {
        res.at(find (i) ).push_back (i);
    }
    for (int i = 0; i < res.size(); ++i) {
        if (res[i].empty()) {
            res[i] = res.back();
            res.pop_back();
            i--;
        }
    }
    for (int i = 0; i < mRank.size(); ++i) {
        mRank[i] = (i == mParent[i] ? 1 : 0);
    }
    return res;
}
