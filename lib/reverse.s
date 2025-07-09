/*-----------------------------------------------------------------------------
   reverse.s
   This file is distributed under the GNU General Public License, version 2 (GPLv2)
   See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html
   Author: Stephen E. MacKenzie
   ------------------------------------------------------------------------------*/
  
           .syntax unified
           .text
           .global reverse_asm
  
  /* -----------------------------------------------------------------------------
  Reverse an array of ints in place
 
  C declaration:
  reverse(int* array, const size_t len)
 
 Parameters: pointer to integer array, number of elements
 
  ------------------------------------------------------------------------------*/

swap:
    // Calculate address of element at index r8
    lsl r2, r8, #2        // r2 = r8 * 4 (size of int)
    add r2, r0, r2        // r2 = base address + r8 * 4

    // Calculate address of element at index r9
    lsl r3, r9, #2        // r3 = r9 * 4 (size of int)
    add r3, r0, r3        // r3 = base address + r9 * 4

    // Load the value at index r8 into r7 (temporary register)
    ldr r7, [r2]          // r7 = array[r8]

    // Load the value at index r9 into r4
    ldr r4, [r3]          // r4 = array[r9]

    // Store the value from r7 (originally array[r8]) into array[r9]
    str r7, [r3]          // array[r9] = r7

    // Store the value from r4 (originally array[r9]) into array[r8]
    str r4, [r2]          // array[r8] = r4

    // Return from the function
    bx lr                 // Return from the function

reverse_asm:
    stmfd   sp!, {r4-r9}   /* we will need more registers for the loops */
    mov     r8, #0          /* counter */
    mov     r9, r1
    sub     r9, r9, #1
    /* r0=s1, len=r1, index r9 is left */
for_loop:
    cmp     r8, r9
    blt     swap           /* Call swap if r8 < r9 */
    bge     reverse_done   /* Branch to done if r8 >= r9 */

    sub     r9, r9, #1
    add     r8, r8, #1
    b       for_loop

reverse_done:
    ldmfd   sp!, {r4-r9}   /* restore */
    bx      lr             /* return */

