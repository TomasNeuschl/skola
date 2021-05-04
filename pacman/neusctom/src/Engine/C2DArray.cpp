#include <Engine/C2DArray.h>

C2DArray::C2DArray(int width, int height)
{
    array.resize(width);
    for (int i = 0; i < width; ++i)
    {
        array[i].resize(height);
    }
}
C2DArray::~C2DArray() {}
/// Returns element at `x` `y`.
char C2DArray::at(int x, int y) const
{
    return array[y][x];
}
/// Sets `value` of element at `x` `y`.
void C2DArray::set(int x, int y, char value)
{
    array[y][x] = value;
}
/// Width size of the array.
size_t C2DArray::width() const
{
    return array.size();
}
/// Height size of the array.
size_t C2DArray::height() const
{
    return array[0].size();
}