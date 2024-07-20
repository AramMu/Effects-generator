#include "convexhull.h"
//#include <stack>
#include "Utils/calc.h"

std::vector<cv::Point> convexHull (const std::vector <cv::Point>& p) {
    //assert (!p.empty());
    if (p.size() <= 2) return p;
    std::vector <cv::Point> res;
    std::vector <cv::Point> st;
    st.push_back(p[0]);
    for (int i = 1; i < p.size(); ++i) {
        while (st.size() >= 2 &&
               Calc::crossProduct(st[st.size()-2], st[st.size()-1], p[i]) <= 0)
        {
            st.pop_back();
        }
        st.push_back(p[i]);
    }
    st.pop_back();
    res = st;

    st.clear();
    st.push_back(p.back());
    for (int i = p.size()-2; i >= 0; --i) {
        while (st.size() >= 2 &&
               Calc::crossProduct(st[st.size()-2], st[st.size()-1], p[i]) <= 0)
        {
            st.pop_back();
        }
        st.push_back(p[i]);
    }
    st.pop_back();
    int oldSize = res.size();
    res.resize(res.size()+st.size());
    for (int i = 0; i < st.size(); ++i) {
        res[oldSize+i] = st[i];
    }
    //std::reverse(res.begin(), res.end());
    return res;
}

void constructDividedHulls (const std::vector<cv::Point>& input, int b, int e,
                            std::vector<cv::Point>& h1, std::vector<cv::Point>& h2)
{
    int m = (e+b)/2;
    std::vector<cv::Point> p1(m-b), p2(e-m);
    for (int i = b; i < m; ++i) {
        p1[i-b] = input[i];
    }
    for (int i = m; i < e; ++i) {
        p2[i-m] = input[i];
    }
    h1 = convexHull(p1);
    h2 = convexHull(p2);
}

int getRightMost (const std::vector<cv::Point>& p) {
    assert (!p.empty());
    int res = 0;
    for (int i = 1; i < p.size(); ++i) {
        if (p[i].x > p[res].x || (p[i].x == p[res].x && p[i].y > p[res].y)) {
            res = i;
        }
    }
    return res;
}
int getLeftMost (const std::vector<cv::Point>& p) {
    assert (!p.empty());
    int res = 0;
    for (int i = 1; i < p.size(); ++i) {
        if (p[i].x < p[res].x || (p[i].x == p[res].x && p[i].y < p[res].y)) {
            res = i;
        }
    }
    return res;
}
int findPointPos (const std::vector<cv::Point>& arr, int b, int e, const cv::Point& p) {
    for (int i = b; i < e; ++i) {
        if (arr[i] == p) {
            return i;
        }
    }
    return -1;
}


std::pair<int,int> getLowerTangent (const std::vector<cv::Point>& p, int b, int e) {
    std::vector<cv::Point> hL, hR;
    constructDividedHulls (p, b, e, hL, hR);
    int indL = getRightMost (hL);
    int indR = getLeftMost (hR);

    int nL = hL.size();
    int nR = hR.size();
    assert (hL.size() >= 2);
    assert (hR.size() >= 2);
    while (true) {
        if (Calc::crossProduct(hL[(indL-1+nL)%nL], hL[indL], hR[indR]) < 0) {
            indL = (indL-1+nL)%nL;
            continue;
        }
        if (Calc::crossProduct(hR[(indR+1)%nR], hR[indR], hL[indL]) > 0) {
            indR = (indR+1)%nR;
            continue;
        }
        break;
    }
    indL = findPointPos (p, b, e, hL[indL]);
    indR = findPointPos (p, b, e, hR[indR]);
    assert (indL >= 0);
    assert (indR >= 0);
    return std::pair<int,int>(indL, indR);
}

std::pair<int,int> getUpperTangent (const std::vector<cv::Point>& p, int b, int e) {
    std::vector<cv::Point> hL, hR;
    constructDividedHulls (p, b, e, hL, hR);
    int indL = getRightMost (hL);
    int indR = getLeftMost (hR);

    int nL = hL.size();
    int nR = hR.size();
    assert (hL.size() >= 2);
    assert (hR.size() >= 2);
    while (true) {
        if (Calc::crossProduct(hL[(indL+1)%nL], hL[indL], hR[indR]) > 0) {
            indL = (indL+1)%nL;
            continue;
        }
        if (Calc::crossProduct(hR[(indR-1+nR)%nR], hR[indR], hL[indL]) < 0) {
            indR = (indR-1+nR)%nR;
            continue;
        }
        break;
    }
    indL = findPointPos (p, b, e, hL[indL]);
    indR = findPointPos (p, b, e, hR[indR]);
    assert (indL >= 0);
    assert (indR >= 0);
    return std::pair<int,int>(indL, indR);
}






