cmake_minimum_required(VERSION 3.15)

project(IGNITE VERSION 1.4.2)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(APPLICATION_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../.. )
set(COMMON_DIRECTORY ${APPLICATION_DIRECTORY}/modules/Common)
#set(TSF_DIRECTORY ${COMMON_DIRECTORY}/Thirdparty/TinySoundFont)
set(BOARD_DIRECTORY ${COMMON_DIRECTORY}/Board)
set(MODULE_DIRECTORY ${COMMON_DIRECTORY}/Modules)
set(FIRMWARE_DIRECTORY ${APPLICATION_DIRECTORY}/modules/Firmware)

# juce helper function to create a library, which is configured as a JUCE plugin

juce_add_plugin(${PROJECT_NAME}
    VERSION                     "${PROJECT_VERSION}"
    COMPANY_NAME                "MusicTribe"
    IS_SYNTH                    FALSE
    NEEDS_MIDI_INPUT            FALSE
    NEEDS_MIDI_OUTPUT           FALSE
    IS_MIDI_EFFECT              FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD     FALSE     # Where does this go in Windows + Linux?
    PLUGIN_MANUFACTURER_CODE    LEOM
    PLUGIN_CODE                 CB1O
    FORMATS                     VST3      # ( VST AAX Unity VST3 AU AUv3 Standalone )
    PRODUCT_NAME                "${PROJECT_NAME}"
)

juce_generate_juce_header(${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME}
        PROPERTY CXX_STANDARD 17
)

# Add plugin source files
target_sources(${PROJECT_NAME}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PluginEditor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PluginProcessor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PluginEditor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PluginProcessor.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
     #   ${TSF_DIRECTORY}
        ${BOARD_DIRECTORY}
        ${MODULE_DIRECTORY}
        ${FIRMWARE_DIRECTORY}/Application/Model

)


# Add any extra JUCE-specific pre-processor definitions
target_compile_definitions(${PROJECT_NAME}
PUBLIC
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_MODAL_LOOPS_PERMITTED=1
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags

        ValueTreeDebugger

        juce::juce_gui_extra
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_processors
        juce::juce_audio_utils
        common_defs
        common_ui_controls
        ignite_ui
        Common
	    Firmware
      #  tsf
)

# Copy assets to executable directory post generating build files...
add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../../assets ${CMAKE_CURRENT_BINARY_DIR}/Ignite_artefacts/Debug/assets
)