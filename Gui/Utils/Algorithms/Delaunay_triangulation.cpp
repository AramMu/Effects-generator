#include "Delaunay_triangulation.h"
#include "Utils/utils.h"
//#include "DataStructures/graph.h"
//#include "Drawables/circle.h"
#include "convexhull.h"
#include "utils/Drawables/circle.h"

std::pair <int, int> getPotential (PlanarGraph& res, const std::pair<int,int>& cur) {
    /*
    std::list<int> p1 = res.g[cur.first];
    std::list<int> p2 = res.g[cur.second];
    double minAng = INF;
    int minInd;
    int k = 0;
    for (const int& ind: p1) {
        int ang = Calc::angle(res.p[cur.second], res.p[cur.first], res.p[ind]);
        if (ang < minAng) {
            minAng = ang;
            minInd = k;
        }
        k++;
    }
    k=0;
    for (const int& ind: p1) {
        if (k == minInd) {
            if ()
        }
        k++;
    }
    */
    return std::pair<int,int>();
}

void _Delaunay (PlanarGraph& res, int b, int e) {
    if (e-b <= 3) {
        for (int i = b; i < e; ++i) {
            for (int j = i+1; j < e; ++j) {
                res.sortedInsert(i, j);
            }
        }
        return;
    }
    int m = (b+e)/2;
    _Delaunay(res, b, m);
    _Delaunay(res, m, e);
    std::pair <int, int> lower = getLowerTangent (res.p, b, e);
    std::pair <int, int> upper = getUpperTangent (res.p, b, e);
    std::pair <int, int> cur = lower;
    while (cur != upper) {
        std::pair <int, int> pot = getPotential (res, cur);
        int index = -1;
        if (pot.first < 0) {
            index = 1;
        } else if (pot.second < 0) {
            index = 0;
        } else {
            if (Circle (res.p[cur.first], res.p[cur.second], res.p[pot.first]).contains(res.p[pot.second])) {
                index = 0;
            } else {
                index = 1;
            }
        }
        if (index == 0) {
            res.sortedInsert(cur.first, pot.first);
            cur = std::pair<int, int> (pot.first, cur.second);
        } else {
            res.sortedInsert(cur.second, pot.second);
            cur = std::pair<int, int> (cur.first, pot.second);
        }
    }
    return;
}

PlanarGraph Delaunay (const std::vector <cv::Point>& input) {
    std::vector <cv::Point> in = input;
    std::sort (in.begin(), in.end(), CvPointCompareXY());
    PlanarGraph res (input);
    _Delaunay (res, 0, input.size());
    return res;
}

