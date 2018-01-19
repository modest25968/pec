#ifndef FLUIDBACK_GLOBAL_H
#define FLUIDBACK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FLUIDBACK_LIBRARY)
#  define FLUIDBACKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FLUIDBACKSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FLUIDBACK_GLOBAL_H
