cmake_minimum_required(VERSION 3.5)


project(qtCmfViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMF_PATH /home/wvn/dirs/projects/cmf)
set(PTL_PATH /home/wvn/dirs/projects/PTL)
set(MPI_PATH /home/wvn/dirs/research/bitcart/dependencies/openmpi-1.8.4/install)
set(CUDA_PATH /usr/local/cuda/)


#note: mpicxx -showme gives:
#g++ -I/home/wvn/dirs/research/bitcart/dependencies/openmpi-1.8.4/install/include -pthread -Wl,-rpath -Wl,/home/wvn/dirs/research/bitcart/dependencies/openmpi-1.8.4/install/lib -Wl,--enable-new-dtags -L/home/wvn/dirs/research/bitcart/dependencies/openmpi-1.8.4/install/lib -lmpi_cxx -lmpi


# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        #Main
        src/Main/main.cpp
        src/Main/mainwindow.cpp
        src/Main/mainwindow.h
        src/Main/mainwindow.ui
        src/Main/PTLDialog.h
        src/Main/PTLDialog.cpp
        src/Main/PTLDialog.ui
        src/Main/ConsoleLog.h
        src/Main/ConsoleLog.cpp
        #View
        src/View/GlViewWindow.h
        src/View/GlViewWindow.cpp
        src/View/SceneView.h
        src/View/GlScene.h
        src/View/GlScene.cpp
        src/View/GlSceneObject.h
        #SceneObjects
        src/SceneObjects/CubeObject.h
        src/SceneObjects/CubeObject.cpp
        src/SceneObjects/CmfCartesianMeshObject.h
        src/SceneObjects/CmfCartesianMeshObject.cpp
        src/SceneObjects/TriangulationObject.h
        src/SceneObjects/TriangulationObject.cpp
        src/SceneObjects/CmfSurfaceTriangulationObject.h
        src/SceneObjects/CmfSurfaceTriangulationObject.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qtCmfViewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(qtCmfViewer SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(qtCmfViewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(qtCmfViewer PUBLIC -lglut -lGL -lGLU -lGLEW)
target_include_directories(qtCmfViewer PUBLIC ${CMF_PATH}/include)

target_link_libraries(qtCmfViewer PUBLIC ${CMF_PATH}/lib/libcmf.a)
target_include_directories(qtCmfViewer PUBLIC ${PTL_PATH}/include)

target_include_directories(qtCmfViewer PUBLIC ${MPI_PATH}/include)
target_link_libraries(qtCmfViewer PUBLIC ${MPI_PATH}/lib/libmpi_cxx.so)
target_link_libraries(qtCmfViewer PUBLIC ${MPI_PATH}/lib/libmpi.so)

target_include_directories(qtCmfViewer PUBLIC ${CUDA_PATH}/include)
target_link_libraries(qtCmfViewer PUBLIC ${CUDA_PATH}/lib64/libcudart.so)
target_link_libraries(qtCmfViewer PUBLIC ${CUDA_PATH}/lib64/libcudadevrt.a)

target_link_libraries(qtCmfViewer PUBLIC ${PTL_PATH}/lib/libPTL.a)
target_link_libraries(qtCmfViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(qtCmfViewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qtCmfViewer)
endif()
