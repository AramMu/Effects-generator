#ifndef COLORMIXERIMPL
#define COLORMIXERIMPL
#include "colormixer.h"
#include <cassert>

class FlameColorMixer : public ColorMixer {
public:
    cv::Vec3b mix (cv::Vec3b c1, cv::Vec3b c2) const {
        uchar magn1 = std::max (std::max(c1[0], c1[1]), c1[2]);
        uchar magn2 = std::max (std::max(c2[0], c2[1]), c2[2]);
        if (magn1 == 0 || magn2 == 0) {
            return cv::Vec3b(0,0,0);
        }
        int power1 = 255-magn1;
        int power2 = 255-magn2;
        int sum = power1 + power2;
        cv::Vec3d res;
        if (sum == 0) {
            res = c1 + c2;
        } else {
            for (int i = 0; i < 3; ++i) {
                res[i] = (c1[i]*1.0/magn1 * power1/sum) + (c2[i]*1.0/magn2 * power2/sum);
            }
        }
        double magnRes = std::max (std::max(res[0], res[1]), res[2]);
        assert (magnRes > 0);
        cv::Vec3b ret;
        uchar minMagn = std::min (magn1, magn2);
        for (int i = 0; i < 3; ++i) {
            ret[i] = res[i] / magnRes * minMagn;
        }
        return ret;
    }
};


class FlameColorInvMixer : public ColorMixer {
public:
    cv::Vec3b mix (cv::Vec3b c1, cv::Vec3b c2) const {
        uchar magn1 = std::max (std::max(c1[0], c1[1]), c1[2]);
        uchar magn2 = std::max (std::max(c2[0], c2[1]), c2[2]);
        if (magn1 == 0) {
            return c2;
        }
        if (magn2 == 0) {
            return c1;
        }
        int power1 = magn1;
        int power2 = magn2;
        int sum = power1 + power2;
        cv::Vec3d res;
        if (sum == 0) {
            res = c1 + c2;
        } else {
            for (int i = 0; i < 3; ++i) {
                res[i] = (c1[i]*1.0/magn1 * power1/sum) + (c2[i]*1.0/magn2 * power2/sum);
            }
        }
        double magnRes = std::max (std::max(res[0], res[1]), res[2]);
        assert (magnRes > 0);
        cv::Vec3b ret;
        uchar maxMagn = std::max (magn1, magn2);
        for (int i = 0; i < 3; ++i) {
            ret[i] = res[i] / magnRes * maxMagn;
        }
        return ret;
    }
};


class LayeredColorMixer : public ColorMixer {
public:
    cv::Vec3b mix(cv::Vec3b, cv::Vec3b c2) const {
        return c2;
    }
};

class MaximumColorMixer : public ColorMixer {
public:
    cv::Vec3b mix(cv::Vec3b c1, cv::Vec3b c2) const {
        return cv::Vec3b (std::max (c1[0], c2[0]), std::max (c1[1], c2[1]), std::max (c1[2], c2[2]));
    }
};

class MinimumColorMixer : public ColorMixer {
public:
    cv::Vec3b mix(cv::Vec3b c1, cv::Vec3b c2) const {
        return cv::Vec3b (std::min (c1[0], c2[0]), std::min (c1[1], c2[1]), std::min (c1[2], c2[2]));
    }
};

class AdditionColorMixer : public ColorMixer {
public:
    cv::Vec3b mix(cv::Vec3b c1, cv::Vec3b c2) const {
        cv::Vec3b res;
        for (int i = 0; i < 3; ++i) {
            int tmp = int(c1[i]) + c2[i];
            if (tmp > 255) tmp = 255;
            res[i] = tmp;
        }
        return res;
    }
};

class SubtractColorMixer : public ColorMixer {
public:
    cv::Vec3b mix(cv::Vec3b c1, cv::Vec3b c2) const {
        cv::Vec3b res;
        for (int i = 0; i < 3; ++i) {
            int tmp = int(c1[i]) - c2[i];
            if (tmp < 0) tmp = 0;
            res[i] = tmp;
        }
        return res;
    }
};

#endif // COLORMIXERIMPL

