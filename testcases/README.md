Here’s my suggested process for creating test cases using only chArm-v1 instructions (listed in chArm-v1.pdf). 
You can do all of this on your laptop. (Don’t do this on the UTCS Linux boxes, because AFAIK you can’t run docker on them.)

1. Make sure you have docker installed and the docker daemon running (e.g., using Docker Desktop). Go to docker.com for information on how 
   to do this.
2. Write your test case in C, as shown in the file gcd.c.
3. You will also need the Makefile and Dockerfile attached below.
4. Run "make all". This will be quite slow the first time (as it will build the docker image), but subsequent runs will be a lot faster.
5. Examine the ASM file (gcd.s). 
6. If your test case routine and start() use only chArm-v1 instructions, you are done. [There is the small issue that the boilerplate 
   code may still contain non-chArm-v1 instructions. This is not a problem, since I have implementations of these instructions from 
   last semester which I will drop into the emulator startup code. The better solution would of course be to rewrite the boilerplate code 
   using chArm-v1 instructions only; I’ll do this cleanup at a later date unless someone wants to volunteer to do it now. In any case, 
   this shouldn’t impact the students.]
7. If not, use the gcd.s file as the starting point, and rewrite the non-chArm instructions using chArm ones in the ASM file.
8. Rebuild the binary and objdump output from this modified gcd.s (you’ll need to update the Makefile and Dockerfile targets — I’ll let 
   y’all figure that piece out).
9. Upload the chArm-v1 binary (gcd) and the objdump output (gcd.od) to this directory. 

As always, this is how I do it, but there are undoubtedly other ways as well. If you come up with a better workflow, please share it.