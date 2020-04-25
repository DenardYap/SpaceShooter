/**** CONTRIBUTION **** 
	
	Bernard: Logic of Laser shooting (5 laser maximum), Logic of randomly spawn alien around the space, Logic of waves and score points (increment and record of score points, new waves etc), introduced the library SDL to his fellow friends, logic of moving spaceship, optimized codes .
	Emang: Worked on graphics of spaceships during gameplay and related logics
	Nazrin H.: Created button design for all three stages (Default, Hover, Click), Logic for creating Start Menu window, Logic for start button’s animation, Logic for start button to run game. 
	Chin Chong Yi (Leo) : Worked on the base logic of the laser (where the laser appears upon activation) , endgame animation and endgame screen.
	Sik Jerlson: Aliens, ScoreBar Logic 
	Idlan azmi:designed the structure of the scoreboard using an editing platform and advised the idea of the wave count in-game. 
	Clement Lim: Pointed out bugs and made relevant suggestions with attempts to optimize source code
	Ethan and Abdullah : Worked on hit detection and related parts of the code
	Nurfara: Worked on overall retrowave theme, graphics of start screen, end screen and related logics
	Ooi Por Zhang: Fixed bugs and provided logic on endgame screen
	Aisyah Nadhirah: Designed the graphics of the planets during gameplay and related logics
	Ng Jia Xin: Designed background and background stars, vectorization of rocket design
	
*/

/**** How to link SDL2 to your compiler (For Windows 10, Dev C++) ****
1) Go to https://www.libsdl.org/download-2.0.php, under development libraries download SDL2-devel-2.0.12-mingw.tar.gz (MinGW 32/64-bit)
2) Extract the folder and remember the folder name, in this case, let’s assume the folder name is SDL2-2.0.12
3) Go to Dev C++, under Tools, click Compiler Options
4) At General section, at the second box, type the following linker command -lSDL2main -lSDL2
5) At Directories section, go to Libraries, click the add files icon, find SDL2-2.0.12\x86_64-w64-mingw32\lib and click ADD 
6) Go to C++ Includes, click the add files icon, find SDL2-2.0.12\x86_64-w64-mingw32\include\SDL2, click ADD 
7) Finally, find SDL2.dll under your SDL2-2.0.12\x86_64-w64-mingw32\bin folder, copy the dll files and put it in where you saves your source code. 
8) For example, you want to save your spaceshooter.cpp under C:/User/Azeem, you then also copy the SDL2.dll files into C:/User/Azeem 
9) Done! Import the library by writing  #include <SDL.h>
10) Notice we also used SDL2.ttf and SDL2.image libraries, the procedure of linking them are identical, the linker commands are  -lSDL2_image  -lSDL2_ttf
Note: If you want to link ttf and images libraires, there are more than one dll files, copy all the dll files in the bin directory of the libraries, there are more than 1
*/

// implementation 
#include "SpaceShooter.h"
using namespace std;

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) { // initialization
		window = SDL_CreateWindow("SpaceShooter", 100, 100, 900, 650, false); // create a window with 900 width, 650 height
		if (window) { // this will run once window created successfully
			cout << "Window created." << endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) { // this will run once renderer created successfully
			cout << "Renderer created." << endl;
		}
	}
	else {
		is_running = false; // if initialization fails (rare case),
		SDL_Quit();			// the program will stop running
	}
	TTF_Init(); // initialize TTF, similar to SDL_Init
	loadImages_setInfos(); // load all images and set their attributes
}

void Game::renderMenu() {
	
	SDL_RenderClear(renderer); // clear the previous screen
	SDL_RenderCopy(renderer, space, NULL, &space_des); 
	SDL_RenderCopy(renderer, sMenuBG, NULL, &sMenuBG_des);

	if (mouse_x >= 285 && mouse_y >= 425
		&& mouse_x <= 615 && mouse_y <= 525) { // detects when the mouse is over the start button
		
		SDL_RenderCopy(renderer, sButtonHover, NULL, &sBG_des);// shows start hover button
		if (mouse_click == true) { // detects when there is a mouse click
			clicked = true;
			SDL_RenderCopy(renderer, sButtonClick, NULL, &sBG_des); // shows clicked button
			}
				if (mouse_click == false && clicked == true){
					is_running = true;
					}

		}
		
	else{
		SDL_RenderCopy(renderer, sButton, NULL, &sBG_des); // shows start button
		}

	SDL_RenderPresent(renderer); // paint everything I previously SDL_RenderCopied
  }

