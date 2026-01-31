#ifndef __DEBUG_H__
#define __DEBUG_H__

#if (IF_DEBUG_1 == 1)
#define __DEBUG_1(...) Serial.print(__VA_ARGS__);
#else
#define __DEBUG_1(...)
#endif

#if (IF_DEBUG_2 == 1)
#define __DEBUG_2(...) Serial.print(__VA_ARGS__);
#else
#define __DEBUG_2(...)
#endif

#if (IF_DEBUG_3 == 1)
#define __DEBUG_3(...) Serial.print(__VA_ARGS__);
#else
#define __DEBUG_3(...)
#endif

#if (IF_DEBUG_4 == 1)
#define __DEBUG_4(...) Serial.print(__VA_ARGS__);
#else
#define __DEBUG_4(...)
#endif

#endif