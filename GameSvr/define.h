#pragma once

#ifdef UNICODE
using STRING = wstring;
#define TO_STRING(n) to_wstring(n)
#else
using STRING = string;
#define TO_STRING(n) to_string(n)
#endif // !UNICODE

using LOCK = recursive_mutex;
using LOCK_GUARD = lock_guard<recursive_mutex>;

#define synchronized(n) if (LOCK_GUARD(n), FALSE) {} else
#define auto_lock(n) LOCK_GUARD al(n)