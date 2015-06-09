#! /usr/bin/python
import os
import sys
import l3cmnd
import fkocmnd
import cmnd

NB = 64
#M = 1600
#lda = 1600

L = 1
TEST = 1
CC = "gcc"
#CCF = "-m32 -x assembler-with-cpp"
CCF = "-x assembler-with-cpp"
(IFKOdir,fko) = fkocmnd.GetFKOinfo()
[ATLdir,ARCH] = fkocmnd.FindAtlas(IFKOdir)
uopt=""

#teopt = "-X 1 1 -Y 1 1 "
#teopt = "-X 1 1 -Y 1 1 -Fx 16 -Fy 16"
#teopt = "-X 1 1 -Y 1 1 -Fx 32 -Fy 32"
teopt = "-X 1 1 -Y 1 1 -Fy 32 -Fx 32"

nargs = len(sys.argv)
if nargs < 4:
    print 'USAGE: %s <pre> <blas> <file> [<N> <M> <lda> <uopt> <TEST> <CC> <CCF>]' % sys.argv[0]
    sys.exit(1)

pre = sys.argv[1]
blas = sys.argv[2]
file = sys.argv[3]

if nargs > 4 :
    NB = int(sys.argv[4])
    if nargs > 5 :
        beta = int(sys.argv[5])
        if nargs > 6 :
            TEST = sys.argv[6]
            if nargs > 7 :
                uopt = sys.argv[7]

#opt = "-X 1 -Y 1 " + uopt
#opt = "-X 1 -Y 1 -Fx 16 -Fy 16 " + uopt
#opt = "-X 1 -Y 1 -Fx 32 -Fy 32 " + uopt
opt = uopt
t0 = -1
mf = -1
if TEST:
    i = l3cmnd.test(ATLdir, ARCH, pre, blas, NB, beta, file, cc=CC, ccf=CCF, opt=opt)
    #i = cmnd.test(ATLdir, ARCH, pre, blas, NB, 0, 0, file, cc=CC, ccf=CCF, opt=teopt)
    if i : PF = "FAIL"
    else : 
        PF = "PASS"
        [t0,mf] = l3cmnd.time(ATLdir, ARCH, pre, blas, NB, beta, file, cc=CC, ccf=CCF, opt=opt)
else : PF = "SKIP"
print "%s%s-%s: time=%e, mflop=%.2f -- %s " % (pre, blas, file, t0, mf, PF)

