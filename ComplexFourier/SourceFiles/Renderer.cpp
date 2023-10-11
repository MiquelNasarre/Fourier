#include "Renderer.h"

Renderer::Renderer(RenderTarget& target, int width, int height)
    : m_target{ target }, Width{ width }, Height{ height }
{
}

void Renderer::multiplyScale(float s)
{
    Scale *= s;
}

void Renderer::setWindowDim(Vector2i dim)
{
    Width = dim.x;
    Height = dim.y;
}

void Renderer::setCenter(Complex z)
{
    Center = z;
}

void Renderer::moveCenter(Complex z)
{
    Center += z;
}

float Renderer::getScale()
{
    return Scale;
}

Complex Renderer::getCenter()
{
    return Center;
}

Vector2f Renderer::ScPos(Complex z)
{
    Vector2f Vec;
    Vec.x = (z.a - Center.a) * Scale + Width / 2;
    Vec.y = -(z.b - Center.b) * Scale + Height / 2;
    return Vec;
}

Complex Renderer::ComplexPos(Vector2f Pos)
{
    Complex z(Pos.x - (float)Width / 2, Height / 2 - (float)Pos.y);
    z = z / Scale + Complex(Center.a, Center.b);
    return z;
}

void Renderer::RenderGrid()
{
    Complex Origin = ComplexPos(Vector2f(0.f, 0.f));
    for (int i = 1; i < -Origin.a / DistanceGrid; i++) {
        Vertex Yaxis[] = { Vertex(ScPos(DistanceGrid * i + I * Origin.b), GridColor) ,Vertex(ScPos(DistanceGrid * i - I * Origin.b),GridColor) };
        m_target.draw(Yaxis, 2, Lines);
    }
    for (int i = 1; i < -Origin.a / DistanceGrid; i++) {
        Vertex Yaxis[] = { Vertex(ScPos(-DistanceGrid * i + I * Origin.b), GridColor) ,Vertex(ScPos(-DistanceGrid * i - I * Origin.b),GridColor) };
        m_target.draw(Yaxis, 2, Lines);
    }
    for (int i = 1; i < Origin.b / DistanceGrid; i++) {
        Vertex Yaxis[] = { Vertex(ScPos(Origin.a + I * DistanceGrid * i),GridColor),Vertex(ScPos(-Origin.a + I * DistanceGrid * i),GridColor) };
        m_target.draw(Yaxis, 2, Lines);
    }
    for (int i = 1; i < Origin.b / DistanceGrid; i++) {
        Vertex Yaxis[] = { Vertex(ScPos(Origin.a - I * DistanceGrid * i),GridColor),Vertex(ScPos(-Origin.a - I * DistanceGrid * i),GridColor) };
        m_target.draw(Yaxis, 2, Lines);
    }
}

void Renderer::RenderAxis()
{
    Vertex t0(Vector2f((float)Width / 2, 0.f));
    t0.color = AxisColor;
    Vertex t1(Vector2f((float)Width / 2, (float)Height));
    t1.color = AxisColor;
    Vertex Yaxis[] = { t0,t1 };
    m_target.draw(Yaxis, 2, Lines);

    t0.position = Vector2f(0.f, (float)Height / 2);
    t1.position = Vector2f((float)Width, (float)Height / 2);
    Vertex Xaxis[] = { t0,t1 };
    m_target.draw(Xaxis, 2, Lines);
}

void Renderer::RenderPlot(std::vector<Complex>& Plot, Color color)
{
    for (int i = 0; i < (int)Plot.size() - 1; i++) {
        Vertex line[] = { Vertex(ScPos(Plot[i]), color),Vertex(ScPos(Plot[i + 1]), color) };
        m_target.draw(line, 2, Lines);
    }
}

void Renderer::RenderLine(Complex z0, Complex z1, Color color)
{
    Vertex line[] = { Vertex(ScPos(z0), color),Vertex(ScPos(z1), color) };
    m_target.draw(line, 2, Lines);
}

void Renderer::RenderPoint(Complex z, Color color, float radius)
{
    CircleShape circle(radius);
    Vector2f Pos(ScPos(z));
    Pos.x -= radius;
    Pos.y -= radius;
    circle.setPosition(Pos);
    circle.setFillColor(color);
    m_target.draw(circle);
}

void Renderer::RenderPoints(std::vector<Complex>& z, Color color, float radius)
{
    CircleShape circle(radius);
    circle.setFillColor(color);
    Vector2f Pos;
    for (unsigned int i = 0; i < z.size(); i++) {
        Pos = ScPos(z[i]);
        Pos.x -= radius;
        Pos.y -= radius;
        circle.setPosition(Pos);
        m_target.draw(circle);
    }
}
