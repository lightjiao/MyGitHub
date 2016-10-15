#ifndef __TEST_RESERVS_RESIZE_H__
#define __TEST_RESERVS_RESIZE_H__
#pragma once  

#include <stdio.h>
#include <iostream>  
#include <vector>  
#include <string>  

using namespace std;

class testReserve_Resize
{
public:
	int m_a;

public:
	testReserve_Resize() :m_a(0)
	{}

	testReserve_Resize(int a) :m_a(a)
	{}

	testReserve_Resize(const testReserve_Resize& A) :m_a(A.m_a)
	{}
};

extern int test_Reserve_Resize_Main();

#endif


//贴一段 探讨效率的说明
// 作者：Milo Yip
// 链接：https ://zhuanlan.zhihu.com/p/22399604
// 来源：知乎
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
// 
// 经性能分析后，发现问题仅在于一行代码：
// 
// // json.cpp
// void escapeString(
// 	StringPiece input,
// 	std::string& out,
// 	const serialization_opts& opts) {
// 	auto hexDigit = [](int c) -> char {
// 		return c < 10 ? c + '0' : c - 10 + 'a';
// 	};
// 
// 	out.reserve(out.size() + input.size() + 2); // <-- 这一行
// 	out.push_back('\"');
// 	// ...
/****************************************************************************/
// 	此行原来的意义，应该是希望预分配字符串的输出缓冲，避免过程中需要重新分配。
//  但在一般的实现中，std::string::reserve() 在空间不足时，会把缓冲设置为指明的大小。
//  由于每次的分配都是刚好够用而已，下次再输出字符串就必会再重新分配，造成 O(n^2) 的性能瓶颈。
//  而如果只是用 std::string::push_back()，它分配新空间会为现有大小的两倍（或其他倍数），达至分摊 O(n) 的时间复杂度。
//  所以，经过实验，只要删去该行，就能达到正常的性能：
/****************************************************************************/