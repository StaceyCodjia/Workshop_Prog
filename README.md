- [🐣 S1 | Prog: Workshop : Rapport](#-s1--prog-workshop--rapport)
  - [⭐ Ne garder que le vert](#-ne-garder-que-le-vert)
  - [⭐ Échanger les canaux](#-échanger-les-canaux)
  - [⭐ Noir \& Blanc](#-noir--blanc)
  - [⭐ Négatif](#-négatif)
  - [⭐ Dégradé](#-dégradé)
  - [⭐⭐ Miroir](#-miroir)
  - [⭐⭐ Image bruitée](#-image-bruitée)
  - [⭐⭐ Rotation de 90°](#-rotation-de-90)
  - [⭐⭐ RGB split](#-rgb-split)
  - [⭐⭐ Luminosité](#-luminosité)

# 🐣 S1 | Prog: Workshop : Rapport

## ⭐ Ne garder que le vert
![](./output/keep_green_only.png)

## ⭐ Échanger les canaux
![](./output/echange.png)  
Pour ce exo j'ai utilisé la fonction `std::swap()` :
```cpp
std::swap(image.pixel(x,y).r, image.pixel(x,y).b);
```

## ⭐ Noir & Blanc
![](./output/black_white.png)  
Utilisation de la formule `0.3*image.pixel(x,y).r + 0.59*image.pixel(x,y).g + 0.11*image.pixel(x,y).b` pour obtenir les tons gris.

## ⭐ Négatif
![](./output/negative.png)  
```cpp
image.pixel(x,y).r = 1 - image.pixel(x,y).r;
``` 

## ⭐ Dégradé
![](./output/gradient.png)  
```cpp
image.pixel(x, y) = glm::vec3 (static_cast<float>(x) / static_cast<float>(image.width() - 1));
``` 


## ⭐⭐ Miroir
![](./output/mirror.png)  
```cpp
glm::vec3& leftPixel = image.pixel(x,y);
glm::vec3& rightPixel = image.pixel(width - 1 - x, y);
std::swap(leftPixel,rightPixel);
```

## ⭐⭐ Image bruitée
![](./output/bruite.png)  
Utilisation de `rand()` pour changer aléatoirement les pixels.

## ⭐⭐ Rotation de 90°
![](./output/rotation.png)  
```cpp
new_image.pixel(height - 1 - y, x) = image.pixel(x,y);
```

## ⭐⭐ RGB split
![](./output/split.png)  
Utilisation de conditions ternaires pour décaler les pixels :  
```cpp
glm::vec3 leftpix = (x >= val) ? image.pixel(x - val, y) : image.pixel(x,y);
glm::vec3 rightpix = (x < width - val) ? image.pixel(x + val, y) : image.pixel(x,y);
```

## ⭐⭐ Luminosité
![](./output/luminosite_dark.png)  ![](./output/luminosite_light.png)  
