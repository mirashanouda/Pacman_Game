#include "Header.h"
#include "Fruit.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Tree.h"

int main()
{
	//Populating the board_arr from the file
	int board_arr[row][column];

	ifstream in;
	in.open("board.txt");
	if (in.fail())
	{
		cout << "Error while opening the file" << endl;
		exit(1);
	}
	else
	{
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
			{
				in >> board_arr[i][j];
			}
	}//end if fail
	in.close();

	//Adjacency Matrix 
	int graph[matrix][matrix];
	//Intialize all with large number
	for (int r = 0; r < matrix; r++)
		for (int c = 0; c < matrix; c++)
			graph[r][c] = infinity;

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < column; c++)
		{
			if (board_arr[r][c] >= 0)
			{
				if (c + 1 < column && c - 1 >= 0 && r + 1 < row && r - 1 >= 0) {
					if (board_arr[r][c + 1] >= 0)
					{
						graph[board_arr[r][c]][board_arr[r][c + 1]] = 1;
						graph[board_arr[r][c + 1]][board_arr[r][c]] = 1;
					}
					if (board_arr[r][c - 1] >= 0)
					{
						graph[board_arr[r][c]][board_arr[r][c - 1]] = 1;
						graph[board_arr[r][c - 1]][board_arr[r][c]] = 1;
					}
					if (board_arr[r + 1][c] >= 0)
					{
						graph[board_arr[r][c]][board_arr[r + 1][c]] = 1;
						graph[board_arr[r + 1][c]][board_arr[r][c]] = 1;
					}
					if (board_arr[r - 1][c] >= 0)
					{
						graph[board_arr[r][c]][board_arr[r - 1][c]] = 1;
						graph[board_arr[r - 1][c]][board_arr[r][c]] = 1;
					}
				}
			}
		}
	}
	//portals:
	graph[93][77] = 1;
	graph[77][93] = 1;

	//score file:
	ofstream S_out;
	ifstream S_read;

	S_out.open("scores.txt", ios::app);
	if (S_out.fail()) {
		cout << "Error while opening the score file!!" << endl;
		exit(1);
	}

	S_read.open("scores.txt");
	if (S_read.fail()) {
		cout << "Error while opening the score file!!" << endl;
		exit(1);
	}

	//the tree to store the scores
	Tree scoresTree;

	vector<int> scoreOrder; 
	int ss;
	while (S_read >> ss){
		scoresTree.userInsert(ss);
	}

	//Design the Board:
	RenderWindow window;
	window.create(VideoMode(860, 940), "Pacman Game");
	RectangleShape arr[row][column]; //make an array of RectangleShape exactly like the array from file

	//Textures on the board
	Texture bricks, dot, power;
	bricks.loadFromFile("Blue.jpg");
	dot.loadFromFile("yellow.jpg");
	power.loadFromFile("Dot.jpg");

	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
		{
			arr[i][j].setSize(Vector2f(40, 40));
			arr[i][j].setPosition(float(50 + j * 40), float(50 + i * 40));

			if (board_arr[i][j] < 0)
			{
				arr[i][j].setTexture(&bricks);
				arr[i][j].setFillColor(Color(24, 94, 255));
			}
			else if (board_arr[i][j] == 22 || board_arr[i][j] == 38 || board_arr[i][j] == 133 || board_arr[i][j] == 147)
				arr[i][j].setTexture(&power);
			else if (board_arr[i][j] <= 63 || board_arr[i][j] >= 106 || board_arr[i][j] == 71 || board_arr[i][j] == 81 || board_arr[i][j] == 94 || board_arr[i][j] == 98 || board_arr[i][j] == 72 || board_arr[i][j] == 76 || board_arr[i][j] == 89 || board_arr[i][j] == 97)
				arr[i][j].setTexture(&dot);
			else
				arr[i][j].setFillColor(Color::Black);
		}//end for

	//displaying the score number
	Font font1;                    font1.loadFromFile("Neon.ttf");
	Font font2;                    font2.loadFromFile("The Happy Bear.otf");
	Text s;
	int score = 0;
	s.setFillColor(Color::White);
	s.setPosition(2, 2);
	s.setCharacterSize(45);
	s.setFont(font1);

	//displaying the score number
	Text l;
	int lives = 3;
	l.setFillColor(Color::White);
	l.setPosition(680, 2);
	l.setCharacterSize(45);
	l.setFont(font1);

	//visible/invisible mood
	Text vis;
	string mood = "Normal";
	vis.setFillColor(Color::Green);
	vis.setPosition(320, 2);
	vis.setCharacterSize(45);
	vis.setFont(font1);

	//Lose/win mood
	Text L_W;
	string lose = "   Game Over \n  You lost X\nCurrent score: ";
	string win = "Congratulations\n   You won :D\nCurrent score: ";
	L_W.setPosition(300, 10);
	L_W.setCharacterSize(60);
	L_W.setFont(font2);

	Text R;
	string ready = "Ready!!";
	R.setFillColor(Color::Yellow);
	R.setPosition(375, 480);
	R.setCharacterSize(45);
	R.setFont(font2);

	//setting clock
	Clock clock;//clock for the game
	Clock f_clock; //clock for the fruits to desplay
	Clock G_clock; //clock to handle the eating the ghosts

	Clock iC;
	Clock pC;
	Clock bC;

	//the Pacman player
	Pacman player;

	//Ghosts
	Ghost inky(1, "inky.png");
	Ghost pinky(2, "pinky.png");
	Ghost blinky(3, "blinky.png");


	//the Fruit //condition for the ready botton
	Fruit fruit;


	//sounds:
	Music beginMusic;
	beginMusic.openFromFile("pacman_beginning.wav");
	beginMusic.play();


	//SoundBuffer beginAudio;
	//beginAudio.loadFromFile("pacman_beginning.wav");
	//Sound b;
	//b.setBuffer(beginAudio);
	
	bool status = false; 
	Event e;
	srand(time(0));

	while (window.isOpen())
	{	
		while (window.pollEvent(e))//pollevent
		{
			if (e.type == Event::Closed)//to close the window
				window.close();
			if (e.type == Event::KeyPressed) {//keyPressed

				//Press space in the begining of the game
				if ((e.key.code == Keyboard::Space) && (!status)) {
					status = true;
					ready.erase(0, ready.size());
				}
			}
		} //end pollEvent
		
		//playing
		if (lives > 0 && player.getPellets() < 153 && status)
		{						
			if (clock.getElapsedTime().asMilliseconds() >= 200)
			{
				//Ghosts movments
				int pacPosition = player.onBoard(board_arr);

				vector<vector<int>> pathI = inky.Dijkstra(graph, inky.onBoard(board_arr));
				vector<vector<int>> pathP = pinky.Dijkstra(graph, pinky.onBoard(board_arr));
				vector<vector<int>> pathB = blinky.Dijkstra(graph, blinky.onBoard(board_arr));

				if (iC.getElapsedTime().asMilliseconds() >= 200) {
					inky.ghostMoving(board_arr, pathI[pacPosition][pathI[pacPosition].size() - 2]);
					iC.restart();
				}
				
				if (pC.getElapsedTime().asMilliseconds() >= 300)
				{
					pinky.ghostMoving(board_arr, pathP[pacPosition][pathP[pacPosition].size() - 2]);
					pC.restart();
				}

				if (bC.getElapsedTime().asMilliseconds() >= 450)
				{
					blinky.ghostMoving(board_arr, pathB[pacPosition][pathB[pacPosition].size() - 2]);
					bC.restart();
				}

				player.moving(e, board_arr);//makeing pacman moves

				if (score == 1000)
					lives = lives + 1;

				if (f_clock.getElapsedTime().asSeconds() >= 30)
				{
					fruit.randPosition(board_arr);
					f_clock.restart();
				}

				vis.setString("Status: " + mood);
				if (player.removeDot(arr, board_arr, dot, power, score, fruit))//ture: pacman ate a Power Pellet
				{
					G_clock.restart();
					mood = "Invisible";
				}
				if (G_clock.getElapsedTime().asSeconds() > 10 || mood == "Normal")
				{
					mood = "Normal";
					player.faceGhost(inky, pinky, blinky, lives);
				}
				else 
					player.resetGhostPosition(inky, pinky, blinky);
				
				clock.restart();
			}
		}
		//losing
		else if (lives <= 0) {//lost 

			S_out << score << endl;
			scoresTree.userInsert(score);
			scoreOrder = scoresTree.getOrder();

			window.close();
			//Design the Gameover window:
			RenderWindow GameOver;
			GameOver.create(VideoMode(860, 940), "Game Over");
			while (GameOver.isOpen())
			{
				while (GameOver.pollEvent(e))//pollevent
				{
					if (e.type == Event::Closed)//to close the window
						GameOver.close();
				}
				L_W.setFillColor(Color::Red);
				L_W.setString(lose + to_string(score));


				vector<Text> sO;
				sO.resize(scoreOrder.size());

				for (int i = 0; i < scoreOrder.size(); i++)
				{
					sO[i].setFillColor(Color::White);
					sO[i].setFont(font1);
					sO[i].setCharacterSize(30);
					sO[i].setPosition(400, 220 + 40 * i);
					sO[i].setString(to_string(scoreOrder.at(i)));
				}
				GameOver.clear();
				GameOver.draw(L_W);
				for (int i = 0; i < sO.size(); i++)
					GameOver.draw(sO[i]);
				GameOver.display();
			}
		}
		//Winning
		else if (status){

			S_out << score << endl;
			scoresTree.userInsert(score);
			scoreOrder = scoresTree.getOrder();

			window.close();
			//Design the Gameover window:
			RenderWindow GameOver;
			GameOver.create(VideoMode(860, 940), "Game Over");
			while (GameOver.isOpen())
			{
				while (GameOver.pollEvent(e))//pollevent
				{
					if (e.type == Event::Closed)//to close the window
						GameOver.close();
				}
				L_W.setFillColor(Color::Green);
				L_W.setString(win + to_string(score));

				vector<Text> sO;
				sO.resize(scoreOrder.size());

				for (int i = 0; i < scoreOrder.size(); i++)
				{
					sO[i].setFillColor(Color::White);
					sO[i].setFont(font1);
					sO[i].setCharacterSize(30);
					sO[i].setPosition(400, 220 + 40 * i);
					sO[i].setString(to_string(scoreOrder.at(i)));
				}
				GameOver.clear();
				GameOver.draw(L_W);
				for (int i = 0; i < sO.size(); i++)
					GameOver.draw(sO[i]);
				GameOver.display();
			}
		}

		s.setString("SCORE: " + to_string(score)); 
		l.setString("LIVES: " + to_string(lives));
		R.setString(ready);

		window.clear();

		//Drawing
		for (int i = 0; i < row; i++)
			for (int j = 0; j < column; j++)
			{
				window.draw(arr[i][j]);
			}
		window.draw(player.getObject());
		window.draw(inky.getObject());
		window.draw(blinky.getObject());
		window.draw(pinky.getObject());
		window.draw(fruit.getObject());
		window.draw(s);
		window.draw(l);
		window.draw(vis);
		window.draw(R);
		window.display();
	}//end isOpen

	S_out.close();
	S_read.close();

	system("pause");
	return 0;
}