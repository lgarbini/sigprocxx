// Copyright (C) 2011 Oliver Schulz <oliver.schulz@tu-dortmund.de>

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.


#ifndef SIGPX_FILTER_H
#define SIGPX_FILTER_H

#include <functional>
#include <vector>
#include <cstddef>
#include <stdint.h>


namespace sigpx {


template<typename From, typename To> class Mapper: public std::unary_function<From, To> {
public:
	virtual To operator()(From x) = 0;

	// src and target may be the same vector if types From and To are equal
	void operator()(const std::vector<From> &src, std::vector<To> &trg);

	std::vector<To> operator()(const std::vector<From> &src);

	virtual ~Mapper() {}
};


template<typename From, typename To> void Mapper<From, To>::operator()(const std::vector<From> &src, std::vector<To> &trg) {
	trg.resize(src.size());
	for (size_t i=0; i<src.size(); ++i) trg[i] = operator()(src[i]);
}


template<typename From, typename To> std::vector<To> Mapper<From, To>::operator()(const std::vector<From> &src)
	{ std::vector<To> trg; operator()(src, trg); return trg; }




template<typename tp_Type> class Filter: public Mapper<tp_Type, tp_Type> {
public:
	virtual tp_Type operator()(tp_Type x) = 0;

	virtual ~Filter() {}
};


} // namespace sigpx


#ifdef __CINT__
#pragma link C++ class sigpx::Mapper< int8_t,   int8_t>-;
#pragma link C++ class sigpx::Mapper<uint8_t,  uint8_t>-;
#pragma link C++ class sigpx::Mapper< int16_t,  int16_t>-;
#pragma link C++ class sigpx::Mapper< int16_t,  int32_t>-;
#pragma link C++ class sigpx::Mapper< int16_t,  float>-;
#pragma link C++ class sigpx::Mapper< int16_t,  double>-;
#pragma link C++ class sigpx::Mapper<uint16_t, uint16_t>-;
#pragma link C++ class sigpx::Mapper< int32_t,  int32_t>-;
#pragma link C++ class sigpx::Mapper< int32_t,  int16_t>-;
#pragma link C++ class sigpx::Mapper< int32_t,  float>-;
#pragma link C++ class sigpx::Mapper< int32_t,  double>-;
#pragma link C++ class sigpx::Mapper<uint32_t, uint32_t>-;
#pragma link C++ class sigpx::Mapper< int64_t,  int64_t>-;
#pragma link C++ class sigpx::Mapper<uint64_t, uint64_t>-;
#pragma link C++ class sigpx::Mapper< float,    float>-;
#pragma link C++ class sigpx::Mapper< float,    double>-;
#pragma link C++ class sigpx::Mapper< double,   double>-;
#pragma link C++ class sigpx::Mapper< double,   float>-;

#pragma link C++ class sigpx::Filter<int8_t>-;
#pragma link C++ class sigpx::Filter<uint8_t>-;
#pragma link C++ class sigpx::Filter<int16_t>-;
#pragma link C++ class sigpx::Filter<uint16_t>-;
#pragma link C++ class sigpx::Filter<int32_t>-;
#pragma link C++ class sigpx::Filter<uint32_t>-;
#pragma link C++ class sigpx::Filter<int64_t>-;
#pragma link C++ class sigpx::Filter<uint64_t>-;
#pragma link C++ class sigpx::Filter<float>-;
#pragma link C++ class sigpx::Filter<double>-;
#endif

#endif // SIGPX_FILTER_H
