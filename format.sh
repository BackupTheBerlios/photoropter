#! /bin/sh
astyle --options=astylerc src/*.h src/*.cpp include/*/*.h testapp/*.cpp | grep formatted
