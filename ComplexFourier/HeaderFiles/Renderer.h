#pragma once

#include "Header.h"
#include "Complex.h"

#define InitialWinPos   Vector2i(86,25)
#define Ex -7
#define Ey 30
#define DistanceGrid 0.5f
#define PointsRadius 1.5f
#define MaxScale 1000
#define MinScale 10

#ifdef DarkTheme
    #define GridColor   Color(15,15,15,255)
    #define PointsColor Color(100,100,100,255)
    #define AxisColor   Color(40,40,40,255)
#else
    #define GridColor   Color(170,170,170,255)
    #define PointsColor Color(100,100,100,255)
    #define AxisColor   Color(0,0,0,255)
#endif

class Renderer
{
private:
    RenderTarget& m_target;
    float Scale = 100;
    Complex Center = 0;
    Font font;

    int Width;
    int Height;

public:
    Renderer(RenderTarget& target, int width = 1180, int height = 640);

    void multiplyScale(float s);
    void setWindowDim(Vector2i dim);
    void setCenter(Complex z);
    void moveCenter(Complex z);

    float getScale();
    Complex getCenter();

    Vector2f ScPos(Complex z);
    Complex ComplexPos(Vector2f Pos);

    void RenderAxis();
    void RenderGrid();
    void RenderPlot(std::vector<Complex>& Plot, Color color = Color::Red);
    void RenderLine(Complex z0, Complex z1, Color color);
    void RenderPoint(Complex z, Color color = PointsColor, float radius = PointsRadius);
    void RenderPoints(std::vector<Complex>& z, Color color = PointsColor, float radius = PointsRadius);
};
