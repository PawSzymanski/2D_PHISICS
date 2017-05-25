#include "MainLoop.h"


MainLoop::MainLoop()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(1280, 720), "engine", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	camera.reset(sf::FloatRect(0, 0, 17.5, 10));
	window.setView(camera);

	createCircle(sf::Vector2f(1, 1), sf::Vector2f(2, 2), 0.5f, sf::Color::Green);
	createCircle(sf::Vector2f(5, 5), sf::Vector2f(0, 0), 0.5f, sf::Color::Red);
}

MainLoop::~MainLoop()
{
}



void MainLoop::setSystems()
{
	ex.systems.add<RenderSystem>(window);
	ex.systems.add<MovementSystem>();
	ex.systems.add<MouseDragSystem>(window, camera);
	ex.systems.add<ForcesSystem>(ex.events);
	ex.systems.add<CollisionSystem>();
	ex.systems.configure();
}

void MainLoop::update(float dt)
{
	ex.systems.update<CollisionSystem>(dt);
	ex.systems.update<MouseDragSystem>(dt);
	ex.systems.update<ForcesSystem>(dt);
	ex.systems.update<MovementSystem>(dt);
}

void MainLoop::render()
{
	ex.systems.update<RenderSystem>(0);
}

void MainLoop::loop()
{
	sf::Time time = sf::Time::Zero;
	sf::Clock clock, fpsclock;
	setSystems();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{


			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
			//else if (event.type == sf::Event::MouseMoved)
			//{
			//	sf::Vector2i mouse_pos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
			//	mouse_posf = window.mapPixelToCoords(mouse_pos, camera);
			//	//std::cout<<"mouse: "<<mouse_posf.x<<" "<<mouse_posf.y<<std::endl;
			//	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			//		createCircle(mouse_posf, sf::Vector2f(0, 0), 1, 1, 0.25, 0.05, 0.07);
			//}
			//else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			//{
			//	createCircle(mouse_posf, sf::Vector2f(0, 0), 1, 4, 0.5, 0.05, 0.07);
			//}

		}
		time += clock.restart();
		int counter = 0;
		while (time.asSeconds() > 0.01 && counter <= 100)
		{
			++counter;

			time -= sf::seconds(0.01f);

			update(0.01f);

			time = clock.restart();
		}
		render();

		float fps = 1.0f / fpsclock.restart().asSeconds();
		// std::cout<<"FPS: "<<fps<<" en:"<<ex.entities.size()<<std::endl;
	}
}

void MainLoop::createCircle(sf::Vector2f pos, sf::Vector2f vel, float r, sf::Color col)
{
	auto en = ex.entities.create();
	en.assign<Position>(pos);
	en.assign<Rotation>(0);
	en.assign<LinearVelocity>(vel);
	en.assign<AngularVelocity>(0);
	en.assign<Circle>(r, col);
	en.assign<Line>(sf::Vector2f(0,0),sf::Vector2f(r, 0), sf::Color::Black);
	en.assign<Transform>();
	en.assign<AngularForce>();
	en.assign<LinearForce>();
	en.assign<Mass>(1);
	en.assign<MOfInertia>(0.5f *r*r);
}