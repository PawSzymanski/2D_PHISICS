#include "MainLoop.h"


MainLoop::MainLoop()  
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(1280, 720), "engine", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	camera.reset(sf::FloatRect(0, 0, 17.5, 10));
	window.setView(camera);

	sf::VertexArray triangle(sf::TriangleFan, 3);
	
	triangle[0].position = sf::Vector2f(-0.5, -0.5);
	triangle[0].color = sf::Color::Red;
	triangle[1].position = sf::Vector2f(0.5, -0.5);
	triangle[1].color = sf::Color::Red;
	triangle[2].position = sf::Vector2f(0, 1);
	triangle[2].color = sf::Color::Red;

	sf::VertexArray long_rect(sf::TriangleFan, 4);

	long_rect[0].position = sf::Vector2f(-8.5, -0.2);
	long_rect[0].color = sf::Color::Black;
	long_rect[1].position = sf::Vector2f(8.5, -0.2);
	long_rect[1].color = sf::Color::Black;
	long_rect[2].position = sf::Vector2f(8.5, 0.2);
	long_rect[2].color = sf::Color::Black;
	long_rect[3].position = sf::Vector2f(-8.5, 0.2);
	long_rect[3].color = sf::Color::Black;

	sf::VertexArray potato(sf::TriangleFan, 6);

	potato[0].position = sf::Vector2f(-0.4, -0.5);
	potato[0].color = sf::Color::Yellow;
	potato[1].position = sf::Vector2f(0.6, -0.5);
	potato[1].color = sf::Color::Yellow;
	potato[2].position = sf::Vector2f(0.8, -0.2);
	potato[2].color = sf::Color::Yellow;
	potato[3].position = sf::Vector2f(0.3, 0.4);
	potato[3].color = sf::Color::Yellow;
	potato[4].position = sf::Vector2f(-0.6, 0.6);
	potato[4].color = sf::Color::Yellow;
	potato[5].position = sf::Vector2f(-0.8, 0.3);
	potato[5].color = sf::Color::Yellow;


	vertCont.addPoly(triangle, 3);
	vertCont.addPoly(long_rect, 4);
	vertCont.addPoly(potato, 6);


	createCircle(sf::Vector2f(5, 1.8), sf::Vector2f(0, 0), 1, sf::Color::Green, 0.5f);
	//createCircle(sf::Vector2f(5, 5), sf::Vector2f(0, 0), 1, sf::Color::Green, 0.5f);

	createPolygon(sf::Vector2f(5, 6.7), sf::Vector2f(0, 0), 0, 1, 0);
	createPolygon(sf::Vector2f(7, 7), sf::Vector2f(0, 0), 0, 1, 2);

	createPolygon(sf::Vector2f(8.75, 10.15), sf::Vector2f(0, 0), 0, 0, 1);
	createPolygon(sf::Vector2f(0.5, 4.5), sf::Vector2f(0, 0), 90, 0, 1);
	createPolygon(sf::Vector2f(17, 4.5), sf::Vector2f(0, 0), 90, 0, 1);
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
			else if (event.type == sf::Event::MouseMoved)
			{
			sf::Vector2i mouse_pos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
				mouse_posf = window.mapPixelToCoords(mouse_pos, camera);					
			}
			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
			{
				createCircle(mouse_posf, sf::Vector2f(0, 0), 1, sf::Color::Green, 0.25f);
			}
			if (event.type == sf::Event::KeyPressed)
			{
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{ }
			
			}

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

void MainLoop::createCircle(sf::Vector2f pos, sf::Vector2f vel, float mass, sf::Color col, float r)
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
	en.assign<Mass>(mass);
	en.assign<MOfInertia>(0.5f* mass *r*r);
	en.assign<Friction>(0.7);
	en.assign<Type>(Type::CIRCLE);
}
void MainLoop::createPolygon(sf::Vector2f pos, sf::Vector2f vel, float rotation, int mass, int polyIndex)
{
	auto en = ex.entities.create();
	en.assign<Rotation>(rotation);
	en.assign<Position>(pos);
	en.assign<LinearVelocity>(vel);
	en.assign<AngularVelocity>(0);
	en.assign<Transform>();
	en.assign<AngularForce>();
	en.assign<LinearForce>();
	en.assign<Mass>(mass);
	en.assign<MOfInertia>(mass);
	en.assign<Friction>(0.7);
	en.assign<VertexArray>(vertCont.vertexArrays[polyIndex], vertCont.normals[polyIndex]);
	en.assign<Type>(Type::POLYGON);
}