void Game::loadImages_setInfos()	// assigning images to attributes
 {

	spaceship = IMG_LoadTexture(renderer, "images/spaceship.png");
	space = IMG_LoadTexture(renderer, "images/BG Color only.png");
	white_stars = IMG_LoadTexture(renderer, "images/Stars Transparent.png");
	planet1 = IMG_LoadTexture(renderer, "images/Planet8.png");
	planet2 = IMG_LoadTexture(renderer, "images/Planet2.png");
	planet3 = IMG_LoadTexture(renderer, "images/Planet3.png");
	planet4 = IMG_LoadTexture(renderer, "images/Planet4.png");
	planet5 = IMG_LoadTexture(renderer, "images/Planet5.png");
	planet6 = IMG_LoadTexture(renderer, "images/Planet7.png");
	laser = IMG_LoadTexture(renderer, "images/redline.png");
	alien = IMG_LoadTexture(renderer, "images/alien.png");
	sButton = IMG_LoadTexture(renderer, "images/Button.png");
	sButtonHover = IMG_LoadTexture(renderer, "images/Button Hover.png");
	sButtonClick = IMG_LoadTexture(renderer, "images/Button Click.png");
	sMenuBG = IMG_LoadTexture(renderer, "images/Start Menu Background.png");
	scorebar = IMG_LoadTexture(renderer, "images/scorebar.png");
	end_line = IMG_LoadTexture(renderer, "images/line.png");
	gameover = IMG_LoadTexture(renderer, "images/gameover.jpg");
	endMenu = IMG_LoadTexture(renderer, "images/endgame.jpg");

	setDes(ship_des, 900 / 2 - 50, 580, 64, 64);
	setDes(space_des, 0, 0, 900, 650);
	setDes(star_des, 0, -650, 900, 1300);
	setDes(planet1_des, 700, 450, 177, 100);
	setDes(planet2_des, 20, 350, 177, 100);
	setDes(planet3_des, 300, 400, 59, 33);
	setDes(planet4_des, 150, 50, 212, 133);
	setDes(planet5_des, 300, 600, 177, 100);
	setDes(planet6_des, 570, 250, 177, 100);
	setDes(laser_des, -1, -1, 0, 0);  
	setDes(sBG_des, 285, 425, 330, 100); 
	setDes(sMenuBG_des, 0, 0, 900, 650);
	setDes(scorebar_des, 10, 10, 300, 80);

	//---- load texts ----//

	score_font = TTF_OpenFont("font/Roboto-Bold.ttf", 400);  // load font
	score_color = { 255, 255, 255 }; // set font color to white
	SDL_Surface* text_surface = TTF_RenderText_Solid(score_font, text.c_str(), score_color); //create the surface from plain text
	// not declaring this in private because we only need to use it locally
	score_text = SDL_CreateTextureFromSurface(renderer, text_surface); // and then create the texture from the surface we created
	setDes(score_rect, 30, 25, 200, 50); 
	SDL_FreeSurface(text_surface); // have to free it after using, something like what we did in clean() function

	wave_font = TTF_OpenFont("font/RobotoCondensed-BoldItalic.ttf", 600); // load font
	wave_color = { 255, 253, 217 }; // set font color to light yellow
	SDL_Surface* wave_surface = TTF_RenderText_Solid(wave_font, wave_text.c_str(), wave_color);
	w_text = SDL_CreateTextureFromSurface(renderer, wave_surface);
	setDes(wave_rect, 665, 10, 200, 80);
	SDL_FreeSurface(wave_surface); 

	//-------------------//

	setDes(end_des, 0, 565, 900, 10);
	setDes(endScreen_des, 0, 0, 900, 650);
}

void Game::setDes(SDL_Rect& rect, int hori, int vert, int width, int height) {
	//function to set picture's coordinate and width and height
	rect.x = hori;
	rect.y = vert;
	rect.w = width;
	rect.h = height;
}


void Game::handle_event() { // this function handles all inputs
							// from the computer to the game
							// i.e: mouse movements 
							// and keyboard inputs.

	SDL_Event event; // initialization
	SDL_GetMouseState(&mouse_x, &mouse_y); // get mouse coordinate

	while (SDL_PollEvent(&event) != 0) { // triggers when an input is detected

		switch (event.type) { // specific detection definitions

			case SDL_QUIT: // when the user clicks "X" at top-right
				is_running = false;
				cout << "Quitting program..." << endl;
				SDL_Quit();
				break;
				
			case SDL_KEYDOWN: // whenever the user pressed a keyboard button
	
				if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) { // pressed arrow right
					motion_detect[MOVE_RIGHT] = true;
					cout << "Motion detect: ";
					cout << motion_detect[MOVE_RIGHT] << endl;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) { // pressed arrow left
					motion_detect[MOVE_LEFT] = true;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) { // pressed spacebar
					motion_detect[SHOOT] = true;
				}
				break;
	
			case SDL_KEYUP: // whenever the user released a keyboard button
				if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) { // released arrow right
					motion_detect[MOVE_RIGHT] = false;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) { // released arrow left
					motion_detect[MOVE_LEFT] = false;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) { // released spacebar
					motion_detect[SHOOT] = false;
				}
				cout << "Someone left his hand off the keyboard" << endl;
				break;
	
			case SDL_MOUSEBUTTONDOWN: // whenever the user pressed a mouse button
				if (event.button.button == SDL_BUTTON_LEFT) { // let only the left click works
					mouse_click = true; 
				}
				break;
	
			case SDL_MOUSEBUTTONUP: // whenever the user released a mouse button
				if (event.button.button == SDL_BUTTON_LEFT) {
					mouse_click = false; 
				}
				break;
	
			default:
				break;
			}
		}

}
	// get mouse coordinate


