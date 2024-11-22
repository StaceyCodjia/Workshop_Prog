#include <sil/sil.hpp>
#include "random.hpp"
#include <algorithm>
#include <iostream>

void keep_green_only(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++)
{
    for (int y{0}; y < image.height(); y++)
    {
        image.pixel(x, y).r = 0.f; 
        image.pixel(x, y).b = 0.f;
        
    }
}
}

void echange(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++){
    for (int y{0}; y < image.height(); y++)
    {
        std::swap(image.pixel(x,y).r, image.pixel(x,y).b);
        
    }
    }
}

void black_white(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++)
{
    for (int y{0}; y < image.height(); y++)
    {
      float gray = static_cast<float>(0.3*image.pixel(x,y).r 
                                            + 0.59*image.pixel(x,y).g 
                                            + 0.11*image.pixel(x,y).b);
        image.pixel(x,y).r = gray;  
        image.pixel(x,y).b = gray;   
        image.pixel(x,y).g = gray;                                 
    
    }
}
}

void negative(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++)
{
    for (int y{0}; y < image.height(); y++)
    {
        image.pixel(x,y).r = 1 - image.pixel(x,y).r;
        image.pixel(x,y).b = 1 - image.pixel(x,y).b;
        image.pixel(x,y).g = 1 - image.pixel(x,y).g;
    }
}
}

void gradient() {
    sil::Image image{300, 200};

    for(int x{0}; x < image.width(); x++) {
        for(int y{0}; y < image.height(); y++) {
            image.pixel(x, y) = glm::vec3 (static_cast<float>(x) / static_cast<float>(image.width() - 1));
        }
    }
    image.save("output/gradient.png");
}

void mirror(sil::Image& image)
{
    int width = image.width();
    for(int x{0}; x < image.width() / 2; x++) {
        for(int y{0}; y < image.height(); y++) {
        glm::vec3& leftPixel = image.pixel(x,y);
        glm::vec3& rightPixel = image.pixel(width - 1 - x, y);
        std::swap(leftPixel,rightPixel);    
        }
    }
}

void bruite(sil::Image& image )
{ 
    int numpixel=50000;
    int width = image.width();
    int height = image.height();
   std::srand(std::time(0));
   for(int i = 0 ; i < numpixel ; i++)
   {
    int x = std::rand() % width;
    int y = std::rand() % height;

    glm::vec3 randomcolor (static_cast<float>(std::rand()) / RAND_MAX, 
                                static_cast<float>(std::rand()) / RAND_MAX,
                                    static_cast<float>(std::rand()) / RAND_MAX
                            );
    
    image.pixel(x,y) = randomcolor;
   }
}

void rotation(sil::Image& image)
{
    int height = image.height();
    int width = image.width();
    sil::Image new_image{height, width};
    for(int x{0}; x < width; x++) {
        for(int y{0}; y < height; y++) {
         new_image.pixel(height - 1 - y, x) = image.pixel(x,y);
        }
    }  
    image = new_image;
}

void split(sil::Image& image)
{
    int val = 20;
    int width = image.width();
    int height = image.height();

    sil::Image splitImg (width,height);

    for (int x{0}; x < width; x++){
    for (int y{0}; y < height; y++)
    {
    glm::vec3 leftpix = (x >= val) ? image.pixel(x - val, y) : image.pixel(x,y);
    glm::vec3 rightpix = (x < width - val) ? image.pixel(x + val, y) : image.pixel(x,y);

    glm::vec3 newcolor (rightpix.r, image.pixel(x,y).g, leftpix.b);

    splitImg.pixel(x,y) = newcolor;
    }
    }
    image = splitImg;
}

void luminosite_dark(sil::Image& image)
{
    // float puissance = 2;
    int width = image.width();
    int height = image.height();

    for (int x{0}; x < width; x++){
    for (int y{0}; y < height; y++)
    {
        glm::vec3 newPixel(
                std::pow(image.pixel(x,y).r, 2),
                std::pow(image.pixel(x,y).g, 2),
                std::pow(image.pixel(x,y).b, 2)
        );
        image.pixel(x,y) = newPixel;
    }
    }
}

