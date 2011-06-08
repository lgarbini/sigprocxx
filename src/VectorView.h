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


#ifndef SIGPX_VECTORVIEW_H
#define SIGPX_VECTORVIEW_H

#include "Filter.h"


namespace sigpx {


template<typename tp_Type> class VectorIterator;



template<typename tp_Type> class VectorView {
protected:
	std::vector<tp_Type> &m_v;
	const size_t m_until;
	size_t m_from;
	const size_t m_stride;
public:
	bool empty() const { return m_from >= m_until; }
	size_t size() const { return (m_until - m_from) / m_stride; }

	const tp_Type* buffer() const { return &(m_v[0]); }
	tp_Type* buffer() { return &(operator[](0)); }
	size_t stride() const { return m_stride; }

	const tp_Type& operator[](size_t index) const { return m_v[m_from + index * m_stride]; }
	tp_Type& operator[](size_t index) { return m_v[m_from + index * m_stride]; }
	
	VectorIterator<tp_Type> iterator() const;

	inline VectorView<tp_Type>& operator=(const VectorView<tp_Type> &src) {
		size_t n = size();
		assert(n == src.size());
		for (size_t i=0; i < n; ++i) (*this)[i] = src[i];
		return *this;
	}

	inline VectorView<tp_Type>& operator=(const tp_Type &x) {
		size_t n = size();
		for (size_t i=0; i < n; ++i) (*this)[i] = x;
		return *this;
	}
	
	inline void fillTo(std::vector<tp_Type> &trg, size_t n) { iterator().fillTo(trg, n); }
	inline void fillTo(std::vector<tp_Type> &trg) { iterator().fillTo(trg); }
	inline void fillTo(TH1I &hist) { iterator().fillTo(hist); }
	inline void fillTo(TH1F &hist) { iterator().fillTo(hist); }

	std::ostream& print(std::ostream &os) { return iterator().print(os); }

	std::string toString() { return iterator().toString(); }

	VectorView(std::vector<tp_Type> &v)
		: m_v(v), m_until(v.size()), m_from(0), m_stride(1) {}

	VectorView(std::vector<tp_Type> &v, size_t fromIdx)
		: m_v(v), m_until(v.size()), m_from(fromIdx), m_stride(1) {}

	VectorView(std::vector<tp_Type> &v, size_t fromIdx, size_t untilIdx)
		: m_v(v), m_until(untilIdx), m_from(fromIdx), m_stride(1) {}

	VectorView(std::vector<tp_Type> &v, size_t fromIdx, size_t untilIdx, size_t strideLen)
		: m_v(v), m_until(untilIdx), m_from(fromIdx), m_stride(strideLen) {}

	VectorView(const VectorView<tp_Type> &v)
		: m_v(v.m_v), m_until(v.m_until), m_from(v.m_from), m_stride(v.m_stride) {}

	VectorView(const VectorView<tp_Type> &v, size_t fromIdx)
		: m_v(v.m_v), m_until(v.m_until),
		  m_from(v.m_from + fromIdx * v.m_stride), m_stride(v.m_stride) {}

	VectorView(const VectorView<tp_Type> &v, size_t fromIdx, size_t untilIdx)
		: m_v(v.m_v), m_until(v.m_from + untilIdx * v.m_stride),
		  m_from(v.m_from + fromIdx * v.m_stride), m_stride(v.m_stride) {}

	VectorView(const VectorView<tp_Type> &v, size_t fromIdx, size_t untilIdx, size_t strideLen)
		: m_v(v.m_v), m_until(v.m_from + untilIdx * v.m_stride * strideLen),
		  m_from(v.m_from + fromIdx * v.m_stride * strideLen),
		  m_stride(v.m_stride * strideLen) {}
};

typedef VectorView<int16_t> VVs;
typedef VectorView<int32_t> VVi;
typedef VectorView<float> VVf;
typedef VectorView<double> VVd;



template<typename tp_Type> class VectorIterator: public Iterator<tp_Type> {
protected:
	const std::vector<tp_Type> &m_v;
	const size_t m_until;
	size_t m_pos;
	const size_t m_stride;
public:
	bool empty() const { return m_pos >= m_until; }
	size_t size() const { return (m_until - m_pos) / m_stride; }
	
	tp_Type next() { tp_Type result = m_v[m_pos]; m_pos += m_stride; return result; }

	VectorIterator(const std::vector<tp_Type> &v, size_t fromIdx = 0)
		: m_v(v), m_until(v.size()), m_pos(fromIdx), m_stride(1) {}

	VectorIterator(const std::vector<tp_Type> &v, size_t fromIdx, size_t untilIdx)
		: m_v(v), m_until(untilIdx), m_pos(fromIdx), m_stride(1) {}

	VectorIterator(const std::vector<tp_Type> &v, size_t fromIdx, size_t untilIdx, size_t strideLen)
		: m_v(v), m_until(untilIdx), m_pos(fromIdx), m_stride(strideLen) {}
};

typedef VectorIterator<int16_t> VIs;
typedef VectorIterator<int32_t> VIi;
typedef VectorIterator<float> VIf;
typedef VectorIterator<double> VId;



template<typename tp_Type> VectorIterator<tp_Type> VectorView<tp_Type>::iterator() const
	{ return VectorIterator<tp_Type>(m_v, m_from, m_until, m_stride); }



} // namespace sigpx


#ifdef __CINT__
#pragma link C++ class sigpx::VectorView<int16_t>-;
#pragma link C++ class sigpx::VectorView<int32_t>-;
#pragma link C++ class sigpx::VectorView<float>-;
#pragma link C++ class sigpx::VectorView<double>-;

#pragma link C++ typedef sigpx::VVs;
#pragma link C++ typedef sigpx::VVi;
#pragma link C++ typedef sigpx::VVf;
#pragma link C++ typedef sigpx::VVd;

#pragma link C++ class sigpx::VectorIterator<int16_t>-;
#pragma link C++ class sigpx::VectorIterator<int32_t>-;
#pragma link C++ class sigpx::VectorIterator<float>-;
#pragma link C++ class sigpx::VectorIterator<double>-;

#pragma link C++ typedef sigpx::VIs;
#pragma link C++ typedef sigpx::VIi;
#pragma link C++ typedef sigpx::VIf;
#pragma link C++ typedef sigpx::VId;

#endif

#endif // SIGPX_VECTORVIEW_H