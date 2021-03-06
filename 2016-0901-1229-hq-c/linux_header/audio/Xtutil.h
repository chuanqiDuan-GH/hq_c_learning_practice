/*
 * Copyright 1993 Network Computing Devices, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name Network Computing Devices, Inc. not be
 * used in advertising or publicity pertaining to distribution of this 
 * software without specific, written prior permission.
 * 
 * THIS SOFTWARE IS PROVIDED 'AS-IS'.  NETWORK COMPUTING DEVICES, INC.,
 * DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING WITHOUT
 * LIMITATION ALL IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR NONINFRINGEMENT.  IN NO EVENT SHALL NETWORK
 * COMPUTING DEVICES, INC., BE LIABLE FOR ANY DAMAGES WHATSOEVER, INCLUDING
 * SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES, INCLUDING LOSS OF USE, DATA,
 * OR PROFITS, EVEN IF ADVISED OF THE POSSIBILITY THEREOF, AND REGARDLESS OF
 * WHETHER IN AN ACTION IN CONTRACT, TORT OR NEGLIGENCE, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * $NCDId: @(#)Xtutil.h,v 1.5 1994/09/19 22:40:13 greg Exp $
 * 
 * 			      <audio/xtutil.h>
 * 
 * This file contains declarations for utilities that may be used with Xt.
 */

#ifndef _AUDIO_XTUTIL_H_
#define _AUDIO_XTUTIL_H_

/*
 * This file must be included after:
 *
 * #include <X11/Intrinsic.h>
 * #include <audio/audiolib.h>
 */

#include <setjmp.h>

/*
 * AuXtErrorJump - Point to which an error handler can return to have
 * the audio handling code exit cleanly to the Xt event loop.
 */

extern jmp_buf AuXtErrorJump;

_AUFUNCPROTOBEGIN

/*
 * AuXtHandleAudioEvents - this routine extracts the AuServer from the
 * Xt callback data and then calls AuHandleEvents.
 */
extern void AuXtHandleAudioEvents (
	XtPointer,	/* caller_arg */
	int *,		/* ptr_to_source */
	XtInputId *	/* opaque_inputid */
);


/*
 * AuXtAppAddAudioHandler - this routine adds AuXtHandleAudioEvents as an
 * Xt input handler to deal with audio events.  This allows the audio service
 * to be used from Xt programs without disturbing their main loop.
 */
extern XtInputId AuXtAppAddAudioHandler (
	XtAppContext,	/* app_context */
        AuServer *	/* server */
);

extern void
AuXtAppRemoveAudioHandler(
       AuServer *,		/* server */
       XtInputId
);

_AUFUNCPROTOEND

#endif /* _AUDIO_XTUTIL_H_ */
