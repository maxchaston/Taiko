#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>

// can't reassign when resize event occurs
/* #define WINDOW_X 800 */
/* #define WINDOW_Y 800 */

float WINDOW_X = 800;
float WINDOW_Y = 800;
/* float number_of_triangles = 1; */

SDL_Window* window;
SDL_Renderer* renderer;
int run_flag;

/* #define deg2rad(deg) (deg==0 ? 0 : deg/360*2*M_PI) */

typedef struct point_struct {
	float x;
	float y;
} point;

float deg2rad(float deg)
{
	if (deg==0)
		return 0;
	return deg/360*2*M_PI;
}

void clear_screen()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("taiko mouse", SDL_WINDOWPOS_UNDEFINED,
														SDL_WINDOWPOS_UNDEFINED,
														WINDOW_X,
														WINDOW_Y,
														SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	clear_screen();
}

void teardown()
{
	SDL_DestroyWindow(window);
}

void handle_events(int *run_flag)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{	
		case SDL_QUIT:
			*run_flag=0;
			break;
		case SDL_WINDOWEVENT:
			switch(event.window.event) // SDL_WindowEventID
			{
			case SDL_WINDOWEVENT_RESIZED:
				WINDOW_X = event.window.data1;
				WINDOW_Y = event.window.data2;
				break;
			}
			break;
		}
	}

	// poll keyboard
	// needs to be ran after events processed
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	// Example keyboard state access with function call
	/* if (keystates[SDL_SCANCODE_W]) */
	/* 	modify_player_state(1); */
	/* if (keystates[SDL_SCANCODE_S]) */
	/* 	modify_player_state(2); */
	/* if (keystates[SDL_SCANCODE_A]) */
	/* 	modify_player_state(3); */
	/* if (keystates[SDL_SCANCODE_D]) */
	/* 	modify_player_state(4); */
}

