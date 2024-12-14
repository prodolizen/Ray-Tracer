
#include "GCP_GFX_Framework.h"
#include "Camera.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Ray.h"

GCP_Framework _myFramework;

void createCircle(int x_centre, int y_centre, int radius)
{
	glm::ivec2 pixelPosition = glm::ivec2(0, 0);
	glm::vec3 pixelColour(0, 255, 0);

	int x = radius, y = 0;

	if (radius > 0) //only creates circle if radius is more than zero 
	{
		pixelPosition = glm::ivec2(x + x_centre, -y + y_centre);
		_myFramework.DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(y + x_centre, x + y_centre);
		_myFramework.DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(-y + x_centre, x + y_centre);
		_myFramework.DrawPixel(pixelPosition, pixelColour);
	}

	int perimiter = 1 - radius;
	while (x > y)
	{
		y++;

		if (perimiter <= 0) //midpoint is in/on perimiter
		{
			perimiter = perimiter + 2 * y + 1;
		}

		else //midpoint is outside perimiter
		{
			x--;
			perimiter = perimiter + 2 * y - 2 * x + 1;
		}

		// All the perimeter points have already been printed
		if (x < y)
			break;

		//below prints the generated points and reflects them into the other octants. This works because a circles point of symmetry is the center
		pixelPosition = glm::ivec2(x + x_centre, y + y_centre);
		_myFramework.DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(-x + x_centre, y + y_centre);
		_myFramework.DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(x + x_centre, -y + y_centre);
		_myFramework.DrawPixel(pixelPosition, pixelColour);
		pixelPosition = glm::ivec2(-x + x_centre, -y + y_centre);
		_myFramework.DrawPixel(pixelPosition, pixelColour);

		if (x != y) //if x != y then perimeter points havent been printed 
		{
			pixelPosition = glm::ivec2(y + x_centre, x + y_centre);
			_myFramework.DrawPixel(pixelPosition, pixelColour);
			pixelPosition = glm::ivec2(-y + x_centre, x + y_centre);
			_myFramework.DrawPixel(pixelPosition, pixelColour);
			pixelPosition = glm::ivec2(y + x_centre, -x + y_centre);
			_myFramework.DrawPixel(pixelPosition, pixelColour);
			pixelPosition = glm::ivec2(-y + x_centre, -x + y_centre);
			_myFramework.DrawPixel(pixelPosition, pixelColour);
		}
	}
}


int main(int argc, char* argv[])
{
	// Set window size
	glm::ivec2 winSize(640, 480);

	Camera _camera;
	_camera.SendWinSize(winSize);
	_camera.Init();
	_camera._Position = glm::vec3(300, 300, 200); //temp

	RayTracer _rayTracer;
	_rayTracer.lightPos = glm::vec3(200, 300, 6000); //set light position in ray tracer
	_rayTracer.lightColour = glm::vec3(1, 1, 1); //set light colour

	Sphere _sphere1;
	Sphere _sphere2;
	
	// This will handle rendering to screen
	//GCP_Framework _myFramework;

	// Initialises SDL and OpenGL and sets up a framebuffer
	if (!_myFramework.Init(winSize))
	{
		return -1;
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

	//sphere 1
	glm::vec3 sphere1pos = glm::vec3(400, winSize.y / 2, 0);
	int _sphere1radius = 100;

	createCircle(sphere1pos.x, sphere1pos.y, _sphere1radius);

	_sphere1._radius = (float)_sphere1radius;
	_sphere1._position = sphere1pos;
	_sphere1._colour = glm::vec3(0.1, 0, 0);

	//sphere 2
	glm::vec3 sphere2pos = glm::vec3(200, winSize.y / 2, 0);
	int _sphere2radius = 45;

	createCircle(sphere2pos.x, sphere2pos.y, _sphere2radius);

	_sphere2._radius = (float)_sphere2radius;
	_sphere2._position = sphere2pos;
	_sphere2._colour = glm::vec3(0, 0.1, 0);

	//add spheres to vector within ray tracer
	_rayTracer.spheres.push_back(_sphere1);
	_rayTracer.spheres.push_back(_sphere2);

	//big loop to cycle through every pixel in the screen
	for (int x = 0; x < winSize.x; x++)
	{
		for (int y = 0; y < winSize.y; y++)
		{
			Ray _ray = _camera.GetRay(glm::vec2(x, y));
			glm::vec3 _colour = _rayTracer.TraceRay(_ray, _rayTracer.spheres, _camera._Position);
			_myFramework.DrawPixel(glm::ivec2(x, y), _colour); //redraw with new colour
		}
	}

	// Pushes the framebuffer to OpenGL and renders to screen
	// Also contains an event loop that keeps the window going until it's closed
	_myFramework.ShowAndHold();
	return 0;


}


