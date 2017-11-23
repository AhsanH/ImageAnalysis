# ImageAnalysis
Implement C++ class(es) to perform "find region", "find perimeter", "display image", and "display pixels" operations:


How to input image via command line
-------------------------------------------
Example: ImageAnalysis read test1.png

How to find segmented region via command line
-------------------------------------
Example: ImageAnalysis find_region 100 100
Here, the last two number are the x,y coordinate of the seed point


How to find the perimeter via command line
-----------------------------------
Example: ImageAnalysis find_perimeter


How to find the smooth perimeter via command line
-----------------------------------
Example: ImageAnalysis find_smooth_perimeter


Similarity parameter of the FIND_REGION member function
-----------------------------------------
A threshold,t is first declared where t = 10
Neighboring pixel whose Red, Green and Blue component lies with in the threshold range from the corresponding component of the seed pixel are accepted into the growing region.

Blue, Red and Green component of the neighboring pixel: B_n, R_n, and G_n;
Blue, Red and Green component of the seed pixel: B_s, R_s, and G_s;

then the neighboring pixel is accepted into the region if
(abs(B_n-B_s)<t)&&(abs(R_n-R_s)<t)&&(abs(G_n-G_s)<t)

Improvment for the FIND_SMOOTH_PERIMETER
------------------------------------------
IF Gaussian kernel is used

