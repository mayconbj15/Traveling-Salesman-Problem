#!/bin/bash

#doxygen -g doxyconfig.txt

rm -rf doc

# Gera o arquivo das configurações da documentação
echo "DOXYFILE_ENCODING = UTF-8
PROJECT_NAME = Travelling_Salesman_Algorithms
RECURSIVE = YES
EXTRACT_ALL = YES
OUTPUT_LANGUAGE = Portuguese
OUTPUT_DIRECTORY = doc
GENERATE_HTML = YES
GENERATE_LATEX = NO
HAVE_DOT = YES" > doxyconfig.txt

# Gera a documentação
doxygen doxyconfig.txt

rm ./doxyconfig.txt
