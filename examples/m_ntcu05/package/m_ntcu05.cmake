bde_prefixed_override(m_ntcu05 application_initialize)
function(m_ntcu05_application_initialize retUor appName)
    string(REGEX REPLACE "(m_)?(.+)" "\\2" appTrimmedName ${appName})
    application_initialize_base("" tmpUor ${appTrimmedName})
    bde_return(${tmpUor})
endfunction()
