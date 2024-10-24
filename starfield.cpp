#include "raylib.h"
#include <iostream>
#include <vector>
#include "Randum.hpp"

constexpr int width = 1200;
constexpr int height = 900;

double map(double value, double in_min, double in_max, double out_min, double out_max)
{
	return (value - in_min) / (in_max - in_min) * (out_max - out_min) + out_min;
}


class Star
{
public:
	Star()
		:x{ xe::randomd(-width / 2, width / 2) }, y{ xe::randomd(-height / 2, height / 2) },
		z{ xe::randomd(0.0,width) }, pz{z}
	{

	}

public:

	void update(float dt)
	{

		speed = map(GetMousePosition().x, 0.0, width, 10.0, 500);
		z -= speed*dt; // Moving towards the viewer

		if (z < 1)
		{
			// If the star is too close, reset its position
			x = xe::randomd(static_cast<double>(-width) / 2, width / 2);
			y = xe::randomd(static_cast<double>(-height) / 2, height / 2);
			z = double(width);
		}
	}

	void render()
	{

		float sx = map(x / z, 0.0, 1.0, 0.0, width) + width / 2; // Center horizontally
		float sy = map(y / z, 0.0, 1.0, 0.0, height) + height / 2; // Center vertically

		float r = map(z, 0.0, width, 3, 0);
		DrawCircle(sx, sy, r, WHITE);
		
		double px = map(x / pz, 0.0, 1.0, 0.0, width) + width / 2;
		double py = map(y / pz, 0.0, 1.0, 0.0, height) + height / 2;

		pz = z;

		DrawLine(px, py, sx, sy, BLUE);
		
	}

public:
	double x{};
	double y{};
	double z{};


	double pz{};
	

private:
	double speed{ 300 };
};



int main()
{

	std::vector<Star> stars{};

	// Push Stars
	for (int i = 0; i < 800; i++)
	{
		stars.emplace_back();
	}

	InitWindow(width, height, "starfield warpspace");
	SetTargetFPS(120);

	while (!WindowShouldClose())
	{

		float dt = GetFrameTime();


		/// RENDERING

		BeginDrawing();
		ClearBackground(BLACK);

		for (auto& i : stars)
		{
			i.update(dt);
			i.render();
		}

		DrawFPS(5, 5);
		EndDrawing();

	}
	CloseWindow();

}  
