#include <opencv2/opencv.hpp>
#include <iostream>


int main(){
    std::string image_path = "../data/neymar.jpg" ; 
    cv::Mat image = cv::imread(image_path) ; 

    if(image.empty()){
        std::cerr << " image non trouvée"<< std::endl  ; 
        return -1 ; 
    }
    //on clone l image originale 
    cv::Mat inverted = image.clone() ; 
    cv::Mat grayscale(image.rows , image.cols, CV_8UC1) ; 


    for( int i = 0 ; i  <= image.rows ;i ++){
        for(int j = 0 ; j < image.cols ; j ++) {

            cv::Vec3b pixel = image.at<cv::Vec3b>(i,j) ; 

            inverted.at<cv::Vec3b>(i,j)[0] = 255 - pixel[0] ; //B
            inverted.at<cv::Vec3b>(i,j)[1] = 255 - pixel[1] ; // G
            inverted.at<cv::Vec3b>(i,j)[2] = 255 - pixel[2]  ; //R
            // Grayscale manuelle
            uchar gray = static_cast<uchar>(0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0]);
            grayscale.at<uchar>(i, j) = gray;
        }
    }

    cv::imwrite("../results/neymar_inveted.jpg", inverted) ; 
    cv::imwrite("../results/neymar_grayscale.jpg", grayscale) ; 
    std::cout << "Images générées et sauvegardées dans /results/\n";
    return 0;
}