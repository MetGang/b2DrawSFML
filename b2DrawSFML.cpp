#include <b2DrawSFML.hpp>

b2DrawSFML::b2DrawSFML(sf::Vector2f const& scale) noexcept
    : m_renderTarget { nullptr }
    , m_convexShape {}
    , m_circleShape {}
    , m_scale { scale }
{

}

b2DrawSFML::b2DrawSFML(sf::RenderTarget& renderTarget, sf::Vector2f const& scale) noexcept
    : m_renderTarget { &renderTarget }
    , m_convexShape {}
    , m_circleShape {}
    , m_scale { scale }
{

}

void b2DrawSFML::SetAllFlags() noexcept
{
    SetFlags(
        b2Draw::e_shapeBit |
        b2Draw::e_jointBit |
        b2Draw::e_aabbBit |
        b2Draw::e_pairBit |
        b2Draw::e_centerOfMassBit
    );
}

void b2DrawSFML::SetRenderTarget(sf::RenderTarget& renderTarget) noexcept
{
    m_renderTarget = &renderTarget;
}

void b2DrawSFML::SetScale(sf::Vector2f const& scale) noexcept
{
    m_scale = scale;
}

void b2DrawSFML::DrawPolygon(b2Vec2 const* vertices, int32 vertexCount, b2Color const& color) noexcept
{
    auto const count = static_cast<size_t>(vertexCount);

    m_convexShape.setPointCount(count);

    for (size_t i = 0; i < count; ++i)
    {
        m_convexShape.setPoint(i, M_ToPixels(vertices[i]));
    }

    m_convexShape.setFillColor(sf::Color{ 0x00000000u });
    m_convexShape.setOutlineColor(M_ConvertColor(color));
    m_convexShape.setOutlineThickness(-1.0f);

    m_renderTarget->draw(m_convexShape);
}

void b2DrawSFML::DrawSolidPolygon(b2Vec2 const* vertices, int32 vertexCount, b2Color const& color) noexcept
{
    auto const count = static_cast<size_t>(vertexCount);

    m_convexShape.setPointCount(count);

    for (size_t i = 0; i < count; ++i)
    {
        m_convexShape.setPoint(i, M_ToPixels(vertices[i]));
    }

    m_convexShape.setFillColor(M_ConvertColor(color, 0.8f));
    m_convexShape.setOutlineColor(sf::Color{ 0x00000000u });
    m_convexShape.setOutlineThickness(0.0f);

    m_renderTarget->draw(m_convexShape);
}

void b2DrawSFML::DrawCircle(b2Vec2 const& center, float radius, b2Color const& color) noexcept
{
    m_circleShape.setRadius(radius);
    m_circleShape.setPosition(M_ToPixels(center));
    m_circleShape.setOrigin({ radius, radius });
    m_circleShape.setFillColor(sf::Color{ 0x00000000u });
    m_circleShape.setOutlineColor(M_ConvertColor(color));
    m_circleShape.setOutlineThickness(-1.0f);

    m_renderTarget->draw(m_circleShape);
}

void b2DrawSFML::DrawSolidCircle(b2Vec2 const& center, float radius, b2Vec2 const& /* axis */, b2Color const& color) noexcept
{
    m_circleShape.setRadius(radius);
    m_circleShape.setPosition(M_ToPixels(center));
    m_circleShape.setOrigin({ radius, radius });
    m_circleShape.setFillColor(M_ConvertColor(color, 0.8f));
    m_circleShape.setOutlineColor(sf::Color{ 0x00000000u });
    m_circleShape.setOutlineThickness(0.0f);

    m_renderTarget->draw(m_circleShape);
}

void b2DrawSFML::DrawSegment(b2Vec2 const& p1, b2Vec2 const& p2, b2Color const& color) noexcept
{
    sf::Vertex const line[] = {
        { M_ToPixels(p1), M_ConvertColor(color) },
        { M_ToPixels(p2), M_ConvertColor(color) }
    };

    m_renderTarget->draw(line, 2u, sf::Lines);
}

void b2DrawSFML::DrawTransform(b2Transform const& xf) noexcept
{
    auto const axisScale = 0.4f;

    DrawSegment(xf.p, xf.p + axisScale * xf.q.GetXAxis(), b2Color{ 1.0f, 0.0f, 0.0f });

    DrawSegment(xf.p, xf.p + axisScale * xf.q.GetYAxis(), b2Color{ 0.0f, 1.0f, 0.0f });
}

void b2DrawSFML::DrawPoint(b2Vec2 const& p, float size, b2Color const& color) noexcept
{
    m_circleShape.setRadius(size);
    m_circleShape.setPosition(M_ToPixels(p));
    m_circleShape.setOrigin({ size, size });
    m_circleShape.setFillColor(M_ConvertColor(color));
    m_circleShape.setOutlineColor(sf::Color{ 0x00000000u });
    m_circleShape.setOutlineThickness(0.0f);

    m_renderTarget->draw(m_circleShape);
}

sf::Vector2f b2DrawSFML::M_ToPixels(b2Vec2 const& p) const noexcept
{
    return { p.x * m_scale.x, p.y * m_scale.y };
}

sf::Color b2DrawSFML::M_ConvertColor(b2Color const& color) const noexcept 
{
    return M_ConvertColor(color, color.a);
}

sf::Color b2DrawSFML::M_ConvertColor(b2Color const& color, float newAlpha) const noexcept
{
    return {
        static_cast<sf::Uint8>(color.r  * 255.0f),
        static_cast<sf::Uint8>(color.g  * 255.0f),
        static_cast<sf::Uint8>(color.b  * 255.0f),
        static_cast<sf::Uint8>(newAlpha * 255.0f)
    };
}
