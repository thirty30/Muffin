#pragma once

#undef COLUMN_ITEM_INDEX
#undef COLUMN_ITEM_N32
#undef COLUMN_ITEM_N64
#undef COLUMN_ITEM_F32
#undef COLUMN_ITEM_STR

#undef ROF_TABLE_HEAD
#undef COLUMN_ITEM
#undef ROF_TABLE_TAIL

#define ROF_TABLE_HEAD(Name) \
n32 T_INLINE CRof##Name::ReadBody(const tcchar* a_pData, n32 a_nLimit){	\
n32 nOffset = 0;	\
const tcchar* pStart = a_pData;
#define COLUMN_ITEM(T, Name)	\
nOffset = DeSerialize##Name(pStart, a_nLimit);	\
if (nOffset == -1) { return -1; }	\
pStart += nOffset;	\
a_nLimit -= nOffset;
#define ROF_TABLE_TAIL(Name) return (n32)(pStart - a_pData); }


