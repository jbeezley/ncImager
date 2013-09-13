export QMAKESPEC=~/git/qt/mkspecs/unsupported/macx-clang
ln -sf deploy.pri ncImager.pri
rm -fr build
mkdir build
pushd build
~/qtstatic/bin/qmake -config release ../
make
strip ncImager.app/Contents/MacOS/ncImager
upx ncImager.app/Contents/MacOS/ncImager
