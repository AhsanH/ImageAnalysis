#include <iostream>
#include <vector>
#include <cstdlib>
#include <climits>
#include <string>
#include <fstream>
#include <cstdio>
#include <opencv2/highgui/highgui.hpp>



using namespace std;
using namespace cv;

class ImageFunc{

Mat image;


public:
    vector<pair<int,int>> myPixels;
    int a,b;
    ImageFunc(){}
    ImageFunc(const string& str){
        image = imread(str);
    }
    void DISPLAY_IMAGE(void){
        namedWindow("input", WINDOW_AUTOSIZE);
        imshow("input", this->image);
        waitKey(0);
    }

    vector<pair<int,int>> FIND_REGION(int x, int y){
        a = x;
        b = y;
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
        const int threshold = 10;
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

    vector<pair<int,int>> FIND_PERIMETER(void){
        int row_size = image.rows;
        int col_size = image.cols;
        vector<pair<int,int>> myBorderPixels;
        vector< vector<int> > map(row_size, vector<int>(col_size));
        int x,y;
        for(int i = 0; i<myPixels.size();i++){
            x = myPixels[i].first;
            y = myPixels[i].second;
            map[x][y] = 1;
        }
        for(int i = 1; i<row_size-1; i++){
            for(int j = 1; j<col_size-1; j++){
                if(((map[i][j-1]==0)&&(map[i][j+1]==1))||((map[i][j-1]==1)&&(map[i][j+1]==0))||((map[i-1][j]==0)&&(map[i+1][j]==1))||((map[i-1][j]==1)&&(map[i+1][j]==0))){
                    myBorderPixels.push_back(make_pair(i,j));
                }
            }
        }

        int prev_size = INT_MAX;
        while(myBorderPixels.size()<prev_size){
            vector< vector<int> > Border_map(row_size, vector<int>(col_size));
            for(int i = 0; i<myBorderPixels.size();i++){
                x = myBorderPixels[i].first;
                y = myBorderPixels[i].second;
                Border_map[x][y] = 1;
            }
            prev_size = myBorderPixels.size();
            myBorderPixels.clear();
            for(int i = 1; i<row_size-1; i++){
                for(int j = 1; j<col_size-1; j++){
                    if(((Border_map[i][j-1]==1)&&(Border_map[i][j+1]==1))||((Border_map[i-1][j]==1)&&(Border_map[i+1][j]==1))||((Border_map[i+1][j]==1)&&(Border_map[i][j-1]==1))||((Border_map[i-1][j]==1)&&(Border_map[i][j+1]==1))||((Border_map[i-1][j]==1)&&(Border_map[i][j-1]==1))||((Border_map[i+1][j]==1)&&(Border_map[i][j+1]==1))){
                        myBorderPixels.push_back(make_pair(i,j));
                    }
                }
            }
        }




        return myBorderPixels;
    }

    vector<pair<int,int>> FIND_SMOOTH_PERIMETER(void){
        int row_size = image.rows;
        int col_size = image.cols;
        vector<pair<int,int>> myBorderPixels;
        vector< vector<int> > map(row_size, vector<int>(col_size));
        int x,y;
        for(int i = 0; i<myPixels.size();i++){
            x = myPixels[i].first;
            y = myPixels[i].second;
            map[x][y] = 1;
        }
        for(int i = 1; i<row_size-1; i++){
            for(int j = 1; j<col_size-1; j++){
                if(((map[i][j-1]==0)&&(map[i][j+1]==1))||((map[i][j-1]==1)&&(map[i][j+1]==0))||((map[i-1][j]==0)&&(map[i+1][j]==1))||((map[i-1][j]==1)&&(map[i+1][j]==0))){
                    myBorderPixels.push_back(make_pair(i,j));
                }
            }
        }

        int prev_size = INT_MAX;
        while(myBorderPixels.size()<prev_size){
            vector< vector<int> > Border_map(row_size, vector<int>(col_size));
            for(int i = 0; i<myBorderPixels.size();i++){
                x = myBorderPixels[i].first;
                y = myBorderPixels[i].second;
                Border_map[x][y] = 1;
            }
            prev_size = myBorderPixels.size();
            myBorderPixels.clear();
            for(int i = 1; i<row_size-1; i++){
                for(int j = 1; j<col_size-1; j++){
                    if(((Border_map[i][j-1]==1)&&(Border_map[i][j+1]==1))||((Border_map[i-1][j]==1)&&(Border_map[i+1][j]==1))||((Border_map[i+1][j]==1)&&(Border_map[i][j-1]==1))||((Border_map[i-1][j]==1)&&(Border_map[i][j+1]==1))||((Border_map[i-1][j]==1)&&(Border_map[i][j-1]==1))||((Border_map[i+1][j]==1)&&(Border_map[i][j+1]==1))){
                        myBorderPixels.push_back(make_pair(i,j));
                    }
                }
            }
        }



        vector< vector<int> > x_map(row_size, vector<int>(col_size));
        vector< vector<int> > y_map(row_size, vector<int>(col_size));
        for(int i = 0; i<myBorderPixels.size();i++){
            x_map[myBorderPixels[i].first][myBorderPixels[i].second] = myBorderPixels[i].first;
            y_map[myBorderPixels[i].first][myBorderPixels[i].second] = myBorderPixels[i].second;
        }

        vector<vector<int> >kernel {
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1}
        };

        int kRow = kernel.size();
        int kCol = kernel[0].size();

        vector< vector<double> > x_map_smooth(row_size,vector<double>(col_size));
        vector< vector<double> > y_map_smooth(row_size,vector<double>(col_size));

        int kCenterX = kCol / 2;
        int kCenterY = kRow / 2;



        int count;

        for(int i=0; i < row_size; ++i) {
            for(int j=0; j < col_size; ++j) {
                if(x_map[i][j] == 0){
                    continue;
                }
                count = 0;
                for(int m=0; m < kRow; ++m) {
                    int mm = kRow - 1 - m;
                    for(int n=0; n < kCol; ++n) {
                        int nn = kCol - 1 - n;
                        int ii = i + (m - kCenterY);
                        int jj = j + (n - kCenterX);

                        if( ii >= 0 && ii < row_size && jj >= 0 && jj < col_size ){
                            x_map_smooth[i][j] += x_map[ii][jj] * kernel[mm][nn];
                            y_map_smooth[i][j] += y_map[ii][jj] * kernel[mm][nn];
                            if(x_map[ii][jj]!=0)
                                count++;
                        }
                    }
                }
                x_map_smooth[i][j] = x_map_smooth[i][j]/count;
                y_map_smooth[i][j] = y_map_smooth[i][j]/count;
            }
        }


        vector<pair<int,int>> smoothBorderPixels;
        for(int i = 0; i<myBorderPixels.size();i++){
            smoothBorderPixels.push_back(make_pair(round(x_map_smooth[myBorderPixels[i].first][myBorderPixels[i].second]),round(y_map_smooth[myBorderPixels[i].first][myBorderPixels[i].second])));
        }


        return smoothBorderPixels;

    }






