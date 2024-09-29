#ifndef SJ_CDEF_H_INCLUDED
#define SJ_CDEF_H_INCLUDED

/*
 * https://github.com/xfitgd/xfitgd/blob/main/sj_cdef.h
 * contacts Discord seongjun456
 * C personal def header made by Seong Jun, 2023/12/22
 */

#include <stdbool.h>
#include <stdint.h>
#include <string>

#define TYPEDEF_STRUCT(name, content) \
  typedef struct {                    \
    content                           \
  } name;
// 까먹으니까 만들어놓자.
/* example
TYPEDEF_STRUCT(BUFFER,
            void* addr_buf;
            int op;
            void* vBuf;
            void* node;
            );
*/

#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
#ifndef _likely_
#define _likely_(x) __builtin_expect(x, 1)
#endif
#ifndef _unlikely_
#define _unlikely_(x) __builtin_expect(x, 0)
#endif
#define _DEPRECATED_STR(str) __attribute__((deprecated(str)))
#define _DEPRECATED __attribute__((deprecated))

#define _THREAD_LOCAL __thread

#ifdef _WIN32
#define _DLL_IMPORT __attribute__((dllimport))
#define _DLL_EXPORT __attribute__((dllexport))
#else
#define _DLL_IMPORT
#define _DLL_EXPORT
#endif


#define _ALWAYS_INLINE __attribute__((always_inline)) inline

#define PACK1_STRUCT(name, content) \
  typedef struct {                 \
    content                        \
  } __attribute__((packed)) name;

#elif defined(_MSC_VER)

#define _ALWAYS_INLINE __forceinline

#define _MSVC 1

#define _DLL_IMPORT __declspec(dllimport)
#define _DLL_EXPORT __declspec(dllexport)

#ifndef _likely_
#define _likely_(x) (x)
#endif
#ifndef _unlikely_
#define _unlikely_(x) (x)
#endif
#define _DEPRECATED_STR(str) __declspec(deprecated(str))
#define _DEPRECATED __declspec(deprecated)

#define _THREAD_LOCAL __declspec(thread)

#define PACK1_STRUCT(name, content)         \
  __pragma("pack(push, 1)") typedef struct { \
    content                                 \
  } name;                                   \
  __pragma("pack(pop)")

#else
#error "unsupport compiler"
#endif

#if INTPTR_MAX == INT64_MAX
#define _BIT_64 1
#elif INTPTR_MAX == INT32_MAX
#define _BIT_32 1
#else
#error "unsupport bits"
#endif

#if __STDC_VERSION__ >= 199901L
#define _C99 1
#endif

#if __STDC_VERSION__ >= 201112L
#define _C11 1
// C11아니어도 내장함수로 구현할 수 있는거 같다. 근데 굳이..? 귀찮아서..
// MSVC의 경우 2023/10/16기준으로 /experimental:c11atomics 컴파일러 옵션이 필요하다.
#define _ATOMIC _Atomic
#endif

#if __STDC_VERSION__ >= 201710L
#define _C17 1
#endif

#if __STDC_VERSION__ >= 202311L
#define _C23 1
#endif

#define _UNUSED(x) ((void)(x))

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define _LITTLE_ENDIAN 1
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define _BIG_ENDIAN 1
#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
#define _PDP_ENDIAN 1
#else
#error "endian error"
#endif
#endif


#ifndef ARRAYSIZE
#define ARRAYSIZE(a) (sizeof(a) / sizeof(*(a)))
#endif

inline bool replaceEx(std::string& _filename, const std::string& _ex) {
  size_t lastDotIndex = _filename.rfind('.');  // 마지막 '.'의 위치 찾기

  if (lastDotIndex != std::string::npos) {  // '.'가 있는 경우
    _filename.erase(lastDotIndex);          // '.' 부터 모든 문자 제거
    _filename += _ex;                       // 새로운 확장자 추가
    return true;
  }
  return false;
}

inline bool replaceEx2(char* _filename, const char* _ex) {
  char* lastDot = strrchr(_filename, '.');  // 마지막 '.'의 위치 찾기

  if (lastDot != NULL) {     // '.'가 있는 경우
    *lastDot = '\0';         // '.' 위치에 null 문자 삽입
    strcat(_filename, _ex);  // 새로운 확장자 추가
    return true;
  }
  return false;
}
