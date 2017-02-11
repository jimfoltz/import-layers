cmake_minimum_required(VERSION 3.7.2)

project (JF_ImportLayers)


include_directories(./ThirdParty/include/ruby/2.2/win32_x64)

include_directories(C:/Users/Jim/SketchUp/SDK/SDK_Win_x64_17-2-2555/headers)

find_library(SK sketchupapi C:/Users/Jim/SketchUp/SDK/SDK_Win_x64_17-2-1973/binaries/sketchup/x64)

find_library(RB x64-msvcrt-ruby220.lib C:/Users/Jim/SketchUp/Plugins/jf_extensions/Extensions/jf_import_layers/src/ThirdParty/lib/win32)

add_library(JF_ImportLayers SHARED import_layer.cpp RubyExtension.def)

target_link_libraries(JF_ImportLayers PUBLIC ${SK} ${RB})
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
