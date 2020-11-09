#pragma once
#define set(verStr) namespace shellcmdVersion { extern int Major, Minor, Revision; struct Parser { Parser(const char*);  }; static Parser parser(#verStr); }

set("SHELLCMD_VERSION" "0.1.0")

#undef set
