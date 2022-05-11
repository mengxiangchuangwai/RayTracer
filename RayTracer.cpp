// RayTracer.cpp : 定义控制台应用程序的入口点。
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