#ifndef _OPERAND_DEF_H_
#define _OPERAND_DEF_H_



typedef unsigned __int8  ZydisU8;
typedef unsigned __int16 ZydisU16;

#include "EnumRegister.h"

/**
 * @brief   Declares a bitfield.
 */
#define ZYDIS_BITFIELD(x) : x

/**
 * @brief   Defines the @c ZydisSemanticOperandType datatype.
 */
typedef ZydisU8 ZydisSemanticOperandType;

/**
 * @brief   Defines the @c ZydisOperandVisibility datatype.
 */
typedef ZydisU8 ZydisOperandVisibility;

/**
 * @brief   Defines the @c ZydisOperandAction datatype.
 */
typedef ZydisU8 ZydisOperandAction;

/**
 * @brief   Defines the @c ZydisInternalElementType datatype.
 */
typedef ZydisU8 ZydisInternalElementType;

/**
 * @brief   Defines the @c ZydisOperandEncoding datatype.
 */
//typedef ZydisU8 ZydisOperandEncoding;
typedef ZydisU16 ZydisOperandEncoding;

/**
 * @brief   Defines the `ZydisRegister` datatype.
 */
typedef ZydisU8 ZydisRegister;

/**
 * @brief   Defines the @c ZydisOperandDefinition struct.
 */
typedef struct ZydisOperandDefinition_
{
	ZydisSemanticOperandType type           ZYDIS_BITFIELD(5);
	ZydisOperandVisibility visibility       ZYDIS_BITFIELD(2);
	ZydisOperandAction action               ZYDIS_BITFIELD(3);
	ZydisU16 size[3];
	ZydisInternalElementType elementType    ZYDIS_BITFIELD(5);
	union
	{
		ZydisOperandEncoding encoding;
		struct
		{
			ZydisU8 type                    ZYDIS_BITFIELD(3);
			union
			{
				ZydisRegister reg           ZYDIS_BITFIELD(ZYDIS_REGISTER_MIN_BITS);
				ZydisU8 id                  ZYDIS_BITFIELD(6);
			} reg;
		} reg;
		struct
		{
			ZydisU8 seg                     ZYDIS_BITFIELD(3);
			ZydisU8 base                    ZYDIS_BITFIELD(3);
		} mem;
	} op;
} ZydisOperandDefinition;

/**
 * @brief   Values that represent semantic operand-types.
 */
enum ZydisSemanticOperandTypes
{
	ZYDIS_SEMANTIC_OPTYPE_UNUSED,
	ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_REG,
	ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_MEM,
	ZYDIS_SEMANTIC_OPTYPE_IMPLICIT_IMM1,
	ZYDIS_SEMANTIC_OPTYPE_GPR8,
	ZYDIS_SEMANTIC_OPTYPE_GPR16,
	ZYDIS_SEMANTIC_OPTYPE_GPR32,
	ZYDIS_SEMANTIC_OPTYPE_GPR64,
	ZYDIS_SEMANTIC_OPTYPE_GPR16_32_64,
	ZYDIS_SEMANTIC_OPTYPE_GPR32_32_64,
	ZYDIS_SEMANTIC_OPTYPE_GPR16_32_32,
	ZYDIS_SEMANTIC_OPTYPE_FPR,
	ZYDIS_SEMANTIC_OPTYPE_MMX,
	ZYDIS_SEMANTIC_OPTYPE_XMM,
	ZYDIS_SEMANTIC_OPTYPE_YMM,
	ZYDIS_SEMANTIC_OPTYPE_ZMM,
	ZYDIS_SEMANTIC_OPTYPE_BND,
	ZYDIS_SEMANTIC_OPTYPE_SREG,
	ZYDIS_SEMANTIC_OPTYPE_CR,
	ZYDIS_SEMANTIC_OPTYPE_DR,
	ZYDIS_SEMANTIC_OPTYPE_MASK,
	ZYDIS_SEMANTIC_OPTYPE_MEM,
	ZYDIS_SEMANTIC_OPTYPE_MEM_VSIBX,
	ZYDIS_SEMANTIC_OPTYPE_MEM_VSIBY,
	ZYDIS_SEMANTIC_OPTYPE_MEM_VSIBZ,
	ZYDIS_SEMANTIC_OPTYPE_IMM,
	ZYDIS_SEMANTIC_OPTYPE_REL,
	ZYDIS_SEMANTIC_OPTYPE_PTR,
	ZYDIS_SEMANTIC_OPTYPE_AGEN,
	ZYDIS_SEMANTIC_OPTYPE_MOFFS,
	ZYDIS_SEMANTIC_OPTYPE_MIB
};

