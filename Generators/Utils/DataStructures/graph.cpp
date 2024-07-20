#include "graph.h"
#include "Utils/calc.h"

Edge2::Edge2 () : u(0), v(0) {}
Edge2::Edge2 (int u, int v) : u(u), v(v) {}
bool Edge2::operator < (const Edge2& e) {
    return u < e.u || (u == e.u && v < e.v);
}


Edge2W::Edge2W () : u(0), w(0) {}
Edge2W::Edge2W (int u, double w) : u(u), w(w) {}
bool Edge2W::operator < (const Edge2W& e) {
    return w < e.w || (w == e.w && u < e.u);
}
bool Edge2W::CompareLessEdge2W::operator () (const Edge2W& e1, const Edge2W& e2) {
    return e1.w < e2.w;
}
bool Edge2W::CompareGreatEdge2W::operator () (const Edge2W& e1, const Edge2W& e2) {
    return e1.w > e2.w;
}



Edge3W::Edge3W () : u(0), v(0), w(0) {}
Edge3W::Edge3W (int u, int v, double w) : u(u), v(v), w(w) {}
bool Edge3W::operator < (const Edge3W& e) {
    return w < e.w || (w == e.w && (u < e.u || (u == e.u && v < e.v)));
}
bool Edge3W::CompareLessEdge3W::operator () (const Edge3W& e1, const Edge3W& e2) {
    return e1.w < e2.w;
}
bool Edge3W::CompareGreatEdge3W::operator () (const Edge3W& e1, const Edge3W& e2) {
    return e1.w > e2.w;
}
Edge3W::Comparator::Comparator () : isGreater(false) {}

Edge3W::Comparator::Comparator (bool isGreater) : isGreater(isGreater) {}
bool Edge3W::Comparator::operator () (const Edge3W& e1, const Edge3W& e2) {
    return (e1.w < e2.w) ^ isGreater;
}

Line::Line (const cv::Point& p1, const cv::Point& p2) : p1(p1), p2(p2) {}

PlanarGraph::PlanarGraph () {}
PlanarGraph::PlanarGraph (int n) :
    p(n),
    g(n) {}
PlanarGraph::PlanarGraph (const std::vector<cv::Point>& points):
    p(points),
    g(points.size()) {}

void PlanarGraph::_insert (int u, int v) {
    std::list<int>::iterator it = g[u].begin();
    while (it != g[u].end() && Calc::angle (p[u], p[*it]) < Calc::angle (p[u], p[v])) {
        it++;
    }
    g[u].insert (it, v);
}

void PlanarGraph::sortedInsert (int u, int v) {
    _insert(u,v);
    _insert(v,u);
}



