// Copyright (C) YEAR AUTHOR <EMAIL>

// This is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.


#ifndef SIGPX_HELLOWORLD_H
#define SIGPX_HELLOWORLD_H

#include <Rtypes.h>


namespace tmplns {


class HelloWorld {
public:
	void run();

	HelloWorld();
	virtual ~HelloWorld();
};


} // namespace tmplns


#ifdef __CINT__
#pragma link C++ class tmplns::HelloWorld-;
#endif

#endif // SIGPX_HELLOWORLD_H
