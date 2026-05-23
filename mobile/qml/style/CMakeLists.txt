set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)

set_source_files_properties(Config.qml
    PROPERTIES
        QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(style
    URI style
    STATIC
    NO_PLUGIN
    QML_FILES
        ApplicationWindow.qml
        BusyIndicator.qml
        Button.qml
        CheckBox.qml
        ComboBox.qml
        ComboBoxPopup.qml
        Config.qml
        Frame.qml
        GroupBox.qml
        ItemDelegate.qml
        PageIndicator.qml
        PageIndicatorDelegate.qml
        Popup.qml
        ProgressBar.qml
        RadioButton.qml
        RangeSlider.qml
        RoundButton.qml
        ScrollBar.qml
        ScrollIndicator.qml
        ScrollView.qml
        Slider.qml
        SpinBox.qml
        StyleImage.qml
        Switch.qml
        TabBar.qml
        TabButton.qml
        TextArea.qml
        TextField.qml
        ToolBar.qml
        ToolButton.qml
        ToolTip.qml
    RESOURCES
        icons/index.theme
        qmldir
        style.qrc
)

target_link_libraries(style PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
)
