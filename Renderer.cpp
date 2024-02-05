#include "Image.h"
#include "Camera.h"
#include "Ray.h"
#include "Color.h"
#include "Sphere.h"
#include "Util.h"
#include "HittableList.h"
#include <iostream>
#pragma once

void main() {
	HittableList scene;
	//Camera camera(224, 400);
	Camera camera(900, 1600);
	camera.samplesPerPixelNum = 35;
	camera.maxDepth = 15;

	scene.add(Sphere(0, -1000, 0, 1000, "lambertian", Color(0.5, 0.5, 0.5), 1));

	/*
	scene.add(Sphere(-1, 0, 0, 0.5, "dielectric", Color(0.6, 0.6, 0.8), 0.8));
	scene.add(Sphere(-1, 0, 0, 0.4, "dielectric", Color(0.6, 0.6, 0.8), -0.8));
	scene.add(Sphere(0, 0, 0, 0.5, "lambertian", Color(0.6, 0.8, 0.6), 1));
	scene.add(Sphere(1, 0, 0, 0.5, "metal", Color(0.8, 0.6, 0.6), 0.2));
	*/

    for (int a = -6; a < 6; a++) {
        for (int b = -6; b < 6; b++) {
            auto randNum = randomDouble();
            Vector3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if ((center - Vector3(4, 0.2, 0)).length() > 0.9) {
                if (randNum < 0.8) {
                    // diffuse
                    Color materialColor = Color(randomDouble(), randomDouble(), randomDouble()) * Color(randomDouble(), randomDouble(), randomDouble());
                    scene.add(Sphere(center, 0.2, "lambertian", materialColor, 1));
                }
                else if (randNum < 0.95) {
                    // metal
                    Color materialColor = Color(randomDouble(), randomDouble(), randomDouble()) * Color(randomDouble(), 0.5, 1);
                    double metalFuzz = randomDouble();
                    scene.add(Sphere(center, 0.2, "lambertian", materialColor, metalFuzz));
                }
                else {
                    // glass
                    Color materialColor = Color(0.85, 0.85, 0.85);
                    scene.add(Sphere(center, 0.2, "dielectric", materialColor, 1.5));
                }
            }
        }
    }

    scene.add(Sphere(0, 1, 0, 1, "dielectric", Color(0.9, 0.9, 0.9), 1.5));
    scene.add(Sphere(-4, 1, 0, 1, "lambertian", Color(0.4, 0.2, 0.1), 1));
    scene.add(Sphere(4, 1, 0, 1, "metal", Color(0.7, 0.6, 0.5), 0));

	camera.renderImage(scene);
	std::cout << "\n";
}