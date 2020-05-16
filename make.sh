cd src && \
    g++ -g -o main.exe \
    -std=c++14 \
    -I algorithms algorithms/*.cpp \
    main.cpp TSP.cpp graph.cpp
    