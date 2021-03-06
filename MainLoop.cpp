#include "MainLoop.h"


MainLoop::MainLoop() : gravity(0.0f, 9.8), phisics(ex, vertCont, gravity)
{
    phisics.init();

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
    triangle[1].color = sf::Color::Yellow;
    triangle[2].position = sf::Vector2f(0, 1);
    triangle[2].color = sf::Color::White;

    sf::VertexArray long_rect(sf::TriangleFan, 4);

    long_rect[0].position = sf::Vector2f(-9.5, -0.2);
    long_rect[0].color = sf::Color::Black;
    long_rect[1].position = sf::Vector2f(9.5, -0.2);
    long_rect[1].color = sf::Color::Black;
    long_rect[2].position = sf::Vector2f(9.5, 0.2);
    long_rect[2].color = sf::Color::Black;
    long_rect[3].position = sf::Vector2f(-9.5, 0.2);
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
    potato[4].position = sf::Vector2f(-0.7, 0.9);
    potato[4].color = sf::Color::Yellow;
    potato[5].position = sf::Vector2f(-0.8, -0.0);
    potato[5].color = sf::Color::Yellow;

    sf::VertexArray square(sf::TriangleFan, 4);

    square[0].position = sf::Vector2f(-0.5, -0.5);
    square[0].color = sf::Color::Black;
    square[1].position = sf::Vector2f(0.5, -0.5);
    square[1].color = sf::Color::Black;
    square[2].position = sf::Vector2f(0.5, 0.5);
    square[2].color = sf::Color::Black;
    square[3].position = sf::Vector2f(-0.5, 0.5);
    square[3].color = sf::Color::Black;


    vertCont.addPoly(triangle, 3);
    vertCont.addPoly(long_rect, 4);
    vertCont.addPoly(potato, 6);
    vertCont.addPoly(square, 4);


    //createCircle(sf::Vector2f(5, 1.8), sf::Vector2f(0, 0), 1, sf::Color::Green, 0.5f);
    //createCircle(sf::Vector2f(5, 5), sf::Vector2f(0, 0), 1, sf::Color::Green, 0.5f);

    //createPolygon(sf::Vector2f(5, 6.7), sf::Vector2f(0, 0), 0, 1, 0);
    //createPolygon(sf::Vector2f(10, 7), sf::Vector2f(0, 0), 0, 1, 2);


//    createPolygon(sf::Vector2f(8.75, 9.64), sf::Vector2f(0, 0), 0, 1 , 3);
//    createPolygon(sf::Vector2f(8.75, 8.63), sf::Vector2f(0, 0), 0, 1 , 3);
//    createPolygon(sf::Vector2f(8.75, 7.62), sf::Vector2f(0, 0), 0, 1 , 3);
//    createPolygon(sf::Vector2f(8.75, 6.61), sf::Vector2f(0, 0), 0, 1 , 3);
//    createPolygon(sf::Vector2f(8.75, 5.60), sf::Vector2f(0, 0), 0, 1 , 3);
//    createPolygon(sf::Vector2f(8.75, 4.59), sf::Vector2f(0, 0), 0, 1 , 3);
//    createPolygon(sf::Vector2f(8.75, 3.58), sf::Vector2f(0, 0), 0, 1, 3);
	
    auto poly1 = ex.entities.create();
    auto poly2 = ex.entities.create();
    auto poly3 = ex.entities.create();

    phisics.createPolygon(poly1,sf::Vector2f(8.75, 10.15), sf::Vector2f(0, 0), 0, 0, 1);
    phisics.createPolygon(poly2,sf::Vector2f(0.5, 4.5), sf::Vector2f(0, 0), 90, 0, 1);
    phisics.createPolygon(poly3,sf::Vector2f(17, 4.5), sf::Vector2f(0, 0), 90, 0, 1);



	auto player1 = ex.entities.create();
	phisics.createPolygon(player1 , sf::Vector2f(1.5 , 9), sf::Vector2f(0, 0),0, 1, 3);


	auto engine1 = ex.entities.create();

	engine1.assign<Position>(sf::Vector2f(0, 0));
	engine1.assign<ForcePoint>(sf::Vector2f(0, 0), sf::Vector2f(0, -0.2));
	engine1.assign<KeyAssigned>(sf::Keyboard::X);
	engine1.assign<Line>(sf::Vector2f(0, 0), sf::Vector2f(0, 0),sf::Color::Magenta);

	auto engine2 = ex.entities.create();
	engine2.assign<Position>(sf::Vector2f(0, 0));
	engine2.assign<ForcePoint>(sf::Vector2f(0.5, 0), sf::Vector2f(0, -0.2));
	engine2.assign<KeyAssigned>(sf::Keyboard::C);
	engine2.assign<Line>(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color::Magenta);

	auto engine3 = ex.entities.create();
	engine3.assign<Position>(sf::Vector2f(0, 0));
	engine3.assign<ForcePoint>(sf::Vector2f(-0.5, 0), sf::Vector2f(0, -0.2));
	engine3.assign<KeyAssigned>(sf::Keyboard::Z);
	engine3.assign<Line>(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color::Magenta);

	/*auto engine4 = ex.entities.create();
	engine4.assign<Line>();
	engine4.assign<Position>(sf::Vector2f(0, 0));
	engine4.assign<LinearForce>(sf::Vector2f(0, 0));
	engine4.assign<ForcePoint>(sf::Vector2f(0, 0));
	engine4.assign<KeyAssigned>(sf::Keyboard::Z);
	engine4.assign<Line>();

	auto engine5 = ex.entities.create();
	engine5.assign<Line>();
	engine5.assign<Position>(sf::Vector2f(0, 0));
	engine5.assign<LinearForce>(sf::Vector2f(0, 0));
	engine5.assign<ForcePoint>(sf::Vector2f(0, 0));
	engine5.assign<KeyAssigned>(sf::Keyboard::Z);
	engine5.assign<Line>();*/

/*
    auto p1 = ex.entities.create();
    phisics.createPolygon(p1, sf::Vector2f(3,1), sf::Vector2f(0,0),0,0,3);
    auto c1 = ex.entities.create();
    phisics.createCircle(c1, sf::Vector2f(5,2), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c2 = ex.entities.create();
    phisics.createCircle(c2, sf::Vector2f(5,3), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c3 = ex.entities.create();
    phisics.createCircle(c3,sf::Vector2f(5,4), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c4 = ex.entities.create();
    phisics.createCircle(c4,sf::Vector2f(5,5), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c5 = ex.entities.create(); 
    phisics.createCircle(c5,sf::Vector2f(5,6), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);

    phisics.createJoint(p1,c1,sf::Vector2f(0,0),sf::Vector2f(0,-0.2f),0.5f);
    phisics.createJoint(c1,c2,sf::Vector2f(0,0.2f),sf::Vector2f(0,-0.2f),0.5f);
    phisics.createJoint(c2,c3,sf::Vector2f(0,0.2f),sf::Vector2f(0,-0.2f),0.5f);
    phisics.createJoint(c3,c4,sf::Vector2f(0,0.2f),sf::Vector2f(0,-0.2f),0.5f);
    phisics.createJoint(c4,c5,sf::Vector2f(0,0.2f),sf::Vector2f(0,-0.2f),0.5f);
	
    auto p2 = ex.entities.create();
    phisics.createPolygon(p2,sf::Vector2f(7,3), sf::Vector2f(0,0),0,0,3);
    auto p3 = ex.entities.create();
    phisics.createPolygon(p3,sf::Vector2f(14,3), sf::Vector2f(0,0),0,0,3);
    auto c6 = ex.entities.create();
    phisics.createCircle(c6,sf::Vector2f(8,3), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c7 = ex.entities.create();
    phisics.createCircle(c7,sf::Vector2f(9,3), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c8 = ex.entities.create();
    phisics.createCircle(c8,sf::Vector2f(10,3), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c9 = ex.entities.create();
    phisics.createCircle(c9,sf::Vector2f(11,3), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c10 = ex.entities.create();
    phisics.createCircle(c10, sf::Vector2f(12,3), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);

    phisics.createJoint(p2,c6,sf::Vector2f(0,0),sf::Vector2f(0,0),1.5f);
    phisics.createJoint(c6,c7,sf::Vector2f(0,0),sf::Vector2f(0,0),1.5f);
    phisics.createJoint(c7,c8,sf::Vector2f(0,0),sf::Vector2f(0,0),1.5f);
    phisics.createJoint(c8,c9,sf::Vector2f(0,0),sf::Vector2f(0,0),1.5f);
    phisics.createJoint(c9,c10,sf::Vector2f(0,0),sf::Vector2f(0,0),1.5f);
    phisics.createJoint(c10,p3,sf::Vector2f(0,0),sf::Vector2f(0,0),1.5f);
	*/
}