/**
 * @brief   Values that represent operand-visibilities.
 */
enum ZydisOperandVisibilities
{
	ZYDIS_OPERAND_VISIBILITY_INVALID,
	/**
	 * @brief   The operand is explicitly encoded in the instruction.
	 */
	ZYDIS_OPERAND_VISIBILITY_EXPLICIT,
	/**
	 * @brief   The operand is part of the opcode, but listed as an operand.
	 */
	ZYDIS_OPERAND_VISIBILITY_IMPLICIT,
	/**
	 * @brief   The operand is part of the opcode, and not typically listed as an operand.
	 */
	ZYDIS_OPERAND_VISIBILITY_HIDDEN,

	/**
	 * @brief   Maximum value of this enum.
	 */
	ZYDIS_OPERAND_VISIBILITY_MAX_VALUE = ZYDIS_OPERAND_VISIBILITY_HIDDEN
};

/**
 * @brief   Values that represent operand-actions.
 */
enum ZydisOperandActions
{
	ZYDIS_OPERAND_ACTION_INVALID,
	/**
	 * @brief   The operand is read by the instruction.
	 */
	ZYDIS_OPERAND_ACTION_READ,
	/**
	 * @brief   The operand is written by the instruction (must write).
	 */
	ZYDIS_OPERAND_ACTION_WRITE,
	/**
	 * @brief   The operand is read and written by the instruction (must write).
	 */
	ZYDIS_OPERAND_ACTION_READWRITE,
	/**
	 * @brief   The operand is conditionally read by the instruction.
	 */
	ZYDIS_OPERAND_ACTION_CONDREAD,
	/**
	 * @brief   The operand is conditionally written by the instruction (may write).
	 */
	ZYDIS_OPERAND_ACTION_CONDWRITE,
	/**
	 * @brief   The operand is read and conditionally written by the instruction (may write).
	 */
	ZYDIS_OPERAND_ACTION_READ_CONDWRITE,
	/**
	 * @brief   The operand is written and conditionally read by the instruction (must write).
	 */
	ZYDIS_OPERAND_ACTION_CONDREAD_WRITE,

	/**
	 * @brief   Mask combining all writing access flags.
	 */
	ZYDIS_OPERAND_ACTION_MASK_WRITE = ZYDIS_OPERAND_ACTION_WRITE |
	ZYDIS_OPERAND_ACTION_READWRITE | ZYDIS_OPERAND_ACTION_CONDWRITE |
	ZYDIS_OPERAND_ACTION_READ_CONDWRITE | ZYDIS_OPERAND_ACTION_CONDREAD_WRITE,
	/**
	 * @brief   Mask combining all reading access flags.
	 */
	ZYDIS_OPERAND_ACTION_MASK_READ = ZYDIS_OPERAND_ACTION_READ | ZYDIS_OPERAND_ACTION_READWRITE |
	ZYDIS_OPERAND_ACTION_CONDREAD | ZYDIS_OPERAND_ACTION_READ_CONDWRITE |
	ZYDIS_OPERAND_ACTION_CONDREAD_WRITE,

	/**
	 * @brief   Maximum value of this enum.
	 */
	ZYDIS_OPERAND_ACTION_MAX_VALUE = ZYDIS_OPERAND_ACTION_CONDREAD_WRITE
};

/**
 * @brief   Values that represent internal element-types.
 */
enum ZydisInternalElementTypes
{
	ZYDIS_IELEMENT_TYPE_INVALID,
	ZYDIS_IELEMENT_TYPE_VARIABLE,
	ZYDIS_IELEMENT_TYPE_STRUCT,
	ZYDIS_IELEMENT_TYPE_INT,
	ZYDIS_IELEMENT_TYPE_UINT,
	ZYDIS_IELEMENT_TYPE_INT1,
	ZYDIS_IELEMENT_TYPE_INT8,
	ZYDIS_IELEMENT_TYPE_INT16,
	ZYDIS_IELEMENT_TYPE_INT32,
	ZYDIS_IELEMENT_TYPE_INT64,
	ZYDIS_IELEMENT_TYPE_UINT8,
	ZYDIS_IELEMENT_TYPE_UINT16,
	ZYDIS_IELEMENT_TYPE_UINT32,
	ZYDIS_IELEMENT_TYPE_UINT64,
	ZYDIS_IELEMENT_TYPE_UINT128,
	ZYDIS_IELEMENT_TYPE_UINT256,
	ZYDIS_IELEMENT_TYPE_FLOAT16,
	ZYDIS_IELEMENT_TYPE_FLOAT32,
	ZYDIS_IELEMENT_TYPE_FLOAT64,
	ZYDIS_IELEMENT_TYPE_FLOAT80,
	ZYDIS_IELEMENT_TYPE_BCD80
};

