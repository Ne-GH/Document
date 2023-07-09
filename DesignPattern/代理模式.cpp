/*
*    Time: 07/09/23 23:27:06
*    Create By yongheng
*/

#include <iostream>
#include <string>

using namespace std;

/*******************************************************************************
 * Player不能直接访问Game,需要通过ProxyPlayer访问Game
*******************************************************************************/

class Game {
    string _game_name;
public:
	Game(string name) : _game_name(name){  }
	~Game(){}
	string GetGameName() { return _game_name; }
};

class Player {
protected:
    Game* _game;
public:
	Player(Game* game){  }
	virtual ~Player(){  }
	virtual void OutputGameName() = 0;
	virtual void PlayGame() = 0;
};


class ProxyPlayer :public Player {
public:
	ProxyPlayer(Game* game):Player(game) {
		_game = game;
	}
	~ProxyPlayer() {  }

	void OutputGameName() {
		cout << "I am ProxyPlayer,Game name:" << _game->GetGameName() << endl;
	}
	void PlayGame() {
		cout << "Start play game with ProxyPlayer." << endl;
	}
};

class PrimaryPlayer :public Player {
    ProxyPlayer* _proxy_player;
public:
	PrimaryPlayer(Game* game) :Player(game) {
		_proxy_player = new ProxyPlayer(game);
	}
	~PrimaryPlayer() {
		delete _proxy_player;
		_proxy_player = NULL;
	}
	void OutputGameName() {
		cout << "/-- PrimaryPlayer:OutputGameName --/" << endl;
		_proxy_player->OutputGameName();
	}
	void PlayGame() {
		cout << "/-- PrimaryPlayer:PlayGame --/" << endl;
		_proxy_player->PlayGame();
	}
};

class MediumPlayer :public Player {
public:
	MediumPlayer(Game* game) :Player(game) {
		_proxy_player = new ProxyPlayer(game);
	}
	~MediumPlayer() {
		delete _proxy_player;
		_proxy_player = NULL;
	}
	void OutputGameName() {
		cout << "/-- MediumPlayer:OutputGameName ---/" << endl;
		_proxy_player->OutputGameName();
	}
	void PlayGame() {
		cout << "/-- MediumPlayer:PlayGame --/" << endl;
		_proxy_player->PlayGame();
	}

private:
	ProxyPlayer* _proxy_player;
};

int main(int argc,char *argv[]) {

	Game* game = new Game("刀塔");

	ProxyPlayer* proxy_player = new ProxyPlayer(game);
	proxy_player->OutputGameName();
	proxy_player->PlayGame();

	PrimaryPlayer* ry_player = new PrimaryPlayer(game);
	ry_player->OutputGameName();
	ry_player->PlayGame();

	MediumPlayer* mu_player = new MediumPlayer(game);
	mu_player->OutputGameName();
	mu_player->PlayGame();

	delete game; game = NULL;
	delete proxy_player; proxy_player = NULL;
	delete ry_player; ry_player = NULL;
	delete mu_player; mu_player = NULL;

	cout << endl;
	for (size_t i = 0; i < 1; i++)
	{
		cout << "* ** *** **** ***** ****** *******" << endl;
		cout << "** *** **** ***** ****** ******* *" << endl;
		cout << "*** **** ***** ****** ******* * **" << endl;
		cout << "**** ***** ****** ******* * ** ***" << endl;
		cout << "**** **** **** <==> **** **** ****" << endl;
		cout << "***** ****** ******* * ** *** ****" << endl;
		cout << "****** ******* * ** *** **** *****" << endl;
		cout << "******* * ** *** **** ***** ******" << endl;
		cout << "* ** *** **** ***** ****** *******" << endl;
	}
	cout << endl;

	cout << "<<<<<<<<== Hello! You are a good man! ==>>>>>>>" << endl;
	return 0;


    return 0;
}