void Game::update() { 	// this function is used for
						// updates on the screen

	planet1_des.y += 1; // allow planets to keep moving in the background
	planet2_des.y += 1;
	planet3_des.y += 1;
	planet4_des.y += 1;
	planet5_des.y += 1;
	planet6_des.y += 1; 
	Sleep(10); //delay it abit to make it move slower
			   // threading substitution

	if (planet1_des.y == 650) { // planets will rerun from the start once they reach the bottom of the window
		planet1_des.y = -100;
	}
	if (planet2_des.y == 650) {
		planet2_des.y = -100;
	}
	if (planet3_des.y == 650) {
		planet3_des.y = -100;
	}
	if (planet4_des.y == 650) {
		planet4_des.y = -100;
	}
	if (planet5_des.y == 650) {
		planet5_des.y = -100;
	}
	if (planet6_des.y == 650) {
		planet6_des.y = -100;
	}	

	// allow white stars to keep moving in the background
	star_des.y += 1;
	if (star_des.y == 0) {
		star_des.y = -650;
	}

	if (motion_detect[MOVE_RIGHT] == true) {
		
		if (ship_des.x <= 832) { // limits scope of spaceship's movement to the right
								 // to make sure the spaceship does not move out of window
			ship_des.x += ship_speed; 	// moves the spaceship to the right
		}
	
	}
	if (motion_detect[MOVE_LEFT] == true) {
		
		if (ship_des.x >= 0) {	// left
			ship_des.x -= ship_speed;
		}
	}
	
	if (motion_detect[SHOOT] == true) {
		// shoots when user presses spacebar
		for (int i = 0; i < 5; i++) {
			if (laser_shot[i] == 0 && clock() >= laser_time + 300) {
				laser_shot[i] = 1;
				laser_time = clock(); 
				// added a time argument in order to delay shooting of each laser
			    // to prevent user from spamming lasers
				current_x[i] = ship_des.x + 32 - 5;
			}
		}

	}
	// check the coordinates of the laser constantly
}


