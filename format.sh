#! /bin/sh
astyle --options=astylerc *.h *.cpp include/*.h testapp/*.cpp | grep formatted
