#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
//Window
constexpr int width = 1920;
constexpr int height = 1080;

//Math
constexpr float PI = 3.1415926f;
constexpr float PI_TO_DEG = PI / 180.0f;

//Ship
constexpr float ship_acceleration = 0.5*width;
constexpr float turning_rate = 270.0f; //Degrees per second
//Bullets
constexpr float bullet_width = 1.0f;
constexpr float bullet_height = 10.0f;
constexpr float bullet_velocity = 2000.0f;
constexpr float fire_rate = 0.15f; // seconds per bullet

//Asteroid
constexpr float asteroid_radius = 0.05f * width;
#endif
