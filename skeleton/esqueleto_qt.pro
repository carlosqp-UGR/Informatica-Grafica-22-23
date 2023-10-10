HEADERS += \
  ceiling.h \
  colors.h \
  basic_object3d.h \
  cone.h \
  cube.h \
  cylinder.h \
  dashboard.h \
  funfair_attraction.h \
  lights.h \
  material.h \
  mechanical_arm.h \
  object3d.h \
  axis.h \
  ply_object.h \
  ply_revolution_object.h \
  revolution_object.h \
  rotatory_base.h \
  seat.h \
  sphere.h \
  tetrahedron.h \
  glwidget.h \
  tex_object3d.h \
  window.h \
  file_ply_stl.h

SOURCES += \
  basic_object3d.cc \
  ceiling.cc \
  cone.cc \
  cube.cc \
  cylinder.cc \
  dashboard.cc \
  funfair_attraction.cc \
  lights.cc \
  material.cc \
  mechanical_arm.cc \
  object3d.cc \
  axis.cc \
  ply_object.cc \
  ply_revolution_object.cc \
  revolution_object.cc \
  rotatory_base.cc \
  seat.cc \
  sphere.cc \
  tetrahedron.cc \
  main.cc \
  glwidget.cc \
  tex_object3d.cc \
  window.cc \
  file_ply_stl.cc


LIBS += -L/usr/X11R6/lib64 -lGL -lGLEW


CONFIG += c++11
QT += widgets
