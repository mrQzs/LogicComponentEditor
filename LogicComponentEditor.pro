QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += AUTO_VECTOR
DEFINES += AUTO_LIST

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = LogicComponentEditor

RC_FILE = res/icon.rc


INCLUDEPATH += "Include/pub"
INCLUDEPATH += "Include/pub/thridparty"
INCLUDEPATH += "Include/pub/yd"
INCLUDEPATH += "Include/pub/base"
INCLUDEPATH += "Include/pub/impl"
INCLUDEPATH += "Include/pub/impl"

INCLUDEPATH += $$PWD/third/inc

CONFIG(debug, debug|release){
LIBS += -L$$PWD/third/lib/debug -lqscintilla2_qt6d
} else {
LIBS += -L$$PWD/third/lib/release -lqscintilla2_qt6
}




QMAKE_CXXFLAGS_RELEASE += $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE += $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
win32{
    include(breakpad/breakpad.pri)
}
win64{
    include(breakpad/breakpad.pri)
}

DEFINES += SCINTILLA_QT SCI_LEXER INCLUDE_DEPRECATED_FEATURES

QT += widgets
!ios:QT += printsupport
macx:lessThan(QT_MAJOR_VERSION, 6) {
    QT += macextras
}
#include(qscintilla/qscintilla.pri)

greaterThan(QT_MAJOR_VERSION,4){
        TARGET_ARCH=$${QT_ARCH}
}else{
        TARGET_ARCH=$${QMAKE_HOST.arch}
}

contains(TARGET_ARCH, x86_64){
    CONFIG(debug, debug|release){
        MOC_DIR = build/x64/moc/debug
        OBJECTS_DIR = build/x64/obj/debug
        RCC_DIR = build/x64/rcc/debug
        UI_DIR = build/x64/ui/debug
        DESTDIR = bin/x64/debug
    }else{
        MOC_DIR = build/x64/moc/release
        OBJECTS_DIR = build/x64/obj/release
        RCC_DIR = build/x64/rcc/release
        UI_DIR = build/x64/ui/release
        DESTDIR = bin/x64/release
    }
}else{
    CONFIG(debug, debug|release){
        MOC_DIR = build/win32/moc/debug
        OBJECTS_DIR = build/win32/obj/debug
        RCC_DIR = build/win32/rcc/debug
        UI_DIR = build/win32/ui/debug
        DESTDIR = bin/win32/debug
    }else{
        MOC_DIR = build/win32/moc/release
        OBJECTS_DIR = build/win32/obj/release
        RCC_DIR = build/win32/rcc/release
        UI_DIR = build/win32/ui/release
        DESTDIR = bin/win32/release
    }
}

#CONFIG(debug,debug|release){
#    INCLUDEPATH += C:/vld/include
#    DEPENDPATH += C:/vld/include
#    LIBS += -LC:/vld/lib/Win64 -lvld
#}


