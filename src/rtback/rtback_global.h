#ifndef RTBACK_GLOBAL_H
#define RTBACK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RTBACK_LIBRARY)
#  define RTBACKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RTBACKSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RTBACK_GLOBAL_H
