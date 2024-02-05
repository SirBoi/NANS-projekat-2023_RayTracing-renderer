#include "Vector3.h"
#include "Image.h"
#include "HittableList.h"
#include "Util.h"
#include <random>
#pragma once

struct Camera {
    double focalLength;
    double viewportHeight;
    double viewportWidth;
    double aspectRatio;
    double fieldOfView;
    double gamma;
    double defocusAngle;
    double focusDistance;
    int samplesPerPixelNum;
    int maxDepth;
    Vector3 lookFrom;
    Vector3 lookAt;
    Vector3 verticalUp;
    Vector3 viewportVectorX;
    Vector3 viewportVectorY;
    Vector3 pixelDeltaX;
    Vector3 pixelDeltaY;
    Vector3 unitX;
    Vector3 unitY;
    Vector3 unitZ;
    Vector3 viewportCorner;
    Vector3 pixel00;
    Vector3 cameraCenter = Vector3(0, 0, 0);
    Vector3 defocusDiskX;
    Vector3 defocusDiskY;
    double defocusRadius;
    Image image;

    Camera(Image);
    Camera(int, int);
    Camera(Image, double, double);
    Camera(Image, double, double, double);

    Vector3 getPixelCenter(int, int);
    void renderImage(HittableList);
};

Vector3 defocusDiskSample(Camera*);