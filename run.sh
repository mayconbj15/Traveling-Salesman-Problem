# echo "Compiling..."
./make.sh

# echo "Executing..."
src/main.exe < src/in2.txt 2>&1 "$@" | tee src/out.txt
