#pragma once

#undef COLUMN_ITEM_INDEX
#undef COLUMN_ITEM_N32
#undef COLUMN_ITEM_N64
#undef COLUMN_ITEM_F32
#undef COLUMN_ITEM_STR

#undef ROF_TABLE_HEAD
#undef COLUMN_ITEM
#undef ROF_TABLE_TAIL


#define COLUMN_ITEM_INDEX(Name)	\
n32 m_n##Name;	\
n32 Get##Name() { return m_n##Name; }	\
n32 DeSerialize##Name(const tcchar* a_pData, n32 a_nLimit)	\
{	if (a_nLimit < sizeof(m_n##Name)){ return -1; }	\
TMemcpy((tcchar*)&m_n##Name, sizeof(m_n##Name), a_pData, sizeof(m_n##Name));	\
return sizeof(m_n##Name); }

#define COLUMN_ITEM_N32(Name)	\
n32 m_n##Name;	\
n32 Get##Name() { return m_n##Name; }	\
n32 DeSerialize##Name(const tcchar* a_pData, n32 a_nLimit)	\
{	if (a_nLimit < sizeof(m_n##Name)){ return -1; }	\
TMemcpy((tcchar*)&m_n##Name, sizeof(m_n##Name), a_pData, sizeof(m_n##Name));	\
return sizeof(m_n##Name); }

#define COLUMN_ITEM_N64(Name)	\
n64 m_n##Name;	\
n64 Get##Name() { return m_n##Name; }	\
n32 DeSerialize##Name(const tcchar* a_pData, n32 a_nLimit)	\
{	if (a_nLimit < sizeof(m_n##Name)){ return -1; }	\
TMemcpy((tcchar*)&m_n##Name, sizeof(m_n##Name), a_pData, sizeof(m_n##Name));	\
return sizeof(m_n##Name); }

#define COLUMN_ITEM_F32(Name)	\
f32 m_f##Name;	\
f32 Get##Name() { return m_f##Name; }	\
n32 DeSerialize##Name(const tcchar* a_pData, n32 a_nLimit)	\
{	if (a_nLimit < sizeof(m_f##Name)){ return -1; }	\
TMemcpy((tcchar*)&m_f##Name, sizeof(m_f##Name), a_pData, sizeof(m_f##Name));	\
return sizeof(m_f##Name); }

#define COLUMN_ITEM_STR(Name)	\
n32 m_n##Name##Length;	\
tcchar* m_p##Name;	\
n32 Get##Name##Length() {return (n32)m_n##Name##Length; }	\
tcchar* Get##Name() { return m_p##Name; }	\
n32 DeSerialize##Name(const tcchar* a_pData, n32 a_nLimit)	\
{	\
if (a_nLimit < sizeof(m_n##Name##Length)){ return -1; }	\
TMemcpy((tcchar*)&m_n##Name##Length, sizeof(m_n##Name##Length), a_pData, sizeof(m_n##Name##Length));	\
a_nLimit -= sizeof(m_n##Name##Length);	\
if (a_nLimit < m_n##Name##Length){ return -1; }	\
m_p##Name = new tcchar[m_n##Name##Length];	\
TMemcpy(m_p##Name, m_n##Name##Length, a_pData + sizeof(m_n##Name##Length), m_n##Name##Length);	\
return sizeof(m_n##Name##Length) + m_n##Name##Length;	\
}


#define ROF_TABLE_HEAD(Name) class CRof##Name : public CRofTableBase {	\
public:	\
	virtual n32 ReadBody(const tcchar* a_pData, n32 a_nOffset);
#define COLUMN_ITEM(T, Name) COLUMN_ITEM_##T(Name)
#define ROF_TABLE_TAIL(Name) };


