# b2DrawSFML

Implementation of Box2D's b2Draw class for SFML.

## Dependencies

* C++11 capable compiler
* [SFML](https://github.com/SFML/SFML) (tested on 2.5.1)
* [Box2D](https://github.com/erincatto/box2d) (tested on 2.4.1)

## Usage

Please refer to the example below.

```cpp
// C++
#include <random>

// b2DrawSFML
#include <b2DrawSFML.hpp>

// Box2D
#include <box2d/box2d.h>

// SFML
#include <SFML/Graphics.hpp>

void CreateScene(b2World& world);

int main()
{
    // Create SFML window for application
    sf::RenderWindow window{ { 1280u, 720u }, "b2DrawSFML example" };

    // Limit framerate for sake of consistency
    window.setFramerateLimit(60u);

    // Create debug drawer for window with 10x scale
    // You can set any sf::RenderTarget as drawing target
    b2DrawSFML drawer{ window, 10.0f };

    // Set flags for things that should be drawn
    // ALWAYS remember to set at least one flag,
    // otherwise nothing will be drawn
    drawer.SetFlags(
        b2Draw::e_shapeBit |
        b2Draw::e_jointBit |
        b2Draw::e_aabbBit |
        b2Draw::e_pairBit |
        b2Draw::e_centerOfMassBit
    );

    // Create Box2D world
    b2World world{ { 0.0f, 9.80665f } };

    // Set our drawer as world's drawer
    world.SetDebugDraw(&drawer);

    // Create scene with all objects
    CreateScene(world);

    // Clock for calculating delta time (for physics simulation)
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Calculate delta time as float seconds
        auto const dt = clock.restart().asSeconds();

        // Calculate physics
        world.Step(dt, 6, 2);

        // Clear window
        window.clear();

        // Draw debug shapes of all physics objects
        world.DebugDraw();

        // Display window content
        window.display();
    }

    return 0;
}

void CreateScene(b2World& world)
{
    auto rng = std::mt19937{ std::random_device{}() };
    auto vposDist = std::uniform_real_distribution<float>{ 10.0f, 118.0f };
    auto hposDist = std::uniform_real_distribution<float>{ 10.0f, 30.0f };
    auto angleDist = std::uniform_real_distribution<float>{ 0.0f, 3.14159f };
    auto sizeDist = std::uniform_real_distribution<float>{ 1.0f, 3.0f };

    {
        b2BodyDef bdef;
        b2PolygonShape shape;

        // Upper platform
        bdef.position = { 64.0f, 2.0f };
        shape.SetAsBox(60.0f, 1.0f);
        world.CreateBody(&bdef)->CreateFixture(&shape, 0.0f);

        // Bottom platform
        bdef.position = { 64.0f, 70.0f };
        shape.SetAsBox(60.0f, 1.0f);
        world.CreateBody(&bdef)->CreateFixture(&shape, 0.0f);

        // Left wall
        bdef.position = { 3.0f, 36.0f };
        shape.SetAsBox(0.5f, 32.0f);
        world.CreateBody(&bdef)->CreateFixture(&shape, 0.0f);

        // Right wall
        bdef.position = { 125.0f, 36.0f };
        shape.SetAsBox(0.5f, 32.0f);
        world.CreateBody(&bdef)->CreateFixture(&shape, 0.0f);

        // Middle mixer
        bdef.type = b2_kinematicBody;
        bdef.position = { 64.0f, 36.0f };
        shape.SetAsBox(32.0f, 0.5f);
        b2Body* body = world.CreateBody(&bdef);
        body->CreateFixture(&shape, 1.0f);
        body->SetAngularVelocity(1.0f);
    }

    // Falling squares
    for (size_t i = 0; i < 30; ++i)
    {
        b2BodyDef bdef;
        bdef.type = b2_dynamicBody;
        bdef.position = { vposDist(rng), hposDist(rng) };

        b2PolygonShape shape;
        shape.SetAsBox(sizeDist(rng), sizeDist(rng));

        world.CreateBody(&bdef)->CreateFixture(&shape, 1.0f);
    }

    // Falling circles
    for (size_t i = 0; i < 30; ++i)
    {
        b2BodyDef bdef;
        bdef.type = b2_dynamicBody;
        bdef.position = { vposDist(rng), hposDist(rng) };
        bdef.angle = angleDist(rng);

        b2CircleShape shape;
        shape.m_radius = sizeDist(rng);

        world.CreateBody(&bdef)->CreateFixture(&shape, 1.0f);
    }
}
```

## Scaling

To ensure best precision Box2D uses units called *meters* which is just a fancy name for small floats because floating-point numbers lose precision when the number gets bigger. That's why it's the best to keep size of your physics object in range from 0.0f to 10.0f and then use scale while rendering.

## License

MIT, see [license](/LICENSE) for more information.
