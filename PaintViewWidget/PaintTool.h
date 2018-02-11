#ifndef PAINTTOOL_H
#define PAINTTOOL_H

enum class PaintTool : unsigned
{
    NN          = 1000,

    Pen         = 0,
    Eraser      = 1,
    Spray       = 2,
    Line        = 3,
    Shape       = 4,
    ColorPicker = 5,
    Text        = 6,
    Selection   = 7,
    FloodFill   = 8
};

#endif // PAINTTOOL_H
