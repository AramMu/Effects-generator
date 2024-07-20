#include <iostream>
#include "Simulation/Generator/flameparabola.h"
#include "Simulation/Generator/flametongue.h"
#include "Simulation/Generator/pixellightning.h"
#include "Simulation/Generator/flameblaze.h"
#include "Simulation/Generator/spider.h"
#include "Simulation/Generator/wave.h"
#include "Simulation/Generator/maze.h"
#include "Simulation/Generator/smoke.h"
#include "Utils/Time/timemeasure.h"
#include "Utils/ImageProcessing/imagecorrection.h"
#include "Utils/ImageProcessing/transformation.h"
#include "Utils/Drawables/doubletongue.h"
#include "Utils/Drawables/ghost.h"
#include "Simulation/Generator/clothghost.h"
#include "Utils/Drawables/polynomial.h"
#include "Utils/Print/global.h"
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    cv::Mat img(500,500,CV_8UC3);
    cv::namedWindow("aaa");
    /*
    Polynomial p({7, -5, 12, 8, 1}, {0, 0});
//    std::cout << p.derivate().a;
    p.draw(img, {255,255,255}, 2);
    cv::imshow("aaa", img);
    */
//    std::cout << p.eval(p.a, 3) << std::endl;

    //ClothGhost sim(img.size());
    Maze sim(img.size()/5);
    //FlameTongue sim(img.size());
    //sim.setFlameCount(10);
    //sim.setColorMode(FlameTongue::eColored);

    //sim.setMergeMode(ClothGhost::eLayered);
    int fileCount=0;

    while (sim.hasNextFrame()) {

        TimeMeasure tm;
        tm.start();
        img = sim.getNextFrame();
        cv::resize(img, img, img.size()*5, 0,0,CV_INTER_NN);
        cv::imshow("aaa", img);
        tm.finish();
        cout << tm.getDifMicro() << endl;

        int key = cv::waitKey(1);
        if (key == 's') {
            fileCount++;
            cv::imwrite(std::string("result/") + std::to_string(fileCount) + ".png", img);
        }
    }

    /*
    Ghost g(200, 100, -0.2);
    g.drawFill(img, cv::Vec3b(255,255,255));

    cv::flip(img,img,0);
    cv::imshow("aaa", img);
    */
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
