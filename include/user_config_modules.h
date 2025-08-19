/* MIT License - Copyright (c) 2019-2024 Francis Van Roie
   For full license information read the LICENSE file in the project folder */

/***************************************************
 *        OPENHASP MODULAR CONFIGURATION
 *        Crowpanel HMI Elecrow S3 8048C070
 *        
 *        💡 EASY ENABLE/DISABLE FEATURES
 *        Uncomment to enable, comment to disable
 ***************************************************/
#ifndef HASP_USER_CONFIG_MODULES_H
#define HASP_USER_CONFIG_MODULES_H

/***************************************************
 *        NETWORK SERVICES
 ***************************************************/
#define ENABLE_WIFI         1       // WiFi connectivity
#define ENABLE_FTP          1       // File transfer protocol
#define ENABLE_TELNET       1       // Remote console access
#define ENABLE_HTTP         1       // Web interface
#define ENABLE_MQTT         1       // MQTT communication
// #define ENABLE_SYSLOG    1       // System logging (disabled for stability)

/***************************************************
 *        LANGUAGES
 ***************************************************/
#define ENABLE_LANG_EN_US   1       // English (primary)
#define ENABLE_LANG_FR_FR   1       // French (secondary)
// Add more languages as needed

/***************************************************
 *        DEBUGGING & LOGGING
 ***************************************************/
// #define ENABLE_DEBUG_VERBOSE 1   // Verbose logging (disabled for stability)
#define ENABLE_DEBUG_WARNING    1   // Warning level logging
// #define ENABLE_DEBUG_MEMORY  1   // Memory debugging (disabled - causes watchdog)
// #define ENABLE_DEBUG_TASKS   1   // Task debugging (disabled for performance)

/***************************************************
 *        DISPLAY FEATURES
 ***************************************************/
#define ENABLE_FREETYPE     1       // TrueType font support
#define ENABLE_PNG_DECODE   1       // PNG image support
#define ENABLE_BMP_DECODE   1       // BMP image support
// #define ENABLE_JPG_DECODE 1      // JPEG support (disabled to save space)
// #define ENABLE_GIF_DECODE 1      // GIF support (disabled to save space)

/***************************************************
 *        HARDWARE FEATURES
 ***************************************************/
#define ENABLE_TOUCH_GT911  1       // GT911 touch driver
// #define ENABLE_GPIO_CUSTOM 1     // Custom GPIO templates
// #define ENABLE_CUSTOM_CODE 1     // Custom user code

/***************************************************
 *        SECURITY & OTA
 ***************************************************/
// #define ENABLE_ARDUINO_OTA 1     // Arduino OTA updates
// #define ENABLE_MDNS        1     // mDNS discovery

/***************************************************
 *        APPLY CONFIGURATION
 *        ⚠️ DO NOT MODIFY BELOW THIS LINE
 ***************************************************/

// Network services
#ifdef ENABLE_WIFI
    #define HASP_USE_WIFI 1
#endif

#ifdef ENABLE_FTP
    #define HASP_USE_FTP 0
#endif

#ifdef ENABLE_TELNET
    #define HASP_USE_TELNET 0
#endif

#ifdef ENABLE_HTTP
    #define HASP_USE_HTTP 1
#endif

#ifdef ENABLE_MQTT
    #define HASP_USE_MQTT 1
#endif

#ifdef ENABLE_SYSLOG
    #define HASP_USE_SYSLOG 1
#else
    #define HASP_USE_SYSLOG 0
#endif

// Languages
#ifdef ENABLE_LANG_EN_US
    #define HASP_LANGUAGE en_US
#endif

#ifdef ENABLE_LANG_FR_FR
    // #define HASP_LANGUAGE fr_FR  // Uncomment if French is primary
#endif

// Debugging
#ifdef ENABLE_DEBUG_VERBOSE
    #define HASP_LOG_LEVEL LOG_LEVEL_VERBOSE
#elif defined(ENABLE_DEBUG_WARNING)
    #define HASP_LOG_LEVEL LOG_LEVEL_WARNING
#else
    #define HASP_LOG_LEVEL LOG_LEVEL_ERROR
#endif

#ifdef ENABLE_DEBUG_MEMORY
    #define HASP_USE_DEBUG_MEMORY 1
#else
    #define HASP_USE_DEBUG_MEMORY 0
#endif

#ifdef ENABLE_DEBUG_TASKS
    #define HASP_LOG_TASKS 1
#endif

// Display features
#ifdef ENABLE_FREETYPE
    #define HASP_USE_FREETYPE 1
#endif

#ifdef ENABLE_PNG_DECODE
    #define HASP_USE_PNGDECODE 1
#endif

#ifdef ENABLE_BMP_DECODE
    #define HASP_USE_BMPDECODE 1
#endif

#ifdef ENABLE_JPG_DECODE
    #define HASP_USE_JPGDECODE 1
#else
    #define HASP_USE_JPGDECODE 0
#endif

#ifdef ENABLE_GIF_DECODE
    #define HASP_USE_GIFDECODE 1
#else
    #define HASP_USE_GIFDECODE 0
#endif

// Hardware
#ifdef ENABLE_TOUCH_GT911
    #define HASP_USE_TAMC_GT911 1
    #define HASP_USE_LGFX_TOUCH 0
#endif

#ifdef ENABLE_ARDUINO_OTA
    #define HASP_USE_ARDUINOOTA 1
#endif

#ifdef ENABLE_MDNS
    #define HASP_USE_MDNS 1
#else
    #define HASP_USE_MDNS 0
#endif

#endif // HASP_USER_CONFIG_MODULES_H
