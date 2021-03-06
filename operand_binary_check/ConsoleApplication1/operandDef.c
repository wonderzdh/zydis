#include "operandDef.h"
#include "OperandDefinitions.inc"
#include "NewOperandDefinitions.inc"
#include <memory.h>

ZydisOperandDefinition* GetZyOperandDef()
{
	return &(operandDefinitions[0]);
}

int GetZyOperandDefSize()
{
	return ( sizeof(operandDefinitions) / sizeof(operandDefinitions[0]) );
}

int CheckOperandStruct()
{
	int n;
	int size = sizeof(operandDefinitions);
	if (size != sizeof(operandDefinitionsNew))
	{
		return -1;
	}
	
	n = memcmp(operandDefinitions, operandDefinitionsNew, size);

	return n;
}