SOURCES += \
    MainWindow.cpp \
    common/YDHelper.cpp \
    common/YDLogger.cpp \
    core/YDProjectManage.cpp \
    core/YDTask.cpp \
    core/YDTimer.cpp \
    core/YDVariable.cpp \
    debug/YDAXisListView.cpp \
    debug/YDAxisListModel.cpp \
    debug/YDDAxisVarModel.cpp \
    debug/YDDAxisVarView.cpp \
    debug/YDDAxisVarWidget.cpp \
    debug/YDDCylinderView.cpp \
    debug/YDDCylinderWidget.cpp \
    debug/YDDInputModel.cpp \
    debug/YDDInputWidget.cpp \
    debug/YDDOutputModel.cpp \
    debug/YDDOutputWidget.cpp \
    debug/YDDTaskWidget.cpp \
    debug/YDDVariableModel.cpp \
    debug/YDDVariableWidget.cpp \
    debug/YDDVariableview.cpp \
    debug/YDDebugDialog.cpp \
    debug/YDDgHelper.cpp \
    debug/YDInputStateView.cpp \
    debug/YDJogButton.cpp \
    debug/YDLogicDebug.cpp \
    debug/YDMoveControlWidget.cpp \
    debug/YDNetSetDialog.cpp \
    debug/YDOutputStateView.cpp \
    debug/YDSpeedSetWidget.cpp \
    debug/YDState.cpp \
    debug/YDStateWidget.cpp \
    debug/YDVarSetDialog.cpp \
    main.cpp \
    model/YDControlModel.cpp \
    model/YDCylinderModel.cpp \
    model/YDDeviceAxisModel.cpp \
    model/YDDeviceInputModel.cpp \
    model/YDDeviceModel.cpp \
    model/YDDeviceOutputModel.cpp \
    model/YDIOModel.cpp \
    model/YDMenuModel.cpp \
    model/YDModulePropModel.cpp \
    model/YDMoveModel.cpp \
    model/YDOtherModel.cpp \
    model/YDReciVariableModel.cpp \
    model/YDSafeVariableModel.cpp \
    model/YDScriptModel.cpp \
    model/YDTempVariableModel.cpp \
    model/YDVariableGroupModel.cpp \
    model/YDVariableModel.cpp \
    modules/YDAbsMotion.cpp \
    modules/YDAlarmConfirm.cpp \
    modules/YDBackZMotion.cpp \
    modules/YDConditionLoop.cpp \
    modules/YDControlAO.cpp \
    modules/YDControlDO.cpp \
    modules/YDCylinder.cpp \
    modules/YDDelayWait.cpp \
    modules/YDIfCondition.cpp \
    modules/YDIfElseCondition.cpp \
    modules/YDJogMotion.cpp \
    modules/YDJumpLoop.cpp \
    modules/YDJumpToTask.cpp \
    modules/YDModule.cpp \
    modules/YDMulMotion.cpp \
    modules/YDProgramable.cpp \
    modules/YDRelMotion.cpp \
    modules/YDStopMotion.cpp \
    modules/YDSubTaskCall.cpp \
    modules/YDTimesLoop.cpp \
    modules/YDWaitComplete.cpp \
    modules/YDWaitMotion.cpp \
    properties/YDCustomWProp.cpp \
    properties/YDProperty.cpp \
    properties/YDPropertyAoVar.cpp \
    properties/YDPropertyAxis.cpp \
    properties/YDPropertyBool.cpp \
    properties/YDPropertyCyDir.cpp \
    properties/YDPropertyCylinder.cpp \
    properties/YDPropertyDelayTime.cpp \
    properties/YDPropertyDelayValue.cpp \
    properties/YDPropertyDoVar.cpp \
    properties/YDPropertyDouble.cpp \
    properties/YDPropertyEnum.cpp \
    properties/YDPropertyIOVar.cpp \
    properties/YDPropertyInPlace.cpp \
    properties/YDPropertyInt.cpp \
    properties/YDPropertyMSpeed.cpp \
    properties/YDPropertyModule.cpp \
    properties/YDPropertyName.cpp \
    properties/YDPropertySafeVar.cpp \
    properties/YDPropertySpeedCard.cpp \
    properties/YDPropertyString.cpp \
    properties/YDPropertyTask.cpp \
    properties/YDPropertyVar.cpp \
    view/YDListView.cpp \
    view/YDModuleView.cpp \
    view/YDTableView.cpp \
    view/YDTreeView.cpp \
    widget/YDBuildOptDialog.cpp \
    widget/YDCodeEditor.cpp \
    widget/YDCodeManage.cpp \
    widget/YDConditionDialog.cpp \
    widget/YDCylinderInfo.cpp \
    widget/YDDTComboBox.cpp \
    widget/YDDeviceSetDialog.cpp \
    widget/YDDeviceTypeComboBox.cpp \
    widget/YDDialog.cpp \
    widget/YDInplaceWaitDialog.cpp \
    widget/YDIntVarComboBox.cpp \
    widget/YDLogo.cpp \
    widget/YDMenu.cpp \
    widget/YDMenuHead.cpp \
    widget/YDMenuItem.cpp \
    widget/YDNameDialog.cpp \
    widget/YDNameLineEdit.cpp \
    widget/YDPicButton.cpp \
    widget/YDProjectDialog.cpp \
    widget/YDScriptPropDialog.cpp \
    widget/YDSetVariableDialog.cpp \
    widget/YDVariableDialog.cpp \
    widget/YDWidget.cpp \
    widget/YDShowMessage.cpp \
    widget/module/YDIfConditionWidget.cpp \
    widget/module/YDModuleConditionWidget.cpp \
    widget/module/YDModuleHead.cpp \
    widget/module/YDModuleIFElseWidget.cpp \
    widget/module/YDModuleListWidget.cpp \
    widget/module/YDModuleLoopWidget.cpp \
    widget/module/YDModuleWidget.cpp \
    widget/module/YDTabWidget.cpp \
    widget/property/YDAddAxisVarDialog.cpp \
    widget/property/YDAddAxisWaitDialog.cpp \
    widget/property/YDAddConditionDialog.cpp \
    widget/property/YDAddCylinderDialog.cpp \
    widget/property/YDAddDelayTimeDialog.cpp \
    widget/property/YDAddDeviceDialog.cpp \
    widget/property/YDAddReciVarDialog.cpp \
    widget/property/YDAddSafeVarDialog.cpp \
    widget/property/YDAddTempVarDialog.cpp \
    widget/property/YDAddVariableDialog.cpp \
    widget/property/YDAlarmAction.cpp \
    widget/property/YDProgramDIalog.cpp

