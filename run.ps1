# echo "Compiling..."
./make.ps1

# echo "Executing..."
gc src/in.txt | src/main.exe 2>&1 @Args | Tee-Object -FilePath src/out.txt
