#Include Directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(CORE OBJECT
	transceiver.cpp
	request.cpp
	fcgistream.cpp
	exceptions.cpp
	manager.cpp
	bits/tempfile.cpp
	bits/sha/sha1.c
	bits/boyer_moore.cpp
	bits/rwlock.cpp
	bits/utf8.cpp
	bits/hash.cpp
	protocol/funcs.cpp
	protocol/message.cpp
	protocol/vars.cpp)

add_library(HTTP OBJECT 
	http/url.cpp
	http/session-timpl.cpp
	http/header/helper.cpp
	http/header/status.cpp
	http/header/redirect.cpp
	http/header/x_sendfile.cpp
	http/header/response.cpp
	http/header/content_type.cpp
	http/header/header.cpp
	http/header/cookie.cpp
	http/converter.cpp
	http/mime.cpp
	http/base64.cpp
	http/qp.cpp
	http/session.cpp
	http/cookie.cpp
	http/misc.cpp)

add_library(HTML OBJECT html/html_doctype.cpp html/element.cpp)