HEADERS += \
    MainWindow.h \
    common/YDGlobal.h \
    common/YDHelper.h \
    common/YDLogger.h \
    core/YDProjectManage.h \
    core/YDTask.h \
    core/YDTimer.h \
    core/YDVariable.h \
    debug/YDAXisListView.h \
    debug/YDAxisListModel.h \
    debug/YDDAxisVarModel.h \
    debug/YDDAxisVarView.h \
    debug/YDDAxisVarWidget.h \
    debug/YDDCylinderView.h \
    debug/YDDCylinderWidget.h \
    debug/YDDInputModel.h \
    debug/YDDInputWidget.h \
    debug/YDDOutputModel.h \
    debug/YDDOutputWidget.h \
    debug/YDDTaskWidget.h \
    debug/YDDVariableModel.h \
    debug/YDDVariableWidget.h \
    debug/YDDVariableview.h \
    debug/YDDebugDialog.h \
    debug/YDDgHelper.h \
    debug/YDInputStateView.h \
    debug/YDJogButton.h \
    debug/YDLogicDebug.h \
    debug/YDMoveControlWidget.h \
    debug/YDNetSetDialog.h \
    debug/YDOutputStateView.h \
    debug/YDSpeedSetWidget.h \
    debug/YDState.h \
    debug/YDStateWidget.h \
    debug/YDVarSetDialog.h \
    model/YDControlModel.h \
    model/YDCylinderModel.h \
    model/YDDeviceAxisModel.h \
    model/YDDeviceInputModel.h \
    model/YDDeviceModel.h \
    model/YDDeviceOutputModel.h \
    model/YDIOModel.h \
    model/YDMenuModel.h \
    model/YDModulePropModel.h \
    model/YDMoveModel.h \
    model/YDOtherModel.h \
    model/YDReciVariableModel.h \
    model/YDSafeVariableModel.h \
    model/YDScriptModel.h \
    model/YDTempVariableModel.h \
    model/YDVariableGroupModel.h \
    model/YDVariableModel.h \
    modules/YDAbsMotion.h \
    modules/YDAlarmConfirm.h \
    modules/YDBackZMotion.h \
    modules/YDConditionLoop.h \
    modules/YDControlAO.h \
    modules/YDControlDO.h \
    modules/YDCylinder.h \
    modules/YDDelayWait.h \
    modules/YDIfCondition.h \
    modules/YDIfElseCondition.h \
    modules/YDJogMotion.h \
    modules/YDJumpLoop.h \
    modules/YDJumpToTask.h \
    modules/YDModule.h \
    modules/YDModules.h \
    modules/YDMulMotion.h \
    modules/YDProgramable.h \
    modules/YDRelMotion.h \
    modules/YDStopMotion.h \
    modules/YDSubTaskCall.h \
    modules/YDTimesLoop.h \
    modules/YDWaitComplete.h \
    modules/YDWaitMotion.h \
    properties/YDCustomWProp.h \
    properties/YDProperties.h \
    properties/YDProperty.h \
    properties/YDPropertyAoVar.h \
    properties/YDPropertyAxis.h \
    properties/YDPropertyBool.h \
    properties/YDPropertyCyDir.h \
    properties/YDPropertyCylinder.h \
    properties/YDPropertyDelayTime.h \
    properties/YDPropertyDelayValue.h \
    properties/YDPropertyDoVar.h \
    properties/YDPropertyDouble.h \
    properties/YDPropertyEnum.h \
    properties/YDPropertyIOVar.h \
    properties/YDPropertyInPlace.h \
    properties/YDPropertyInt.h \
    properties/YDPropertyMSpeed.h \
    properties/YDPropertyModule.h \
    properties/YDPropertyName.h \
    properties/YDPropertySafeVar.h \
    properties/YDPropertySpeedCard.h \
    properties/YDPropertyString.h \
    properties/YDPropertyTask.h \
    properties/YDPropertyVar.h \
    view/YDListView.h \
    view/YDModuleView.h \
    view/YDTableView.h \
    view/YDTreeView.h \
    widget/YDBuildOptDialog.h \
    widget/YDCodeEditor.h \
    widget/YDCodeManage.h \
    widget/YDConditionDialog.h \
    widget/YDCylinderInfo.h \
    widget/YDDTComboBox.h \
    widget/YDDeviceSetDialog.h \
    widget/YDDeviceTypeComboBox.h \
    widget/YDDialog.h \
    widget/YDInplaceWaitDialog.h \
    widget/YDIntVarComboBox.h \
    widget/YDLogo.h \
    widget/YDMenu.h \
    widget/YDMenuHead.h \
    widget/YDMenuItem.h \
    widget/YDNameDialog.h \
    widget/YDNameLineEdit.h \
    widget/YDPicButton.h \
    widget/YDProjectDialog.h \
    widget/YDScriptPropDialog.h \
    widget/YDSetVariableDialog.h \
    widget/YDVariableDialog.h \
    widget/YDWidget.h \
    widget/YDShowMessage.h \
    widget/module/YDIfConditionWidget.h \
    widget/module/YDModuleConditionWidget.h \
    widget/module/YDModuleHead.h \
    widget/module/YDModuleIFElseWidget.h \
    widget/module/YDModuleListWidget.h \
    widget/module/YDModuleLoopWidget.h \
    widget/module/YDModuleWidget.h \
    widget/module/YDTabWidget.h \
    widget/property/YDAddAxisVarDialog.h \
    widget/property/YDAddAxisWaitDialog.h \
    widget/property/YDAddConditionDialog.h \
    widget/property/YDAddCylinderDialog.h \
    widget/property/YDAddDelayTimeDialog.h \
    widget/property/YDAddDeviceDialog.h \
    widget/property/YDAddReciVarDialog.h \
    widget/property/YDAddSafeVarDialog.h \
    widget/property/YDAddTempVarDialog.h \
    widget/property/YDAddVariableDialog.h \
    widget/property/YDAlarmAction.h \
    widget/property/YDProgramDIalog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    MainWindow.ui \

RESOURCES += \
    res/res.qrc
