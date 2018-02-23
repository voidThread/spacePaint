#ifndef PAINTTOOL_H
#define PAINTTOOL_H

enum class PaintTool : unsigned
{
    NN          = 1000,

    Hand        = 0,
    Pen         = 1,
    Crayon      = 2,
    Brush       = 3,
    Eraser      = 4,
    Spray       = 5,
    Line        = 6,
    Shape       = 7,
    ColorPicker = 8,
    Text        = 9,
    Selection   = 10,
    FloodFill   = 11,
    Zoom        = 12
};

#endif // PAINTTOOL_H
