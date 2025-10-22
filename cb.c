/**
 * @file   cb.c
 * @brief  Example cb build system.
 * @author Alicia Amarilla (smushyaa@gmail.com)
 * @date   September 23, 2025
*/
#undef CB_IMPL
#include "cb.h"

DirWalkAction walk( const char* path, DirWalkInfo* info, void* params ) {
    logger_output( LOG_INFO, "[I] " );
    for( size_t i = 0; i < info->level; ++i ) {
        logger_output( LOG_INFO, "|   " );
    }

    logger_output( LOG_INFO, "%s\n", path + info->path_name_offset );

    return DWA_CONTINUE;
}

int main( int argc, char** argv ) {
    CB_BUILD_INIT();

    dir_walk( ".", walk, NULL );

    return 0;
}

#define CB_IMPL
#include "cb.h"

