/** 
 * @file   KawazuInclude.h
 * @brief  Header of Library's include
 * @author Maeda Takumi
 */
#ifndef KAWAZUINCLUDE_H
#define KAWAZUINCLUDE_H

// <stdio.h>, <libmingwex.a> での vsnprintf の競合を防ぐ
#define __USE_MINGW_ANSI_STDIO 0 
#define PROPID ULONG // <gdiplus.h>の#ifdefをごまかす

#include <algorithm>
#include <chrono>
#include <fstream>
#include <gdiplus.h>
#include <imm.h>
#include <iomanip>
#include <iostream>
#include <list>
#include <mmsystem.h>
#include <new>
#include <pthread.h>
#include <queue>
#include <random>
#include <regex>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <tchar.h>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include <windows.h>
#include <commctrl.h> // windows.hの後でないとダメ

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glcorearb.h>
#include <GL/glext.h>
#include <GL/wglext.h>

#endif /* KAWAZUINCLUDE_H */

