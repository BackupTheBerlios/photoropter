#! /bin/sh
astyle --options=misc/astylerc src/*.cpp src/*.h src/mem/*.cpp src/model/*.cpp include/*/*.h include/*/*/*.h testapp/*.cpp testapp/*.h | grep formatted
