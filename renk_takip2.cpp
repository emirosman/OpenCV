#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int fonk1()
{
    cout<<"çalıştı"<<endl;
    return 1;
}

int main(int argc,char** argv)
{
    int eskix=-1,eskiy=-1,yenix,yeniy;
    double xeksen,yeksen,alan;
    Mat araframe,cizgiresim,yeniframe,hsvres,isres;
    VideoCapture vid(0);
    if (!vid.isOpened())
    {
        cout<<"videocapture Hata"<<endl;
        return -1;
    }
    namedWindow("kontrol",WINDOW_AUTOSIZE);
    int Hmin=170;
    int Hmax=179;
    int Smin=150;
    int Smax=255;
    int Vmin=179;
    int Vmax=255;
    
    createTrackbar("Hue Min","kontrol",&Hmin,179);
    createTrackbar("Hue Max","kontrol",&Hmax,179);
    createTrackbar("Sat Min","kontrol",&Smin,255);
    createTrackbar("Sat Max","kontrol",&Smax,255);
    createTrackbar("Val Min","kontrol",&Vmin,255);
    createTrackbar("Val Max","kontrol",&Vmax,255);
    
    vid.read(araframe);
    cizgiresim=Mat::zeros(araframe.size(),CV_8UC3);
    
    while(1)
    {
        bool kontrol = vid.read(yeniframe);
        if(!kontrol)
        {
            cout<<"frame okumada hata"<<endl;
            break;
        }
        cvtColor(yeniframe,hsvres,COLOR_BGR2HSV);
        inRange(hsvres,Scalar(Hmin,Smin,Vmin),Scalar(Hmax,Smax,Vmax),isres);
        double flt=5;
        erode(isres,isres,getStructuringElement(MORPH_ELLIPSE,Size(flt,flt)) );
        dilate(isres,isres,getStructuringElement(MORPH_ELLIPSE,Size(flt,flt)) );
        
        dilate(isres,isres,getStructuringElement(MORPH_ELLIPSE,Size(flt,flt)) );
        erode(isres,isres,getStructuringElement(MORPH_ELLIPSE,Size(flt,flt)) );
        
        Moments konum=moments(isres);
        xeksen=konum.m10;
        yeksen=konum.m01;
        alan=konum.m00;
        if(alan>500)
        {
            yenix=xeksen/alan;
            yeniy=yeksen/alan;
            fonk1();
            if(eskix>=0 && eskiy>=0 && yenix>=0 && yeniy>=0)
            {
                line(cizgiresim,Point(yenix,yeniy),Point(eskix,eskiy),Scalar(0,0,255),5);
            }
            
            eskix=yenix;
            eskiy=yeniy;
        }
        
        imshow("SB",isres);
        yeniframe=yeniframe+cizgiresim;
        imshow("orj",yeniframe);
        if(waitKey(30)==27)
            break;
    }
    
    
    
    return 0;
}



























