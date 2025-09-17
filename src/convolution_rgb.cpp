#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    //  Charger l’image couleur
    Mat image = imread("../data/neymar.jpg");

    if (image.empty()) {
        cerr << "Erreur de chargement de l'image." << endl;
        return -1;
    }

    //  Créer une image de sortie de même taille
    Mat result = Mat::zeros(image.size(), image.type());

    // 🔹 Définir le noyau (kernel) 3x3
   vector<vector<float>> kernel = {
    { -1, -2, -1 },
    {  0,  0,  0 },
    {  1,  2,  1 }
};



    int kernelSize = 3;
    int offset = kernelSize / 2;

    //  Parcourir chaque pixel (sauf les bords pour l’instant)
    for (int y = offset; y < image.rows - offset; y++) {
        for (int x = offset; x < image.cols - offset; x++) {

            // Initialiser les 3 canaux à zéro
            float sumB = 0.0, sumG = 0.0, sumR = 0.0;

            //  Appliquer la convolution dans une fenêtre 3x3
            for (int ky = 0; ky < kernelSize; ky++) {
                for (int kx = 0; kx < kernelSize; kx++) {
                    // TODO : Récupérer le pixel voisin à (x + dx, y + dy)
                    Vec3b pixel = image.at<Vec3b>(y+ky -1 , x +kx -1) ; 

                    // TODO : Multiplier chaque canal (R, G, B) par kernel[ky][kx]
    
                    // TODO : Ajouter aux sommes sumB, sumG, sumR
                    float coef = kernel[ky][kx] ;
                    sumB += pixel[0] *coef ; 
                    sumG += pixel[1] *coef ; 
                    sumR += pixel[2] *coef ; 



                }
            }

            // Clipper les résultats entre 0 et 255
            sumB = min(max(int(sumB), 0), 255);
            sumG = min(max(int(sumG), 0), 255);
            sumR = min(max(int(sumR), 0), 255);

            //  Placer le nouveau pixel dans l’image résultat
            result.at<Vec3b>(y, x) = Vec3b(sumB, sumG, sumR);
        }
    }

    // 🔹 Sauvegarder l’image traitée
    imwrite("../results/convolution_rgb.jpg", result);

    cout << "✅ Convolution couleur terminée." << endl;
    return 0;
}
