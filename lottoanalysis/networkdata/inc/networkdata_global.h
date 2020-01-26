#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NETWORKDATA_LIB)
#  define NETWORKDATA_EXPORT Q_DECL_EXPORT
# else
#  define NETWORKDATA_EXPORT Q_DECL_IMPORT
# endif
#else
# define NETWORKDATA_EXPORT
#endif
