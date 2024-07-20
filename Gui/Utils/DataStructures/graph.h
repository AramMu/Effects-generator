#ifndef GRAPH
#define GRAPH
//#include <opencv2/imgproc.hpp>
#include <opencv2/core/types.hpp>
#include <list>

struct Edge2 {
    int u;
    int v;
    Edge2 ();
    Edge2 (int u, int v);
    bool operator < (const Edge2& e);
};
struct Edge2W {
    int u;
    double w;
    Edge2W ();
    Edge2W (int u, double w);
    bool operator < (const Edge2W& e);
    struct CompareLessEdge2W {
        bool operator () (const Edge2W& e1, const Edge2W& e2);
    };
    struct CompareGreatEdge2W {
        bool operator () (const Edge2W& e1, const Edge2W& e2);
    };
};

struct Edge3W {
    int u;
    int v;
    double w;
    Edge3W ();
    Edge3W (int u, int v, double w);
    bool operator < (const Edge3W& e);
    struct CompareLessEdge3W {
        bool operator () (const Edge3W& e1, const Edge3W& e2);
    };
    struct CompareGreatEdge3W {
        bool operator () (const Edge3W& e1, const Edge3W& e2);
    };
    class Comparator {

    public:
        Comparator ();
        Comparator (bool isGreater);
        bool operator () (const Edge3W& e1, const Edge3W& e2);
    private:
        bool isGreater;
    };
};


struct Line {
    cv::Point2i p1;
    cv::Point2i p2;
    Line (const cv::Point& p1, const cv::Point& p2);
};
typedef std::vector <std::vector <int> > Graph;
typedef std::vector <Edge2> EdgeList;
typedef std::vector <std::vector <Edge2W> > GraphW;
typedef std::vector <Edge3W> EdgeListW;


class PlanarGraph {
public:
    PlanarGraph ();
    PlanarGraph (int n);
    PlanarGraph (const std::vector<cv::Point>& points);

    void sortedInsert (int u, int v);

    std::vector <cv::Point> p;
    std::vector <std::list<int> > g;
private:
    void _insert (int u, int v);
};

#endif // GRAPH

