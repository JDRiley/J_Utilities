#!/usr/bin/env python 
#Argument letter of code u want

import sys
import os

if 2 != len(sys.argv):
    print "Error Wrong number of Arguments. Expected 1"
    exit()


if  1 != len(sys.argv[1]):
    print "Error First Argument is not one char"
    exit()

char_code = sys.argv[1][0]

print 'Char: [%c]\tCode: [%d]' %(char_code, ord(char_code))
exit()

  