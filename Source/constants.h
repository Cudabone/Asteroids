#pragma once
//Window
constexpr int width = 1920;
constexpr int height = 1080;

//Math
constexpr float PI = 3.1415926f;
constexpr float DEG_TO_RAD = PI / 180.0f;

//Ship
constexpr float ship_acceleration = 0.5*width;
constexpr float turning_rate = 270.0f; //Degrees per second
constexpr float ship_max_velocity = 1500.f; 
//Bullets
constexpr float bullet_width = 1.0f;
constexpr float bullet_height = 1.0f;
constexpr float bullet_velocity = 2000.0f;
constexpr float fire_rate = 0.15f; // seconds per bullet

//Asteroid
//Big Asteroid
constexpr float asteroid_radius = 0.05f * width;
//Asteroid Broken once
constexpr float asteroid_radius_smaller = 0.5f * asteroid_radius;
//Asteroid Broken twice
constexpr float asteroid_radius_smallest = 0.5f * asteroid_radius_smaller;
constexpr float asteroid_max_velocity = .1f*width;
constexpr float center_x = width / 2;
constexpr float center_y = height / 2;

//Radius around ship that asteroids cannot spawn
constexpr float safety_radius = 2.0f * asteroid_radius; 
