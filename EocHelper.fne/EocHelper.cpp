#include "stdafx.h"
#include "EocHelper.h"
#include "elib/lib2.h"
#include "elib/lang.h"
#include "elib/fnshare.h"
#include "elib/fnshare.cpp"
#include <stdlib.h>

//------------------------库常量、命令、数据类型定义区-----------------------------


#ifndef __E_STATIC_LIB
LIB_CONST_INFO Consts[] =
{
	/* { 中文名称, 英文名称, 常量布局, 常量等级(LVL_), 参数类型(CT_), 文本内容, 数值内容 } */
	{ _WT("是否为EOC模式"), _WT("IsEocMode"), NULL, LVL_HIGH, CT_BOOL, NULL, 0 },//数值常量,
	{ _WT("是否为64位模式"), _WT("Is64bitMode"), NULL, LVL_HIGH, CT_BOOL, NULL, 0 }//数值常量
};
#endif


/*
   常量等级有: LVL_SIMPLE          1        // 初级 
	LVL_SECONDARY       2        // 中级 
	LVL_HIGH            3        // 高级 

	参数类型有 : CT_NUM             1    // sample: 3.1415926 
	CT_BOOL            2    // sample: 1 
	CT_TEXT            3    // sample: "abc" 

	文本内容是CT_TEXT用，数值内容是CT_NUM和CT_BOOL用。
*/


//定义自定义数据类型
#ifndef __E_STATICLIB

static LIB_DATA_TYPE_INFO s_DataType[] =
{
	/*m_szName*/                _T("平台整数"),
	/*m_szEgName*/              _T("intptr"),
	/*m_szExplain*/             NULL,
	/*m_nCmdCount*/             0,      // 没有成员方法
	/*m_pnCmdsIndex*/           NULL,
	/*m_dwState*/               LDT_ENUM,
	/*m_dwUnitBmpID*/           0,
	/*m_nEventCount*/           0,      // 必须为 0 。
	/*m_pEventBegin*/           NULL,
	/*m_nPropertyCount*/        0,      // 必须为 0 。
	/*m_pPropertyBegin*/        NULL,
	/*m_pfnGetInterface*/       NULL,   // 必须为 NULL 。
	/*m_nElementCount*/         0,
	/*m_pElementBegin*/         0,
};




//INT DatatypeCommandIndexs[] =
//{
//	2
//};
//static LIB_DATA_TYPE_INFO DataTypes[] =
//{
//	/* { 中文名称, 英文名称, 数据描述, 索引数量, 命令索引, 对象状态, 图标索引, 事件数量, 事件指针, 属性数量, 属性指针, 界面指针, 元素数量, 元素指针 } */
//	{ _WT("测试数据类型"), _WT("DatatypeCommand"), _WT("测试数据类型命令"), sizeof(DatatypeCommandIndexs) / sizeof(DatatypeCommandIndexs[0]), DatatypeCommandIndexs, NULL, 0, 0, NULL, 0, NULL, NULL, 0, NULL },
//	{ _WT("字体"), _WT("ziti"), _WT("字体类型"), sizeof(DatatypeCommandIndexs) / sizeof(DatatypeCommandIndexs[0]), DatatypeCommandIndexs, NULL, 0, 0, NULL, 0, NULL, NULL, 0, NULL }
//};
#endif

// 关于LIB_DATA_TYPE_INFO的解释 以及 窗口型数据的定义 都可参见开发文档中 "m_pDataType成员说明"和"数据类型说明"。

//定义命令

EXTERN_C void EocHelper_ToIntPtr(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	switch (pArgInf[0].m_dtDataType)
	{
	case SDT_BYTE:
		pRetData->m_int = pArgInf[0].m_byte;
		break;
	case SDT_SHORT:
		pRetData->m_int = pArgInf[0].m_short;
		break;
	case SDT_INT:
		pRetData->m_int = pArgInf[0].m_int;
		break;
	case SDT_INT64:
		pRetData->m_int = pArgInf[0].m_int64;
		break;
	case SDT_FLOAT:
		pRetData->m_int = pArgInf[0].m_float;
		break;
	case SDT_DOUBLE:
		pRetData->m_int = pArgInf[0].m_double;
		break;
	case SDT_BOOL:
		pRetData->m_int = pArgInf[0].m_bool;
		break;
	case SDT_SUB_PTR:
		pRetData->m_int = (int)pArgInf[0].m_pdwSubCodeAdr;
		break;
	case SDT_TEXT:
		pRetData->m_int = atol(pArgInf[0].m_pText);
		break;
	default:
		pRetData->m_int = 0;
		break;
	}
};

EXTERN_C void EOCAttribute_AutoParam(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	return;
}

/*
函数的实现都需要定义在宏的外面以便静态和动态库都能使用，但ExecuteCommand，Commands则只需定义在宏的里面供动态库使用。
pRetData 输出数据指针。当对应CMD_INFO中m_dtRetType为_SDT_NULL（即定义无返回值）时，pRetData无效；
iArgCount 函数参数个数
pArgInf 函数参数指针
*/



