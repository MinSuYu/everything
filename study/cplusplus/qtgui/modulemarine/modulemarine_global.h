#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MODULEMARINE_LIB)
#  define MODULEMARINE_EXPORT Q_DECL_EXPORT
# else
#  define MODULEMARINE_EXPORT Q_DECL_IMPORT
# endif
#else
# define MODULEMARINE_EXPORT
#endif