// draw a circle by rendering a fan of triangles
void draw_circle(float radius, float x, float y, SDL_Color colour_left, SDL_Color colour_right)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	/* float number_of_triangles = 100; // 200 seems to be a good number for 800x800 resolution */
	/* float number_of_lines = M_PI * 2 * radius; */
	float number_of_lines = 50;
	/* float number_of_lines = 500; */

	// Triangles
	/* for (int i=0; i<number_of_triangles; i++) */
	/* { */
	/* 	float initial_angle = 120/number_of_triangles*i; */
	/* 	float angle1 = fmod(initial_angle, 360); */
	/* 	float angle2 = fmod(initial_angle+120, 360); */
	/* 	float angle3 = fmod(initial_angle+240, 360); */
	/* 	SDL_Vertex vertices[] = { */
	/* 		{{x+radius*sin(deg2rad(angle1)), y-radius*cos(deg2rad(angle1))}, i<= 100 ? colour_left : colour_right, {1,1}}, */
	/* 		{{x+radius*sin(deg2rad(angle2)), y-radius*cos(deg2rad(angle2))}, i<= 100 ? colour_left : colour_right, {1,1}}, */
	/* 		{{x+radius*sin(deg2rad(angle3)), y-radius*cos(deg2rad(angle3))}, i<= 100 ? colour_left : colour_right, {1,1}}}; */
	/* 	SDL_RenderGeometry(renderer, */
	/* 									NULL, */
	/* 									vertices, 3, */
	/* 									NULL, 0); */
	/* 	} */

	// Single-pixel lines
	/* for (int i=0; i<number_of_lines; i++) */
	/* { */
	/* 	float angle = 360/number_of_lines*i; */
	/* 	angle<=180 ? SDL_SetRenderDrawColor(renderer, colour_right.r, colour_right.g, colour_right.b, colour_right.a) : SDL_SetRenderDrawColor(renderer, colour_left.r, colour_left.g, colour_left.b, colour_left.a); */
	/* 	SDL_RenderDrawLine(renderer, x, y, x+radius*sin(deg2rad(angle)), y-radius*cos(deg2rad(angle))); */
	/* } */

	// Variable width triangles
	/* for (int i=0; i<number_of_lines; i++) */
	/* { */
	/* 	float rect_width = 50; */
	/* 	float angle = 360/number_of_lines*i; */
	/* 	printf("number: %d main angle: %f ", i, angle); */
	/* 	/\* SDL_Color current_colour = (angle<=180) ? ((SDL_Color){colour_right.r, colour_right.g, colour_right.b, colour_right.a}) : ((SDL_Color){colour_left.r, colour_left.g, colour_left.b, colour_left.a}); *\/ */
	/* 	SDL_Color current_colour; */
	/* 	if (angle<180) */
	/* 	  current_colour = (SDL_Color){colour_right.r, colour_right.g, colour_right.b, colour_right.a}; */
	/* 	else */
	/* 		current_colour = (SDL_Color){colour_left.r, colour_left.g, colour_left.b, colour_left.a}; */
	/* 	float line_x = x+radius*sin(deg2rad(angle)); */
	/* 	float line_y = y+radius*cos(deg2rad(angle)); */
	/* 	/\* float anticlock_angle = -45; *\/ */
	/* 	/\* float clock_angle = 135; *\/ */
	/* 	float anticlock_angle = angle-90; */
	/* 	printf("2nd angle: %f\n", anticlock_angle); */
	/* 	SDL_Vertex vertex_1 = {{line_x+rect_width/2*sin(deg2rad(anticlock_angle)), line_y+rect_width/2*cos(deg2rad(anticlock_angle))}, {current_colour.r, current_colour.g, current_colour.b, current_colour.a}, {1, 1}}; // top left */
	/* 	SDL_Vertex vertex_2 = {{line_x-rect_width/2*sin(deg2rad(anticlock_angle)), line_y-rect_width/2*cos(deg2rad(anticlock_angle))}, {current_colour.r, current_colour.g, current_colour.b, current_colour.a}, {1, 1}}; // top right */
	/* 	SDL_Vertex vertex_3 = {x, y, {current_colour.r, current_colour.g, current_colour.b, current_colour.a}, {1, 1}}; // bottom */
	/* 	SDL_Vertex vertices[] = {vertex_1, vertex_2, vertex_3}; */
	/* 	SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0); */
	/* 	/\* SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); *\/ */
	/* 	/\* SDL_RenderDrawLineF(renderer, vertex_1.position.x, vertex_1.position.y, vertex_2.position.x, vertex_2.position.y); *\/ */
	/* 	/\* SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); *\/ */
	/* 	/\* SDL_RenderDrawLine(renderer, x, y, line_x, line_y); *\/ */
	/* } */

	// Automatic width triangles with correct half split
	int number_of_sides = 16; // must be even for correct split, adding odd is more trouble than it's worth I think
	for (int i=0; i<number_of_sides; i++)
	{
		float angle_1 = i*(360.0/number_of_sides);
		float angle_2 = (i+1)*(360.0/number_of_sides);
		SDL_Color current_colour;
		if (angle_2<=180)
		  current_colour = (SDL_Color){colour_right.r, colour_right.g, colour_right.b, colour_right.a};
		else
			current_colour = (SDL_Color){colour_left.r, colour_left.g, colour_left.b, colour_left.a};
		SDL_Vertex vertex_1 = {{x+radius*sin(deg2rad(angle_1)), y-radius*cos(deg2rad(angle_1))}, {current_colour.r, current_colour.g, current_colour.b, current_colour.a}, {1, 1}}; // top left
		SDL_Vertex vertex_2 = {{x+radius*sin(deg2rad(angle_2)), y-radius*cos(deg2rad(angle_2))}, {current_colour.r, current_colour.g, current_colour.b, current_colour.a}, {1, 1}}; // top right
		SDL_Vertex vertex_3 = {x, y, {current_colour.r, current_colour.g, current_colour.b, current_colour.a}, {1, 1}}; // bottom
		SDL_Vertex vertices[] = {vertex_1, vertex_2, vertex_3};
		SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);
	}
}

void draw_ui()
{
	// draw drum
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	draw_circle(350.0, WINDOW_X/2, WINDOW_Y, (SDL_Color){181, 88, 7, 255}, (SDL_Color){181, 88, 7, 255});
	draw_circle(320.0, WINDOW_X/2, WINDOW_Y, (SDL_Color){255, 255, 255, 180}, (SDL_Color){255, 200, 200, 180});
	SDL_SetRenderDrawColor(renderer, 221, 221, 221, 221);
	SDL_RenderFillRect(renderer, &((SDL_Rect){WINDOW_X/2-5, WINDOW_Y-320, 10, 320}));

	// draw test bar
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &((SDL_Rect){0, 100, WINDOW_X, 200}));
}

int main()
{
	init();
	run_flag=1;
	while(run_flag)
	{
		handle_events(&run_flag);
		clear_screen();
		draw_ui();
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);
	}
	teardown();
	return 0;
}

// TODO unlock fps and add counter at the top left
