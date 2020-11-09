#pragma once
#define set(verStr) namespace mylibVersion { extern int Major, Minor, Revision; struct Parser { Parser(const char*);  }; static Parser parser(#verStr); }

set("MYLIB_VERSION" "1.0.0")

#undef set
