#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "chain.hpp"

#define WIDTH 1000
#define HEIGHT 800

#define FPS 60

#define ALLEGRO_MOUSE_BUTTON_LEFT 1
#define ALLEGRO_MOUSE_BUTTON_RIGHT 2

int main()
{
	al_init();
	al_init_primitives_addon();

	ALLEGRO_DISPLAY* disp = al_create_display(WIDTH, HEIGHT);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(1.0f / FPS);

	al_install_mouse();

	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_mouse_event_source());

	ALLEGRO_EVENT e;
	bool redraw = true;

	al_start_timer(timer);

	std::vector<Segment> segments;
	bool placeMode = true;

	Vector2 curMousePos;

	while (true)
	{
		al_wait_for_event(queue, &e);

		if (e.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			break;
		if (e.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (e.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT)
			{
				if (placeMode)
				{
					std::cout << "Placing new segment" << std::endl;
					Segment newsegment = Segment();
					newsegment.position = Vector2(e.mouse.x, e.mouse.y);
					if (segments.size() == 0) newsegment.length = 0;
					else newsegment.length = Vector2::Distance(newsegment.position, segments[segments.size() - 1].position);
					segments.push_back(newsegment);
				}
				else
				{
					//std::cout << "FABRIK solving inverse kinematics" << std::endl;
					//fabrik_solve(segments, Vector2(e.mouse.x, e.mouse.y));
					//debug_print_positions(segments);
				}
			}
			else if (e.mouse.button == ALLEGRO_MOUSE_BUTTON_RIGHT)
			{
				placeMode = !placeMode;
			}
		}
		if (e.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			curMousePos.x = e.mouse.x;
			curMousePos.y = e.mouse.y;
		}

		if (e.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			if (!placeMode)
				fabrik_solve(segments, curMousePos);
		}

		if (redraw && al_is_event_queue_empty(queue))
		{
			al_clear_to_color(al_map_rgb(57, 69, 68));
			render_chain(segments);

			redraw = false;
			al_flip_display();
		}


	}

	al_uninstall_mouse();

	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	al_destroy_display(disp);

}