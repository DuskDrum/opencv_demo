//
// Created by 王逸 on 2022/6/7.
//

#include "opencv_cvtcolor_imwrite.h"
using namespace std;

void QuickDemo::colorSpace_Demo(Mat &image) {
    Mat gray, hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);
    // H 0 ~ 180 S,V
    // RBG
    cvtColor(image, gray, COLOR_BGR2GRAY);
    imshow("hsv", hsv);
    imshow("灰度", gray);
    // 保存
    imwrite("/Users/wangyi/opencv/opencv_tutorial_data-master/images/hsv.png",hsv);
    imwrite("/Users/wangyi/opencv/opencv_tutorial_data-master/images/gray.png",gray);
}

void QuickDemo::mat_creation_demo(Mat &image) {
    Mat m1, m2;
    // 两个相同的
    m1 = image.clone();
    image.copyTo(m2);

    //创建空白图像, 8*8，无符号的8位，单通道
    Mat m3 = Mat::ones(Size(400,400),CV_8UC3);
    m3 = Scalar(0,0,255);
    std::cout<<"width:"<<m3.cols<<"heigth:"<<m3.rows<<"通道数:"<<m3.channels()<<std::endl;
    std::cout<<m3 << std::endl;
    imshow("输出", m3);

    // 赋值不会改变原来的Mat图像
    Mat m4 = m3;
    m4 = Scalar(0,255,255);
    imshow("输出3", m3);
    imshow("输出4", m4);

}

void QuickDemo::pixel_visit_demo(Mat &image) {
    int w = image.cols;
    int h = image.rows;
    int dims = image.channels();
    // for循环
//    for (int row = 0; row < h; ++row) {
//        for (int col = 0; col < w; ++col) {
//            // 灰度图像
//            if (dims==1){
//                int pv = image.at<uchar>(row,col);
//                // 像素取反
//                image.at<uchar>(row,col) = 255 - pv;
//            }
//            // 彩色图像
//            if (dims==3){
//                Vec3b bgr = image.at<Vec3b>(row,col);
//                image.at<Vec3b>(row,col)[0] = 255- bgr[0];
//                image.at<Vec3b>(row,col)[1] = 255- bgr[1];
//                image.at<Vec3b>(row,col)[2] = 255- bgr[2];
//            }
//        }
//    }
    // 指针
    for (int row = 0; row < h; ++row) {
        uchar* current_row = image.ptr<uchar>(row);
        for (int col = 0; col < w; ++col) {
            // 灰度图像
            if (dims==1){
                int pv = *current_row;
                // 像素取反
                *current_row++ = 255-pv;
            }
            // 彩色图像
            if (dims==3){
                *current_row++ = 255-*current_row;
                *current_row++ = 255-*current_row;
                *current_row++ = 255-*current_row;
            }
        }
    }
    imshow("像素读写演示", image);
}

void QuickDemo::operators_demo(Mat &image) {
    // + -0 * /
    Mat dst;
//    // 每个像素点+50
//    dst = image + Scalar (50,50,50);
//    imshow("加法操作", dst);

    // 每个像素点-50
//    dst = image - Scalar (50,50,50);
//    imshow("减法操作", dst);

    // 每个像素点除以50
//    dst = image / Scalar (50,50,50);
//    imshow("除法操作", dst);

    // 每个像素点乘以50，有可能会超过255，所以使用multiply方法做截取
//    dst = image * Scalar (50,50,50);
//    imshow("除法操作", dst);
    Mat m = Mat::zeros(image.size(),image.type());
    m = Scalar(2,2,2);
//    multiply(image, m, dst);
//    imshow("乘法操作", dst);

    // saturate_cast<uchar>方法用来判断范围判定，一定要是uchar，否则会做截取

    // 上面是手写的, opencv有自己的方法
    add(image,m,dst);
    subtract(image, m, dst);
    divide(image,m,dst);
    multiply(image, m, dst);
    imshow("乘法操作", dst);


}

