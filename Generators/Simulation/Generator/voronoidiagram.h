#ifndef VORONOIDIAGRAM_H
#define VORONOIDIAGRAM_H
#include "abstract_simulation.h"
#include "utils/matrix.h"



/* rate: 25
 * func: 19
 * speed: 61
 * total: 55
*/
class VoronoiDiagram : public AbstractSimulation{
public:
    enum DistanceMode {
        eEuclid, eCity, eChess
    };

    explicit VoronoiDiagram(const cv::Size& size);

    cv::Mat getNextFrame ();
    bool hasNextFrame();
    void restart();
    void resetToDefault();

    void setDistanceMode (DistanceMode mode);
    void setEmptyColor (cv::Vec3b color);
    void setPointColor (cv::Vec3b color);
    void setLineColor (cv::Vec3b color);
    void setPointCount (int count);

    DistanceMode defDistanceMode () const;
    cv::Vec3b defEmptyColor () const;
    cv::Vec3b defPointColor () const;
    cv::Vec3b defLineColor () const;
    int defPointCount () const;
private:
    void setDefault();
    void start();
    bool isEdge (const cv::Point& p);
    int getDistance (const cv::Point& p1, const cv::Point& p2);

    Matrix<int> mMat;

    DistanceMode mDistanceMode;

    cv::Vec3b mEmptyColor;
    cv::Vec3b mLineColor;
    cv::Vec3b mPointColor;

    bool mConsumed;
    int mPointCount;

    std::vector <cv::Point> mPoints;
};

#endif // VORONOIDIAGRAM_H
