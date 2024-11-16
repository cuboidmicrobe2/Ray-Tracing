#include <cstdint>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Disc.h"
#include "OBB.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "stb_image_write.h"
#include <vector>
#include <iostream>

int main() {
	const unsigned int width = 512;
	const unsigned int height = 512;
	const int channels = 3;
	// uint8_t = unsigned integer type consisting of 8 bits, often just unsigned
	// char in the background
	uint8_t* imageData = new uint8_t[width * height * channels];

	Shape* shapes[]{
		new Triangle(Vector3D(255, 255, 255), Vector3D(128, 64, 240), Vector3D(128 + 256, 64, 240), Vector3D(128 + 128, 512, 200)),
		new Sphere(Vector3D(255,0,0), Vector3D(256,256,256), 128),
		new OBB(Vector3D(0,0,200), Vector3D(128,200,250),Vector3D(0.7071,0.3535,-0.6124),Vector3D(0.7071,-0.3535,0.6124),Vector3D(1,0,1),50,50,50),
		new Plane(Vector3D(0,0,0), Vector3D(0,0,400), Vector3D(0,0,1))
	};

	double* distances = new double[width * height];
	std::fill(&distances[0], &distances[0] + width * height,
		std::numeric_limits<double>::infinity());

	Vector3D cameraPos(0, 0, 0);
	Vector3D cameraDirection(0, 0, 1);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < height; x++) {
			Vector3D rayOrigin = Vector3D(x, y, 0) + cameraPos;

			for (Shape* shape : shapes) {
				double distance;
				if (shape->Intersection(Ray(rayOrigin, cameraDirection), distance)) {
					if (distance < distances[y * width + x]) {
						distances[y * width + x] = distance;
						Vector3D colour = shape->GetColour();
						//colour = colour * (1 / (((distance - 150) / 100) + 1)); // Light dependent on distance
						imageData[(y * width + x) * channels] = static_cast<uint8_t>(colour.GetX());
						imageData[(y * width + x) * channels + 1] = static_cast<uint8_t>(colour.GetY());
						imageData[(y * width + x) * channels + 2] = static_cast<uint8_t>(colour.GetZ());
					}
				}
			}
		}
	}

	// This is the main function in which you should create shapes and use them to
	// ray trace a simple scene containing the shapes It is ok to create helper
	// functions and utelize them Make sure that you pass all of the automatic
	// tests before implementing this part

	// To switch which main function is being used, exclude either this file from
	// the build, or all the test files Right click file, properties,
	// configuration properties, general, exclude from build = Yes/No

	stbi_write_png("Traced.png", width, height, channels, imageData,
		width * channels);
	delete[] imageData;
	delete[] distances;

	return 0;
}