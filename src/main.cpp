#include <opencv2/opencv.hpp>
#include <iostream> 


int main(){
    std::string image_path = "../data/neymar.jpg" ;
    cv::Mat image = cv::imread(image_path) ;
    
    if (image.empty()){
        std::cerr << " image non chargé \n" ; 

    }

    // sinon je donne les dimmensions de l image et ses caracteristiques 
    std::cout << "taille de l image" << image.rows << "x" << image.cols << "\n" ; 
    std::cout << "type d image " << image.type() << std::endl ; 


    //affichage 25 pixels du coin en haut a gauiche  
    for ( int i = 0 ; i < 5 ;  i++){
        for( int j =0 ; j< 5 ; j++) {
            // un pixel est de type Vec3b de la classe cv ?
            cv::Vec3b pixel = image.at<cv::Vec3b>(i,j) ; 
            std::cout << "Pixel(" << i <<"," << j << " >= "
                      << " B= " <<(int)pixel[0] 
                      << ", G =" <<(int)pixel[1]
                << " , R = " << (int)pixel[2] << " ]\n" ;
        }
    }
    
    return 0 ; 
}