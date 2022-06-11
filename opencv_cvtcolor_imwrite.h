//
// Created by 王逸 on 2022/6/7.
//

#ifndef HELLOWORLD_OPENCV_CVTCOLOR_IMWRITE_H
#define HELLOWORLD_OPENCV_CVTCOLOR_IMWRITE_H


class opencv_cvtcolor_imwrite {

};

#include <opencv2/opencv.hpp>
using namespace cv;

class QuickDemo{
public:
    void colorSpace_Demo(Mat &image);
    void mat_creation_demo(Mat &image);
    void pixel_visit_demo(Mat &image);
    void operators_demo(Mat &image);
    // trackbar
    void tracking_bar_demo(Mat &image);
    // 键盘操作
    void key_demo(Mat &image);
    // 颜色表操作
    void color_style_demo(Mat &image);
    // 像素逻辑操作
    void bitwise_demo(Mat &image);
    // 通道分离与合并(RGB)
    void channels_demo(Mat &image);
    // 图像色彩空间转换
    void inrange_demo(Mat &image);
    // 像素统计信息(所有像素的最小值、最大值、平均值、方差)min\max\mean\standard dev
    void pixel_statistic_demo(Mat &image);
    // 图形几何形状绘制
    void drawing_demo(Mat &image);
    // 随机颜色画线
    void random_drawing_demo();
    // 绘制多边形，填充多边形
    void polyline_drawing_demo();
    // 鼠标操作和响应
    void mouse_drawing_demo(Mat &image);
    // 图像类型转化与归一化,把数据指定为特定数值，有四种算法
    void norma_demo(Mat &image);
    // 图像放缩与插值
    void resize_demo(Mat &image);
    // 图像翻转
    void flip_demo(Mat &image);
    // 图像旋转，多少度，中心位置
    void rotate_demo(Mat &image);
    // 视频文件摄像头使用(电脑摄像头)
    void video_demo(Mat &image);
    // 读视频
    void video_demo_1(Mat &image);
    // 视频处理和保存(手机分辨率480p，SD:标清，HD:高清)
    void video_operate_demo();
    // 图像直方图
    // 二维直方图(HSV，只有两个通道，有个字母代表亮度)
    // 直方图均衡化
    // 图像卷积操作（原数据乘以卷积积，相加得到然后除以9，并赋值给中间的那个值(铆钉点)），上下左右会各有一排没办法被卷积，一般会做填充处理，或者直接丢掉
    void blur_demo(Mat &image);
    // 高斯模糊,离中心越远越小(正态分布)，越靠近中间越大
    void gaussia_blur_demo(Mat &image);
    // 高斯双边模糊,对重要的信息保存，不重要的细节给模糊。类似于磨皮
    void bifilter_demo(Mat &image);
    // 实时人脸检测
};


#endif //HELLOWORLD_OPENCV_CVTCOLOR_IMWRITE_H
