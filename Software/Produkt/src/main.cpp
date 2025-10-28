#include "ui/UIManager.h"
#include <firstcode.h>
#include <iostream>
#include <stdexcept>
#include <optionparser.h>
#include <firstcode.h>
#include "ui/UIManager.h"
#include "raytracing.hpp"

int main() { // NOLINT(bugprone-exception-escape)
    try {
        std::cout << "Hello Prisma++" << "\n";
        std::cout << "Add-Lib: " << add(1, 2) << "\n";

		// NOLINTBEGIN
		//  basic raytracing algorithm example
    	Triangle tri1{{glm::vec3{-3, -3, 0}, glm::vec3{5, 7, 0}, glm::vec3{3, -3, 0}}, {0, 255, 0}};
    	Triangle tri2{{glm::vec3{-3, -3, 0}, glm::vec3{5, 7, 0}, glm::vec3{-4, 5, -2}}, {0, 255, 0}};
    	Triangle tri3{{glm::vec3{-4, 5, -2}, glm::vec3{5, 7, 0}, glm::vec3{-2, 9, -3}}, {0, 255, 0}};
    	// apparently the order of points makes a difference??
    	// (overlapping, not at right coordinates?)
    	Triangle tri4{{glm::vec3{5, 7, 0}, glm::vec3{3, -3, 0}, glm::vec3{12, 4, -1}}, {0, 255, 0}};
    	Triangle tri5{{glm::vec3{-3, -3, 0}, glm::vec3{0, -9, -0.5}, glm::vec3{3, -3, 0}}, {0, 255, 0}};
 
    	std::vector<Triangle> triangles{tri1, tri2, tri3, tri4, tri5};

    	Camera camera{{0, -0.1, 10}, 5, 12.8, 9.6, 0.01};
    	glm::vec3 light{0, 5, 5};
    	save_ppm(camera.update({triangles}, light), "output.ppm"); //visualize output array
		// NOLINTEND		

        //  create window
        UIManager ui(800, 600, "Prisma++");
        ui.run(); // run main UI loop
        return 0;
    } catch (const std::exception &e) {
        // Handle it internally to prevent it from escaping.
        // Note: I/O itself can still throw, but this is the intent.
        std::cerr << "ERROR: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "ERROR: Unknown exception caught." << "\n";
    }

    // Since we caught the exception, we can still exit cleanly with an error code.
    return 1;
}

auto test() -> int
{
    return 1;
}
