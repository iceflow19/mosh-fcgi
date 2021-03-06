//! @file  mosh/fcgi/http/conv/base64.hpp Base64 converter
/***************************************************************************
* Copyright (C) 2011 m0shbear                                              *
*                                                                          *
* This file is part of mosh-fcgi.                                          *
*                                                                          *
* mosh-fcgi is free software: you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as  published   *
* by the Free Software Foundation, either version 3 of the License, or (at *
* your option) any later version.                                          *
*                                                                          *
* mosh-fcgi is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or    *
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public     *
* License for more details.                                                *
*                                                                          *
* You should have received a copy of the GNU Lesser General Public License *
* along with mosh-fcgi.  If not, see <http://www.gnu.org/licenses/>.       *
****************************************************************************/
#ifndef MOSH_FCGI_HTTP_BASE64_HPP
#define MOSH_FCGI_HTTP_BASE64_HPP

#include <stdexcept>
#include <string>
#include <mosh/fcgi/bits/u.hpp>
#include <mosh/fcgi/http/conv/converter.hpp>
#include <mosh/fcgi/bits/namespace.hpp>

MOSH_FCGI_BEGIN

namespace http {

//! Base64 converter
struct Base64 : public Converter {
	/*! @brief Decode a quoted-printable string.
	 *
	 * @param[in] in Start of encoded data
	 * @param[in] in_end End of encoded data
	 * @param[in] in_next On return, this points to the first untranslated character
	 * @return decoded input
	 */
	u_string in(const char* in, const char* in_end, const char*& in_next) const;
	/*! @brief Encode a quoted-printable string [UNIMPLEMENTED]
	 * \warning This function is not implemented.
	 * \warning Using it will throw a std::logic_errror.
	 * @throws std::logic_error if function call is attempted
	 * @param[in] in Start of decoded data
	 * @param[in] in_end End of decoded data
	 * @param[in] in_next On return, this points to the first untranslated character
	 * @return encoded input
	 */
	std::string out(const uchar* in, const uchar* in_end, const uchar*& in_next) const {
		throw std::logic_error("mosh::fcgi::http::Base64::out: UNIMPLEMENTED");
	}
};

}

MOSH_FCGI_END

#endif
