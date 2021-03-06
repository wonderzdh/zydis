// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <windows.h>

extern "C"
{
#include "operandDef.h"
}
/*
BOOLEAN VSDBinToString(unsigned char* pBufIn, int inLen, char* pBufOut, int outLen)
{
	BOOLEAN bRet = TRUE;

	if (!pBufIn || !inLen || !pBufOut || !outLen) {
		printf("[VSDBinToString] invalid parameter!");
		return FALSE;
	}

	if ((inLen * 2 + 1) > outLen) {
		printf("[VSDBinToString] inLen:%x, outLen:%x, invalid Len!", inLen, outLen);
		return FALSE;
	}

	// 访问pBufIn的时候可能触发异常
	__try {
		for (int i = 0; i < inLen; ++i)
		{
			_snprintf(&(pBufOut[2 * i]), 3, "%02x", pBufIn[i]);
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		bRet = FALSE;
		printf("[VSDBinToString] catch exception!");
	}

	return bRet;
}
*/

int main()
{
	std::cout << "ZydisOperandDefinition size:" << sizeof(ZydisOperandDefinition) << "\n";
	std::cout << "ZydisOperandDefinition count:" << GetZyOperandDefSize() << "\n";
    std::cout << "Hello World!\n"; 

	ZydisOperandDefinition* operand_def = GetZyOperandDef();
	operand_def = &(operand_def[GetZyOperandDefSize() - 1]);

	if (0 != CheckOperandStruct())
	{
		std::cout << "CheckOperandStruct fail.\n";
	}

	getchar();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