void luminosite_light(sil::Image& image)
{
    int width = image.width();
    int height = image.height();

    for (int x{0}; x < width; x++){
    for (int y{0}; y < height; y++)
    {
        glm::vec3 newPixel(
                std::pow(image.pixel(x,y).r, 0.4),
                std::pow(image.pixel(x,y).g, 0.4),
                std::pow(image.pixel(x,y).b, 0.4)
        );
        image.pixel(x,y) = newPixel;
    }
    }
}

void disk(sil::Image& image)
{
    int width = image.width();
    int height = image.height();

    float centreX = width / 2.f;
    float centreY = height / 2.f;

    for (int x{0}; x < width; x++){
    for (int y{0}; y < height; y++)
    {
        float dx = x - centreX;
        float dy = y - centreY;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= 150) {
                image.pixel(x, y) = glm::vec3(1.0f, 1.0f, 1.0f); 
            } else {
                image.pixel(x, y) = glm::vec3(0.0f, 0.0f, 0.0f); 
            }
    }
    }
}

void circle(sil::Image& image, float centreX, float centreY,int rayonint = 100,int rayonext = 105)
{
    int width = image.width();
    int height = image.height();

    for (int x{0}; x < width; x++){
    for (int y{0}; y < height; y++)
    {
        float dx = x - centreX;
        float dy = y - centreY;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= rayonext && distance >= rayonint) {
                image.pixel(x, y) = glm::vec3(1.0f, 1.0f, 1.0f); 
        }
            
    }
    }

    
}

void disk_0(sil::Image& image)
{
    int width = image.width();
    int height = image.height();

    float centreX = 0;
    float centreY = height / 2.f;

    for (int x{0}; x < width; x++){
    for (int y{0}; y < height; y++)
    {
        float dx = x - centreX;
        float dy = y - centreY;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= 150) {
                image.pixel(x, y) = glm::vec3(1.0f, 1.0f, 1.0f); 
            } else {
                image.pixel(x, y) = glm::vec3(0.0f, 0.0f, 0.0f); 
            }
    }
    }
}

void disk_1(sil::Image& image)
{
    int width = image.width();
    int height = image.height();

    float centreX = width;
    float centreY = height / 2.f;

    for (int x{0}; x < width; x++){
    for (int y{0}; y < height; y++)
    {
        float dx = x - centreX;
        float dy = y - centreY;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= 150) {
                image.pixel(x, y) = glm::vec3(1.0f, 1.0f, 1.0f); 
            } else {
                image.pixel(x, y) = glm::vec3(0.0f, 0.0f, 0.0f); 
            }
    }
    }
}

void rosace(sil::Image& image)
{
    int width = image.width();
    int height = image.height();
    int rayonint = 100;
    int rayonext = 105;
    float centreX = width / 2.f;
    float centreY = height / 2.f;

    circle(image, centreX, centreY);

    float offset = rayonext;

    for (int i = 0; i < 6; i++) {
            float angle = i * M_PI / 3.0f; 
            float newCenterX = centreX + offset * std::cos(angle);
            float newCenterY = centreY + offset * std::sin(angle);

            
            circle(image, newCenterX, newCenterY);
        }



}

void mosaique(sil::Image& image)
{
    int new_width = image.width() * 5;
    int new_height = image.height() * 5;

    sil::Image new_image{new_width, new_height};

    for (int x = 0; x < new_width; ++x)
    {
        for (int y = 0; y < new_height; ++y)
        {
            int old_x = x % image.width();
            int old_y = y % image.height();

            new_image.pixel(x, y) = image.pixel(old_x, old_y);
        }
    }
    image = new_image;
}

void mosaique_mirror(sil::Image& image){

    sil::Image mosaique{image.width() * 5, image.height() * 5};

    for(int x{0}; x < mosaique.width(); x++) 
    {
        for(int y{0}; y < mosaique.height(); y++)
        {
            int old_x {x % image.width()};
            int old_y {y % image.height()};

            bool mirrorX {(x / image.width()) % 2 == 1};
            bool mirrorY {(y / image.height()) % 2 == 1}; 

            if (mirrorX) {
                old_x = image.width() - old_x - 1;
            }
            if (mirrorY) {
                old_y = image.height() - old_y - 1;
            }

            mosaique.pixel(x, y) = image.pixel(old_x, old_y);
        }
    }
    image = mosaique;
}

