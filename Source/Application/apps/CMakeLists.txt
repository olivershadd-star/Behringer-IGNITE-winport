# Main application.  
add_subdirectory( ignite )

# IGNITE VST plugin
if( IGNITE_VST_PLUGIN )
    add_subdirectory(ignitevst)
endif()
