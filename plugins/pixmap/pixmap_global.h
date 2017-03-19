#ifndef PIXMAP_GLOBAL_H
#define PIXMAP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PIXMAP_LIBRARY)
#  define PIXMAPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PIXMAPSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PIXMAP_GLOBAL_H
