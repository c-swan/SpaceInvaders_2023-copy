//
//  GameScene.hpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-20.
//

#ifndef GameScene_hpp
#define GameScene_hpp

class GameScene {
public:
	GameScene();
	~GameScene();

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;

};

class Gameplay : public GameScene {
public:
	Gameplay();
	~Gameplay();

	virtual void Update();
	virtual void Render();
};

class StartScene : public GameScene {
public:
	StartScene();
	~StartScene();

	virtual void Update();
	virtual void Render();
};

class EndScene : public GameScene {
public:
	EndScene(); //no new highscore
	EndScene(bool highscore); //new highscore
	~EndScene();

	virtual void Update();
	virtual void Render();

private:
	bool newHighScore = false;
	int highscore = 0;
};

#endif /* GameScene_hpp */
