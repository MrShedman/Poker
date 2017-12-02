#include <GameState.hpp>
#include <ResourceHolder.hpp>
#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>
#include <Utility.h>
#include <Button.hpp>
#include <AI.h>
#include <SoundNode.hpp>
#include <SpriteNode.hpp>

GameState::GameState(StateStack& stack, Context context)
:
State(stack, context),
mSceneGraph()
{
	std::unique_ptr<Deck> d(new Deck(context));
	deck = d.get();
	mSceneGraph.attachChild(std::move(d));

	sf::Texture& backgroundTexture = context.textures->get(Textures::GameBackground);
	backgroundTexture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> background(new SpriteNode(backgroundTexture));
	centreSpriteToWindow(background->getSprite(), *context.window);
	mSceneGraph.attachChild(std::move(background));

	sf::Texture& tableTexture = context.textures->get(Textures::Table);
	tableTexture.setRepeated(true);

	// Add the table sprite to the scene
	std::unique_ptr<SpriteNode> table(new SpriteNode(tableTexture));
	centreSpriteToWindow(table->getSprite(), *context.window, sf::Vector2f(0.f, 40.f));
	mSceneGraph.attachChild(std::move(table));

	// Add sound effect node
	std::unique_ptr<SoundNode> soundNode(new SoundNode(*context.sounds));
	mSceneGraph.attachChild(std::move(soundNode));

	std::array<float, 9> ppx = { { 0.59f, 0.75f, 0.82f, 0.67f, 0.44f, 0.21f, 0.06f, 0.13f, 0.29f } };
	std::array<float, 9> ppy = { { 0.21f, 0.28f, 0.59f, 0.77f, 0.81f, 0.77f, 0.59f, 0.28f, 0.21f } };
	std::array<std::string, 9> ppn = { "Dwan", "Antonious", "Ivey", "Hellmuth", "Elezra", "Ferguson", "Laak", "Esfandiari", "Samahies" };

	std::unique_ptr<PlayerCodex> c(new PlayerCodex(*deck));
	codex = c.get();

	codex->registerPlayer("Dwan");
	codex->registerPlayer("Antonious");
	codex->registerPlayer("Ivey");
	codex->registerPlayer("Hellmuth");
	codex->registerPlayer("Elezra");
	codex->registerPlayer("Ferguson");
	codex->registerPlayer("Laak");
	codex->registerPlayer("Esfandiari");
	codex->registerPlayer("Samahies");

	for (int i = 0; i < 9; ++i)
	{
		std::unique_ptr<PlayerPanel> panel(new PlayerPanel(context, sf::FloatRect(std::floor(ppx[i] * 1280), std::floor(ppy[i] * 720), 240, 60)));
		//auto c = std::make_unique<PlayerPanel>(context, sf::FloatRect(std::floor(ppx[i] * 1280), std::floor(ppy[i] * 720), 240, 60));

		panels.push_back(panel.get());

		mSceneGraph.attachChild(std::move(panel));
	}

	panels[0]->registerPlayer(codex->getPlayer("Dwan"));
	panels[1]->registerPlayer(codex->getPlayer("Antonious"));
	panels[2]->registerPlayer(codex->getPlayer("Ivey"));
	panels[3]->registerPlayer(codex->getPlayer("Hellmuth"));
	panels[4]->registerPlayer(codex->getPlayer("Elezra"));
	panels[5]->registerPlayer(codex->getPlayer("Ferguson"));
	panels[6]->registerPlayer(codex->getPlayer("Laak"));
	panels[7]->registerPlayer(codex->getPlayer("Esfandiari"));
	panels[8]->registerPlayer(codex->getPlayer("Samahies"));

	mSceneGraph.attachChild(std::move(c));

	for (int i = 0; i < 9; ++i)
	{
		panels[i]->getPlayer().setController(*this);
	}

	/*controllers.push_back(factory.make(codex.GetPlayer("Dwan"), *this));
	controllers.push_back(factory.make(codex.GetPlayer("Antonious"), *this));
	controllers.push_back(factory.make(codex.GetPlayer("Ivey"), *this));
	controllers.push_back(factory.make(codex.GetPlayer("Hellmuth"), *this));
	controllers.push_back(factory.make(codex.GetPlayer("Elezra"), *this));
	controllers.push_back(factory.make(codex.GetPlayer("Ferguson"), *this));
	controllers.push_back(factory.make(codex.GetPlayer("Laak"), *this));
	controllers.push_back(factory.make(codex.GetPlayer("Esfandiari"), *this));
	controllers.push_back(factory.make(codex.GetPlayer("Samahies"), *this));*/

	float y = context.window->getSize().y;
	float x = context.window->getSize().x;

	auto fold = std::make_shared<GUI::Button>(context);
	fold->setPosition(x - 170, y - 70);
	fold->setSize(sf::Vector2f(160.f, 60.f));
	fold->setText("Fold");
	fold->setCallback([this]()
	{
		this->fold();
	});

	auto check = std::make_shared<GUI::Button>(context);
	check->setPosition(x - 340, y - 70);
	check->setSize(sf::Vector2f(160.f, 60.f));
	check->setText("Check");
	check->setCallback([this]()
	{
		this->flip();
	});

	auto raise = std::make_shared<GUI::Button>(context);
	raise->setPosition(x - 510, y - 70);
	raise->setSize(sf::Vector2f(160.f, 60.f));
	raise->setText("Raise");
	raise->setCallback([this]()
	{
		dealCards();
	});

	mGUIContainer.pack({ fold, check, raise });
}


void GameState::fold()
{
	std::cout << "fold" << std::endl;
}

void GameState::flip()
{
	std::cout << "flip" << std::endl;

	/*playerManager.flipAnim();

	if (!deck.board.empty())
	{
		for (i = 0; i < 5; ++i)
		{
			deck.board[i]->flipAnimation.setFlipDirection(false);
			deck.board[i]->flipAnimation.start();
		}
	}*/
}

void GameState::dealCards()
{
	//panels[2]->removePlayer();
	deck->createDeck();


	deck->flop();
}

void GameState::completeRound()
{
	/*std::cout << "The board: " << std::endl << std::endl;

	for (i = 0; i < 5; ++i)
	{
		if (!deck.board.empty())
		{
			std::cout << "	" << deck.board[i]->faceValue << std::endl;

			deck.board[i]->dealAnimation.start();
		}
	}

	std::cout << std::endl;

	playerManager.findWinner();*/
}


void GameState::draw()
{
	sf::RenderWindow &window = *getContext().window;

	deck->animate();

	window.draw(*deck);

	window.draw(mSceneGraph);

	window.draw(mGUIContainer);
}

bool GameState::update(sf::Time dt)
{
	while (!mCommandQueue.isEmpty())
	{
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	}

	timeElapsed += dt;

	/*if (controllers.getCurrent()->process() || !controllers.getCurrent()->isEnabled())
	{
		controllers.goForward();
		timeElapsed = sf::Time::Zero;
	}
	*/
	player& p = panels.getCurrent()->getPlayer();
	

	if (p.process())
	{
		panels.goForward();
		std::cout << std::endl << panels.getCurrent()->getPlayer().getName() << std::endl;
		timeElapsed = sf::Time::Zero;
	}

	mSceneGraph.update(dt, mCommandQueue);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Escape pressed, trigger the pause screen
		if (event.key.code == sf::Keyboard::Escape)
		{
			requestStackPush(States::Pause);
		}
	}

	for (int i = 0; i < 9; ++i)
	{
		panels[i]->handleEvent(event);
	}

	mGUIContainer.handleEvent(event);

	return true;
}