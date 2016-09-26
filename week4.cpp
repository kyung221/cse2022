#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 800;
const int height = 480;

float* pixels = new float[width*height * 3];


void drawCircle2(const int&i, const int&j, const int&k);

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}
void drawCircle(const int&i, const int&j, const int&k)
{
	for (int a = 0; a < width; a++)
	{
		for (int b = 0; b < height; b++)
		{
			
			if (sqrt((i - a)*(i - a) + (j - b)*(j - b)) < k)
				drawPixel(a, b, 1.0f, 0.0f, 0.0f);
			if (sqrt((i - a)*(i - a) + (j - b)*(j - b)) < k-2)
				drawPixel(a, b, 1.0f, 1.0f, 1.0f);
		}
	}
}
void drawCircle2(const int&i, const int&j, const int&k)
{
	for (int a = 0; a < width; a++)
	{
		for (int b = 0; b < height; b++)
		{
			
			if (sqrt((i - a)*(i - a) + (j - b)*(j - b)) < k)
				drawPixel(a, b, 0.0f, 0.0f, 1.0f);
			if (sqrt((i - a)*(i - a) + (j - b)*(j - b)) < k - 2)
				drawPixel(a, b, 1.0f, 1.0f, 1.0f);
		}
	}
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

	
	
	//TODO: try moving object
}

int main(void)
{
	GLFWwindow* window;
	double xpos, ypos;

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
		glfwGetCursorPos(window, &xpos, &ypos);

		drawCircle(100, 100, 50);
		double f1 = (xpos - 100)*(xpos - 100) + (ypos - 380)*(ypos - 380) - 50 * 50;
		if (f1 <= 0.0)
			drawCircle2(100, 100, 50);
		drawLine(80, 100, 120, 100, 1.0f, 0.0f, 0.0f);
		drawLine(110, 110, 120, 100, 1.0f, 0.0f, 0.0f);
		drawLine(110, 90, 120, 100, 1.0f, 0.0f, 0.0f);
		

		

		drawCircle(250, 100, 50);
		double f2 = (xpos - 250)*(xpos - 250) + (ypos - 380)*(ypos - 380) - 50 * 50;
		if (f2 <= 0.0)
			drawCircle2(250, 100, 50);
		drawLine(230, 80, 250, 120, 1.0f, 0.0f, 0.0f);
		drawLine(250, 120, 270, 80, 1.0f, 0.0f, 0.0f);
		drawLine(240, 100, 260, 100, 1.0f, 0.0f, 0.0f);

		drawCircle(400, 100, 50);
		double f3 = (xpos - 400)*(xpos - 400) + (ypos - 380)*(ypos - 380) - 50 * 50;
		if (f3 <= 0.0)
			drawCircle2(400, 100, 50);
		drawLine(400, 70, 400, 130, 1.0f, 0.0f, 0.0f);

		drawCircle(550, 100, 50);
		double f4 = (xpos - 550)*(xpos - 550) + (ypos - 380)*(ypos - 380) - 50 * 50;
		if (f4 <= 0.0)
			drawCircle2(550, 100, 50);
		drawLine(530, 100, 570, 100, 1.0f, 0.0f, 0.0f);
		drawLine(530, 100, 540, 110, 1.0f, 0.0f, 0.0f);
		drawLine(530, 100, 540, 90, 1.0f, 0.0f, 0.0f);

		drawCircle(700, 100, 50);
		double f5 = (xpos - 700)*(xpos - 700) + (ypos - 380)*(ypos - 380) - 50 * 50;
		if (f5 <= 0.0)
			drawCircle2(700, 100, 50);
		drawLine(700, 80, 700, 120, 1.0f, 0.0f, 0.0f);
		drawLine(690, 110, 700, 120, 1.0f, 0.0f, 0.0f);
		drawLine(700, 120, 710, 110, 1.0f, 0.0f, 0.0f);

		drawCircle(100, 300, 50);
		double f6 = (xpos - 100)*(xpos - 100) + (ypos - 180)*(ypos - 180) - 50 * 50;
		if (f6 <= 0.0)
			drawCircle2(100, 300, 50);
		for (int i0 = 80; i0 <= 82; i0++)
		{
			for (int i1 = 280; i1 <= 282; i1++)
			{
				for (int j0 = 120; j0 <= 122; j0++)
				{
					for (int j1 = 320; j1 <= 322; j1++)
						drawLine(i0, i1, j0, j1, 1.0f, 0.0f, 0.0f);
				}
			}
		}

		drawCircle(250, 300, 50);
		double f7 = (xpos - 250)*(xpos - 250) + (ypos - 180)*(ypos - 180) - 50 * 50;
		if (f7 <= 0.0)
			drawCircle2(250, 300, 50);
		drawCircle(250, 300, 20);
		

		drawCircle(400, 300, 50);
		double f8 = (xpos - 400)*(xpos - 400) + (ypos - 180)*(ypos - 180) - 50 * 50;
		if (f8 <= 0.0)
			drawCircle2(400, 300, 50);
		drawLine(380, 280, 420, 280, 1.0f, 0.0f, 0.0f);
		drawLine(380, 280, 380, 320, 1.0f, 0.0f, 0.0f);
		drawLine(380, 320, 420, 320, 1.0f, 0.0f, 0.0f);
		drawLine(420, 280, 420, 320, 1.0f, 0.0f, 0.0f);

		drawCircle(550, 300, 50);
		double f9 = (xpos - 550)*(xpos - 550) + (ypos - 180)*(ypos - 180) - 50 * 50;
		if (f9 <= 0.0)
			drawCircle2(550, 300, 50);
		drawLine(530, 280, 570, 320, 1.0f, 0.0f, 0.0f);
		drawLine(530, 320, 570, 280, 1.0f, 0.0f, 0.0f);


		drawCircle(700, 300, 50);
		double f10 = (xpos - 700)*(xpos - 700) + (ypos - 180)*(ypos - 180) - 50 * 50;
		if (f10 <= 0.0)
			drawCircle2(700, 300, 50);
		drawLine(700, 280, 700, 320, 1.0f, 0.0f, 0.0f);
		drawLine(690, 290, 700, 280, 1.0f, 0.0f, 0.0f);
		drawLine(700, 280, 710, 290, 1.0f, 0.0f, 0.0f);
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