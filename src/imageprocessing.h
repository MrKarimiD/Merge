#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include "QString"
#include "QFileDialog"
#include "filtersettings.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/cuda.hpp>
#include <gameground.h>
#include "constants.h"
#include "QSemaphore"

#define ASPECT_RATIO_TRESH 4

using namespace cv;
using namespace std;

#include <QObject>

class ImageProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcessing(QObject *parent = 0);

    Mat shapeDetection(Mat input,Mat src,Rect cropedRect);

    Mat applyFilters(Mat input);

    Mat undistortImage(Mat input);

    void changeOutputSetting(bool con,bool geom,bool bound,bool rotate,bool boundries);

    void updateFilterSettings(filterSettings *fs);

    Mat returnAdaptiveThreshlodImage();

    Mat returnThreshlodImage();

    Mat returnCannyImage();

    Mat returnCropedImage();

    void findColors(Mat input);

    void sendSignal();

    Mat Outputs[5];//0->Crop    1->Adaptive    2->threshold   3->canny     4->final

    static GameGround returnStaticData();

    /*static*/ GameGround result;
    /*static*/ QSemaphore semaphore;

private:
    vector<Vec3f> finding_circles;
    filterSettings *filterSetting;
    //Mat cameraMatrix, distCoeffs;
    bool drawContoursBool,drawGeometricLabels,drawBoundedRect,drawRotatedRect,drawBoundries;
    bool checkAspectRatio(vector<Point> contours_poly);
    bool checkAspectRatioForRotatedRect(RotatedRect input);
    void prepareDataForOutput(std::vector<cv::Point>& contour,QString type);
    double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0);
    void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour,Rect cropedRect);

signals:
    void gameGroundReady(const GameGround &out);

public slots:
    void test(const GameGround &out);

};

#endif // IMAGEPROCESSING_H