void Game::render() { // painter function

		/* Important Note: Render has a
		   hierarchy structure. Whatever
		   comes first will render at the bottom */

	SDL_RenderClear(renderer); // clear the previous screen
	SDL_RenderCopy(renderer, space, NULL, &space_des); 
	SDL_RenderCopy(renderer, white_stars, NULL, &star_des); 
	SDL_RenderCopy(renderer, planet1, NULL, &planet1_des);
	SDL_RenderCopy(renderer, planet2, NULL, &planet2_des);
	SDL_RenderCopy(renderer, planet3, NULL, &planet3_des);
	SDL_RenderCopy(renderer, planet4, NULL, &planet4_des);
	SDL_RenderCopy(renderer, planet5, NULL, &planet5_des);
	SDL_RenderCopy(renderer, planet6, NULL, &planet6_des);
	SDL_RenderCopy(renderer, scorebar, NULL, &scorebar_des);
	SDL_RenderCopy(renderer, score_text, NULL, &score_rect);
	SDL_RenderCopy(renderer, w_text, NULL, &wave_rect);
	SDL_RenderCopy(renderer, end_line, NULL, &end_des);
	SDL_RenderCopy(renderer, gameover, NULL, &game_des);
	
	/*
		This is a triple for-loop, in which a lot of problems may arise,
		such as computational costs, run-time delays etc. For instance:
		the lasers will slow down or speed up depending on where it is placed.
		As such, be cautious when editing this section.
	*/

	for (int laser_count = 0; laser_count < 5; laser_count++) {
	
		//render my lasers if the respective array position is 1
		if (laser_shot[laser_count] == 1) {

			int laser_y = ship_des.y + velocity[laser_count];
			int laser_x = current_x[laser_count]; //current_x was updated in update() function
												  // repeating again with laser_x just to make it intuitive

			velocity[laser_count] -= laser_speed;	// minus because lasers go up

			setDes(laser_des, laser_x, laser_y, 10, 30);
			SDL_RenderCopy(renderer, laser, NULL, &laser_des);

			if (laser_y <= -30) { //if the laser ran out of scope
				laser_shot[laser_count] = 0;
				velocity[laser_count] = 0;
			}

		}
		
		// move on to second and third loop, which render my aliens with similar logics
		for (int alien_row = 0; alien_row < 3; alien_row++) { 
			for (int alien_column = 0; alien_column < 14; alien_column++) {
				
				if (aliens_coordinate[alien_row][alien_column] == 1) { //if an alien is present
					if (time(NULL) >= time_now + 2) { // increase increment_value every 2 seconds
						time_now = time(NULL);
						increment_value += (3 + alien_speed); 
					}
					
					int alien_y = 62 * alien_row + 100 + increment_value; // the increment_value previously increased 
																		  // is used here to make the aliens keep moving down
					int alien_x = 64 * alien_column;
					
					setDes(alien_des, alien_x, alien_y, 62, 49);
					SDL_RenderCopy(renderer, alien, NULL, &alien_des);

					if (alien_y + 49 >= 570){  // once an alien touched the end-game line
						confirm = false;
					}

					if (laser_des.x + 10 >= alien_des.x && laser_des.x <= alien_des.x + 62 
					&& laser_des.y <= alien_des.y + 49 && laser_des.y >= alien_des.y) { // if laser hits alien
						
						// score update
						current_score += 5;
						text = "Score: " + to_string(current_score);
						SDL_Surface* text_surface = TTF_RenderText_Solid(score_font, text.c_str(), score_color);
						score_text = SDL_CreateTextureFromSurface(renderer, text_surface);
						SDL_FreeSurface(text_surface);
						// -------------

						aliens_coordinate[alien_row][alien_column] = 0;
						alien_count -= 1;
						laser_shot[laser_count] = 0;
						velocity[laser_count] = 0;
						end_game_pause = clock();
					}

				}

			}

		}
		if (alien_count == 0) { // increase the difficulty of the game if all aliens are killed

			motion_detect[SHOOT] = false;  // prohibits shooting during this short pause
			if (clock() >= end_game_pause + 2500) { // pauses for about 2.5 seconds
				if (alien_limit < 42) { // since our limit is 42 aliens
					alien_limit += 1;
				}
				spawn_alien();
				increment_value = 0;
				alien_speed += 1;
				current_wave += 1;

				// update wave
				string wave_text = "Wave " + to_string(current_wave);
				SDL_Surface* wave_surface = TTF_RenderText_Solid(wave_font, wave_text.c_str(), wave_color);
				w_text = SDL_CreateTextureFromSurface(renderer, wave_surface);
				SDL_FreeSurface(wave_surface);
			}
		}
	}
	SDL_RenderCopy(renderer, spaceship, NULL, &ship_des); 
	SDL_RenderPresent(renderer); 

	if (confirm == false) { // the alien touched the line, player lost the game
		setDes(game_des, 380 , 300, 120, 80);
		SDL_RenderCopy(renderer, gameover, NULL, &game_des);
		SDL_RenderPresent(renderer); // start painting! 
		Sleep(5000);
		is_running = false;
		cout << "You lose!" << endl;
	}
	

}

void Game::spawn_alien() {
	srand(time(NULL)); // set a seed
	
	while (alien_count < alien_limit) {
		int row = rand() % 3; // spawn 10 aliens with the generated row and column numbers
		int column = rand() % 14;
		if (aliens_coordinate[row][column] == 1) {  
			// no action required since an alien is already present
		}
		else {
			aliens_coordinate[row][column] = 1;
			alien_count += 1;	// add 1 if an alien is absent
		}
	}
}

void Game::endgame_menu() {

	SDL_RenderClear(renderer);		
	SDL_RenderCopy(renderer, endMenu, NULL, &endScreen_des);
	SDL_RenderPresent(renderer); // stops for 10 seconds
	Sleep(5000);
}

bool Game::is_it_running() {
	return is_running;
}

void Game::clean() { 	// this dynamic memory allocated function
						// is used to avoid memory leak

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(spaceship);
	SDL_DestroyTexture(space);
	SDL_DestroyTexture(white_stars);
	SDL_DestroyTexture(planet1);
	SDL_DestroyTexture(planet2);
	SDL_DestroyTexture(planet3);
	SDL_DestroyTexture(planet4);
	SDL_DestroyTexture(planet5);
	SDL_DestroyTexture(planet6);
	SDL_DestroyTexture(laser);
	SDL_DestroyTexture(sButton);
	SDL_DestroyTexture(sButtonHover);
	SDL_DestroyTexture(sButtonClick);
	SDL_DestroyTexture(alien);
	SDL_DestroyTexture(score_text);
	SDL_DestroyTexture(sMenuBG);
	SDL_DestroyTexture(scorebar);
	SDL_DestroyTexture(end_line);
	SDL_Quit();

}

Game::~Game() {
	cout << "Class Game has reached the end of its lifetime --- destructing..." << endl;
}	