// 回调函数
static void on_track(int b, void* userdata){
    Mat tracking_image = *((Mat*)userdata);
    Mat tracking_dst = Mat::zeros(tracking_image.size(),tracking_image.type());
    Mat tracking_m = Mat::zeros(tracking_image.size(),tracking_image.type());
    tracking_m = Scalar(b,b,b);
    // tracking_bar变亮
//    add(tracking_src,tracking_m,tracking_dst);
    // tracking_bar变暗
//    subtract(tracking_image,tracking_m,tracking_dst);
    // 两张图片叠加处理，融合两张图
    addWeighted(tracking_image, 1.0,tracking_m, 0, b, tracking_dst);
    imshow("亮度调整", tracking_dst);
}

void QuickDemo::tracking_bar_demo(Mat &image) {
    namedWindow("亮度调整", WINDOW_AUTOSIZE);
    // 亮度参数
    int lightness = 50;
    int max_value=100;
    // 对比度参数
    int contrast_value = 2;
    // 增加trackbar
    createTrackbar("Value Bar", "亮度与对比度调整", &lightness, max_value,on_track,(void*)(&image));

    createTrackbar("Contrast Bar", "亮度与对比度调整", &contrast_value, 5,on_track,(void*)(&image));

    on_track(50,&image);
}

void QuickDemo::key_demo(Mat &image) {
    Mat dst = Mat::zeros(image.size(),image.type());
    while(true){
        int c = waitKey(100);
        if (c==27){
            break;
        }
        // 1
        if(c==49){
            std::cout<<"you enter #1"<<std::endl;
            cvtColor(image, dst, COLOR_BGR2GRAY);
        }
        // 2
        if(c==50){
            std::cout<<"you enter #2"<<std::endl;
            cvtColor(image, dst, COLOR_BGR2HSV);
        }
        // 3
        if(c==51){
            std::cout<<"you enter #3"<<std::endl;
            dst = Scalar(50,50,50);
            add(image,dst,dst);
        }
        imshow("键盘响应",dst);
    }
}


void QuickDemo::color_style_demo(Mat &image) {
    int colormap[] = {
      COLORMAP_AUTUMN,
      COLORMAP_BONE,
      COLORMAP_CIVIDIS,
      COLORMAP_COOL,
      COLORMAP_DEEPGREEN,
      COLORMAP_HOT,
      COLORMAP_HSV,
      COLORMAP_INFERNO,
      COLORMAP_JET,
      COLORMAP_MAGMA,
      COLORMAP_OCEAN,
      COLORMAP_PARULA,
      COLORMAP_PINK,
      COLORMAP_PLASMA,
      COLORMAP_RAINBOW,
      COLORMAP_SPRING,
      COLORMAP_SUMMER,
      COLORMAP_TURBO,
      COLORMAP_TWILIGHT,
      COLORMAP_TWILIGHT_SHIFTED,
      COLORMAP_VIRIDIS,
      COLORMAP_WINTER
    };
    Mat dst;
    int index = 0;
    while(true){
        int c = waitKey(500);
        if (c==27){
            break;
        }
        applyColorMap(image,dst,colormap[index%19]);
        index++;
        imshow("颜色风格", dst);
    }
}


void QuickDemo::bitwise_demo(Mat &image) {
    Mat m1 = Mat::zeros(Size(256,256), CV_8SC3);
    Mat m2 = Mat::zeros(Size(256,256), CV_8SC3);
    // lineType用来处理像素锯齿
    // tickness: -1是填充
    // tickness: 2是描边
    // Scalar三个是BGR
    rectangle(m1, Rect(100,100,80,80), Scalar(255,255,0),-1,LINE_8,0);
    rectangle(m2, Rect(150,150,80,80), Scalar(0,255,255),-1,LINE_8,0);
    imshow("m1",m1);
    imshow("m2",m2);
    Mat dst;
    // 与操作
//    bitwise_and(m1,m2,dst);
    // 或操作
//    bitwise_or(m1,m2,dst);
    // 非操作
//    bitwise_not(image,dst);
    // 非操作2
//    dst = ~image;
    // 异或
    bitwise_xor(m1,m2,dst);

    imshow("位操作", dst);
}

