#pragma once

// SFML
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

// Box2D
#include <box2d/b2_draw.h>

///
class b2DrawSFML : public b2Draw
{
public:

    ///
    explicit b2DrawSFML(float scale = 1.0f) noexcept;

    ///
    explicit b2DrawSFML(sf::RenderTarget& renderTarget, float scale = 1.0f) noexcept;

    ///
    void SetAllFlags() noexcept;

    ///
    void SetRenderTarget(sf::RenderTarget& renderTarget) noexcept;

    ///
    sf::RenderTarget& GetRenderTarget() noexcept;

    ///
    void SetScale(float scale) noexcept;

    ///
    float GetScale() noexcept;

    ///
    void DrawPolygon(b2Vec2 const* vertices, int32 vertexCount, b2Color const& color) noexcept;

    ///
    void DrawSolidPolygon(b2Vec2 const* vertices, int32 vertexCount, b2Color const& color) noexcept;

    ///
    void DrawCircle(b2Vec2 const& center, float radius, b2Color const& color) noexcept;

    ///
    void DrawSolidCircle(b2Vec2 const& center, float radius, b2Vec2 const& axis, b2Color const& color) noexcept;

    ///
    void DrawSegment(b2Vec2 const& p1, b2Vec2 const& p2, b2Color const& color) noexcept;

    ///
    void DrawTransform(b2Transform const& xf) noexcept;

    ///
    void DrawPoint(b2Vec2 const& p, float size, b2Color const& color) noexcept;

private:

    /// PRIV:
    float M_ToPixels(float f) const noexcept;

    /// PRIV:
    sf::Vector2f M_ToPixels(b2Vec2 const& p) const noexcept;

    /// PRIV:
    sf::Color M_ConvertColor(b2Color const& color) const noexcept;

    /// PRIV:
    sf::Color M_ConvertColor(b2Color const& color, float newAlpha) const noexcept;

    sf::RenderTarget* m_renderTarget;
    sf::ConvexShape m_convexShape;
    sf::CircleShape m_circleShape;
    float m_scale;
};
