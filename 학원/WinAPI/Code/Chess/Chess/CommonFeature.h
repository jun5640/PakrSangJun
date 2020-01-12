#pragma once

#define PAWN 0
#define ROOK 1
#define KINGHT 2
#define BISHOP 3
#define QUEEN 4
#define KING 5


#define BLACKTEAM 0
#define WHITETEAM 1

#define BROWNTILE 0
#define WHITETILE 1

#define BLACKPAWNPATH TEXT("Res/block_b_00.bmp")
#define BLACKKINGHTPATH TEXT("Res/block_b_01.bmp")
#define BLACKBISHOPPATH TEXT("Res/block_b_02.bmp")
#define BLACKROOKPATH TEXT("Res/block_b_03.bmp")
#define BLACKQUEENPATH TEXT("Res/block_b_05.bmp")
#define BLACKKINGPATH TEXT("Res/block_b_04.bmp")

#define WHITEPAWNPATH TEXT("Res/block_w_00.bmp")
#define WHITEKINGHTPATH TEXT("Res/block_w_01.bmp")
#define WHITEBISHOPPATH TEXT("Res/block_w_02.bmp")
#define WHITEROOKPATH TEXT("Res/block_w_03.bmp")
#define WHITEQUEENPATH TEXT("Res/block_w_05.bmp")
#define WHITEKINGPATH TEXT("Res/block_w_04.bmp")

#include <Windows.h>
#include <vector>
using namespace std;
#include <time.h>