void QuickDemo::channels_demo(Mat &image) {
    std::vector<Mat> mv;
    // 分离通道
//    split(image, mv);
//    imshow("蓝色", mv[0]);
//    imshow("绿色", mv[1]);
//    imshow("红色", mv[2]);

    Mat dst = Mat::zeros(image.size(), image.type());
    // 蓝色
//    mv[1] = 0;
//    mv[2] = 0;
//    merge(mv, dst);
//    imshow("蓝色",dst);
    // 绿色
//    mv[0] = 0;
//    mv[2] = 0;
//    merge(mv, dst);
//    imshow("绿色",dst);

    // 红色
//    mv[0] = 0;
//    mv[1] = 0;
//    merge(mv, dst);
//    imshow("红色",dst);

    int from_to[] = {0,2,1,1,2,0};
    mixChannels(&image,1, &dst, 1,from_to,3);
    imshow("通道混合", dst);
}


void QuickDemo::inrange_demo(Mat &image) {
    // 扣出绿幕里的人像
    Mat hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);
    Mat mask;
    // HSV, h:0-180； s:0-255; v:0-255
    inRange(hsv, Scalar(35,43,46), Scalar(77,255,255), mask);
    imshow("mask", mask);
    //
    Mat redback = Mat::zeros(image.size(),image.type());
    redback = Scalar (40,40,200);
    bitwise_not(mask,mask);
    image.copyTo(redback, mask);
    imshow("roi区域",redback);

}


void QuickDemo::pixel_statistic_demo(Mat &image) {
    double minv, maxv;
    Point minLoc, maxLoc;

    std::vector<Mat> mv;
    split(image, mv);
    for (int i = 0; i < mv.size(); ++i) {
        minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, Mat());
        std::cout<<"最小值"<<minv<<"最大值"<<maxv<<std::endl;
    }
    // mean均值，stddev方差
    Mat mean, stddev;
    meanStdDev(image, mean, stddev);
    std::cout<<"mean:"<<mean<<"stddev:"<<stddev<<std::endl;


}

void QuickDemo::drawing_demo(Mat &image) {
    // 矩形,计算机里的坐标系原点在左上角
    Rect rect;
    rect.x = 200;
    rect.y = 200;
    rect.width = 100;
    rect.height = 100;



    // 画红色的框
//    rectangle(image, rect, Scalar(0,0,255));
    // 画红色的矩形填充,-1指的是填充
    rectangle(image, rect, Scalar(0,0,255),-1,8,0);

    // 圆, 2是框，-1是填充
//    circle(image, Point(350, 400), 15, Scalar(255,0,0), 2, 8,0);

    // 线
    line(image, Point(200,200),Point(300,300),Scalar(0,255,0));

    // 椭圆
    RotatedRect rrt;
    rrt.center = Point(200,200);
    rrt.size = Size(100,200);
    rrt.angle = 90.0;

    ellipse(image, rrt, Scalar(0,255,255),2,8);

    imshow("绘制演示", image);

}

void QuickDemo::random_drawing_demo() {
    Mat canvas = Mat::zeros(Size(512,512),CV_8UC3);
    RNG rng(12345);
    int w = canvas.cols;
    int h = canvas.rows;
    while(true){
        int c = waitKey(10);
        if (c==27){
            break;
        }
        int x1 = rng.uniform(0,w);
        int y1 = rng.uniform(0,h);
        int x2 = rng.uniform(0,w);
        int y2 = rng.uniform(0,h);

        int b = rng.uniform(0,255);
        int g = rng.uniform(0,255);
        int r = rng.uniform(0,255);

        line(canvas, Point(x1,y1),Point(x2,y2),Scalar(b,g,r));
        imshow("随机绘制演示", canvas);
    }
}

