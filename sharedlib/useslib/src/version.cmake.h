#pragma once
#define set(verStr) namespace useslibVersion { extern int Major, Minor, Revision; struct Parser { Parser(const char*);  }; static Parser parser(#verStr); }

set("USESLIB_VERSION" "0.1.0")

#undef set