MainLoop::~MainLoop()
{
}

void MainLoop::setSystems()
{
    ex.systems.add<RenderSystem>(window);
    ex.systems.add<MouseDragSystem>(window, camera, mouse_posf); 
	ex.systems.add<AddForceToPlayer>();
    ex.systems.configure();
}

void MainLoop::update(float dt)
{
    phisics.update(dt);
    ex.systems.update<MouseDragSystem>(dt);
	ex.systems.update<AddForceToPlayer>(dt);
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

	int poligonsCount = 0;
	while (window.isOpen())
	{	
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
            auto en = ex.entities.create();
            phisics.createCircle(en, mouse_posf, sf::Vector2f(0, 0), 1, sf::Color::Green, 0.25f);
			++poligonsCount;
			std::cout << "obj Count: " << poligonsCount << std::endl;
		}
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
//			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//			{
//				createCircle(mouse_posf, sf::Vector2f(0, 0), 1, sf::Color::Green, 0.25f);
//				++poligonsCount;
//				std::cout << "obj Count: " << poligonsCount << std::endl;
//			}
			if (event.type == sf::Event::KeyPressed)
			{
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{ }
				if (event.key.code == sf::Keyboard::Q)
				{
                    auto en = ex.entities.create();
                    phisics.createPolygon(en, mouse_posf, sf::Vector2f(0, 0), 180, 3, 0);
					++poligonsCount;
					std::cout << "obj Count: " << poligonsCount << std::endl;
				}
				else if (event.key.code == sf::Keyboard::W)
				{
                    auto en = ex.entities.create();
                    phisics.createPolygon(en, mouse_posf, sf::Vector2f(0, 0), 0, 5, 2);
					++poligonsCount;
					std::cout << "obj Count: " << poligonsCount << std::endl;
				}	
				else if (event.key.code == sf::Keyboard::E)
				{
                    auto en = ex.entities.create();
                    phisics.createPolygon(en, mouse_posf, sf::Vector2f(0, 0), 0, 5, 3);
					++poligonsCount;
					std::cout << "obj Count: " << poligonsCount << std::endl;
				}
			}
		}
		time += clock.restart();
		int counter = 0;
		while (time.asSeconds() > 0.01 && counter <= 100)
		{
			++counter;

			time -= sf::seconds(0.01f);
			//std::cout << ex.entities.size() << std::endl;
			//update(0.01f);

			time = clock.restart();
		}
		update(0.01f);
		render();
		float fps = 1.0f / fpsclock.restart().asSeconds();
		// std::cout<<"FPS: "<<fps<<" en:"<<ex.entities.size()<<std::endl;
	}
}

//entityx::Entity MainLoop::createCircle(sf::Vector2f pos, sf::Vector2f vel, float mass, sf::Color col, float r)
//{
//    auto en = ex.entities.create();

//    return en;
//}
//entityx::Entity MainLoop::createPolygon(sf::Vector2f pos, sf::Vector2f vel, float rotation, float mass, int polyIndex)
//{
//    auto en = ex.entities.create();

//    return en;
//}

//void MainLoop::createJoint(entityx::Entity en1, entityx::Entity en2, sf::Vector2f pos1, sf::Vector2f pos2, float lenght)
//{
//    auto en = ex.entities.create();

//}