void QuickDemo::polyline_drawing_demo() {
    Mat canvas = Mat::zeros(Size(512,512),CV_8UC3);
    Point p1(100, 100);
    Point p2(350, 350);
    Point p3(450, 280);
    Point p4(320, 450);
    Point p5(80, 400);
    std::vector<Point> pts;
    pts.push_back(p1);
    pts.push_back(p2);
    pts.push_back(p3);
    pts.push_back(p4);
    pts.push_back(p5);
    // 这个方法不支持填充，所以把thickness改成负数会报错，那么填充需要另一个方法
//    polylines(canvas,pts,true, Scalar(0,0,255),2,LINE_AA,0);
//    fillPoly(canvas,pts,Scalar(0,0,255),8,0);
    std::vector<std::vector<Point>> contours;
    contours.push_back(pts);
    // 填充的方法，一次性绘制和填充
    drawContours(canvas, contours, -1,Scalar(255,0,0),-1);
    imshow("多边形绘制", canvas);
}

// event值的事件，左键右键移动
Point  sp(-1, -1);
Point  ep(-1, -1);
static void on_draw(int event, int x,int y, int flags, void *userdata){
    Mat image = *((Mat*)userdata);
    if (event == EVENT_LBUTTONDOWN){
        sp.x = x;
        sp.y = y;
        std::cout<<"start point:"<<sp<<std::endl;
    } else if (event == EVENT_LBUTTONUP){
        ep.x = x;
        ep.y = y;
        int dx = ep.x-sp.x;
        int dy = ep.y-sp.y;
        if (dx>0 && dy>0){
            Rect box(sp.x,sp.y,dx,dy);
            rectangle(image, box, Scalar(0,0,255),2,8,0);
            imshow("鼠标绘制",image);
        }
    } else if (event == EVENT_MOUSEMOVE){
        if(sp.x>0 && sp.y>0){
            ep.x = x;
            ep.y = y;
            int dx = ep.x-sp.x;
            int dy = ep.y-sp.y;
            if (dx>0 && dy>0){
                Rect box(sp.x,sp.y,dx,dy);
                rectangle(image, box, Scalar(0,0,255),2,8,0);
                imshow("鼠标绘制",image);
                sp.x = -1;
                sp.y = -1;
            }
        }

    }


}

void QuickDemo::mouse_drawing_demo(Mat &image) {
    namedWindow("鼠标绘制", WINDOW_AUTOSIZE);
    setMouseCallback("鼠标绘制", on_draw, (void*)(&image));
    imshow("鼠标绘制",image);


}

void QuickDemo::norma_demo(Mat &image) {
    Mat dst;
    // 16,代表cv_8UC3(8位3通道)
    std::cout << image.type() << std::endl;
//    image.convertTo(dst, CV_32F);
    // 21，CV_32FC3
//    std::cout << dst.type() << std::endl;
//
//    Mat dst1;
//    image.convertTo(dst1, CV_32S);
//    // 20
//    std::cout << dst1.type() << std::endl;
    image.convertTo(image, CV_32F);
    // dst转为了浮点型，就可以做归一化了.不转浮点不行
    normalize(image, dst,1.0,0,NORM_MINMAX);
    imshow("归一化", dst);

}

void QuickDemo::resize_demo(Mat &image) {
    imshow("image", image);
    Mat zoomin, zoomout;
    int h = image.rows;
    int w = image.cols;
    resize(image, zoomin, Size(w/2,h/2),0,0,INTER_LINEAR);
    imshow("zoomin", zoomin);
    resize(image, zoomout, Size(w*1.5,h*1.5),0,0,INTER_LINEAR);
    imshow("zoomout", zoomout);
}


