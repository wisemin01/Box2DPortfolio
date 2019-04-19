#pragma once

template <typename T>
void Lerp(T* dot, const T& p1, const T& p2, float speed = 0.2f)
{
	*dot = p1 + (p2 - p1) * speed;
}

static bool Inspection(const RECT* rc, const Vector3* pt)
{
	return (pt->x <= rc->right &&
		pt->x >= rc->left &&
		pt->y <= rc->bottom &&
		pt->y >= rc->top);
}