    void Display_Pixels(vector<pair<int,int>> &pixels){
        int x, y;
        Mat cpy_image(image.rows, image.cols, image.type());
        image.copyTo(cpy_image);
        Vec3b *p;
        for(int i = 0; i<pixels.size();i++){
            x = pixels[i].first;
            p = cpy_image.ptr<Vec3b>(x);
            y = pixels[i].second;
            p[y][0] = 0;
            p[y][1] = 0;
            p[y][2] = 0;
        }

        namedWindow("output", WINDOW_AUTOSIZE);
        imshow("output", cpy_image);
        waitKey(0);
    }

    void Save_Pixels(string const &path_name, const Mat &image){
        imwrite(path_name, image);
    }

    friend void Serializer(ImageFunc obj);

    friend ImageFunc Deserializer(void);



};

class S_Data{
public:
    int nRows;
    int nCols;
    int type;
    int a;
    int b;
    uchar str[1000000];

};

void Serializer(ImageFunc obj){
    ofstream file;
    file.open("aaa.txt");
    S_Data data;
    int nRows = obj.image.rows;
    int nCols = obj.image.cols;
    int type = obj.image.type();
    data.nRows = nRows;
    data.nCols = nCols;
    data.type = type;
    int ix = 0;
    Vec3b *p;
    for (int i = 0; i < nRows; ++i) {
        p = obj.image.ptr<Vec3b>(i);
        for (int j = 0; j < nCols; ++j) {
            data.str[ix] = p[j][0];
            ix++;
            data.str[ix] = p[j][1];
            ix++;
            data.str[ix] = p[j][2];
            ix++;
        }
    }

    if(obj.myPixels.size()!=0){
        //cout<<obj.myPixels.size()<<endl;
        data.a = obj.a;
        data.b = obj.b;

    }
    file.write((char*)&data,sizeof(data));
    file.close();

}

ImageFunc Deserializer(void){
    ifstream file;
    file.open("aaa.txt");
    S_Data data;
    ImageFunc obj;
    file.read((char*)&data,sizeof(data));
    int nRows = data.nRows;
    int nCols = data.nCols;
    int type = data.type;

    Mat r_image(nRows, nCols, type);


    int ix = 0;
    Vec3b *p;
    for (int i = 0; i < nRows; ++i) {
        p = r_image.ptr<Vec3b>(i);
        for (int j = 0; j < nCols; ++j) {
            p[j][0] = data.str[ix];
            ix++;
            p[j][1] = data.str[ix];
            ix++;
            p[j][2] = data.str[ix];
            ix++;
        }
    }
    obj.image = r_image;

    if(data.a!=0){

        obj.a = data.a;
        obj.b = data.b;


    }
    return obj;
}


int main(int argc, char* argv[])
{
    if(string(argv[1]) == "read"){
        ImageFunc I(argv[2]);
        Serializer(I);

    }
    else if(string(argv[1])== "display_image"){
        ImageFunc I = Deserializer();
        I.DISPLAY_IMAGE();
    }
    else if(string(argv[1])== "find_region"){
        ImageFunc I = Deserializer();
        vector<pair<int, int> >myPix = I.FIND_REGION(atoi(argv[2]),atoi(argv[3]));
        I.Display_Pixels(myPix);
        Serializer(I);
    }
    else if(string(argv[1])=="find_perimeter"){
        ImageFunc I = Deserializer();
        I.FIND_REGION(I.a,I.b);
        vector<pair<int, int> >myBorder = I.FIND_PERIMETER();
        I.Display_Pixels(myBorder);
    }
    else if(string(argv[1])=="find_smooth_perimeter"){
        ImageFunc I = Deserializer();
        I.FIND_REGION(I.a,I.b);
        vector<pair<int, int> >mySmoothBorder = I.FIND_SMOOTH_PERIMETER();
        I.Display_Pixels(mySmoothBorder);
    }



    /*
    ImageFunc I("test1.png");
    I.Display_Image();
    vector<pair<int, int> >myPix = I.FIND_REGION(10,10);
    //cout<<myPix.size()<<endl;
    I.Display_Pixels(myPix);

    vector<pair<int, int> >myBorder = I.FIND_PERIMETER(myPix);
    //cout<<myBorder.size()<<endl;
    I.Display_Pixels(myBorder);

    return 0;
    */
}
