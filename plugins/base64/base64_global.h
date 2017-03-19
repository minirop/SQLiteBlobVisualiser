#ifndef BASE64_GLOBAL_H
#define BASE64_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BASE64_LIBRARY)
#  define BASE64SHARED_EXPORT Q_DECL_EXPORT
#else
#  define BASE64SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BASE64_GLOBAL_H
