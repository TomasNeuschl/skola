#pragma once

#include <vector>
#include <cstdlib>

/// Basically a 2D array of chars made with std::vector.
class C2DArray
{
public:
	/// Creates a 2D array with `width` and `height`.
	C2DArray(int width, int height);
	~C2DArray();
	/// Returns element at `x` `y`.
	char at(int x, int y) const;
	/// Sets `value` of element at `x` `y`.
	void set(int x, int y, char value);
	/// Width size of the array.
	size_t width() const;
	/// Height size of the array.
	size_t height() const;

private:
	/// Internal vector storage of chars.
	std::vector<std::vector<char>> array;
};