// RayTracer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "World/World.h"
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[])
{

    World w;
    w.Build();
    w.RenderScene();
	return 0;
}