//
//  GameState.hpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//

#ifndef GameState_hpp
#define GameState_hpp


class Game;

class GameState {
public:
	virtual void enter(const Game &game) = 0;
	virtual void exit(const Game &game) = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual ~GameState() {}
};

class StartScreen : public GameState {
public:
	void enter(const Game &game) {}
	void exit(const Game &game) {}
	virtual void Update();
	virtual void Render();
	
	static GameState& getInstance();

private:
	StartScreen() {}
	StartScreen(const StartScreen& other);
	StartScreen& operator=(const StartScreen& other);
};

class Gameplay : public GameState {
public:
	void enter(const Game &game) {}
	void exit(const Game &game) {}
	virtual void Update();
	virtual void Render();

	static GameState& getInstance();

private:
	Gameplay() {}
	Gameplay(const Gameplay& other);
	Gameplay& operator=(const Gameplay& other);
};

class EndScreen : public GameState {
public:
	void enter(const Game &game);
	void exit(const Game &game);
	virtual void Update();
	virtual void Render();
	
	static GameState& getInstance();

private:
	EndScreen() {}
	EndScreen(const EndScreen& other);
	EndScreen& operator=(const EndScreen& other);
	static EndScreen singleton;
};

//
//enum struct State { //are these the only states...?
//	STARTSCREEN,
//	GAMEPLAY,
//	ENDSCREEN
//};



#endif /* GameState_hpp */
