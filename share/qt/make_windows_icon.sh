#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/PupaCoin.ico

convert ../../src/qt/res/icons/PupaCoin-16.png ../../src/qt/res/icons/PupaCoin-32.png ../../src/qt/res/icons/PupaCoin-48.png ${ICON_DST}
