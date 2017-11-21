#include <iostream>
#include <vector>
#include <cstdlib>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class ImageFunc{

Mat image;
vector<pair<int,int>> myPixels;
public:

    ImageFunc(const string& str){
        image = imread(str);
    }
    void Display_Image(void){
        namedWindow("input", WINDOW_AUTOSIZE);
        imshow("input", this->image);
        waitKey(0);
    }

    vector<pair<int,int>> FIND_REGION(int x, int y){
        int row_size = image.rows;
        int col_size = image.cols;

        Vec3b *p;
        p = image.ptr<Vec3b>(x);
        uchar R_i = p[y][0];
        uchar G_i = p[y][1];
        uchar B_i = p[y][2];

        vector< vector<int> > map(row_size, vector<int>(col_size));
        vector<pair<int, int> >myStack;
        pair<int,int> current;
        myStack.push_back(make_pair(x,y));
        map[x][y] = 1;
        const int threshold = 30;
        while(myStack.size()>0){
            current = myStack.back();
            myStack.pop_back();

            if((current.first == 0)&&(current.second == 0)){
                if(map[0][1] == 0){
                    p = image.ptr<Vec3b>(0);
                    if((abs(p[1][0]-R_i)<threshold)&&(abs(p[1][1]-G_i)<threshold)&&(abs(p[1][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(0,1));
                        myPixels.push_back(make_pair(0,1));
                        map[0][1] = 1;
                    }
                }
                if(map[1][0] == 0){
                    p = image.ptr<Vec3b>(1);
                    if((abs(p[0][0]-R_i)<threshold)&&(abs(p[0][1]-G_i)<threshold)&&(abs(p[0][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(1,0));
                        myPixels.push_back(make_pair(1,0));
                        map[1][0] = 1;
                    }
                }
            }
            else if((current.first == 0)&&(current.second == (col_size-1))){
                if(map[0][current.second-1] == 0){
                    p = image.ptr<Vec3b>(0);
                    if((abs(p[current.second-1][0]-R_i)<threshold)&&(abs(p[current.second-1][1]-G_i)<threshold)&&(abs(p[current.second-1][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(0,current.second-1));
                        myPixels.push_back(make_pair(0,current.second-1));
                        map[0][current.second-1] = 1;

                    }
                }
                if(map[1][current.second] == 0){
                    p = image.ptr<Vec3b>(1);
                    if((abs(p[current.second][0]-R_i)<threshold)&&(abs(p[current.second][1]-G_i)<threshold)&&(abs(p[current.second][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(1,current.second));
                        myPixels.push_back(make_pair(1,current.second));
                        map[1][current.second] = 1;

                    }
                }
            }
            else if((current.first == row_size-1)&&(current.second == 0)){
                if(map[current.first-1][current.second] == 0){
                    p = image.ptr<Vec3b>(current.first-1);
                    if((abs(p[current.second][0]-R_i)<threshold)&&(abs(p[current.second][1]-G_i)<threshold)&&(abs(p[current.second][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first-1,0));
                        myPixels.push_back(make_pair(current.first-1,0));
                        map[current.first-1][current.second] = 1;

                    }
                }
                if(map[current.first][current.second+1] == 0){
                    p = image.ptr<Vec3b>(current.first);
                    if((abs(p[current.second+1][0]-R_i)<threshold)&&(abs(p[current.second+1][1]-G_i)<threshold)&&(abs(p[current.second+1][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first,1));
                        myPixels.push_back(make_pair(current.first,1));
                        map[current.first][current.second+1] = 1;

                    }
                }
            }
            else if((current.first == row_size-1)&&(current.second == col_size-1)){
                if(map[current.first-1][current.second] == 0){
                    p = image.ptr<Vec3b>(current.first-1);
                    if((abs(p[current.second][0]-R_i)<threshold)&&(abs(p[current.second][1]-G_i)<threshold)&&(abs(p[current.second][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first-1,current.second));
                        myPixels.push_back(make_pair(current.first-1,current.second));
                        map[current.first-1][current.second] = 1;

                    }
                }
                if(map[current.first][current.second-1] == 0){
                    p = image.ptr<Vec3b>(current.first);
                    if((abs(p[current.second-1][0]-R_i)<threshold)&&(abs(p[current.second-1][1]-G_i)<threshold)&&(abs(p[current.second-1][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first,current.second-1));
                        myPixels.push_back(make_pair(current.first,current.second-1));
                        map[current.first][current.second-1] = 1;

                    }
                }
            }
            else if(current.first == 0){
                if(map[current.first+1][current.second] == 0){
                    p = image.ptr<Vec3b>(current.first+1);
                    if((abs(p[current.second][0]-R_i)<threshold)&&(abs(p[current.second][1]-G_i)<threshold)&&(abs(p[current.second][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first+1,current.second));
                        myPixels.push_back(make_pair(current.first+1,current.second));
                        map[current.first+1][current.second] = 1;

                    }
                }
                if(map[current.first][current.second-1] == 0){
                    p =image.ptr<Vec3b>(current.first);
                    if((abs(p[current.second-1][0]-R_i)<threshold)&&(abs(p[current.second-1][1]-G_i)<threshold)&&(abs(p[current.second-1][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first,current.second-1));
                        myPixels.push_back(make_pair(current.first,current.second-1));
                        map[current.first][current.second-1] = 1;

                    }
                }
                if(map[current.first][current.second+1] == 0){
                    p = image.ptr<Vec3b>(current.first);
                    if((abs(p[current.second+1][0]-R_i)<threshold)&&(abs(p[current.second+1][1]-G_i)<threshold)&&(abs(p[current.second+1][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first,current.second+1));
                        myPixels.push_back(make_pair(current.first,current.second+1));
                        map[current.first][current.second+1] = 1;

                    }
                }
            }
            else if(current.second == 0){
                if(map[current.first+1][current.second] == 0){
                    p = image.ptr<Vec3b>(current.first+1);
                    if((abs(p[current.second][0]-R_i)<threshold)&&(abs(p[current.second][1]-G_i)<threshold)&&(abs(p[current.second][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first+1,current.second));
                        myPixels.push_back(make_pair(current.first+1,current.second));
                        map[current.first+1][current.second] = 1;

                    }
                }
                if(map[current.first-1][current.second] == 0){
                    p = image.ptr<Vec3b>(current.first-1);
                    if((abs(p[current.second][0]-R_i)<threshold)&&(abs(p[current.second][1]-G_i)<threshold)&&(abs(p[current.second][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first-1,current.second));
                        myPixels.push_back(make_pair(current.first-1,current.second));
                        map[current.first-1][current.second] = 1;

                    }
                }
                if(map[current.first][current.second+1] == 0){
                    p = image.ptr<Vec3b>(current.first);
                    if((abs(p[current.second+1][0]-R_i)<threshold)&&(abs(p[current.second+1][1]-G_i)<threshold)&&(abs(p[current.second+1][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first,current.second+1));
                        myPixels.push_back(make_pair(current.first,current.second+1));
                        map[current.first][current.second+1] = 1;

                    }
                }

            }
            else if(current.first == row_size-1){
                if(map[current.first-1][current.second] == 0){
                    p = image.ptr<Vec3b>(current.first-1);
                    if((abs(p[current.second][0]-R_i)<threshold)&&(abs(p[current.second][1]-G_i)<threshold)&&(abs(p[current.second][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first-1,current.second));
                        myPixels.push_back(make_pair(current.first-1,current.second));
                        map[current.first-1][current.second] = 1;

                    }
                }
                if(map[current.first][current.second-1] == 0){
                    p = image.ptr<Vec3b>(current.first);
                    if((abs(p[current.second-1][0]-R_i)<threshold)&&(abs(p[current.second-1][1]-G_i)<threshold)&&(abs(p[current.second-1][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first,current.second-1));
                        myPixels.push_back(make_pair(current.first,current.second-1));
                        map[current.first][current.second-1] = 1;

                    }
                }
                if(map[current.first][current.second+1] == 0){
                    p = image.ptr<Vec3b>(current.first);
                    if((abs(p[current.second+1][0]-R_i)<threshold)&&(abs(p[current.second+1][1]-G_i)<threshold)&&(abs(p[current.second+1][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first,current.second+1));
                        myPixels.push_back(make_pair(current.first,current.second+1));
                        map[current.first][current.second+1] = 1;

                    }
                }
            }
            else if(current.second == col_size-1){
                if(map[current.first+1][current.second] == 0){
                    p = image.ptr<Vec3b>(current.first+1);
                    if((abs(p[current.second][0]-R_i)<threshold)&&(abs(p[current.second][1]-G_i)<threshold)&&(abs(p[current.second][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first+1,current.second));
                        myPixels.push_back(make_pair(current.first+1,current.second));
                        map[current.first+1][current.second] = 1;

                    }
                }
                if(map[current.first-1][current.second] == 0){
                    p = image.ptr<Vec3b>(current.first-1);
                    if((abs(p[current.second][0]-R_i)<threshold)&&(abs(p[current.second][1]-G_i)<threshold)&&(abs(p[current.second][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first-1,current.second));
                        myPixels.push_back(make_pair(current.first-1,current.second));
                        map[current.first-1][current.second] = 1;

                    }
                }
                if(map[current.first][current.second-1] == 0){
                    p = image.ptr<Vec3b>(current.first);
                    if((abs(p[current.second-1][0]-R_i)<threshold)&&(abs(p[current.second-1][1]-G_i)<threshold)&&(abs(p[current.second-1][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first,current.second-1));
                        myPixels.push_back(make_pair(current.first,current.second-1));
                        map[current.first][current.second-1] = 1;

                    }
                }
            }
            else {
                if(map[current.first+1][current.second] == 0){
                    p = image.ptr<Vec3b>(current.first+1);
                    if((abs(p[current.second][0]-R_i)<threshold)&&(abs(p[current.second][1]-G_i)<threshold)&&(abs(p[current.second][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first+1,current.second));
                        myPixels.push_back(make_pair(current.first+1,current.second));
                        map[current.first+1][current.second] = 1;

                    }
                }
                if(map[current.first-1][current.second] == 0){
                    p = image.ptr<Vec3b>(current.first-1);
                    if((abs(p[current.second][0]-R_i)<threshold)&&(abs(p[current.second][1]-G_i)<threshold)&&(abs(p[current.second][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first-1,current.second));
                        myPixels.push_back(make_pair(current.first-1,current.second));
                        map[current.first-1][current.second] = 1;

                    }
                }
                if(map[current.first][current.second-1] == 0){
                    p = image.ptr<Vec3b>(current.first);
                    if((abs(p[current.second-1][0]-R_i)<threshold)&&(abs(p[current.second-1][1]-G_i)<threshold)&&(abs(p[current.second-1][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first,current.second-1));
                        myPixels.push_back(make_pair(current.first,current.second-1));
                        map[current.first][current.second-1] = 1;

                    }
                }
                if(map[current.first][current.second+1] == 0){
                    p = image.ptr<Vec3b>(current.first);
                    if((abs(p[current.second+1][0]-R_i)<threshold)&&(abs(p[current.second+1][1]-G_i)<threshold)&&(abs(p[current.second+1][2]-B_i)<threshold)){
                        myStack.push_back(make_pair(current.first,current.second+1));
                        myPixels.push_back(make_pair(current.first,current.second+1));
                        map[current.first][current.second+1] = 1;

                    }
                }
            }
        }
        return myPixels;
    }

    void Display_Pixels(void){
        int x, y;
        Mat cpy_image = image;
        Vec3b *p;
        for(int i = 0; i<myPixels.size();i++){
            x = myPixels[i].first;
            p = cpy_image.ptr<Vec3b>(x);
            y = myPixels[i].second;
            p[y][0] = 255;
            p[y][1] = 255;
            p[y][2] = 255;
        }

        namedWindow("output", WINDOW_AUTOSIZE);
        imshow("output", cpy_image);
        waitKey(0);
    }





};


int main()
{
    ImageFunc I("bench.jpg");
    I.Display_Image();
    vector<pair<int, int> >myPix = I.FIND_REGION(23,34);
    cout<<myPix.size()<<endl;
    I.Display_Pixels();

    return 0;
}
