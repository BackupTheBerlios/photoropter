#! /usr/bin/python

'''Convert emor.txt and inv_emor.txt into header file format so it can be
included in a C++ class'''

import re

def print_seq(file, key, vals):
    first = True
    l = ""
    i = 0
    for v in vals:
        if first:
            first = False
        else:
            l = l + ", "

        if (i % 8) == 0:
            l = l + "\n"
        i = i + 1

        l = l + str(v)

    print >>file, "const double GammaEMOR::%s_[] = {%s};" % (key, l)

def convert(basename):    
    inp = open(basename + ".txt")

    key = ""
    all_seq = {}
    cur_seq = []
    first = True;

    for line in inp:
        match = re.match(r'\s*(\S+.*?)\s*=', line)

        if (match):
            if (not first):
                all_seq[key] = cur_seq
                cur_seq = []

            else:
                first = False;

            key = match.group(1)

        else:
            line_parts = re.split(r"\s+", line)

            for p in line_parts:
                try:
                    num = float(p)
                    cur_seq.append(num)
                except:
                    pass

    all_seq[key] = cur_seq
    cur_seq = []

    outp = open("modpar_" + basename + ".h", "w")
    print >>outp, '''/*
*
* Sensor response curve data converted from '%s.txt'
*
* The EMOR model was proposed and described by  M.D. Grossberg
* and S.K. Nayar from the University of Columbia (Computer
* Vision Laboratory). For more information on EMoR please visit
*
* http://www.cs.columbia.edu/CAVE/software/softlib/dorf.php
*
*/
/// @cond''' % basename


    param_seq = []
    param_keys = {}
    dst_seq = []
    for key in all_seq.keys():
        match = re.match(r'(\S+)\((\d+)\)', key)
        if (match):
            c = match.group(1)
            n = int(match.group(2))
            s = "%s%02i" % (c,n)

            param_seq.append(s)
            param_keys[s] = key

        else:
            print_seq(outp, key, all_seq[key])

    param_seq.sort()

    for key in param_seq:
        print_seq(outp, key, all_seq[param_keys[key]])

    print >>outp, "/// @endcond"
    outp.close()
    inp.close()

convert("emor")
convert("invemor")
