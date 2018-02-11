#ifndef PAINTTOOL_H
#define PAINTTOOL_H

enum class PaintTool : unsigned
{
    NN          = 1000,

    Hand        = 0,
    Pen         = 1,
    Eraser      = 2,
    Spray       = 3,
    Line        = 4,
    Shape       = 5,
    ColorPicker = 6,
    Text        = 7,
    Selection   = 8,
    FloodFill   = 9
};

#endif // PAINTTOOL_H