/**
 * @brief   Values that represent implicit-register types.
 */
enum ZydisImplicitRegisterType
{
	ZYDIS_IMPLREG_TYPE_STATIC,
	ZYDIS_IMPLREG_TYPE_GPR_OSZ,
	ZYDIS_IMPLREG_TYPE_GPR_ASZ,
	ZYDIS_IMPLREG_TYPE_GPR_SSZ,
	ZYDIS_IMPLREG_TYPE_IP_ASZ,
	ZYDIS_IMPLREG_TYPE_IP_SSZ,
	ZYDIS_IMPLREG_TYPE_FLAGS_SSZ
};

/**
 * @brief   Values that represent implicit-memory base-registers.
 */
enum ZydisImplicitMemBase
{
	ZYDIS_IMPLMEM_BASE_ABX,
	ZYDIS_IMPLMEM_BASE_ASP,
	ZYDIS_IMPLMEM_BASE_ABP,
	ZYDIS_IMPLMEM_BASE_ASI,
	ZYDIS_IMPLMEM_BASE_ADI
};

/**
 * @brief   Values that represent operand-encodings.
 */
enum ZydisOperandEncodings
{
	ZYDIS_OPERAND_ENCODING_NONE,
	ZYDIS_OPERAND_ENCODING_MODRM_REG,
	ZYDIS_OPERAND_ENCODING_MODRM_RM,
	ZYDIS_OPERAND_ENCODING_OPCODE,
	ZYDIS_OPERAND_ENCODING_NDSNDD,
	ZYDIS_OPERAND_ENCODING_IS4,
	ZYDIS_OPERAND_ENCODING_MASK,
	ZYDIS_OPERAND_ENCODING_DISP8,
	ZYDIS_OPERAND_ENCODING_DISP16,
	ZYDIS_OPERAND_ENCODING_DISP32,
	ZYDIS_OPERAND_ENCODING_DISP64,
	ZYDIS_OPERAND_ENCODING_DISP16_32_64,
	ZYDIS_OPERAND_ENCODING_DISP32_32_64,
	ZYDIS_OPERAND_ENCODING_DISP16_32_32,
	ZYDIS_OPERAND_ENCODING_UIMM8,
	ZYDIS_OPERAND_ENCODING_UIMM16,
	ZYDIS_OPERAND_ENCODING_UIMM32,
	ZYDIS_OPERAND_ENCODING_UIMM64,
	ZYDIS_OPERAND_ENCODING_UIMM16_32_64,
	ZYDIS_OPERAND_ENCODING_UIMM32_32_64,
	ZYDIS_OPERAND_ENCODING_UIMM16_32_32,
	ZYDIS_OPERAND_ENCODING_SIMM8,
	ZYDIS_OPERAND_ENCODING_SIMM16,
	ZYDIS_OPERAND_ENCODING_SIMM32,
	ZYDIS_OPERAND_ENCODING_SIMM64,
	ZYDIS_OPERAND_ENCODING_SIMM16_32_64,
	ZYDIS_OPERAND_ENCODING_SIMM32_32_64,
	ZYDIS_OPERAND_ENCODING_SIMM16_32_32,
	ZYDIS_OPERAND_ENCODING_JIMM8,
	ZYDIS_OPERAND_ENCODING_JIMM16,
	ZYDIS_OPERAND_ENCODING_JIMM32,
	ZYDIS_OPERAND_ENCODING_JIMM64,
	ZYDIS_OPERAND_ENCODING_JIMM16_32_64,
	ZYDIS_OPERAND_ENCODING_JIMM32_32_64,
	ZYDIS_OPERAND_ENCODING_JIMM16_32_32,

	/**
	 * @brief   Maximum value of this enum.
	 */
	ZYDIS_OPERAND_ENCODING_MAX_VALUE = ZYDIS_OPERAND_ENCODING_JIMM16_32_32
};

ZydisOperandDefinition* GetZyOperandDef();
int GetZyOperandDefSize();
int CheckOperandStruct();

#endif  // _OPERAND_DEF_H_