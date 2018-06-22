#include "stdafx.h"
#include "Geometry.h"

Geometry::Geometry() : pVB(NULL), pIB(NULL)
{
}

Geometry::~Geometry()
{
}

void Geometry::release()
{
	if (pVB != NULL)
	{
		pVB->Release();
		pVB = NULL;
	}
	if (pIB != NULL)
	{
		pIB->Release();
		pIB = NULL;
	}
}