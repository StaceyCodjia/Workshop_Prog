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
Utiliser la formule `0.3*image.pixel(x,y).r + 0.59*image.pixel(x,y).g + 0.11*image.pixel(x,y).b`