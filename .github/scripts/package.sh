#!/bin/bash

rm -rf Plugins/Release
rm -f Plugins/Tests
cp -r Plugins PlugData
cp README.md PlugData/README.md
cp LICENSE PlugData/LICENSE.txt

if [[ "$OSTYPE" == "darwin"* ]]; then
  sudo chmod -R 777 ./Plugins/

echo $MACOS_CERTIFICATE | base64 --decode > certificate.p12
security create-keychain -p $AC_PASSWORD build.keychain
security default-keychain -s build.keychain
security unlock-keychain -p $AC_PASSWORD build.keychain
security import certificate.p12 -k build.keychain -P $MACOS_CERTIFICATE_PWD -T /usr/bin/codesign
security set-key-partition-list -S apple-tool:,apple:,codesign: -s -k $AC_PASSWORD build.keychain

/usr/bin/codesign --force -s "Developer ID Application: Timothy Schoen (7SV7JPRR2L)" ./PlugData/VST3/*.vst3
/usr/bin/codesign --force -s "Developer ID Application: Timothy Schoen (7SV7JPRR2L)" ./PlugData/Standalone/*.app
/usr/bin/codesign --force -s "Developer ID Application: Timothy Schoen (7SV7JPRR2L)" ./PlugData/AU/*.component
/usr/bin/codesign --force -s "Developer ID Application: Timothy Schoen (7SV7JPRR2L)" ./PlugData/LV2/PlugData.lv2/libPlugData.so
/usr/bin/codesign --force -s "Developer ID Application: Timothy Schoen (7SV7JPRR2L)" ./PlugData/LV2/PlugDataFx.lv2/libPlugDataFx.so

elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
 mv PlugData PlugData-$1
fi