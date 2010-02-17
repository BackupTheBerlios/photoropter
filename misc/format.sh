#! /bin/sh
astyle --options=misc/astylerc src/*.h src/*.cpp include/*/*.h testapp/*.cpp | grep formatted
