#pragma once
#define set(verStr) namespace guiVersion { extern int Major, Minor, Revision; struct Parser { Parser(const char*);  }; static Parser parser(#verStr); }

set("GUI_VERSION" "0.1.0")

#undef set
