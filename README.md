C98 support.


union initialization:
detail:
https://en.cppreference.com/w/c/language/struct_initialization

The original:
const ZydisOperandDefinition operandDefinitions[] =
{
    { ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_REG, ZYDIS_OPERAND_VISIBILITY_HIDDEN, ZYDIS_OPERAND_ACTION_READ, { 0, 0, 0 }, ZYDIS_IELEMENT_TYPE_INVALID, { .reg = { ZYDIS_IMPLREG_TYPE_STATIC, { .reg = ZYDIS_REGISTER_AX } } } }
}

use ReBuildInc.py after modification:
const ZydisOperandDefinition operandDefinitions[] =
{
    { ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_REG, ZYDIS_OPERAND_VISIBILITY_HIDDEN, ZYDIS_OPERAND_ACTION_READ, { 0, 0, 0 }, ZYDIS_IELEMENT_TYPE_INVALID, { ZYDIS_REGISTER_AX << 8 | ZYDIS_IMPLREG_TYPE_STATIC } }
}