void glitch(sil::Image& image)
{
    std::srand(std::time(0));

    int width = image.width();
    int height = image.height();

    for (int i = 0; i < 50; ++i) {
        
        int rectWidth = std::rand() % (width / 10) + 1;  
        int rectHeight = std::rand() % (height / 10) + 1; 

        int x1 = std::rand() % (width - rectWidth);
        int y1 = std::rand() % (height - rectHeight);
        int x2 = std::rand() % (width - rectWidth);
        int y2 = std::rand() % (height - rectHeight);

        for (int y = 0; y < rectHeight; ++y) {
            for (int x = 0; x < rectWidth; ++x) {
                std::swap(image.pixel(x1 + x,y1 + y), image.pixel(x2 + x,y2 + y));
            }
        }    
    }
}

// Tri de pixels
float brightness(glm::vec3 const&color){
    float gray = color.r * 0.21 + color.g *0.72 + color.b *0.07;

    return gray;
}
void pixel_sorting(sil::Image& image){
    for (int i=0; (i + 70) < image.pixels().size(); i++)
    {
        if (random_int(0, 150) == 75){
            std::sort(image.pixels().begin() + i, image.pixels().begin() + (i + 70), [](glm::vec3 const& color1, glm::vec3 const& color2)
            {
            return brightness(color1) > brightness(color2);
            });
            i = i + 70;
        }
    }
}


void normalizing_histogram(sil::Image& image){
    
    float darkest = 1.f;
    float whitest = 0.f;
    for (int x{0}; x < image.width(); x++) {
        for (int y{0}; y < image.height(); y++) {

            glm::vec3 &pixel = image.pixel(x, y);
            float lum = brightness(pixel);
            if(lum < darkest){
                // si lum est + sombre que darkest, alors on remplace darkesst par lum
                darkest = lum;
            }
            
            else if (lum > whitest){
                whitest = lum;
            }

            float normalizedLum = (lum - darkest) / (whitest - darkest);
            pixel = pixel * (normalizedLum / lum);
        }
    }
    std::cout << darkest << std::endl;
    std::cout << whitest << std::endl;

}

int main()
{
    {
        sil::Image image{"images/logo.png"}; 
        keep_green_only(image); 
        image.save("output/keep_green_only.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        echange(image); 
        image.save("output/echange.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        black_white(image); 
        image.save("output/black_white.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        negative(image); 
        image.save("output/negative.png");
    }

    {
        gradient(); 
    }
        
    {
        sil::Image image{"images/logo.png"}; 
        mirror(image); 
        image.save("output/mirror.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        bruite(image); 
        image.save("output/bruite.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        rotation(image); 
        image.save("output/rotation.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        split(image); 
        image.save("output/split.png");
    }

    {
        sil::Image image{"images/photo.jpg"}; 
        luminosite_dark(image); 
        image.save("output/luminosite_dark.png");
    }

    {
        sil::Image image{"images/photo.jpg"}; 
        luminosite_light(image); 
        image.save("output/luminosite_light.png");
    }

    {
        sil::Image image{500, 500};
        disk(image); 
        image.save("output/disk.png");
    }

    {
        
        sil::Image image{500, 500};
        circle(image, image.width()/2, image.height()/2); 
        image.save("output/circle.png");
    }

    {
        sil::Image image{500, 500};
        disk_0(image); 
        image.save("output/disk_0.png");
    }

    {
        sil::Image image{500, 500};
        disk_1(image); 
        image.save("output/disk_1.png");
    }

    {
        sil::Image image{500, 500};
        rosace(image); 
        image.save("output/rosace.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        mosaique(image); 
        image.save("output/mosaique.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        mosaique_mirror(image); 
        image.save("output/mosaique_mirror.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        glitch(image); 
        image.save("output/glitch.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        pixel_sorting(image); 
        image.save("output/pixel_sorting.png");
    }
    
    {
        sil::Image image{"images/photo_faible_contraste.jpg"}; 
        normalizing_histogram(image); 
        image.save("output/normalizing_histogram.png");
    }

}