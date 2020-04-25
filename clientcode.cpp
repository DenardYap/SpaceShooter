// clientcode
#include "SpaceShooter.cpp"  		
// this is for VisualStudio
// for DevC++ change to “SpaceShooter.cpp”


int main(int argc, char* argv[]) { 	// command line arguments
									// have to add these arguments 
									// as it's required by the library
	
	/*
	
		We used while loops to keep iterate over 
		the functions/methods we created in the class
		so that it keeps running and update, or else
		it would be very static, and it's almost impossible
		to create a game without using a while loop logic like this
		
	*/
	Game game;
	while (game.is_it_running() == false) { 	// main menu
		game.renderMenu();		// run main menu
		game.handle_event();	// mouse position and click detection
	}

	game.spawn_alien(); // spawn aliens before the game starts

	while (game.is_it_running() == true) {
		game.handle_event();
		game.render();
		game.update();

		// run as long as is_running is true
	}
	game.endgame_menu();
	game.clean();

	return 0;
}

