#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>


/* this function apply an convolution computing on an input image 
** input = the input image on grayscale 
** kernel = the filter , is a 3*3 matrix that say how to combine pixels 
*/

cv::Mat applyConvolution(const cv::Mat& input , const std::vector<std::vector<int>>& kernel , int divisor){
    int rows = input.rows ; 
    int cols = input.cols ; 
    cv::Mat output = input.clone() ; 

    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j){
            int sum = 0 ; 
            for(int ki = -1 ; ki <= 1 ; ki++){
                for( int kj= -1 ; kj<= 1 ; kj++){
                    int pixel = input.at<uchar>(i+ki, j+kj); // i + ki est dasn [0, 2]
                    int coef = kernel[ki +1][kj + 1] ; 
                    sum += pixel *coef ; 
                }
            }
            // clamp the value to [0 , 255]
            output.at<uchar>(i,j) = cv::saturate_cast<uchar>(sum/divisor) ; 
        }
    }
    return output ; 
}


int main(){
    std::string path = "../data/neymar.jpg";
    cv::Mat image = cv::imread(path, cv::IMREAD_GRAYSCALE);

    if (image.empty()) {
        std::cerr << "Image non trouvée.\n";
        return -1;
    }

    //filtre 
    std::vector<std::vector<int>> blur_kernel = {
        {1, 1, 1},
        {1, 1 , 1},
        {1, 1, 1}
    };
    // Filtre de contours (Sobel horizontal)
    std::vector<std::vector<int>> edge_kernel = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    cv::Mat blurred = applyConvolution( image , blur_kernel, 9) ; 
    cv::Mat edges = applyConvolution( image , edge_kernel, 1) ; 

    cv::imwrite("../results/blurred.jpg", blurred);
    cv::imwrite("../results/edges.jpg", edges);
    std::cout << "Filtres appliqués et images sauvegardées.\n";
    return 0;
}