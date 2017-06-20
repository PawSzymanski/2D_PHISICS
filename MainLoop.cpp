#include "MainLoop.h"


MainLoop::MainLoop() : gravity(0.0f, 9.8)
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
    square[2].color = sf::Color::White;
    square[3].position = sf::Vector2f(-0.5, 0.5);
    square[3].color = sf::Color::White;


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
	

    createPolygon(sf::Vector2f(8.75, 10.15), sf::Vector2f(0, 0), 0, 0, 1);
    createPolygon(sf::Vector2f(0.5, 4.5), sf::Vector2f(0, 0), 90, 0, 1);
    createPolygon(sf::Vector2f(17, 4.5), sf::Vector2f(0, 0), 90, 0, 1);

    auto p1 = createPolygon(sf::Vector2f(3,1), sf::Vector2f(0,0),0,0,3);
    auto c1 = createCircle(sf::Vector2f(5,2), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c2 = createCircle(sf::Vector2f(5,3), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c3 = createCircle(sf::Vector2f(5,4), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c4 = createCircle(sf::Vector2f(5,5), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c5 = createCircle(sf::Vector2f(5,6), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);

    createJoint(p1,c1,sf::Vector2f(0,0),sf::Vector2f(0,0),1);
    createJoint(c1,c2,sf::Vector2f(0,0),sf::Vector2f(0,0),1);
    createJoint(c2,c3,sf::Vector2f(0,0),sf::Vector2f(0,0),1);
    createJoint(c3,c4,sf::Vector2f(0,0),sf::Vector2f(0,0),1);
    createJoint(c4,c5,sf::Vector2f(0,0),sf::Vector2f(0,0),1);

    auto p2 = createPolygon(sf::Vector2f(7,3), sf::Vector2f(0,0),0,0,3);
    auto p3 = createPolygon(sf::Vector2f(14,3), sf::Vector2f(0,0),0,0,3);
    auto c6 = createCircle(sf::Vector2f(8,3), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c7 = createCircle(sf::Vector2f(9,3), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c8 = createCircle(sf::Vector2f(10,3), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c9 = createCircle(sf::Vector2f(11,3), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);
    auto c10 = createCircle(sf::Vector2f(12,3), sf::Vector2f(0,0),1,sf::Color::Green,0.3f);

    createJoint(p2,c6,sf::Vector2f(0,0),sf::Vector2f(0,0),1.5f);
    createJoint(c6,c7,sf::Vector2f(0,0),sf::Vector2f(0,0),1.5f);
    createJoint(c7,c8,sf::Vector2f(0,0),sf::Vector2f(0,0),1.5f);
    createJoint(c8,c9,sf::Vector2f(0,0),sf::Vector2f(0,0),1.5f);
    createJoint(c9,c10,sf::Vector2f(0,0),sf::Vector2f(0,0),1.5f);
    createJoint(c10,p3,sf::Vector2f(0,0),sf::Vector2f(0,0),1.5f);

}

MainLoop::~MainLoop()
{
}

void MainLoop::setSystems()
{
    ex.systems.add<JointSystem>();
    ex.systems.add<RenderSystem>(window);
    ex.systems.add<MouseDragSystem>(window, camera, mouse_posf);
    ex.systems.add<ForcesSystem>(ex.events);
    ex.systems.add<CollisionSystem>(gravity);
    ex.systems.add<MovementSystem>();
    ex.systems.configure();
}

void MainLoop::update(float dt)
{
    ex.systems.update<CollisionSystem>(dt);
    ex.systems.update<JointSystem>(dt);
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

	int poligonsCount = 0;
	while (window.isOpen())
	{	
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			createCircle(mouse_posf, sf::Vector2f(0, 0), 1, sf::Color::Green, 0.25f);
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
                    createPolygon(mouse_posf, sf::Vector2f(0, 0), 180, 3, 0);
					++poligonsCount;
					std::cout << "obj Count: " << poligonsCount << std::endl;
				}
				else if (event.key.code == sf::Keyboard::W)
				{
					createPolygon(mouse_posf, sf::Vector2f(0, 0), 0, 5, 2);
					++poligonsCount;
					std::cout << "obj Count: " << poligonsCount << std::endl;
				}	
				else if (event.key.code == sf::Keyboard::E)
				{
					createPolygon(mouse_posf, sf::Vector2f(0, 0), 0, 5, 3);
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

entityx::Entity MainLoop::createCircle(sf::Vector2f pos, sf::Vector2f vel, float mass, sf::Color col, float r)
{
    auto en = ex.entities.create();
    en.assign<Position>(pos);
    en.assign<Rotation>(0);
    en.assign<LinearVelocity>(vel);
    en.assign<AngularVelocity>(0);
    en.assign<Circle>(r, col);
    en.assign<Line>(sf::Vector2f(0,0),sf::Vector2f(r, 0), sf::Color::Black);
    en.assign<Transform>(pos, 0.0);
    en.assign<AngularForce>();
    en.assign<LinearForce>();
    en.assign<Mass>(mass);
    en.assign<MOfInertia>(0.5f* mass *r*r);
    en.assign<Friction>(0.7);
    en.assign<Type>(Type::CIRCLE);
    en.assign<IsResting>();

    return en;
}
entityx::Entity MainLoop::createPolygon(sf::Vector2f pos, sf::Vector2f vel, float rotation, float mass, int polyIndex)
{
    auto en = ex.entities.create();
    en.assign<Rotation>(rotation);
    en.assign<Position>(pos);
    en.assign<LinearVelocity>(vel);
    en.assign<AngularVelocity>(0);
    en.assign<Transform>(pos, rotation);
    en.assign<AngularForce>();
    en.assign<LinearForce>();
    en.assign<Mass>(mass);
    en.assign<MOfInertia>(mass);
    en.assign<Friction>(0.7);
    en.assign<VertexArray>(vertCont.vertexArrays[polyIndex], vertCont.normals[polyIndex]);
    en.assign<Type>(Type::POLYGON);
    en.assign<IsResting>();

    return en;
}

void MainLoop::createJoint(entityx::Entity en1, entityx::Entity en2, sf::Vector2f pos1, sf::Vector2f pos2, float lenght)
{
    auto en = ex.entities.create();
    en.assign<Joint>(en1,en2,pos1,pos2,lenght);
    en.assign<Line>(sf::Vector2f(0,0), sf::Vector2f(0,0), sf::Color::Yellow);
}
