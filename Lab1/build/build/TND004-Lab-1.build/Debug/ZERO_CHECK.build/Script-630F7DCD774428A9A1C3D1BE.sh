#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/klarabratteby/Desktop/Skola/TND004/Lab 1/build"
  make -f /Users/klarabratteby/Desktop/Skola/TND004/Lab\ 1/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/klarabratteby/Desktop/Skola/TND004/Lab 1/build"
  make -f /Users/klarabratteby/Desktop/Skola/TND004/Lab\ 1/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Users/klarabratteby/Desktop/Skola/TND004/Lab 1/build"
  make -f /Users/klarabratteby/Desktop/Skola/TND004/Lab\ 1/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Users/klarabratteby/Desktop/Skola/TND004/Lab 1/build"
  make -f /Users/klarabratteby/Desktop/Skola/TND004/Lab\ 1/build/CMakeScripts/ReRunCMake.make
fi

