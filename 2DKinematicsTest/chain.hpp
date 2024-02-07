#ifndef _CHAIN_HPP_
#define _CHAIN_HPP_

#include <vector>
#include "vec2.hpp"

struct Segment
{
	Vector2 position;
	float length;
};

void render_chain(const std::vector<Segment>& segments);

void fabrik_solve(std::vector<Segment>& segments, Vector2 target);

void debug_print_positions(const std::vector<Segment>& segments);

#endif