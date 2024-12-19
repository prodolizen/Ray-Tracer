#include "GCP_GFX_Framework.h"
#include "Camera.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Ray.h"
#include <chrono>
#include <fstream>
#include <string>
#include <thread>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <mutex>
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
    // Time testing
    std::chrono::steady_clock::time_point time1 = std::chrono::high_resolution_clock::now();

    // Set window size
    glm::ivec2 winSize(640, 480);

    Camera _camera;
    _camera.SendWinSize(winSize);
    _camera.Init();
    _camera._Position = glm::vec3(300, 300, 200); // Temp

    RayTracer _rayTracer;
    _rayTracer.lightPos = glm::vec3(200, 300, 6000); // Set light position in ray tracer
    _rayTracer.lightColour = glm::vec3(1, 1, 1); // Set light colour

    Sphere _sphere1;
    Sphere _sphere2;
    Sphere _sphere3;

    // File to put in time data
    std::ofstream outputFile("data.csv", std::ios::app);

    // Initialises SDL and OpenGL and sets up a framebuffer
    if (!_myFramework.Init(winSize))
    {
        return -1;
    }

    // Preparing a position to draw a pixel
    glm::ivec2 pixelPosition = winSize / 2;

    // Preparing a colour to draw (Colors are RGB, each value ranges between 0 and 1)
    glm::vec3 pixelColour(1, 0, 0);

    // Sets all pixels the same colour
    _myFramework.SetAllPixels(glm::vec3(0.1f, 0.1f, 0.3f));

    // Draws a single pixel
    _myFramework.DrawPixel(pixelPosition, pixelColour);

    // Sphere 1
    glm::vec3 sphere1pos = glm::vec3(3, 3, -20);
    int _sphere1radius = 3;
    _sphere1._radius = (float)_sphere1radius;
    _sphere1._position = sphere1pos;
    _sphere1._colour = glm::vec3(1, 0, 0);

    // Sphere 2
    glm::vec3 sphere2pos = glm::vec3(-3, -3, -20);
    int _sphere2radius = 3;
    _sphere2._radius = (float)_sphere2radius;
    _sphere2._position = sphere2pos;
    _sphere2._colour = glm::vec3(0, 0, 1);

    // Sphere 3
    glm::vec3 sphere3pos = glm::vec3(0, 0, -50);
    int _sphere3radius = 10;
    _sphere3._radius = (float)_sphere3radius;
    _sphere3._position = sphere3pos;
    _sphere3._colour = glm::vec3(0, 1, 0);

    // Add spheres to vector within ray tracer
    _rayTracer.spheres.push_back(_sphere1);
    _rayTracer.spheres.push_back(_sphere2);
    _rayTracer.spheres.push_back(_sphere3);

    // Time before big draw loop
    std::chrono::steady_clock::time_point time3 = std::chrono::high_resolution_clock::now();

    // Create threads for each section of the screen (for multithreading)
    std::vector<std::mutex> drawMutexes(winSize.y); // One mutex per row

auto renderSection = [&drawMutexes](GCP_Framework& myFramework, Camera& camera, RayTracer& rayTracer, const glm::ivec2& winSize, int startRow, int endRow) {
    for (int x = 0; x < winSize.x; x++) {
        for (int y = startRow; y < endRow; y++) {
            Ray _ray = camera.GetRay(glm::vec2(x, y));
            glm::vec3 _colour = rayTracer.TraceRay(_ray, rayTracer.spheres, camera._Position);

            // Lock the specific row mutex to avoid other threads from modifying this row at the same time
            std::lock_guard<std::mutex> lock(drawMutexes[y]);
            myFramework.DrawPixel(glm::ivec2(x, y), _colour); // Redraw with new colour
        }
    }
};

    int numThreads = 4; // splitting screen in to 4 sections and assigning each one to its own thread
    std::vector<std::thread> threads;

    // Split the rendering task into multiple threads
    for (int i = 0; i < numThreads; i++) {
        int startRow = (winSize.y / numThreads) * i;
        int endRow = (winSize.y / numThreads) * (i + 1);
        if (i == numThreads - 1) {
            endRow = winSize.y; // Ensure the last thread covers the rest of the rows
        }

        threads.push_back(std::thread(renderSection, std::ref(_myFramework), std::ref(_camera), std::ref(_rayTracer), std::cref(winSize), startRow, endRow));
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    std::chrono::steady_clock::time_point time2 = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds loopTime = std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time3);
    std::chrono::milliseconds mainTime = std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1);
    std::cout << "Time taken: " << mainTime.count() << std::endl;

    if (outputFile.is_open()) {
        // Check if the file is empty
        outputFile.seekp(0, std::ios::end); // Move to the end of the file

        if (outputFile.tellp() == 0) {
            // If file is empty, write the header row
            outputFile << "Total Completion (ms), Ray Tracing Loop Time (ms) \n";
        }

        // Write to CSV file
        outputFile << mainTime.count() << "," << loopTime.count() << "\n";

        outputFile.close();
    }
    else {
        std::cerr << "Couldn't open .csv for writing" << std::endl;
    }

    // Pushes the framebuffer to OpenGL and renders to screen
    _myFramework.ShowAndHold();

    return 0;
}
