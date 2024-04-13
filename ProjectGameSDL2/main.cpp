#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "ThreatToHouse.h"
#include "ThreatToMain.h"
#include "ImpTimer.h"


BaseObject g_background;

const int max_blood_of_house = 20000;
const int max_blood_of_player = 300;

int blood_of_house = max_blood_of_house;
int blood_of_player = max_blood_of_player;

bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
	{
		return false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Game Cpp SDL 2.0 Tran Van Quyet", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
			{
				success = false;
			}
		}
	}

	return success;
}

bool LoadBackground()
{
	bool ret = g_background.LoadImg("image/background.png", g_screen);

	return ret;
}

void Close()
{
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (InitData() == false)
	{
		return -1;
	}
	if (LoadBackground() == false)
	{
		return -1;
	}

	// Init time to calculate fps
	ImpTimer fps_timer;

	// Init time start of game
	ImpTimer time_start;
	time_start.start();

	// Init blood bar of house
	BaseObject blood_bar_of_house;
	blood_bar_of_house.LoadImg("image/heartbar.png", g_screen);
	blood_bar_of_house.SetRect(15, 9);

	// Init main object player
	MainObject p_player;
	p_player.LoadImg("image/tankmain.png", g_screen);

	// Init main house
	BaseObject main_house;
	main_house.LoadImg("image/house.png", g_screen);
	main_house.SetRect(SCREEN_WIDTH/2 - 105, SCREEN_HEIGHT/2 - 85);
	SDL_Rect rect_of_main_house = main_house.GetRect();

	//// Init threat to house
	//ThreatToHouse threat_to_house;
	//threat_to_house.LoadImg("image/threat_to_house.png", g_screen);

	// Init list threat to house
	std::vector<ThreatToHouse*> p_threat_to_house_list;


	//// Init threat to main
	//ThreatToMain threat_to_main;
	//threat_to_main.LoadImg("image/threat_to_house.png", g_screen);

	// Init list threat to main
	std::vector<ThreatToMain*> p_threat_to_main_list;
	
	bool is_quit = false;
	while (!is_quit)
	{
		fps_timer.start();

		int time_of_game = time_start.get_ticks();
		//std::cout << time_of_game << "\n";

		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
			}

			p_player.HandleInputAction(g_event, g_screen);
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);

		//// Move threat to house
		//threat_to_house.DoThreat(main_house.GetRect());
		//threat_to_house.Render(g_screen, NULL);

		// Add threat into threat to house list
		if (time_of_game / TIME_THREAT_TO_HOUSE_APPEAR > p_threat_to_house_list.size())
		{
			ThreatToHouse* threat_to_house = new ThreatToHouse();
			threat_to_house->LoadImg("image/threat_to_house.png", g_screen);
			p_threat_to_house_list.push_back(threat_to_house);
		}

		// Move threat of threat to house list
		for (int i = 0; i < p_threat_to_house_list.size(); i++)
		{
			ThreatToHouse* threat_to_house = p_threat_to_house_list.at(i);

			// Check threat attack house and do threat
			bool ret1 = threat_to_house->DoThreat(rect_of_main_house);
			if (ret1)
			{
				blood_of_house -= 1;
			}

			// Check bullet of player with threat
			std::vector<BulletObject*> list_bullet_of_player = p_player.get_bullet_list();
			for (int i2 = 0; i2 < list_bullet_of_player.size(); i2++)
			{
				BulletObject* p_bullet = list_bullet_of_player.at(i2);
				if (p_bullet != NULL && threat_to_house != NULL)
				{
					bool ret2 = threat_to_house->CheckCollision(p_bullet->GetRect());
					if (ret2)
					{
						// Delete this bullet out list
						p_bullet->set_is_move(false);

						// Decrease blood of threat
						threat_to_house->DecreaseBlood();

					}
				}
			}

			// If blood = 0 -> delete threat
			if (threat_to_house->get_blood() < 1)
			{
				p_threat_to_house_list.erase(p_threat_to_house_list.begin() + i);
				if (threat_to_house != NULL)
				{
					delete threat_to_house;
					threat_to_house = NULL;
				}
			}
			else
			{
				threat_to_house->Render(g_screen, NULL);
			}

			
		}

		//// Move threat to main
		//threat_to_main.DoThreat(p_player.GetRect());
		//threat_to_main.Render(g_screen, NULL);

		// Add threat into threat to main list
		if (time_of_game / TIME_THREAT_TO_MAIN_APPEAR > p_threat_to_main_list.size())
		{
			ThreatToMain* threat_to_main = new ThreatToMain();
			threat_to_main->LoadImg("image/threat_to_main.png", g_screen);
			p_threat_to_main_list.push_back(threat_to_main);
		}

		// Move threat of threat to main list
		for (int i = 0; i < p_threat_to_main_list.size(); i++)
		{
			ThreatToMain* threat_to_main = p_threat_to_main_list.at(i);
			threat_to_main->DoThreat(p_player.GetRect(), rect_of_main_house);
			threat_to_main->HandleBullet(g_screen);

			//Check bullet of threat with main and house
			std::vector<BulletObject*> list_bullet_of_threat = threat_to_main->get_bullet_list();
			for (int i2 = 0; i2 < list_bullet_of_threat.size(); i2++)
			{
				BulletObject* p_bullet = list_bullet_of_threat.at(i2);
				if (p_bullet != NULL)
				{
					// Check bullet with house
					bool ret1 = p_bullet->CheckCollision(rect_of_main_house);
					if (ret1)
					{
						blood_of_house -= 1;
					}

					// Check bullet with player
					bool ret2 = p_bullet->CheckCollision(p_player.GetRect());
					if (ret2)
					{
						blood_of_player -= 1;
					}

					// Delete bullet out list 
					if (ret1 || ret2)
					{
						p_bullet->set_is_move(false);
					}
				}
			}

			// Check bullet of player with threat
			std::vector<BulletObject*> list_bullet_of_player = p_player.get_bullet_list();
			for (int i2 = 0; i2 < list_bullet_of_player.size(); i2++)
			{
				BulletObject* p_bullet = list_bullet_of_player.at(i2);
				if (p_bullet != NULL && threat_to_main != NULL)
				{
					bool ret2 = threat_to_main->CheckCollision(p_bullet->GetRect());
					if (ret2)
					{
						// Delete this bullet out list
						p_bullet->set_is_move(false);

						// Decrease blood of threat
						threat_to_main->DecreaseBlood();

					}
				}
			}

			bool ret1 = threat_to_main->CheckCollision(rect_of_main_house);
			if (ret1)
			{
				blood_of_house -= 5;
			}

			// If blood = 0 or threat collision with house -> delete threat
			if (ret1 || threat_to_main->get_blood() < 1)
			{
				p_threat_to_main_list.erase(p_threat_to_main_list.begin() + i);
				if (threat_to_main != NULL)
				{
					delete threat_to_main;
					threat_to_main = NULL;
				}
			}
			else
			{
				threat_to_main->Render(g_screen, NULL);
			}
			
		}

		// Move player
		p_player.DoPlayer(rect_of_main_house);
		p_player.Show(g_screen);
		p_player.HandleBullet(g_screen);

		// Render main house
		main_house.Render(g_screen, NULL);


		// Render blood bar of house
		blood_bar_of_house.Render(g_screen);
		int blood_remain_of_house = blood_of_house * 558 / max_blood_of_house;
		SDL_Rect blood_losted = { blood_remain_of_house + 44, 21, 558 - blood_remain_of_house, 18 };
		SDL_RenderFillRect(g_screen, &blood_losted);
		
		// Render blood bar of player
		SDL_SetRenderDrawColor(g_screen, 0, 153, 0, 255);
		int x_pos_bar = p_player.GetRect().x - 9;
		int y_pos_bar = p_player.GetRect().y - 15;
		SDL_Rect blood_of_main_game = { x_pos_bar, y_pos_bar, 80, 12 };
		SDL_RenderFillRect(g_screen, &blood_of_main_game);
		int blood_remain_of_player = blood_of_player * 80 / max_blood_of_player;
		SDL_Rect blood_losted_of_main = {blood_remain_of_player + x_pos_bar, y_pos_bar, 80 - blood_remain_of_player, 12};
		SDL_SetRenderDrawColor(g_screen, 102, 0, 51, 255);
		SDL_RenderFillRect(g_screen, &blood_losted_of_main);

		//SDL_Delay(2);
		/*SDL_Rect big_house = { p_player.GetRect().x - 9, p_player.GetRect().y - 15, 80, 12};
		SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 255);
		SDL_RenderDrawRect(g_screen, &big_house);*/
		//std::cout << blood_of_house << " " << blood_of_player << "\n";

		if (blood_of_house < 0 || blood_of_player < 0) {
			if (MessageBox(NULL, L"GAME OVER!", L"Info", MB_OK) == IDOK)
			{
				Close();

				return 1;
			}
		}
		

		SDL_RenderPresent(g_screen);

		int real_imp_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;

		if (real_imp_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_imp_time;
			SDL_Delay(delay_time);
		}
	}

	Close();

	return 0;
}