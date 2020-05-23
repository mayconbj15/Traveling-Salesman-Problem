#doxygen -g doxyconfig.txt

# Gera o arquivo das configurações da documentação
echo "DOXYFILE_ENCODING = UTF-8
PROJECT_NAME = Travelling Salesman Problem Algorithms
RECURSIVE = YES
EXTRACT_ALL = YES
OUTPUT_LANGUAGE = Portuguese
OUTPUT_DIRECTORY = doc
GENERATE_HTML = YES
GENERATE_LATEX = NO" | Out-File -Encoding "UTF8" doxyconfig.txt
# Caso você esteja num sistema unix, substitua a linha a cima por:
# GENERATE_LATEX = NO" > doxyconfig.txt

# Gera a documentação
doxygen doxyconfig.txt

rm ./doxyconfig.txt
