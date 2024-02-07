#include <vector>
#include <iostream>
#include "chain.hpp"
#include "vec2.hpp"

#define ITERATIONS 15
#define STOP_DIST 0.05f

void fabrik_solve(std::vector<Segment>& segments, Vector2 target)
{

	Vector2 base = segments[0].position;

	if (segments.size() < 2) return;
	for (int i = 0; i < ITERATIONS; i++)
	{
		if (Vector2::Distance(segments[segments.size() - 1].position, target) < STOP_DIST) return;
		Vector2 curTarget = target;

		for (int j = segments.size() - 1; j >= 0; j--)
		{
			auto& cur = segments[j];
			float betweendist = (j == segments.size() - 1) ? 0 : segments[j + 1].length;
			float maxdist = Vector2::Distance(curTarget, cur.position) - betweendist;
			
			Vector2 direction = (curTarget - cur.position).Normalized() * maxdist;
			cur.position += direction;

			curTarget = cur.position;
		}

		curTarget = base;
		
		for (int j = 0; j < segments.size(); j++)
		{
			auto& cur = segments[j];
			float maxdist = Vector2::Distance(curTarget, cur.position) - cur.length;

			Vector2 direction = (curTarget - cur.position).Normalized() * maxdist;
			cur.position += direction;

			curTarget = cur.position;
		}

	}

}

void debug_print_positions(const std::vector<Segment>& segments)
{
	for (const Segment& s : segments)
	{
		std::cout << '(' << s.position.x << ", " << s.position.y << ')' << std::endl;
	}
}
