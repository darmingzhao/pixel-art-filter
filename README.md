# PixelArtFilter
Pixel Art Filter is an image filter that pixelates PNG images using a lossy image compression algorithm, written in C++.

![functionality1](https://user-images.githubusercontent.com/31530273/51096227-d989b480-176f-11e9-8c3b-be3d59a36daf.PNG)

![functionality2](https://user-images.githubusercontent.com/31530273/51096249-fe7e2780-176f-11e9-9caa-0967a5edcf48.PNG)

## Prerequisites
To run this project after cloning it:
### Add LodePNG
LodePNG is used to encode and deocde PNG images:
* Add lodepng.cpp and lodepng.h files from https://lodev.org/lodepng/ to the util/lodepng/ folder
### Clang
Clang is used to compile the project:
* Installing clang on a local machine is different depending on the OS
* A tutorial can be found online

## Deployment
To compile the project, use the command:
```
make
```
And once that is finished, run the project using:
```
./paf
```
Once this is completed the output will be in the images/ folder.

You can also remove the compiler output values by running the command:
```
make clean
```

##Create different effects
To add your own images, add PNG files to the images/ folder.

Go to main.cpp and change the following parameters to the new image names
```C++
origImg1.readFromFile("images/starry-night.png");
origImg2.readFromFile("images/mona-lisa.png");
origImg3.readFromFile("images/hokusai.png");
```
To play with the pixelation effect, modify the parameters for:
```C++
t1.prune(0.99, 8500);
t2.prune(0.99, 8500);
t3.prune(0.95, 8500);
```
Finally, to change the output image names, change the following parameters:
```C++
pic1.writeToFile("images/output-starry-night.png");
pic2.writeToFile("images/output-mona-lisa.png");
pic3.writeToFile("images/output-hokusai.png");
```
