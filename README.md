# b2DrawSFML

Implementation of Box2D's b2Draw class for SFML.

## Dependencies

* C++11 capable compiler
* [SFML](https://github.com/SFML/SFML) (tested on 2.5.1)
* [Box2D](https://github.com/erincatto/box2d) (tested on 2.4.1)

## Usage

Please refer to the example below.

```cpp
// b2DrawSFML
#include <b2DrawSFML.hpp>

// SFML
#include <SFML/Graphics.hpp>

// Box2D
#include <box2d/box2d.h>

void CreateScene(b2World& world)
{
    // Crate your scene with all objects here
}

int main()
{
    // Create SFML window for application
    sf::RenderWindow window{ { 1280u, 720u }, "b2DrawSFML example" };

    // Limit framerate for sake of consistency
    window.setFramerateLimit(60u);

    // Create debug drawer for window with 10x scale
    // You can set any sf::RenderTarget as drawing target
    b2DrawSFML drawer{ window, { 10.0f, 10.0f } };

    // Set flags for things that should be drawn
    // ALWAYS rememeber to set at least one flag
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
```

## Scaling

To ensure best precision Box2D uses units called *meters* which is just a fancy name for small floats because floating-point numbers lose precision when the number gets bigger. That's why it's the best to keep size of your physics object in range from 0.0f to 10.0f and then use scale while rendering.

## License

MIT, see [license](/LICENSE) for more information.
