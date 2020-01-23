#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LOTTOAPISERVER_LIB)
#  define LOTTOAPISERVER_EXPORT Q_DECL_EXPORT
# else
#  define LOTTOAPISERVER_EXPORT Q_DECL_IMPORT
# endif
#else
# define APISERVER_EXPORT
#endif