#ifndef ARK_MACROS_H
#define ARK_MACROS_H


#ifndef ARK_ATTRIB_DEPRECATED
    #if defined(__GNUC__) || defined(__clang__)
        #define ARK_ATTRIB_DEPRECATED __attribute__((deprecated))
    #elif define(_MSVC)
        #define ARK_ATTRIB_DEPRECATED
    #else
        #define ARK_ATTRIB_DEPRECATED
    #endif
#endif


#endif