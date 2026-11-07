set_property(TARGET ${TargetName}
        PROPERTY CXX_STANDARD 17
)

 add_subdirectory(Common) 
juce_add_modules(
	Common
    common_defs
    common_ui_controls
    common_ui_components
    hardware
    ignite_ui
	Firmware
)

