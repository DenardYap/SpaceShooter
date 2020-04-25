// header file
#include <iostream>
#include <SDL.h>		// SDL library
#include <SDL_image.h> 	// SDL library for image
#include <SDL_ttf.h> 	// True type font 
#include <windows.h> 	// Sleep
#include <time.h> 		// time
#include <stdlib.h>		// rand and srand function
#include <string> 		// to_string and c_str()
using namespace std;
#ifndef SPACESHOOTER	// include guard
#define SPACESHOOTER

class Game {
	private:
		//----- Start Game Variables ----- //
		enum motion {
			MOVE_RIGHT = 0,
			MOVE_LEFT = 1,
			SHOOT = 2
		}; // leveraged enum to control our spaceship via SDL_Event
		bool motion_detect[3] = { false,false,false }; // works with the enum, 
													   // my logic: MOVE_RIGHT represent first element
													   // MOVE_LEFT represent second element.. etc
													   
		bool clicked = false;
		bool is_running = false; // set the game to not running at first, this bool variable also determine our screen-switching
		bool mouse_click = false;
		bool start_game = false;//game start variable
	
		//----- Laser Variables ------//
		
		int laser_speed = 3; // laser speed is 3 
		clock_t laser_time = clock(); // the controller of laser shoot rate
									  // use clock instead of time because we 
									  // need to keep track of decimal seconds
		
		// the three arrays below is use to control our "5 lasers" 
		int current_x[5] = { 0,
							 0,
							 0,
							 0,
							 0 }; // the x location of each laser at the start
	
		int velocity[5] = {  0,
							 0,
							 0,
							 0,
							 0 }; // the velocity of each laser at the start
	
		bool laser_shot[5] = { 0,
									 0,
									 0,
									 0,
									 0 }; // keep track of how many laser have been shot
		//---------------//
		int ship_speed = 5; // speed of spaceship
		int mouse_x, mouse_y; // keep track of current mouse x and y location
		//---------------//
	
		//----- Alien Variables -----//
		int alien_limit = 10, alien_speed = 0, alien_count = 0;
		int increment_value = 0;
		int time_now = time(NULL);
		bool aliens_coordinate[3][14] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // not my own idea, saw it online and used 
										  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}   // this is so called tile map logic
										};						  					   // 0 means there's no alien present, 1 means an alien is present									 	
	
		//----- SDL Variables -----//
		//----- General section -----//
		SDL_Window* window; //window object
		SDL_Renderer* renderer; //graphic object
		//---- Picture and coordinate for planets spaceship and space ----//
		SDL_Texture* spaceship, * space, * white_stars, * planet1, * planet2, * planet3, * planet4, * planet5, * planet6;
		SDL_Rect ship_des, space_des, star_des, planet1_des, planet2_des, planet3_des, planet4_des, planet5_des, planet6_des;
		//---- Picture and coordinate for laser ----//
		SDL_Texture* laser;
		SDL_Rect laser_des;
		//---- Picture and coordinate for button ----//
		SDL_Texture* sMenuBG, * sButton, * sButtonHover, * sButtonClick;
		SDL_Rect sBG_des;
		SDL_Rect sMenuBG_des;
		//---- Picture and coordinate for alien ----//
		SDL_Texture* alien;
		SDL_Rect alien_des;
	
		//---- Picture and coordiante for end game line ----//
		bool confirm=true;
		SDL_Texture *end_line , *gameover , *endMenu;
		SDL_Rect end_des, game_des ,endScreen_des;
	
		//---- Score Variables ----//
		SDL_Texture* scorebar;
		SDL_Rect scorebar_des;
		int current_score = 0;
		SDL_Rect score_rect;
		TTF_Font* score_font; 		// load text
		SDL_Color score_color;		// set font color to white
		SDL_Texture* score_text;
		string text = "Score: " + to_string(current_score);
		
		//---- Wave Variables ----//
		int current_wave = 1;
		SDL_Rect wave_rect;
		TTF_Font* wave_font; 	// load text
		SDL_Color wave_color;	// set font color to white
		SDL_Texture* w_text;
		string wave_text = "Wave " + to_string(current_wave);
		clock_t end_game_pause = clock(); // keep track of the time when each wave end
	
	public:
		Game();
		void loadImages_setInfos(); // setup graphics, load images and set attributes of images
		void setDes(SDL_Rect& rect, int hori, int vert, int width, int height); // set x,y,width and height of each image
		void handle_event(); // handle what's happened on the keyboard, this function detects what key/mousebutton has been pressed and response
		void update(); // update everything on the screen e.g. planet moving, spaceship moving..
		void renderMenu(); // render (paint) the menu screen
		void render(); // render (paint) the main game screen
		void endgame_menu(); // render (paint) the end game screen
		void spawn_alien(); // spawn aliens randomly on the map
		bool is_it_running(); // return the is_running variable
		void clean(); // cleanup to prevent memory leaks
	
		~Game(); 
};

#endif

