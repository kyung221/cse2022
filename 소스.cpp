#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.
void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i0 == i1) {
		for (int j = j0; j < j1; j++)
			drawPixel(i0, j, red, green, blue);
		return;
	}
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;
		drawPixel(i, j, red, green, blue);
	}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);


	// drawing a line
	//TODO: anti-aliasing
	
	for(int i0=50 ; i0<=55 ; i0++)
	{
		for (int i1 = 200; i1 <= 205; i1++)
		{
			for (int j0 = 150; j0 <= 155; j0++)
			{
				for (int j1 = 280; j1 <= 285; j1++)
					drawLine(i0, i1, j0, j1, 1.0f, 0.0f, 0.0f);
			}
		}
	}


	drawLine(50, 50, 75, 100, 1.0f, 0.0f, 0.0f);
	drawLine(75, 100, 100, 50, 1.0f, 0.0f, 0.0f);
	drawLine(50, 50, 100, 50, 1.0f, 0.0f, 0.0f);
	//triangle

	drawLine(200, 50, 250, 50, 1.0f, 0.0f, 0.0f);
	drawLine(170, 100, 200, 50, 1.0f, 0.0f, 0.0f);
	drawLine(170, 100, 225, 150, 1.0f, 0.0f, 0.0f);
	drawLine(225, 150, 280, 100, 1.0f, 0.0f, 0.0f);
	drawLine(250, 50, 280, 100,  1.0f, 0.0f, 0.0f);
	//pentagon

	drawLine(170, 200, 250, 200, 1.0f, 0.0f, 0.0f);
	drawLine(170, 200, 170, 280, 1.0f, 0.0f, 0.0f);
	drawLine(170, 280, 250, 280, 1.0f, 0.0f, 0.0f);
	drawLine(250, 200, 250, 280, 1.0f, 0.0f, 0.0f);
	//rectangle


	const int i_center = 400, j_center = 250;
	const int thickness = 45;

	for(int j=j_center-thickness;j<j_center+thickness;j++)
		for (int i = i_center - thickness; i < i_center + thickness; i++)
		{
			drawPixel(i, j, 1.0f, 0.0f, 0.0f);
		}
	

	for (int a = 0; a < width; a++)
	{
		for (int b = 0; b < height; b++)
		{
			const int c1 = 400, c2 = 70;
			const int r = 50;
			if (sqrt((c1-a)*(c1-a) + (c2-b)*(c2-b)) < r)
				drawPixel(a, b, 1.0f, 0.0f, 0.0f);
			if (sqrt((400 - a)*(400 - a) + (70 - b)*(70 - b)) < 48)
				drawPixel(a, b, 1.0f, 1.0f, 1.0f);
		}
	}
	


	
	//TODO: try moving object
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}
