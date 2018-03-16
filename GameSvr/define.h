#pragma once

#ifdef UNICODE
using STRING = wstring;
#else
using STRING = string;
#endif // !UNICODE