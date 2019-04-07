#pragma once
#include <cstdint>
namespace e
{
	namespace lib
	{
		namespace EocHelper
		{
			namespace constant
			{
				constexpr bool IsEocMode = true;
				constexpr bool Is64bitMode = sizeof(intptr_t) == 8;
			}
		}
	}
}