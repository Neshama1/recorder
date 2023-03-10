#
# SPDX-FileCopyrightText: 2020 Jonah Brüchert <jbb@kaidan.im>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

project(krecorder)

cmake_minimum_required(VERSION 3.0)

include(FeatureSummary)

################# set KDE specific information #################
find_package(ECM 0.0.8 REQUIRED NO_MODULE)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

set(CMAKE_CXX_FLAGS "-o0")

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMPoQmTools)

################# Find dependencies #################
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Qml QuickControls2 Multimedia DBus)
find_package(KF5Kirigami2)
find_package(KF5I18n)
find_package(KF5Config)
find_package(KF5CoreAddons)

################# Enable C++11 features for clang and gcc #################
set(CMAKE_CXX_STANDARD 11)

################# build and install #################
add_subdirectory(src)

install(PROGRAMS org.kde.krecorder.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.kde.krecorder.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(FILES org.kde.krecorder.svg DESTINATION ${KDE_INSTALL_FULL_ICONDIR}/hicolor/scalable/apps)
kde_enable_exceptions()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
find_package(KF5I18n CONFIG REQUIRED)
ki18n_install(po)
