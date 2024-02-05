#include "Camera.h"

Camera::Camera(int height, int width) {
    image = Image(height, width);

	gamma = 1;
	fieldOfView = 20;
	defocusAngle = 0.6;
	focusDistance = 10;
	aspectRatio = double(width) / height;
	lookFrom = Vector3(13, 2, 3);
	lookAt = Vector3(0, 0, 0);
	verticalUp = Vector3(0, 1, 0);
	cameraCenter = lookFrom;
	focalLength = (lookFrom - lookAt).length();
	viewportHeight = 2 * tan(degToRad(fieldOfView) / 2) * focusDistance;
	viewportWidth = viewportHeight * aspectRatio;
	unitZ = (lookFrom - lookAt).unitVector();
	unitX = verticalUp.cross(unitZ).unitVector();
	unitY = unitZ.cross(unitX);
	viewportVectorX = unitX * viewportWidth;
	viewportVectorY = unitY * -viewportHeight;
    pixelDeltaX = viewportVectorX / image.width;
    pixelDeltaY = viewportVectorY / image.height;
    viewportCorner = cameraCenter - (unitZ * focusDistance) - viewportVectorX / 2 - viewportVectorY / 2;
    pixel00 = viewportCorner + (pixelDeltaX + pixelDeltaY) * 0.5;
	defocusRadius = focusDistance * tan(degToRad(defocusAngle / 2));
	defocusDiskX = unitX * defocusRadius;
	defocusDiskY = unitY * defocusRadius;
};

Vector3 Camera::getPixelCenter(int x, int y) {
    return pixel00 + (pixelDeltaX * x) + (pixelDeltaY * y);
};

Color getColor(Ray ray, HittableList scene, int depth) {
	if (depth <= 0)
		return Color(0, 0, 0);

	HitRecord hr;

	if (scene.isHit(ray, 0.001, inf, &hr)) {
		Color attenuation = Color(0, 0, 0);
		Ray scattered = Ray();
		Color* a = &attenuation;
		Ray* s = &scattered;

		if (hr.scatter(ray, hr, a, s))
			return attenuation * getColor(scattered, scene, depth-1);

		return Color(0, 0, 0);

		//return getColor(Ray(hr.point, hr.normal + randomUnitVector()), scene, depth-1) * 0.5;
	}
	else {
		Vector3 unitDirection = ray.direction.unitVector();
		double a = 0.5 * (unitDirection.y + 1);

		return Color(a, a, a);
	}
}

void Camera::renderImage(HittableList scene) {
	std::uniform_real_distribution<double> unif(0, 1);
	std::default_random_engine r;

	std::cout << "Rendering image...\n";

	int total = image.height * image.width;
	int counter = 0;

	for (int y = 0; y < image.height; ++y) {
		std::cout << "Line " << y << "\n";
		for (int x = 0; x < image.width; ++x) {
			std::cout << counter << " / " << total << "\n";
			++counter;

			Color color;

			for (int sample = 0; sample < samplesPerPixelNum; ++sample) {
				Vector3 pixelSampleSquare = pixelDeltaX * (unif(r) - 0.5) + pixelDeltaY * (unif(r) - 0.5);
				Vector3 pixelSample = getPixelCenter(x, y) + pixelSampleSquare;
				
				Vector3 rayOrigin = (defocusAngle <= 0) ? cameraCenter : defocusDiskSample(this);
				Ray ray(rayOrigin, pixelSample - rayOrigin);

				color = color + getColor(ray, scene, maxDepth) * gamma;
			}

			image.writePixel(color / samplesPerPixelNum);
		}
	}
	std::cout << "Making JPG...\n";
	image.createPNG();

	std::cout << "Image successfully created!\n";
}

Vector3 defocusDiskSample(Camera* camera) {
	Vector3 v = randomInUnitDisk();

	return camera->cameraCenter + (camera->defocusDiskX * v.x) + (camera->defocusDiskY * v.y);
}