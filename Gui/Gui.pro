#-------------------------------------------------
#
# Project created by QtCreator 2017-04-16T15:10:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



TARGET = Gui
TEMPLATE = app
CONFIG += c++14




#CONFIG(release, debug|release) {
#    DEFINES += "NDEBUG"
#}


INCLUDEPATH += $$PWD\Utils

#if using MinGW
INCLUDEPATH += $$PWD\Dependencies\opencv_3_1_mingw\include
LIBS += -L$$PWD\Dependencies\opencv_3_1_mingw\lib
LIBS += -lopencv_world310.dll

#if using Visual studio
#DEFINES += "NOMINMAX"
#INCLUDEPATH += $$PWD\Dependencies\opencv_3_2_msvc2015\include
#LIBS += -L$$PWD\Dependencies\opencv_3_2_msvc2015\lib
#CONFIG(debug, debug|release) {
#    LIBS += -lopencv_world320d
#}
#CONFIG(release, debug|release) {
#    LIBS += -lopencv_world320
#}




FORMS    +=

HEADERS += \
    Simulation/Descriptor/Effect/all_effect_descriptions.h \
    Simulation/Descriptor/Effect/contrast_description.h \
    Simulation/Descriptor/Effect/effect_description.h \
    Simulation/Descriptor/Effect/gaussiannoise_description.h \
    Simulation/Descriptor/types/abstract_description.h \
    Simulation/Descriptor/types/color_description.h \
    Simulation/Descriptor/types/description_list.h \
    Simulation/Descriptor/types/double_description.h \
    Simulation/Descriptor/types/int_description.h \
    Simulation/Descriptor/types/radio_description.h \
    Simulation/Descriptor/Simulation/simulation_description.h \
    Simulation/Generator/abstract_simulation.h \
    Utils/Algorithms/convexhull.h \
    Utils/Algorithms/Delaunay_triangulation.h \
    Utils/DataStructures/disjointset.h \
    Utils/DataStructures/graph.h \
    Utils/DataStructures/point.h \
    Utils/Drawables/circle.h \
    Utils/Drawables/doubletongue.h \
    Utils/Drawables/ellipse.h \
    Utils/Drawables/parabola.h \
    Utils/Drawables/tongue.h \
    Utils/Functions/colormixer.h \
    Utils/Functions/colormixerimpl.h \
    Utils/Functions/pointmapper.h \
    Utils/Functions/pointmapperimpl.h \
    Utils/ImageProcessing/imagecorrection.h \
    Utils/ImageProcessing/noisegenerator.h \
    Utils/Time/sleeper.h \
    Utils/Time/timemeasure.h \
    Utils/Utils/calc.h \
    Utils/Utils/matrix.h \
    Utils/Utils/randomgenerator.h \
    Utils/Utils/utils.h \
    colorbutton.h \
    doublebutton.h \
    effectbutton.h \
    frameprocessor.h \
    frameview.h \
    intbutton.h \
    mainwindow.h \
    pushbutton.h \
    qtutils.h \
    radiobutton.h \
    simulationevents.h \
    simulationwindow.h

SOURCES += \
    Simulation/Descriptor/Effect/all_effect_descriptions.cpp \
    Simulation/Descriptor/Effect/contrast_description.cpp \
    Simulation/Descriptor/Effect/effect_description.cpp \
    Simulation/Descriptor/Effect/gaussiannoise_description.cpp \
    Simulation/Descriptor/types/abstract_description.cpp \
    Simulation/Descriptor/types/color_description.cpp \
    Simulation/Descriptor/types/double_description.cpp \
    Simulation/Descriptor/types/int_description.cpp \
    Simulation/Descriptor/types/radio_description.cpp \
    Simulation/Descriptor/Simulation/simulation_description.cpp \
    Simulation/Generator/abstract_simulation.cpp \
    Utils/Algorithms/convexhull.cpp \
    Utils/Algorithms/Delaunay_triangulation.cpp \
    Utils/DataStructures/disjointset.cpp \
    Utils/DataStructures/graph.cpp \
    Utils/DataStructures/point.cpp \
    Utils/Drawables/circle.cpp \
    Utils/Drawables/doubletongue.cpp \
    Utils/Drawables/ellipse.cpp \
    Utils/Drawables/parabola.cpp \
    Utils/Drawables/tongue.cpp \
    Utils/Functions/pointmapper.cpp \
    Utils/Functions/pointmapperimpl.cpp \
    Utils/ImageProcessing/imagecorrection.cpp \
    Utils/ImageProcessing/noisegenerator.cpp \
    Utils/Time/sleeper.cpp \
    Utils/Time/timemeasure.cpp \
    Utils/Utils/calc.cpp \
    Utils/Utils/randomgenerator.cpp \
    Utils/Utils/utils.cpp \
    colorbutton.cpp \
    doublebutton.cpp \
    effectbutton.cpp \
    frameprocessor.cpp \
    frameview.cpp \
    intbutton.cpp \
    main.cpp \
    mainwindow.cpp \
    pushbutton.cpp \
    qtutils.cpp \
    radiobutton.cpp \
    simulationwindow.cpp
