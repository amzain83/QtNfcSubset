/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2012
 * Research In Motion Limited. All rights reserved.
 */

#ifndef NFC_NDEF_GLOBAL_H
#define NFC_NDEF_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(NFC_NDEF_LIBRARY)
#  define NFC_NDEFSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NFC_NDEFSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NFC_NDEF_GLOBAL_H
