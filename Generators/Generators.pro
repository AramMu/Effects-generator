TEMPLATE = app
CONFIG += console c++14

#TEMPLATE = lib
#CONFIG += console c++14 dll

CONFIG -= app_bundle
CONFIG -= qt

DEFINES += GENERATORS_LIBRARY

INCLUDEPATH += Utils
INCLUDEPATH += D:\\Dependencies\\opencv_3_1_0\\include
LIBS += -LD:\\Dependencies\\opencv_3_1_0\\x86\\mingw\\lib -lopencv_world310.dll

HEADERS += \
    Simulation/Descriptor/Effect/all_effect_descriptions.h \
    Simulation/Descriptor/Effect/contrast_description.h \
    Simulation/Descriptor/Effect/effect_description.h \
    Simulation/Descriptor/Effect/gaussiannoise_description.h \
    Simulation/Descriptor/Simulation/all_simulation_descriptions.h \
    Simulation/Descriptor/Simulation/distancecrystal_description.h \
    Simulation/Descriptor/Simulation/dlaggregation_description.h \
    Simulation/Descriptor/Simulation/flameblaze_description.h \
    Simulation/Descriptor/Simulation/flameparabola_description.h \
    Simulation/Descriptor/Simulation/flametongue_description.h \
    Simulation/Descriptor/Simulation/forestfire_description.h \
    Simulation/Descriptor/Simulation/lightningtree_description.h \
    Simulation/Descriptor/Simulation/magnet_description.h \
    Simulation/Descriptor/Simulation/mstree_description.h \
    Simulation/Descriptor/Simulation/plasma_description.h \
    Simulation/Descriptor/Simulation/randomwalker_description.h \
    Simulation/Descriptor/Simulation/simulation_description.h \
    Simulation/Descriptor/Simulation/smoke_description.h \
    Simulation/Descriptor/Simulation/tvnoise_description.h \
    Simulation/Descriptor/Simulation/voronoidiagram_description.h \
    Simulation/Descriptor/types/abstract_description.h \
    Simulation/Descriptor/types/color_description.h \
    Simulation/Descriptor/types/description_list.h \
    Simulation/Descriptor/types/double_description.h \
    Simulation/Descriptor/types/int_description.h \
    Simulation/Descriptor/types/radio_description.h \
    Simulation/Generator/abstract_simulation.h \
    Simulation/Generator/distancecrystal.h \
    Simulation/Generator/dlaggregation.h \
    Simulation/Generator/flameblaze.h \
    Simulation/Generator/flameparabola.h \
    Simulation/Generator/flametongue.h \
    Simulation/Generator/forestfire.h \
    Simulation/Generator/lightningtree.h \
    Simulation/Generator/magnet.h \
    Simulation/Generator/mstree.h \
    Simulation/Generator/plasma.h \
    Simulation/Generator/randomwalker.h \
    Simulation/Generator/smoke.h \
    Simulation/Generator/spider.h \
    Simulation/Generator/tvnoise.h \
    Simulation/Generator/voronoidiagram.h \
    Simulation/Generator/wave.h \
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
    Utils/ImageProcessing/imagecorrection.h \
    Utils/ImageProcessing/noisegenerator.h \
    Utils/Time/sleeper.h \
    Utils/Time/timemeasure.h \
    Utils/Utils/calc.h \
    Utils/Utils/matrix.h \
    Utils/Utils/randomgenerator.h \
    Utils/Utils/utils.h \
    Utils/ImageProcessing/transformation.h \
    Simulation/Generator/pixellightning.h \
    wrapper.h \
    Simulation/Descriptor/Simulation/pixellightningdescription.h \
    Utils/Drawables/ghost.h \
    Simulation/Generator/clothghost.h \
    Utils/Drawables/polynomial.h \
    Utils/Algorithms/spline.h \
    Utils/Print/global.h \
    Simulation/Generator/maze.h
SOURCES += \
    Simulation/Descriptor/Effect/all_effect_descriptions.cpp \
    Simulation/Descriptor/Effect/contrast_description.cpp \
    Simulation/Descriptor/Effect/effect_description.cpp \
    Simulation/Descriptor/Effect/gaussiannoise_description.cpp \
    Simulation/Descriptor/Simulation/all_simulation_descriptions.cpp \
    Simulation/Descriptor/Simulation/distancecrystal_description.cpp \
    Simulation/Descriptor/Simulation/dlaggregation_description.cpp \
    Simulation/Descriptor/Simulation/flameblaze_description.cpp \
    Simulation/Descriptor/Simulation/flameparabola_description.cpp \
    Simulation/Descriptor/Simulation/flametongue_description.cpp \
    Simulation/Descriptor/Simulation/forestfire_description.cpp \
    Simulation/Descriptor/Simulation/lightningtree_description.cpp \
    Simulation/Descriptor/Simulation/magnet_description.cpp \
    Simulation/Descriptor/Simulation/mstree_description.cpp \
    Simulation/Descriptor/Simulation/plasma_description.cpp \
    Simulation/Descriptor/Simulation/randomwalker_description.cpp \
    Simulation/Descriptor/Simulation/simulation_description.cpp \
    Simulation/Descriptor/Simulation/smoke_description.cpp \
    Simulation/Descriptor/Simulation/tvnoise_description.cpp \
    Simulation/Descriptor/Simulation/voronoidiagram_description.cpp \
    Simulation/Descriptor/types/abstract_description.cpp \
    Simulation/Descriptor/types/color_description.cpp \
    Simulation/Descriptor/types/double_description.cpp \
    Simulation/Descriptor/types/int_description.cpp \
    Simulation/Descriptor/types/radio_description.cpp \
    Simulation/Generator/abstract_simulation.cpp \
    Simulation/Generator/distancecrystal.cpp \
    Simulation/Generator/dlaggregation.cpp \
    Simulation/Generator/flameblaze.cpp \
    Simulation/Generator/flameparabola.cpp \
    Simulation/Generator/flametongue.cpp \
    Simulation/Generator/forestfire.cpp \
    Simulation/Generator/lightningtree.cpp \
    Simulation/Generator/magnet.cpp \
    Simulation/Generator/mstree.cpp \
    Simulation/Generator/plasma.cpp \
    Simulation/Generator/randomwalker.cpp \
    Simulation/Generator/smoke.cpp \
    Simulation/Generator/spider.cpp \
    Simulation/Generator/tvnoise.cpp \
    Simulation/Generator/voronoidiagram.cpp \
    Simulation/Generator/wave.cpp \
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
    Utils/ImageProcessing/imagecorrection.cpp \
    Utils/ImageProcessing/noisegenerator.cpp \
    Utils/Time/sleeper.cpp \
    Utils/Time/timemeasure.cpp \
    Utils/Utils/calc.cpp \
    Utils/Utils/randomgenerator.cpp \
    Utils/Utils/utils.cpp \
    main.cpp \
    wrapper.cpp \
    Utils/ImageProcessing/transformation.cpp \
    Simulation/Generator/pixellightning.cpp \
    Simulation/Descriptor/Simulation/pixellightningdescription.cpp \
    Utils/Drawables/ghost.cpp \
    Simulation/Generator/clothghost.cpp \
    Utils/Drawables/polynomial.cpp \
    Utils/Algorithms/spline.cpp \
    Utils/Print/global.cpp \
    Simulation/Generator/maze.cpp
