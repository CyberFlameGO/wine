/*
 * cap20wxx.c
 *
 * Copyright 2002-2003 AVM Computersysteme Vertriebs GmbH
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#define __NO_CAPIUTILS__

#include "config.h"

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef HAVE_LINUX_CAPI_H
# include <linux/capi.h>
#endif
#ifdef HAVE_CAPI20_H
# include <capi20.h>
#endif
#include "wine/debug.h"
#include "cap20wxx.h"

WINE_DEFAULT_DEBUG_CHANNEL(capi);

/*===========================================================================*\
\*===========================================================================*/

DWORD APIENTRY wrapCAPI_REGISTER (DWORD MessageBufferSize, DWORD maxLogicalConnection, DWORD maxBDataBlocks, DWORD maxBDataLen, DWORD *pApplID) {
#ifdef HAVE_CAPI4LINUX
    unsigned aid = 0;
    DWORD fret = capi20_register (maxLogicalConnection, maxBDataBlocks, maxBDataLen, &aid);
    *pApplID   = aid;
    TRACE ( "(%lx) -> %lx\n", *pApplID, fret);
    return fret;
#else
    FIXME ( "(), no CAPI4LINUX support compiled into WINE.\n" );
    return 0x1009;
#endif
}

/*---------------------------------------------------------------------------*\
\*---------------------------------------------------------------------------*/
DWORD APIENTRY wrapCAPI_RELEASE (DWORD ApplID) {
#ifdef HAVE_CAPI4LINUX
    DWORD fret = capi20_release (ApplID);
    TRACE ("(%lx) -> %lx\n", ApplID, fret);
    return fret;
#else
    return 0x1109;
#endif
}

/*---------------------------------------------------------------------------*\
\*---------------------------------------------------------------------------*/
DWORD APIENTRY wrapCAPI_PUT_MESSAGE (DWORD ApplID, PVOID pCAPIMessage) {
#ifdef HAVE_CAPI4LINUX
    DWORD fret = capi20_put_message (ApplID, pCAPIMessage);
    TRACE ("(%lx) -> %lx\n", ApplID, fret);
    return fret;
#else
    return 0x1109;
#endif
}

/*---------------------------------------------------------------------------*\
\*---------------------------------------------------------------------------*/
DWORD APIENTRY wrapCAPI_GET_MESSAGE (DWORD ApplID, PVOID *ppCAPIMessage) {
#ifdef HAVE_CAPI4LINUX
    DWORD fret = capi20_get_message (ApplID, (unsigned char **)ppCAPIMessage);
    TRACE ("(%lx) -> %lx\n", ApplID, fret);
    return fret;
#else
    return 0x1109;
#endif
}

/*---------------------------------------------------------------------------*\
\*---------------------------------------------------------------------------*/
DWORD APIENTRY wrapCAPI_WAIT_FOR_SIGNAL (DWORD ApplID) {
#ifdef HAVE_CAPI4LINUX
    TRACE ("(%lx)\n", ApplID);
    return capi20_waitformessage (ApplID, NULL);
#else
    return 0x1109;
#endif
}

/*---------------------------------------------------------------------------*\
\*---------------------------------------------------------------------------*/
DWORD APIENTRY wrapCAPI_GET_MANUFACTURER (char *SzBuffer) {
#ifdef HAVE_CAPI4LINUX
    DWORD fret = (capi20_get_manufacturer (0, SzBuffer) != 0) ? 0 : 0x1108;
    if (!strncmp (SzBuffer, "AVM", 3)) {
        strcpy (SzBuffer, "AVM-GmbH");
    }
    TRACE ("(%s) -> %lx\n", SzBuffer, fret);
    return fret;
#else
    return 0x1109;
#endif
}

/*---------------------------------------------------------------------------*\
\*---------------------------------------------------------------------------*/
DWORD APIENTRY wrapCAPI_GET_VERSION (DWORD *pCAPIMajor, DWORD *pCAPIMinor, DWORD *pManufacturerMajor, DWORD *pManufacturerMinor) {
#ifdef HAVE_CAPI4LINUX
    unsigned char version[4 * sizeof (unsigned)];
    DWORD fret = (capi20_get_version (0, version) != 0) ? 0 : 0x1108;
    *pCAPIMajor         = *(unsigned *)(version + 0 * sizeof (unsigned));
    *pCAPIMinor         = *(unsigned *)(version + 1 * sizeof (unsigned));
    *pManufacturerMajor = *(unsigned *)(version + 2 * sizeof (unsigned));
    *pManufacturerMinor = *(unsigned *)(version + 3 * sizeof (unsigned));
    TRACE ("(%lx.%lx,%lx.%lx) -> %lx\n", *pCAPIMajor, *pCAPIMinor, *pManufacturerMajor,
             *pManufacturerMinor, fret);
    return fret;
#else
    return 0x1109;
#endif
}

/*---------------------------------------------------------------------------*\
\*---------------------------------------------------------------------------*/
DWORD APIENTRY wrapCAPI_GET_SERIAL_NUMBER (char *SzBuffer) {
#ifdef HAVE_CAPI4LINUX
    DWORD fret = (capi20_get_serial_number (0, SzBuffer) != 0) ? 0 : 0x1108;
    TRACE ("(%s) -> %lx\n", SzBuffer, fret);
    return fret;
#else
    return 0x1109;
#endif
}

/*---------------------------------------------------------------------------*\
\*---------------------------------------------------------------------------*/
DWORD APIENTRY wrapCAPI_GET_PROFILE (PVOID SzBuffer, DWORD CtlrNr) {
#ifdef HAVE_CAPI4LINUX
    DWORD fret = capi20_get_profile (CtlrNr, SzBuffer);
    TRACE ("(%lx,%x) -> %lx\n", CtlrNr, *(unsigned short *)SzBuffer, fret);
    return fret;
#else
    return 0x1109;
#endif
}

/*---------------------------------------------------------------------------*\
\*---------------------------------------------------------------------------*/
DWORD APIENTRY wrapCAPI_INSTALLED (void) {
#ifdef HAVE_CAPI4LINUX
    DWORD fret = capi20_isinstalled();
    TRACE ("() -> %lx\n", fret);
    return fret;
#else
    return 0x1109;
#endif
}

/*---------------------------------------------------------------------------*\
\*---------------------------------------------------------------------------*/
DWORD APIENTRY wrapCAPI_MANUFACTURER (DWORD Class, DWORD Function, DWORD Ctlr, PVOID pParams, DWORD ParamsLen) {
    FIXME ("(), not supported!\n");
    return 0x1109;
}

/*---------------------------------------------------------------------------*\
\*---------------------------------------------------------------------------*/
