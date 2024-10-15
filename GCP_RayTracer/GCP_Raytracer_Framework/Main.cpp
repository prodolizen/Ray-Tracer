
#include "GCP_GFX_Framework.h"
#include "Camera.h"
#include "RayTracer.h"

int main(int argc, char* argv[])
{
	// Set window size
	glm::ivec2 winSize(640, 480);

	Camera _camera;
	_camera.SendWinSize(winSize);

	RayTracer _rayTracer;

	Sphere ssss;

	// This will handle rendering to screen
	GCP_Framework _myFramework;

	// Initialises SDL and OpenGL and sets up a framebuffer
	if (!_myFramework.Init(winSize))
	{
		return -1;
	}

	//big loop to cycle through every pixel in the screen
	for (int x = 0; x < winSize.x; x++)
	{
		for (int y = 0; y < winSize.y; y++)
		{
			Ray _ray = _camera.GetRay(glm::vec2(x, y));
			glm::vec3 _colour = _rayTracer.TraceRay(_ray, ssss);
		}
	}


	// Preparing a position to draw a pixel
	glm::ivec2 pixelPosition = winSize / 2;

	// Preparing a colour to draw
	// Colours are RGB, each value ranges between 0 and 1
	glm::vec3 pixelColour(1, 0, 0);


	// Sets all pixels the same colour
	_myFramework.SetAllPixels( glm::vec3(0.1f,0.1f,0.3f) );

	// Draws a single pixel
	_myFramework.DrawPixel(pixelPosition, pixelColour);



	// Pushes the framebuffer to OpenGL and renders to screen
	// Also contains an event loop that keeps the window going until it's closed
	_myFramework.ShowAndHold();
	return 0;


}