void QuickDemo::flip_demo(Mat &image) {
    imshow("image",image);
    Mat dst;
//    // 上下翻转
//    flip(image ,dst, 0);
    // 左右翻转
//    flip(image ,dst, 1);
    // 原点中心对称180°旋转
    flip(image ,dst, -1);
    imshow("flip",dst);
}


void QuickDemo::rotate_demo(Mat &image) {
    imshow("image", image);
    Mat dst, M;
    int h = image.rows;
    int w  = image.cols;
    M = getRotationMatrix2D(Point2f(w/2,h/2),45, 1.0);
    double cos = abs(M.at<double>(0,0));
    double sin = abs(M.at<double>(0,1));
    int nw = cos*w+sin*h;
    int nh = sin*w+cos*h;
    M.at<double>(0,2) += (nw/2-w/2);
    M.at<double>(1,2) += (nh/2-h/2);
    warpAffine(image, dst,M,Size(nw,nh),INTER_LINEAR,0,Scalar(255,255,0));
    imshow("warpAffine", dst);
}


void QuickDemo::video_demo(Mat &image) {
    VideoCapture capture(0);
    Mat frame;
    while(true) {
        capture.read(frame);
        flip(frame,frame,1);
        if(frame.empty()){
            break;
        }
        imshow("frame", frame);
        int c = waitKey(10);
        if (c == 27) {
            break;
        }
    }
}
void QuickDemo::video_demo_1(Mat &image) {
    VideoCapture capture("/Users/wangyi/opencv/opencv_tutorial_data-master/images/01.mp4");
    Mat frame;
    while(true) {
        capture.read(frame);
        flip(frame,frame,1);
        if(frame.empty()){
            break;
        }
        imshow("frame", frame);
        int c = waitKey(10);
        if (c == 27) {
            break;
        }
    }
    capture.release();
}

void QuickDemo::video_operate_demo() {
    VideoCapture capture("/Users/wangyi/opencv/opencv_tutorial_data-master/images/01.mp4");
    int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
    int count = capture.get(CAP_PROP_FRAME_COUNT);
    //fps:1s处理多少张图片
    double fps = capture.get(CAP_PROP_FPS);
    std::cout<<"frame_width"<<frame_width<<std::endl;
    std::cout<<"frame_height"<<frame_height<<std::endl;
    std::cout<<"count"<<count<<std::endl;
    std::cout<<"fps"<<fps<<std::endl;
    VideoWriter writer("/Users/wangyi/opencv/opencv_tutorial_data-master/images/01_result.mp4", capture.get(CAP_PROP_FOURCC), fps,Size(frame_width,frame_height),true);
    Mat frame;
    while(true) {
        capture.read(frame);
        flip(frame,frame,1);
        if(frame.empty()){
            break;
        }
        imshow("frame", frame);
        writer.write(frame);
        int c = waitKey(10);
        if (c == 27) {
            break;
        }
    }
    capture.release();
    writer.release();
}


void QuickDemo::blur_demo(Mat &image) {
    imshow("image", image);

    Mat dst;
    // 3乘3模糊卷积
//    blur(image, dst,Size(3,3),Point(-1,-1));
    // 23乘23模糊卷积
//    blur(image, dst,Size(23,23),Point(-1,-1));
    // 一维卷积
//    blur(image, dst,Size(15,1),Point(-1,-1));
    blur(image, dst,Size(1,15),Point(-1,-1));
    imshow("blur", dst);


}


void QuickDemo::gaussia_blur_demo(Mat &image) {
    imshow("image", image);
    Mat dst;
//    GaussianBlur(image, dst,Size(5,5),15);
//    GaussianBlur(image, dst,Size(0,0),15);
// 输入需要是奇数，正数(size)
    GaussianBlur(image, dst,Size(0,0),15);
    imshow("blur", dst);

}

void QuickDemo::bifilter_demo(Mat &image) {
    imshow("image", image);
    Mat dst;
    bilateralFilter(image,dst,0,100,10);
    imshow("blur", dst);
}