#include <sil/sil.hpp>
#include "random.hpp"

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

void circle(sil::Image& image)
{
    int width = image.width();
    int height = image.height();

    float centreX = width / 2.f;
    float centreY = height / 2.f;

    int rayonint = 100;
    int rayonext = 110;
    for (int x{0}; x < width; x++){
    for (int y{0}; y < height; y++)
    {
        float dx = x - centreX;
        float dy = y - centreY;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= rayonext && distance >= rayonint) {
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

    float centreX = width / 2.f;
    float centreY = height / 2.f;

    int rayonint = 100;
    int rayonext = 110;
    for (int x{0}; x < width; x++){
    for (int y{0}; y < height; y++)
    {
        float dx = x - centreX;
        float dy = y - centreY;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= rayonext && distance >= rayonint) {
                image.pixel(x, y) = glm::vec3(1.0f, 1.0f, 1.0f); 
            } else {
                image.pixel(x, y) = glm::vec3(0.0f, 0.0f, 0.0f); 
            }
    }
    }

    float centreX = width / 4.f;
    float centreY = height / 2.f;
    for (int x{0}; x < width; x++){
    for (int y{0}; y < height; y++)
    {
        float dx = x - centreX;
        float dy = y - centreY;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= rayonext && distance >= rayonint) {
                image.pixel(x, y) = glm::vec3(1.0f, 1.0f, 1.0f); 
            } else {
                image.pixel(x, y) = glm::vec3(0.0f, 0.0f, 0.0f); 
            }
    }
    }
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

    // {
    //     sil::Image image{"images/logo.png"}; 
    //     bruite(image); 
    //     image.save("output/bruite.png");
    // }

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
        circle(image); 
        image.save("output/circle.png");
    }
    
}