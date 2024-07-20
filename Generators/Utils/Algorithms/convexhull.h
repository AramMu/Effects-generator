#ifndef CONVEXHULL
#define CONVEXHULL
#include "DataStructures/graph.h"

std::vector<cv::Point> convexHull (const std::vector <cv::Point>& p);

std::pair<int,int> getLowerTangent (const std::vector<cv::Point>& p, int b, int e);
std::pair<int,int> getUpperTangent (const std::vector<cv::Point>& p, int b, int e);

#endif // CONVEXHULL
