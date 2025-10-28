#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/string_cast.hpp>
#include <stack>
#include <vector>
#include <array>
#include <cstdint>
#include <cmath>
#include <algorithm>

#define PI constexpr 3.14159265359f

// from Ray Tracing in One Weekend to visualize output array

void save_ppm(const std::vector<std::vector<std::array<uint8_t, 3>>>& img,
              const std::string& filename) {
    int height = img.size();
    int width = img[0].size();

    std::ofstream ofs(filename, std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (int y = 0; y < height; y++) { // flip vertically if needed
        for (int x = 0; x < width; ++x) {
            ofs.write(reinterpret_cast<const char*>(img[y][x].data()), 3);
        }
    }
}


struct Triangle{
//	private:
		std::array<glm::vec3, 3> points;
		glm::vec3 normal;
		float d;
		std::array<uint8_t, 3> rgb;
 
//	public:
		Triangle() = default;
		Triangle(const std::array<glm::vec3, 3> _points, const std::array<uint8_t, 3> _rgb) : points(_points), rgb(_rgb), d{}, normal{}{
			glm::vec3 v1 = points.at(1) - points.at(0);
			glm::vec3 v2 = points.at(2) - points.at(0);
			normal = glm::normalize(glm::cross(v1, v2));
			d = glm::dot(normal, -points.at(0));
			
			//checks whether normal vector points away from origin, important for sign of light intensity
			//this is by no means finished, especially the edge case of d=0 has to be investigated!
			// also this seems like very bad code :/
			if(d < 0.0f){
				normal *= -1;
			}else if(d == 0.0f){
				int sign = 1;
				if(normal.x < 0.0f) {sign *= -1;}
				if(normal.y < 0.0f) {sign *= -1;}
				if(normal.z < 0.0f) {sign *= -1;}
				if(sign < 0) {normal *= -1;}
			}
		}
};

struct Subray{
//	private:
		glm::vec3 direction;
		glm::vec3 startpoint;
		std::array<uint8_t, 3> rgba;
		glm::vec3 intersect;
	
//	public:
		Subray() = default;
		
		auto intersection(const Triangle& t) -> glm::vec3{
			float dot_strtpt = glm::dot(t.normal, startpoint);
			float dot_dir = glm::dot(t.normal, direction);
			return  startpoint + direction * ((t.d - dot_strtpt) / dot_dir);
		}

		auto hit(const Triangle& t) -> bool{
			intersect = intersection(t);
			glm::vec3 v0 = t.points[2] - t.points[0];
			glm::vec3 v1 = t.points[1] - t.points[0];
			glm::vec3 v2 = intersect - t.points[0];
			float dot00 = glm::dot(v0, v0);
			float dot01 = glm::dot(v0, v1);
			float dot11 = glm::dot(v1, v1);
			float dot20 = glm::dot(v2, v0);
			float dot21 = glm::dot(v2, v1);

			float u = (dot11 * dot20 - dot01 * dot21) / (dot00 * dot11 - dot01 * dot01);
			float v = (dot00 * dot21 - dot01 * dot20) / (dot00 * dot11 - dot01 * dot01);
			

			return (u >= 0) && (v >= 0) && ((u + v) <= 1);
		}
};

struct Ray{
//	private:
		std::stack<Subray> subray_stack;
		std::array<uint8_t, 3> rgb;
		Triangle hit_triangle;
//	public:
		Ray() = default;

		Ray(Subray& s, const std::vector<Triangle>& t, const glm::vec3& light): subray_stack{}, rgb{}, hit_triangle{}{
			forward(s, t, light);
			rgb = backward(light);
		}
		
		void forward(Subray& s, const std::vector<Triangle>& t, const glm::vec3& light){
			subray_stack.push(s);
			for(Triangle tri : t){
				if(s.hit(tri)){
					Subray next = Subray{light - s.intersect, s.intersect, {tri.rgb}};
					subray_stack.push(next);
					hit_triangle = tri;
					return;
				}
			}
		}

		auto backward(const glm::vec3& light) -> std::array<uint8_t, 3>{
			if(subray_stack.size() <= 1) return {100, 100, 100};
			
			// ideal diffuse reflection (Lambertian)
			Subray from_light = subray_stack.top();
			subray_stack.pop();
			Subray to_camera = subray_stack.top();
			subray_stack.pop();

			// the angle correction is only a quick fix to get the lighting right, I have to think about the directions further probably
			float angle_light_triangle = glm::angle(glm::normalize(from_light.direction), hit_triangle.normal);
			if(angle_light_triangle > PI / 2) {angle_light_triangle = PI - angle_light_triangle;}
			
			float angle_camera_triangle = glm::angle(glm::normalize(to_camera.direction), hit_triangle.normal);
			float intensity = std::cos(angle_light_triangle);

			uint8_t color_r = static_cast<uint8_t>(hit_triangle.rgb.at(0) * intensity);
			uint8_t color_b = static_cast<uint8_t>(hit_triangle.rgb.at(1) * intensity);
			uint8_t color_g = static_cast<uint8_t>(hit_triangle.rgb.at(2) * intensity);
			
			//std::cout << glm::to_string(from_light.direction) << std::endl;
			
			return {color_r, color_b, color_g};
		}
		
};

struct Camera{
	glm::vec3 eye;
	float distance_to_screen;
	glm::vec3 top_left;
	glm::vec3 v_i; //vertical edge
	glm::vec3 v_j; //horizontal edge
	float height;
	float width;
	float delta;
	std::vector<std::vector<std::array<uint8_t, 3>>> screen;
	std::vector<std::vector<Ray>> rays;

	Camera(const glm::vec3& eye, const float& d, const float& w, const float& h, const float& delta) : eye(eye), distance_to_screen(d), width(w), height(h), delta(delta), top_left{}, v_i{}, v_j{}, screen{}, rays{}{
			
		glm::vec3 screen_midpoint = eye - glm::normalize(eye) * distance_to_screen;
		// this does not work if eye is exactly on z axis
		// also I am not sure about the vector orientation yet
		v_j = glm::normalize(glm::cross(glm::vec3{0, 0, 1}, eye));
		//std::cout << glm::to_string(v_j) << std::endl;
		v_i = glm::normalize(glm::cross(v_j, eye));
		//std::cout << glm::to_string(v_i) << std::endl;
		top_left = screen_midpoint - height / 2 * v_i - width / 2 * v_j;

		for(int i = 0; i < static_cast<int>(height / delta); i++) {
			screen.push_back(std::vector<std::array<uint8_t, 3>>{});
			for(int j = 0; j < static_cast<int>(width / delta); j++) {
				screen.at(i).push_back({255, 0, 255});
			}
		}
	}

	auto pixel(Ray& r) -> std::vector<char>{
		return {};
	}

	 auto update(const std::vector<Triangle>& t, const glm::vec3& light) -> std::vector<std::vector<std::array<uint8_t, 3>>>{
		
		for(int i = 0; i < static_cast<int>(height / delta); i++) {
        	rays.push_back(std::vector<Ray>{});
            for(int j = 0; j < static_cast<int>(width / delta); j++) {
                glm::vec3 point = top_left + i * delta * v_i + j * delta * v_j;
                glm::vec3 eye_to_point = point - eye;
                Subray s{eye_to_point, eye, {255, 255, 255}};
				rays.at(i).push_back(Ray{s, t, light});
				screen.at(i).at(j) = rays.at(i).at(j).rgb;
             }
         }
		return screen;

	}

};

