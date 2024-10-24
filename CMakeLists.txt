cmake_minimum_required(VERSION 3.5)

project(Hong VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the path to FFmpeg, replace this with the path where FFmpeg is located
# This step is especially necessary on Windows or if FFmpeg is in a non-standard location

# set(FFMPEG_DIR "C:/ffmpeg-2024-04-04-git-478d97f303-full_build")
set(FFMPEG_DIR "C:/ffmpeg-20210728-0068b3d0f0-win64-shared")

# Include directories for FFmpeg headers
include_directories(${FFMPEG_DIR}/include)

# Link directories for FFmpeg libraries
link_directories(${FFMPEG_DIR}/lib)



# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Multimedia REQUIRED)
# find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Multimedia REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Hong
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc
        KSlider.h
        KSlider.cpp
        ConvertDialog.h
        ConvertDialog.cpp
        ConversionManager.h
        ConversionManager.cpp
        PlaylistWindow.h
        PlaylistWindow.cpp
        VisualizerWidget.h
        VisualizerWidget.cpp
        KVideoWidget.h
        KVideoWidget.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Hong APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Hong SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Hong
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# target_link_libraries(Hong PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Hong PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia)
# Now that the target has been defined, link against Qt and FFmpeg libraries
# target_link_libraries(Hong
#     PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
#     PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia
#     # Specify the FFmpeg libraries to link against
#     PRIVATE avformat avcodec avutil swresample
# )
target_link_libraries(Hong
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia
    PRIVATE Qt${QT_VERSION_MAJOR}::MultimediaWidgets # Add this line
    # Specify the FFmpeg libraries to link against
    PRIVATE avformat avcodec avutil swresample
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Hong)
endif()
set_target_properties(Hong PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Hong
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Hong)
endif()
