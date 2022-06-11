//
// Created by 王逸 on 2022/6/7.
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include "opencv_cvtcolor_imwrite.h"


using namespace cv;
using namespace std;

int main(int argc, char** argv){
    Mat src = imread("/Users/wangyi/opencv/opencv_tutorial_data-master/images/ttt.png");
    // 千万别变
//    Mat src = imread("/Users/wangyi/opencv/opencv_tutorial_data-master/images/age_gender.jpg", IMREAD_UNCHANGED);
    // 灰白色
//    Mat src = imread("/Users/wangyi/opencv/opencv_tutorial_data-master/images/age_gender.jpg", IMREAD_GRAYSCALE);
    if (src.empty()){
        printf("没找到文件\n");
        return -1;
    }
    // 自适应窗口
//    namedWindow("输入窗口",WINDOW_FREERATIO);
//    imshow("input", src);

    QuickDemo qd;
//    qd.colorSpace_Demo(src);

//    qd.mat_creation_demo(src);
//    qd.operators_demo(src);
//    qd.tracking_bar_demo(src);
//    qd.key_demo(src);
//    qd.color_style_demo(src);
//    qd.bitwise_demo(src);
//    qd.channels_demo(src);
//    qd.inrange_demo(src);
//    qd.pixel_statistic_demo(src);
//    qd.drawing_demo(src);
//    qd.random_drawing_demo();
//    qd.polyline_drawing_demo();
//    qd.mouse_drawing_demo(src);
//    qd.norma_demo(src);
//    qd.resize_demo(src);
//    qd.flip_demo(src);
//    qd.rotate_demo(src);





//    qd.video_demo(src);
//    qd.video_demo_1(src);
//    qd.video_operate_demo();
//    qd.blur_demo(src);
//    qd.gaussia_blur_demo(src);
    qd.bifilter_demo(src);





    // 停留多少毫秒
    waitKey(10000);
    destroyAllWindows();
    return 0;
}