#ifndef __E_STATIC_LIB
PFN_EXECUTE_CMD ExecuteCommand[] =
{
	EocHelper_ToIntPtr, // 所有需要库中调用的函数都列在这里，用逗号隔开
	EOCAttribute_AutoParam
};
static const char* const CommandNames[] =
{
	"EocHelper_ToIntPtr", // 所有需要库中调用的函数名都写在这里，用逗号隔开
	"EOCAttribute_AutoParam"
};
ARG_INFO ArgsInfo_ToIntPtr[] =
{
	/* { 参数名称, 参数描述, 图像索引, 图像数量, 参数类型(参见SDT_), 默认数值, 参数类别(参见AS_) } */
	{ _WT("数据"), _WT("待转换的数据"), 0, 0, _SDT_ALL, NULL, NULL }
};
ARG_INFO ArgsInfo_EOCAttribute_AutoParam[] =
{
	{ _WT("参数"), _WT("待标记的子程序参数"), 0, 0, _SDT_ALL, NULL, NULL }
};
static CMD_INFO Commands[] =
{
	/* { 中文名称, 英文名称, 对象描述, 所属类别(-1是数据类型的方法), 命令状态(CT_), 返回类型(SDT_), 此值保留, 对象等级(LVL_), 图像索引, 图像数量, 参数个数, 参数信息 } */
	{ _WT("到平台整数"), _WT("ToIntPtr"), _WT("类似 到整数/到长整数"), 1, 0, 1, 0, LVL_HIGH, 0, 0, 1, ArgsInfo_ToIntPtr },
	{ _WT("EOC标记_自适应参数"), _WT("EOCAttribute_AutoParam"), _WT("【必须放置在子程序开头】仅在非成员方法中可用，用于将参数标记为自适应（Auto）类型，非EOC程序自动忽略"), 1, CT_DISABLED_IN_RELEASE, _SDT_NULL, 0, LVL_HIGH, 0, 0, 1, ArgsInfo_EOCAttribute_AutoParam },
};
#endif




//--------------------------------------------------------------------

EXTERN_C INT WINAPI EocHelper_ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
#ifndef __E_STATIC_LIB
	if (nMsg == NL_GET_CMD_FUNC_NAMES) // 返回所有命令实现函数的的函数名称数组(char*[]), 支持静态编译的动态库必须处理
		return (INT)CommandNames;
	else if (nMsg == NL_GET_NOTIFY_LIB_FUNC_NAME) // 返回处理系统通知的函数名称(PFN_NOTIFY_LIB函数名称), 支持静态编译的动态库必须处理
		return (INT)"EocHelper_ProcessNotifyLib";
	else if (nMsg == NL_GET_DEPENDENT_LIBS) return (INT)NULL;
	// 返回静态库所依赖的其它静态库文件名列表(格式为\0分隔的文本,结尾两个\0), 支持静态编译的动态库必须处理
	// kernel32.lib user32.lib gdi32.lib 等常用的系统库不需要放在此列表中
	// 返回NULL或NR_ERR表示不指定依赖文件  
#endif
	return ProcessNotifyLib(nMsg, dwParam1, dwParam2);
};


#ifndef __E_STATIC_LIB
static LIB_INFO LibInfo =
{
	/* { 库格式号, GUID串号, 主版本号, 次版本号, 构建版本号, 系统主版本号, 系统次版本号, 核心库主版本号, 核心库次版本号,
	支持库名, 支持库语言, 支持库描述, 支持库状态,
	作者姓名, 邮政编码, 通信地址, 电话号码, 传真号码, 电子邮箱, 主页地址, 其它信息,
	类型数量, 类型指针, 类别数量, 命令类别, 命令总数, 命令指针, 命令入口,
	附加功能, 功能描述, 消息指针, 超级模板, 模板描述,
	常量数量, 常量指针, 外部文件} */
	LIB_FORMAT_VER,
	_T(LIB_GUID_STR),
	LIB_MajorVersion,
	LIB_MinorVersion,
	LIB_BuildNumber,
	LIB_SysMajorVer,
	LIB_SysMinorVer,
	LIB_KrnlLibMajorVer,
	LIB_KrnlLibMinorVer,
	_T(LIB_NAME_STR),
	__GBK_LANG_VER,
	_WT(LIB_DESCRIPTION_STR),
	_LIB_OS(__OS_WIN),
	_WT(LIB_Author),
	_WT(LIB_ZipCode),
	_WT(LIB_Address),
	_WT(LIB_Phone),
	_WT(LIB_Fax),
	_WT(LIB_Email),
	_WT(LIB_HomePage),
	_WT(LIB_Other),
	sizeof(s_DataType) / sizeof(s_DataType[0]),
	s_DataType,
	LIB_TYPE_COUNT,
	_WT(LIB_TYPE_STR),
	sizeof(Commands) / sizeof(Commands[0]),
	Commands,
	ExecuteCommand,
	NULL,
	NULL,
	EocHelper_ProcessNotifyLib,
	NULL,
	NULL,
	sizeof(Consts) / sizeof(Consts[0]),
	Consts,
	NULL
};
PLIB_INFO WINAPI GetNewInf()
{
	return (&LibInfo);
};
#endif


