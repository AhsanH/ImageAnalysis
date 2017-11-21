#include <iostream>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class ImageFunc{

Mat image;
public:

    ImageFunc(const string& str){
        image = imread(str);
    }
    void Display_Image(void){
        namedWindow("input", WINDOW_AUTOSIZE);
        imshow("input", this->image);
        waitKey(0);
    }
};


int main()
{
    ImageFunc I("bench.jpg");
    I.Display_Image();
    return 0;
}
