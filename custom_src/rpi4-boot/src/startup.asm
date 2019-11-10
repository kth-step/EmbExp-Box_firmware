/*
 * Derived from code with this copyright notice:
 *
 * Copyright (c) 2016 Stephen Warren <swarren@wwwdotorg.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of the copyright holder nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

.globl _start
_start:
	b cores0123

	// an infinite loop at location 0x4 (to catch all cores here after initialization)
	// (if we use a more sophisticated loop with "wfe" or a more involved one,
        //  we may need an exit strategy with a flag or something I guess)
hang:
	b hang


cores0123:
	// all four cores are executing from here

	// first, we need to stop all cores except core0
	mrs x2, MPIDR_EL1
	and x2, x2, #0xFF
	cbnz x2, cores123

	// then, core0 can move on to execute the main c function
	ldr x5, =0x00100000
	mov sp, x5
	bl main_core0
	b hang





cores123:
	sub x2, x2, #1
	cbnz x2, cores23
	// only core 1 continues

	ldr x5, =0x00200000
	mov sp, x5
	bl main_core1
	b hang


cores23:
	sub x2, x2, #1
	cbnz x2, cores3
	// only core 2 continues

	ldr x5, =0x00300000
	mov sp, x5
	bl main_core2
	b hang


cores3:
	sub x2, x2, #1
	cbnz x2, hang
	// only core 3 continues

	ldr x5, =0x00400000
	mov sp, x5
	bl main_core3
	b hang






