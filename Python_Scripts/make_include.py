#!/usr/bin/env python 
#Argument order is arguments. then name of file. must start in directory it began in

import sys
import os

prefix = ''
num_prefix_folders = 0
files_to_make = []



def set_prefix_folder_num():
    num_prefix_folders = 0
    if len(prefix):
        num_prefix_folders = num_prefix_folders + 1
        
    for x in prefix:
        if x == '/' or x == '\\':
            num_prefix_folders = num_prefix_folders + 1
            
    print "Num Prefix[%d] : Prefix: [%s]" % (num_prefix_folders, prefix)
    return num_prefix_folders

x = 1

#parsing args
while x < len(sys.argv):
    print(sys.argv[x][0])
    if sys.argv[x][0] != '-':
        break
    
    option_char = sys.argv[x][1]
    
    if 'p' == option_char:
        prefix = sys.argv[x+1]
        x = x + 1
        num_prefix_folders = set_prefix_folder_num()
        print 'num prefix folders[%d]'  %(num_prefix_folders)       
    
    x = x + 1


MAX_DEPTH = 4
found_include_folder = False
include_depth = 1

include_str = '..'

rest_of_path, path_to_file = os.path.split(os.getcwd())

print (" PWD: [", path_to_file , "]")

while include_depth < MAX_DEPTH:
    if os.path.exists(include_str + '/' + 'include'):
        found_include_folder = True
        break
    
    include_depth = include_depth + 1
    include_str = include_str = '/..'
    next_piece = ''
    rest_of_path, next_piece = os.path.split(rest_of_path)
    path_to_file = next_piece + '/' + path_to_file


print("Path to file: [" , path_to_file , "]")

if not found_include_folder:
    print("Could Not Find Include Folder")
    exit()
    
        
        

for file in sys.argv[x:]:
    include_path = include_str  + '/include/' + prefix
    if not os.path.exists(include_path):
        print 'Making path [%s]' %(include_path)
        os.mkdir(include_path)
    new_file = include_path +  '/' + file
    print "Include File: [%s]" % (new_file)
    dest_file = open(new_file, 'w')
    i = 0
    dest_file.write('#include "')

    while i < num_prefix_folders:
        dest_file.write('../')
        i = i+1


    dest_file.write('../' + path_to_file + '/' + file)
    dest_file.write('"')
    
    
    