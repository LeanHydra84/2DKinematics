#include "chain.hpp"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

static const float RADIUS = 10;
static const float THICKNESS = 5;

void render_chain(const std::vector<Segment>& segments)
{
	for (int i = 0; i < segments.size(); i++)
	{
		const Vector2& s = segments[i].position;
		if (i > 0)
		{
			const Vector2& l = segments[i - 1].position;
			al_draw_line(s.x, s.y, l.x, l.y, al_map_rgb(65, 156, 152), THICKNESS);
		}
		al_draw_filled_circle(s.x, s.y, RADIUS, al_map_rgb(43, 240, 233));
	}
}