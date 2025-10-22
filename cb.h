#if !defined(CB_H)
#define CB_H
/**
 * @file   cb.h
 * @brief  C Build system.
 * @author Alicia Amarilla (smushyaa@gmail.com)
 * @date   August 20, 2025
*/
// IWYU pragma: begin_exports
#define _XOPEN_SOURCE 800
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
// IWYU pragma: end_exports

/// @brief Major version.
#define CB_VERSION_MAJOR 0
/// @brief Minor version.
#define CB_VERSION_MINOR 1
/// @brief Patch version.
#define CB_VERSION_PATCH 0

// NOTE(alicia): identifying current platform ---------------------------------

/// @brief Compiler: Unknown
#define CB_COMPILER_UNKNOWN 0
/// @brief Compiler: GCC
#define CB_COMPILER_GCC     1
/// @brief Compiler: clang
#define CB_COMPILER_CLANG   2
/// @brief Compiler: Microsoft Visual C/C++
#define CB_COMPILER_MSVC    3
/// @brief Compiler count.
#define CB_COMPILER_COUNT   4

#define CB_COMPILER_CURRENT        CB_COMPILER_UNKNOWN
#define CB_COMPILER_GNU_COMPATIBLE 0

#if defined(__GNUC__)
    #undef  CB_COMPILER_GNU_COMPATIBLE
    /// @brief Current compiler is GNU C/C++ compatible.
    #define CB_COMPILER_GNU_COMPATIBLE 1

    #if defined(__clang__)
        #undef  CB_COMPILER_CURRENT
        /// @brief Current compiler: clang
        #define CB_COMPILER_CURRENT CB_COMPILER_CLANG
    #else
        #undef  CB_COMPILER_CURRENT
        /// @brief Current compiler: GCC
        #define CB_COMPILER_CURRENT CB_COMPILER_GCC
    #endif
#elif defined(_MSC_VER)
    #undef  CB_COMPILER_CURRENT
    /// @brief Current compiler: Microsoft Visual C/C++
    #define CB_COMPILER_CURRENT CB_COMPILER_MSVC
#endif

/// @brief OS: Unknown
#define CB_OS_UNKNOWN   0
/// @brief OS: GNU-Linux
#define CB_OS_GNU_LINUX 1
/// @brief OS: Windows
#define CB_OS_WINDOWS   2
/// @brief OS: MacOS
#define CB_OS_MACOS     3
/// @brief OS count.
#define CB_OS_COUNT     4

#define CB_OS_CURRENT  CB_OS_UNKNOWN
#define CB_OS_IS_POSIX 0

#if defined(__gnu_linux__)
    #undef  CB_OS_CURRENT
    #undef  CB_OS_IS_POSIX
    /// @brief Current OS: GNU-Linux
    #define CB_OS_CURRENT CB_OS_GNU_LINUX
    /// @brief Current OS is Posix compatible.
    #define CB_OS_IS_POSIX 1
#elif defined(__MACOS)
    #undef  CB_OS_CURRENT
    #undef  CB_OS_IS_POSIX
    /// @brief Current OS: MacOS
    #define CB_OS_CURRENT CB_OS_MACOS
    /// @brief Current OS is Posix compatible.
    #define CB_OS_IS_POSIX 1
#elif defined(_WIN32)
    #undef  CB_OS_CURRENT
    #undef  CB_OS_IS_POSIX
    /// @brief Current OS: Windows
    #define CB_OS_CURRENT CB_OS_WINDOWS
    /// @brief Current OS is NOT Posix compatible.
    #define CB_OS_IS_POSIX 0
#endif

/// @brief Architecture: Unknown
#define CB_ARCH_UNKNOWN 0
/// @brief Architecture: x86
#define CB_ARCH_X86     1
/// @brief Architecture: ARM
#define CB_ARCH_ARM     2
/// @brief Architecture count.
#define CB_ARCH_COUNT   3

#define CB_ARCH_CURRENT   CB_ARCH_UNKNOWN
#define CB_ARCH_WORD_SIZE 64
#define CB_ARCH_IS_64BIT  1

#if defined(__aarch64__) || defined(_M_ARM64)
    #undef  CB_ARCH_CURRENT
    /// @brief Current Architecture: ARM
    #define CB_ARCH_CURRENT CB_ARCH_ARM
#elif defined(__arm__) || defined(_M_ARM)
    #undef  CB_ARCH_CURRENT
    #undef  CB_ARCH_WORD_SIZE
    #undef  CB_ARCH_IS_64BIT
    /// @brief Current Architecture: ARM
    #define CB_ARCH_CURRENT CB_ARCH_ARM
    /// @brief Current Architecture Word Size: 32-bit
    #define CB_ARCH_WORD_SIZE 32
    /// @brief Current Architecture Is 64-bit: false
    #define CB_ARCH_IS_64BIT 0
#elif defined(__X86__) || defined(__x86_64__)
    #undef  CB_ARCH_CURRENT
    /// @brief Current Architecture: x86
    #define CB_ARCH_CURRENT CB_ARCH_X86
#elif defined(__i386__) || defined(_M_IX86)
    #undef  CB_ARCH_CURRENT
    #undef  CB_ARCH_WORD_SIZE
    #undef  CB_ARCH_IS_64BIT
    /// @brief Current Architecture: x86
    #define CB_ARCH_CURRENT CB_ARCH_X86
    /// @brief Current Architecture Word Size: 32-bit
    #define CB_ARCH_WORD_SIZE 32
    /// @brief Current Architecture Is 64-bit: false
    #define CB_ARCH_IS_64BIT 0
#endif

/// @brief Endianness: Little
#define CB_ENDIAN_LITTLE 0
/// @brief Endianness: Big
#define CB_ENDIAN_BIG    1
/// @brief Endianness count.
#define CB_ENDIAN_COUNT  2

/// @brief Current Endianness: Little
#define CB_ENDIAN_CURRENT CB_ENDIAN_LITTLE

// NOTE(alicia): identifying current platform end -----------------------------

/// @brief Version string.
#define CB_VERSION_STRING \
    CB_STRINGIFY2(CB_VERSION_MAJOR) "." \
    CB_STRINGIFY2(CB_VERSION_MINOR) "." \
    CB_STRINGIFY2(CB_VERSION_PATCH)

/// @brief Version number.
#define CB_VERSION \
    CB_VERSION_CREATE( CB_VERSION_MAJOR, CB_VERSION_MINOR, CB_VERSION_PATCH )

/// @brief Create a version number.
/// @param major (uint16_t) Major version.
/// @param minor (uint8_t)  Minor version.
/// @param patch (uint8_t)  Patch version.
/// @return (uint32_t) Version number.
#define CB_VERSION_CREATE( major, minor, patch ) \
    ((unsigned int)((major) << 16u | (minor) << 8u | (patch)))

/// @brief Read Major version number.
/// @param version (uint32_t) Version number.
/// @return (uint16_t) Major version number.
#define CB_VERSION_READ_MAJOR( version ) \
    ((unsigned short)(((version) & 0xFFFF0000u) >> 16u))
/// @brief Read Minor version number.
/// @param version (uint32_t) Version number.
/// @return (uint8_t) Minor version number.
#define CB_VERSION_READ_MINOR( version ) \
    ((unsigned char)(((version) & 0x0000FF00u) >> 8u))
/// @brief Read Patch version number.
/// @param version (uint32_t) Version number.
/// @return (uint8_t) Patch version number.
#define CB_VERSION_READ_PATCH( version ) \
    ((unsigned char)((version) & 0x000000FFu))

/// @brief Concatenate tokens.
/// @param a, b Tokens.
/// @return Concatenated tokens.
#define CB_CONCAT( a, b ) a##b
/// @brief Concatenate expanded tokens.
/// @param a, b Tokens.
/// @return Concatenated tokens.
#define CB_CONCAT2( a, b ) CB_CONCAT( a, b )

/// @brief Create string from token.
/// @param x Token.
/// @return String literal.
#define CB_STRINGIFY(x)  #x
/// @brief Create string from expanded token.
/// @param x Token.
/// @return String literal.
#define CB_STRINGIFY2(x) CB_STRINGIFY(x)

#if !defined(CB_FLT_EPSILON)
    /// @brief Float epsilon constant.
    #define CB_FLT_EPSILON (1e-6f)
#endif

#if !defined(CB_DBL_EPSILON)
    /// @brief Double epsilon constant.
    #define CB_DBL_EPSILON (1e-12f)
#endif

/// @brief Maximum path length.
#define CB_MAX_PATH (4096)

#if !defined(CB_LOCAL_COUNT)
    /// @brief Local buffer count.
    #define CB_LOCAL_COUNT (8)
#endif

#if CB_LOCAL_COUNT < 4
    #undef CB_LOCAL_COUNT
    /// @brief Local buffer count.
    #define CB_LOCAL_COUNT (4)
#endif

#if !defined(CB_THREAD_STACK_SIZE)
    /// @brief Size of thread stack.
    #define CB_THREAD_STACK_SIZE (1 * 1024 * 1024)
#endif

#if CB_THREAD_STACK_SIZE < 4096
    #undef CB_THREAD_STACK_SIZE
    /// @brief Size of thread stack.
    #define CB_THREAD_STACK_SIZE (4096)
#endif

#if !defined(CB_THREAD_COUNT)
    /// @brief Minimum thread count.
    #define CB_THREAD_COUNT (8)
#endif

#if CB_THREAD_COUNT < 4
    #undef CB_THREAD_COUNT
    /// @brief Minimum thread count.
    #define CB_THREAD_COUNT (4)
#endif

#if !defined(CB_JOB_COUNT)
    /// @brief Job count.
    #define CB_JOB_COUNT (32)
#endif

#if CB_JOB_COUNT < 16
    #undef CB_JOB_COUNT
    /// @brief Job count.
    #define CB_JOB_COUNT (16)
#endif

#if !defined(CB_DEF)
    /// @brief Function prefix.
    #define CB_DEF
#endif

#if CB_COMPILER_GNU_COMPATIBLE
    /// @brief Function uses printf formatting.
    /// @param FormatIndex Index of format string literal.
    /// @param ArgIndex    Index of arguments.
    #define CB_FMT(FormatIndex, ArgIndex) \
        __attribute__((format(printf, FormatIndex, ArgIndex)))
#else
    /// @brief Function uses printf formatting.
    /// @param FormatIndex Index of format string literal.
    /// @param ArgIndex    Index of arguments.
    #define CB_FMT(FormatIndex, ArgIndex)
#endif

#if __cplusplus
    /// @brief Function inline prefix.
    #define CB_INL inline
    /// @brief Thread local prefix.
    #define CB_TLS thread_local
#else
    /// @brief Function inline prefix.
    #define CB_INL static inline
    /// @brief Thread local prefix.
    #define CB_TLS _Thread_local
#endif

#if !defined(CB_PREFIX_TYPE)
    /// @brief Prefix token for types.
    #define CB_PREFIX_TYPE
#endif

#if !defined(CB_PREFIX_FUNC)
    /// @brief Prefix token for functions.
    #define CB_PREFIX_FUNC
#endif

#if !defined(CB_PREFIX_ENUM)
    /// @brief Prefix token for enums.
    #define CB_PREFIX_ENUM
#endif

/// @brief Prefixed type.
/// @param x Type name token.
/// @return Prefixed type name.
#define _T(x) CB_CONCAT2( CB_PREFIX_TYPE, x )
/// @brief Prefixed function.
/// @param x Function name token.
/// @return Prefixed function name.
#define _F(x) CB_CONCAT2( CB_PREFIX_FUNC, x )
/// @brief Prefixed enum.
/// @param x Enum name token.
/// @return Prefixed enum name.
#define _E(x) CB_CONCAT2( CB_PREFIX_ENUM, x )

/// @brief Multi-threaded wait infinite.
#define CB_WAIT_INF 0xFFFFFFFF

/// @brief ANSI Color Constant: Black
#define CB_COLOR_BLACK   "\033[1;30m"
/// @brief ANSI Color Constant: White
#define CB_COLOR_WHITE   "\033[1;37m"
/// @brief ANSI Color Constant: Red
#define CB_COLOR_RED     "\033[1;31m"
/// @brief ANSI Color Constant: Green
#define CB_COLOR_GREEN   "\033[1;32m"
/// @brief ANSI Color Constant: Blue
#define CB_COLOR_BLUE    "\033[1;34m"
/// @brief ANSI Color Constant: Magenta
#define CB_COLOR_MAGENTA "\033[1;35m"
/// @brief ANSI Color Constant: Yellow 
#define CB_COLOR_YELLOW  "\033[1;33m"
/// @brief ANSI Color Constant: Cyan
#define CB_COLOR_CYAN    "\033[1;36m"
/// @brief ANSI Color Constant: Reset
#define CB_COLOR_RESET   "\033[1;00m"

/// @brief UTF-8 Replacement Character Constant.
#define CB_CP8_REPLACEMENT_CHARACTER \
    _F(cp8_from_code_units)( 0xEF, 0xBF, 0xBD, 0 )

/// @brief UTF-16 Replacement Character Constant.
#define CB_CP16_REPLACEMENT_CHARACTER \
    _F(cp16_from_code_units)( 0xFFFD, 0 )

/// @brief UTF-32 Replacement Character Constant.
#define CB_CP32_REPLACEMENT_CHARACTER \
    _F(cp32_from_code_units)( 0xFFFD )

// NOTE(alicia): types --------------------------------------------------------

/// @brief Allocator Function Prototype: Alloc.
/// @param[in] ptr      (optional) Pointer to memory to reallocate.
/// @param     old_size (optional) Size of memory pointed to by @c ptr.
/// @param     new_size Size of memory to allocate or reallocate @c ptr to.
/// @param[in] params   (optional) Allocator context.
/// @return
///     - @c NULL : Failed to allocate memory.
///     - Pointer : Start of memory block that was allocated.
typedef void* _T(AllocFN)( void* ptr, size_t old_size, size_t new_size, void* params );
/// @brief Allocator Function Prototype: Free.
/// @param[in] ptr    Pointer to memory to free.
/// @param     size   Size of memory pointed to by @c ptr.
/// @param[in] params (optional) Allocator context.
typedef void  _T(FreeFN)( void* ptr, size_t size, void* params );

/// @brief ID of Multi-threaded job.
typedef int _T(JobID);
/// @brief Multi-threaded job function prototype.
/// @param     id     ID of job.
/// @parma[in] params (optional) Pointer to job parameters.
/// @return Exit code of job. Zero == success.
typedef int _T(JobFN)( _T(JobID) id, void* params );

/// @brief Atomic Mutex.
/// @warning Do not directly modify fields!
typedef struct {
    /// @brief Mutex atom.
    volatile int atom;
} _T(Mutex);

/// @brief Atomic Semaphore.
/// @warning Do not directly modify fields!
typedef struct {
    /// @brief Semaphore atom.
    volatile int atom;
    /// @brief Semaphore mutex.
    _T(Mutex)    mtx;
} _T(Semaphore);

/// @brief Slice of bytes.
typedef struct {
    /// @brief Length of slice.
    size_t len;
    /// @brief Pointer to start of slice.
    char*  ptr;
} _T(ByteSlice);

/// @brief Buffer of bytes.
typedef struct {
    /// @brief Capacity of buffer in bytes.
    size_t cap;
    /// @brief Anonymous union of buffer components and slice.
    union {
        /// @brief Anonymous struct of buffer components.
        struct {
            /// @brief Length of valid data in buffer.
            size_t len;
            /// @brief Pointer to start of buffer.
            char*  ptr;
        };
        /// @brief Slice of valid buffer bytes.
        _T(ByteSlice) slice;
    };
} _T(ByteBuf);

/// @brief String slice.
typedef _T(ByteSlice) _T(String);
/// @brief String buffer.
typedef _T(ByteBuf)   _T(StringBuf);

/// @brief Buffer of null-terminated strings.
typedef struct {
    /// @brief Number of pointers buffer can hold.
    size_t       cap;
    /// @brief Number of pointers in buffer.
    size_t       len;
    /// @brief Pointer to start of buffer.
    const char** ptr;
} _T(CStringBuf);

/// @brief List of dependencies.
typedef struct {
    /// @brief Anonymous union of dependency path buffer components and buffer.
    union {
        /// @brief Anonymous struct of dependency path buffer components.
        struct {
            /// @brief Number of paths buffer can hold.
            size_t       cap;
            /// @brief Number of valid paths in buffer.
            size_t       len;
            /// @brief Pointer to start of buffer.
            const char** ptr;
        };
        /// @brief Buffer of dependency paths.
        _T(CStringBuf) deps;
    };
    /// @brief Path to target of dependencies.
    const char*   target;
    /// @brief String buffer.
    _T(StringBuf) string;
} _T(Deps);

/// @brief Code units for UTF-8 rune.
typedef struct {
    /// @brief Code units array.
    uint8_t cp[4];
} _T(CodeUnits8);

/// @brief Code units for UTF-16 rune.
typedef struct {
    /// @brief Code units array.
    uint16_t cp[2];
} _T(CodeUnits16);

/// @brief UTF-32 rune.
typedef uint32_t _T(Rune32);
/// @brief UTF-16 rune.
typedef uint16_t _T(Rune16);
/// @brief UTF-8 rune.
typedef uint8_t  _T(Rune8);

/// @brief Set of runes.
typedef struct {
    /// @brief Number of runes pointed to by @c ptr.
    size_t      len;
    /// @brief Pointer to start of rune set.
    _T(Rune32)* ptr;
} _T(Rune32Set);

/// @brief Log levels.
typedef enum {
    /// @brief Log level: INFO.
    /// @details
    /// Info log messages are printed when information for the end user needs to be printed.
    _E(LOG_INFO),
    /// @brief Log level: WARN.
    /// @details
    /// Warning log messages are printed when something unintended or unoptimal happens.
    _E(LOG_WARN),
    /// @brief Log level: ERROR.
    /// @details
    /// Error log messages are printed when a recoverable error is encountered.
    _E(LOG_ERROR),
    /// @brief Log level: FATAL.
    /// @details
    /// Fatal log messages are printed before a crash.
    _E(LOG_FATAL),
    /// @brief Log level: NONE.
    /// @details
    /// This is only used to tell library to not output log messages.
    _E(LOG_NONE),

    /// @brief Number of log levels.
    _E(LOG_COUNT)
} _T(LogLevel);

/// @brief Opaque handle to OS resource.
/// @warning Fields in this struct should never be directly modified!
typedef union {
    /// @brief Opaque pointer.
    void* opaque_ptr;
    /// @brief Opaque file descriptor. (Posix only)
    int   opaque_fd;
} _T(Handle);

/// @brief File handle.
typedef _T(Handle) _T(File);
/// @brief Pipe handle.
typedef _T(Handle) _T(Pipe);
/// @brief Process handle.
typedef _T(Handle) _T(Process);

/// @brief Posix timestamp.
typedef intptr_t _T(Time);

/// @brief Year number.
typedef uint32_t _T(TimeYear);
/// @brief Month number.
typedef uint32_t _T(TimeMonth);
/// @brief Day number.
typedef uint32_t _T(TimeDay);
/// @brief Hour number.
typedef uint32_t _T(TimeHour);
/// @brief Minute number.
typedef uint32_t _T(TimeMinute);
/// @brief Second number.
typedef uint32_t _T(TimeSecond);

/// @brief Time stamp split into its various components.
typedef struct {
    /// @brief Year.
    _T(TimeYear)   year;
    /// @brief Month.
    _T(TimeMonth)  month;
    /// @brief Day.
    _T(TimeDay)    day;
    /// @brief Hour.
    _T(TimeHour)   hour;
    /// @brief Minute.
    _T(TimeMinute) minute;
    /// @brief Second.
    _T(TimeSecond) second;
} _T(TimeSplit);

/// @brief Flags for opening a file.
typedef enum {
    /// @brief Open file for reading.
    _E(FF_READ)     = (1 << 0),
    /// @brief Open file for writing.
    _E(FF_WRITE)    = (1 << 1),
    /// @brief Provide execution permission when creating file.
    _E(FF_EXECUTE)  = (1 << 2),
    /// @brief Create file if it doesn't exist.
    _E(FF_CREATE)   = (1 << 4),
    /// @brief Truncate file if it already exists.
    _E(FF_TRUNCATE) = (1 << 5),
    /// @brief If file exists, set write pointer to end of file.
    _E(FF_APPEND)   = (1 << 6),
} _T(FileFlags);

/// @brief Whence to seek from when seeking a file.
typedef enum {
    /// @brief Set write pointer to given offset from the start of file.
    _E(FS_SET),
    /// @brief Set write pointer to offset from current position of the write pointer.
    _E(FS_CUR),
    /// @brief Set write pointer to offset from the end of file.
    _E(FS_END),
} _T(FileSeek);

/// @brief File types.
typedef enum {
    /// @brief File does not exist.
    _E(FT_NULL),
    /// @brief File is a regular file.
    _E(FT_FILE),
    /// @brief File is a directory.
    _E(FT_DIR),
    /// @brief File is a pipe.
    _E(FT_PIPE),
} _T(FileType);

/// @brief File information.
typedef struct {
    /// @brief Type of file.
    _T(FileType) type;
    /// @brief Size of file in bytes.
    size_t       size;
    /// @brief Time that file was created.
    _T(Time)     time_create;
    /// @brief Time that file was last modified.
    _T(Time)     time_modify;
} _T(FileInfo);

/// @brief Directory walk actions.
typedef enum {
    /// @brief Continue walking into sub-directory or to next item in directory.
    _E(DWA_CONTINUE),
    /// @brief Stop walking through directory and sub-directories.
    _E(DWA_STOP),
    /// @brief Skip sub-directory and walk to next item in current directory.
    _E(DWA_SKIP),
} _T(DirWalkAction);

/// @brief Information for current item in directory when walking a directory.
typedef struct {
    /// @brief Type of file.
    _T(FileType) file_type;
    /// @brief Time when file was created.
    _T(Time)     file_time_create;
    /// @brief Last time file was modified.
    _T(Time)     file_time_modify;
    /// @brief Size of file in bytes.
    size_t       file_size;
    /// @brief Length of path in bytes.
    size_t       path_len;
    /// @brief Byte offset of file name in path.
    size_t       path_name_offset;
    /// @brief If path has an extension.
    bool         path_has_ext    : 1;
    /// @brief Byte offset of extension part of path.
    size_t       path_ext_offset : CB_ARCH_WORD_SIZE - 1;
    /// @brief Sub-directory level of current item.
    intptr_t     level;
} _T(DirWalkInfo);

/// @brief Function prototype for directory walk.
/// @param[in] path   Path of current item.
/// @param[in] info   Info for current item.
/// @param[in] params (optional) User params.
/// @return What directory walk function should do after this item.
/// @see DirWalkAction
typedef _T(DirWalkAction) _T(DirWalkFN)( const char* path, _T(DirWalkInfo)* info, void* params );

/// @brief Command line for a process.
typedef struct {
    /// @brief Number of strings in command line.
    size_t       len;
    /// @brief Pointer to first argument, name of process is always first.
    /// @warning Must always end with a NULL pointer.
    const char** ptr;
} _T(Cmd);

/// @brief Current process' command line.
typedef struct {
    /// @brief Number of strings in command line.
    size_t       len;
    /// @brief Pointer to first argument, name of process is always first.
    const char** ptr;
} _T(CmdLine);

/// @brief Buffer of command line arguments.
typedef struct {
    /// @brief Number of strings buffer can hold.
    size_t cap;
    /// @brief Anonymous union of string pointer slice and components.
    union {
        /// @brief Anonymous struct of string pointer slice components.
        struct {
            /// @brief Number of strings in buffer.
            size_t       len;
            /// @brief Pointer to start of string pointer buffer.
            const char** ptr;
        };
        /// @brief Slice of arguments.
        _T(Cmd) cmd;
    };
    /// @brief String buffer.
    _T(StringBuf) string;
} _T(CmdBuf);

/// @brief String slice. Offset from pointer.
typedef struct {
    /// @brief Number of bytes in string.
    size_t len;
    /// @brief Byte offset of start of string.
    size_t offset;
} _T(StringOffset);

/// @brief Environment variable key/value pair.
typedef struct {
    /// @brief key, value Key/value pair.
    _T(StringOffset) key, value;
} _T(EnvKV);

/// @brief Environment variable set.
typedef struct {
    /// @brief Number of key/value pairs buffer can hold. 
    size_t        cap;
    /// @brief Number of key/value pairs in buffer. 
    size_t        len;
    /// @brief Pointer to start of key/value pair buffer.
    _T(EnvKV)*    ptr;
    /// @brief String buffer.
    _T(StringBuf) string;
} _T(Env);

/// @brief Process signals.
typedef enum {
    /// @brief Null signal. Does nothing.
    _E(PSIG_NULL),
    /// @brief Kill signal. Used to force end of execution unless it's caught by process.
    _E(PSIG_KILL),

    /// @brief Number of signals.
    _E(PSIG_COUNT)
} _T(ProcessSignal);

/// @brief Process data.
typedef struct {
    /// @brief Process handle.
    _T(Process) handle;
    /// @brief Exit code of process.
    int         exit_code;
} _T(ProcessData);

/// @brief Group of related processes.
typedef struct {
    /// @brief Number of processes group can hold.
    size_t           cap;
    /// @brief Number of active processes in group.
    size_t           len;
    /// @brief Pointer to processes.
    _T(ProcessData)* ptr;
} _T(ProcessGroup);

/// @brief CRC-32 hash.
typedef uint32_t _T(CRC32);

/// @brief MD5 hash.
typedef struct {
    /// @brief Array of components.
    uint32_t c[4];
} _T(MD5);

/// @brief SHA1 hash.
typedef struct {
    /// @brief Array of components.
    uint32_t c[5];
} _T(SHA1);

/// @brief 64-bit generic hash.
typedef union {
    struct {
        /// @brief Low half of hash.
        uint32_t lo;
        /// @brief High half of hash.
        uint32_t hi;
    };
    /// @brief Array of components.
    uint32_t c[2];
} _T(Hash);

// NOTE(alicia): internal structures ------------------------------------------

typedef struct {
    /// @brief (optional) Working directory for process.
    const char*       wd;
    /// @brief (optional) Pointer to environment for process.
    _T(Env)*          env;
    /// @brief (optional) Pointer to stdin pipe (Read).
    _T(Pipe)*         pstdin;
    /// @brief (optional) Pointer to stdout pipe (Write).
    _T(Pipe)*         pstdout;
    /// @brief (optional) Pointer to stderr pipe (Write).
    _T(Pipe)*         pstderr;
    /// @brief (optional) Pointer to process group to add process to.
    /// @details
    /// Setting this pointer will execute process asynchronously.
    _T(ProcessGroup)* group;
    /// @brief (optional) Pointer to write process to.
    /// @details
    /// Setting this pointer will execute process asynchronously.
    _T(Process)*      proc;
} __CbExecParams;

// NOTE(alicia): macro functions ----------------------------------------------

#if CB_COMPILER_CURRENT == CB_COMPILER_MSVC
    /// @brief Insert unreachable statement.
    #define CB_INSERT_UNREACHABLE() __assume(0)

    /// @brief Insert a trap statement. (crash program)
    #define CB_INSERT_TRAP() __debugbreak()

    /// @brief Insert a debugger break statement.
    #define CB_INSERT_DBG_BREAK() __debugbreak()
#else
    /// @brief Insert unreachable statement.
    #define CB_INSERT_UNREACHABLE() __builtin_unreachable()

    /// @brief Insert a trap statement. (crash program)
    #define CB_INSERT_TRAP() __builtin_trap()

    /// @brief Insert a debugger break statement.
    #define CB_INSERT_DBG_BREAK() __builtin_debugtrap()
#endif

/// @brief Crash program with a message.
/// @param ... (const char* literal, ...) Format string and arguments for message.
#define CB_PANIC( ... ) do {                      \
    CB_FATAL(                                     \
        "Panic! "                                 \
        __FILE__ ":" CB_STRINGIFY2(__LINE__) ": " \
        __VA_ARGS__ );                            \
    CB_INSERT_TRAP();                             \
} while(0)

/// @brief Debug break with a message.
/// @details
/// If running in a debugger, pauses execution with a message to stderr.
///
/// If not, outputs message to stderr and crashes.
/// @param ... (const char* literal, ...) Format string and arguments for message.
#define CB_DBG_BREAK( ... ) do {                  \
    CB_FATAL(                                     \
        "Debug Break: "                           \
        __FILE__ ":" CB_STRINGIFY2(__LINE__) ": " \
        __VA_ARGS__ );                            \
    CB_INSERT_DBG_BREAK();                        \
} while(0)

/// @brief Assert that condition is true.
/// @details
/// If condition is true, continues execution as normal.
///
/// If condition is false, crashes program.
/// @param Condition (boolean expression) Condition to check for.
/// @param ...       (const char* literal, ...) Format string and arguments for message.
#define CB_ASSERT(Condition, ...) do {                \
    if( !(Condition) ) {                              \
        CB_FATAL(                                     \
            "Assertion Failed! (" #Condition ") "     \
            __FILE__ ":" CB_STRINGIFY2(__LINE__) ": " \
            __VA_ARGS__ );                            \
        CB_INSERT_TRAP();                             \
    }                                                 \
} while(0)

/// @brief Mark values as unused to silence warnings.
/// @param ... (Tokens) List of values to mark as unused.
#define CB_UNUSED(...) \
    __cb_unused( 0, __VA_ARGS__ )

/// @brief Calculate bytes in kilobytes.
/// @param kb Number of kilobytes.
/// @return Bytes.
#define CB_KILOBYTES( kb ) (kb * 1000ULL)
/// @brief Calculate bytes in megabytes.
/// @param mb Number of megabytes.
/// @return Bytes.
#define CB_MEGABYTES( mb ) (CB_KILOBYTES(mb) * 1000ULL)
/// @brief Calculate bytes in gigabytes.
/// @param gb Number of gigabytes.
/// @return Bytes.
#define CB_GIGABYTES( gb ) (CB_MEGABYTES(gb) * 1000ULL)
/// @brief Calculate bytes in terabytes.
/// @param tb Number of terabytes.
/// @return Bytes.
#define CB_TERABYTES( tb ) (CB_GIGABYTES(tb) * 1000ULL)

/// @brief Calculate bytes in kibibytes.
/// @param kb Number of kibibytes.
/// @return Bytes.
#define CB_KIBIBYTES( kb ) (kb * 1024ULL)
/// @brief Calculate bytes in mebibytes.
/// @param mb Number of mebibytes.
/// @return Bytes.
#define CB_MEBIBYTES( mb ) (CB_KIBIBYTES(mb) * 1024ULL)
/// @brief Calculate bytes in gibibytes.
/// @param gb Number of gibibytes.
/// @return Bytes.
#define CB_GIBIBYTES( gb ) (CB_MEBIBYTES(gb) * 1024ULL)
/// @brief Calculate bytes in tebibytes.
/// @param tb Number of tebibytes.
/// @return Bytes.
#define CB_TEBIBYTES( tb ) (CB_GIBIBYTES(tb) * 1024ULL)

/// @brief Define a slice.
/// @param T    (Token) Type of slice pointer.
/// @param Name (Token) Name of slice. Result is NameSlice.
/// @return Slice.
#define CB_QUICK_SLICE( T, Name ) \
typedef struct Name##Slice {      \
    size_t len;                   \
    T*     ptr;                   \
} Name##Slice

/// @brief Define a buffer.
/// @param T    (Token) Type of buffer pointer.
/// @param Name (Token) Name of buffer. Result is NameBuf.
/// @return Buffer.
#define CB_QUICK_BUF( T, Name ) \
typedef struct Name##Buf {      \
    size_t cap;                 \
    size_t len;                 \
    T*     ptr;                 \
} Name##Buf

/// @brief Calculate length of static array.
/// @param Array Array to calculate length for.
/// @return (size_t) Number of items in array.
#define CB_ARRAY_LEN( Array ) \
    (sizeof((Array)) / sizeof((Array)[0]))

/// @brief String slice format string.
/// @details
/// Does not include preceding @c \%
#define CB_STRING_FMT ".*s"

/// @brief Deconstruct string slice arguments for format string.
/// @param[in] StringStruct (String*) Pointer to string slice.
#define CB_STRING_ARG( StringStruct ) \
    (int)(StringStruct)->len, (char*)((StringStruct)->ptr)

/// @brief Create string slice from null-terminated string.
/// @note Use CB_STRING if @c CStr is a string literal.
/// @param[in] CStr (const char*) Null-terminated string.
/// @return String slice.
#define CB_STRING_FROM_CSTR( CStr ) \
    CB_STRUCT( _T(String), .len=_F(cstr_len)( (CStr) ), .ptr=(char*)(CStr) )

#define __CB_FOREACH( Slice, CodeSnippet, Value, Index, ... ) do {    \
    __typeof((Slice)->ptr) Value = (Slice)->ptr;                      \
    for( size_t Index = 0; Index < (Slice)->len; ++Index, ++Value ) { \
        CodeSnippet                                                   \
    }                                                                 \
} while(0)

/// @brief Foreach loop.
/// @param Slice       (Slice*) Pointer to slice to loop over.
/// @param CodeSnippet (Token)  Code to run for each item. Must be wrapped with {}.
/// @param ...         (Tokens) Name of pointer for argument values and name of index.
#define CB_FOREACH( Slice, CodeSnippet, ... ) \
    __CB_FOREACH(                             \
        Slice,                                \
        { CodeSnippet },                      \
        __VA_ARGS__ __VA_OPT__(,)             \
        CB_CONCAT2(__ptr_,__LINE__),          \
        CB_CONCAT2(__i_,__LINE__) )

#define __CB_FOREACH_REV( Slice, CodeSnippet, Value, Index, ... ) do { \
    __typeof((Slice)->ptr) Value = (Slice)->ptr + (Slice)->len;        \
    for( size_t Index = (Slice)->len; Value--, Index-- > 0; ) {        \
        CodeSnippet                                                    \
    }                                                                  \
} while(0)

/// @brief Reverse foreach loop.
/// @param Slice       (Slice*) Pointer to slice to loop over.
/// @param CodeSnippet (Token)  Code to run for each item. Must be wrapped with {}.
/// @param ...         (Tokens) Name of pointer for argument values and name of index.
#define CB_FOREACH_REV( Slice, CodeSnippet, ... ) \
    __CB_FOREACH_REV(                             \
        Slice,                                    \
        CodeSnippet,                              \
        __VA_ARGS__ __VA_OPT__(,)                 \
        CB_CONCAT2(__ptr_,__LINE__),              \
        CB_CONCAT2(__i_,__LINE__) )

/// @brief Print formatted info message.
/// @param[in] fmt (const char* literal) Format string.
/// @param     ... Format string arguments.
#define CB_INFO( fmt, ... ) \
    _F(logger_output)( _E(LOG_INFO), "[I] " fmt "\n" __VA_OPT__(,) __VA_ARGS__ )

/// @brief Print formatted warning message.
/// @param[in] fmt (const char* literal) Format string.
/// @param     ... Format string arguments.
#define CB_WARN( fmt, ... ) \
    _F(logger_output)( _E(LOG_WARN), "[W] " fmt "\n" __VA_OPT__(,) __VA_ARGS__ )

/// @brief Print formatted error message.
/// @param[in] fmt (const char* literal) Format string.
/// @param     ... Format string arguments.
#define CB_ERROR( fmt, ... ) \
    _F(logger_output)( _E(LOG_ERROR), "[E] " fmt "\n" __VA_OPT__(,) __VA_ARGS__ )

/// @brief Print formatted fatal message.
/// @param[in] fmt (const char* literal) Format string.
/// @param     ... Format string arguments.
#define CB_FATAL( fmt, ... ) \
    _F(logger_output)( _E(LOG_FATAL), "[F] " fmt "\n" __VA_OPT__(,) __VA_ARGS__ )

#if defined(__cplusplus)
    /// @brief Struct literal.
    /// @param Name (Token)  Name of struct.
    /// @param ...  (Tokens) Struct fields.
    #define CB_STRUCT( Name, ... ) Name{ __VA_ARGS__ }
#else
    /// @brief Struct literal.
    /// @param Name (Token)  Name of struct.
    /// @param ...  (Tokens) Struct fields.
    #define CB_STRUCT( Name, ... ) (Name){ __VA_ARGS__ }
#endif

/// @brief String slice literal.
/// @param[in] Literal (const char* literal) String literal.
#define CB_STRING( Literal ) \
    CB_STRUCT(_T(String), .len=sizeof((Literal)) - 1, .ptr=(char*)(Literal) )

/// @brief Rune set literal.
/// @param ... (uint32_t literals) Rune literals.
#define CB_RUNE_SET( ... ) \
    CB_STRUCT( _T(Rune32Set), \
        .len=sizeof((_T(Rune32)[]){ __VA_ARGS__ }) / sizeof(_T(Rune32)), \
        .ptr=(_T(Rune32)[]){ __VA_ARGS__ } )

/// @brief Reserve items in buffer.
/// @param[in] Buf     (Buffer*) Pointer to buffer.
///                      Takes any struct with size_t @c cap,
///                      size_t @c len and non-void pointer @c ptr fields.
/// @param     Minimum (size_t) Minimum number of items buffer should be able to hold.
///                      Compares against @c cap - @c len.
#define CB_BUF_RESERVE( Buf, Minimum ) do {                            \
    size_t __remaining__ = (Buf)->cap - (Buf)->len;                    \
    if( __remaining__ < (Minimum) ) {                                  \
        size_t __new_cap__  = (Buf)->cap + (Minimum) + 16;             \
        size_t __old_size__ = sizeof((Buf)->ptr[0]) * (Buf)->cap;      \
        size_t __new_size__ = sizeof((Buf)->ptr[0]) * __new_cap__;     \
        *(void**)(&(Buf)->ptr) =                                       \
            _F(mem_realloc)( (Buf)->ptr, __old_size__, __new_size__ ); \
        (Buf)->cap = __new_cap__;                                      \
    }                                                                  \
} while(0)

/// @brief Push item to end of buffer.
/// @param[in] Buf  (Buffer*) Pointer to buffer.
///                   Takes any struct with size_t @c cap,
///                   size_t @c len and non-void pointer @c ptr fields.
/// @param     Item (typeof(Buffer->ptr[0])) Item to push to end of buffer.
///                   Must dereference if it's a pointer.
#define CB_BUF_PUSH( Buf, Item ) do {  \
    CB_BUF_RESERVE( Buf, 1 );          \
    (Buf)->ptr[(Buf)->len++] = (Item); \
} while(0)

/// @brief Append items to end of buffer.
/// @param[in] Buf   (Buffer*) Pointer to buffer.
///                    Takes any struct with size_t @c cap,
///                    size_t @c len and non-void pointer @c ptr fields.
/// @param[in] Items (typeof(Buffer->ptr)) Pointer to items to append.
/// @param     Count (size_t) Number of items pointed to by @c Items.
#define CB_BUF_APPEND( Buf, Items, Count ) do {                                        \
    CB_BUF_RESERVE( (Buf), (Count) );                                                  \
    _F(mem_copy)( (Buf)->ptr + (Buf)->len, (Items), sizeof((Buf)->ptr[0]) * (Count) ); \
    (Buf)->len += (Count);                                                             \
} while(0)

/// @brief Remove item from buffer, keeps existing order.
/// @warning This macro-function does not check if index is in range!
/// @param[in] Buf   (Buffer*) Pointer to buffer.
///                    Takes any struct with size_t @c cap,
///                    size_t @c len and non-void pointer @c ptr fields.
/// @param     Index (size_t) Index of item to remove.
#define CB_BUF_REMOVE( Buf, Index ) do {                        \
    _F(mem_move)(                                               \
        (Buf)->ptr + (Index),                                   \
        (Buf)->ptr + (Index) + 1,                               \
        sizeof((Buf)->ptr[0]) * ((Buf)->cap - ((Index) + 1)) ); \
    (Buf)->len--;                                               \
} while(0)

/// @brief Remove item from buffer, swaps last item to index of item to remove.
/// @warning This macro-function does not check if index is in range!
/// @param[in] Buf   (Buffer*) Pointer to buffer.
///                    Takes any struct with size_t @c cap,
///                    size_t @c len and non-void pointer @c ptr fields.
/// @param     Index (size_t) Index of item to remove.
#define CB_BUF_REMOVE_SWAP( Buf, Index ) do {       \
    (Buf)->ptr[(Index)] = (Buf)->ptr[--(Buf)->len]; \
} while(0)

/// @brief Create byte slice from item slice.
/// @param[in] Slice (Slice*) Pointer to slice to create byte slice from.
/// @return ByteSlice.
#define CB_BYTES_FROM_SLICE( Slice ) \
    CB_STRUCT( _T(ByteSlice), sizeof(*((Slice)->ptr)) * (Slice)->len, (char*)(Slice)->ptr )

/// @brief Create byte buffer from item buffer.
/// @param[in] Buf (Buffer*) Pointer to buffer to create byte buffer from.
/// @return ByteBuf.
#define CB_BYTES_FROM_BUF( Buf )                                      \
    CB_STRUCT( _T(ByteBuf), sizeof(*((Array)->ptr)) * (Array)->cap,   \
        sizeof(*((Array)->ptr)) * (Array)->len, (char*)(Array)->ptr )

/// @brief Create new slice.
/// @param BaseType  (Token)  Type of items in slice.
/// @param SliceType (Token)  Type of slice to create.
/// @param ...       (Tokens) Items in slice.
/// @return Slice.
#define CB_SLICE_NEW( BaseType, SliceType, ... )            \
    CB_STRUCT(                                              \
        SliceType,                                          \
        .len=(CB_ARRAY_LEN(((BaseType[]){ __VA_ARGS__ }))), \
        .ptr=((BaseType[]){ __VA_ARGS__ }) )

#define __CB_SLICE_ADVANCE( Slice, Amount, ... )                                           \
    CB_STRUCT( __typeof(*(Slice)),                                                         \
        (Amount) <= (Slice)->len ? (Slice)->len - (Amount) : 0,                            \
        (Amount) <= (Slice)->len ? (Slice)->ptr + (Amount) : (Slice)->ptr + (Slice)->len )

/// @brief Advance slice.
/// @param[in] Slice (Slice*) Pointer to slice to advance.
/// @param     ...   (none or size_t) If no arguments,
///                    advances by one item, otherwise advances by input count.
/// @return Slice advanced by given number of items.
#define CB_SLICE_ADVANCE( Slice, ... ) \
    __CB_SLICE_ADVANCE( Slice, __VA_ARGS__ __VA_OPT__(,) 1 )

/// @brief Allocate slice.
/// @param[in] Slice  (Slice*) Pointer to slice to allocate.
/// @param     Amount (size_t) Number of items to allocate.
#define CB_SLICE_ALLOC( Slice, Amount ) do {                 \
    *(void**)(&(Slice)->ptr) =                               \
        _F(mem_alloc)( (Amount) * sizeof(*((Slice)->ptr)) ); \
    (Slice)->len = (Amount);                                 \
} while(0)

/// @brief Reallocate slice.
/// @param[in] Slice     (Slice*) Pointer to slice to reallocate.
/// @param     NewAmount (size_t) Number of items to reallocate to.
#define CB_SLICE_REALLOC( Slice, NewAmount ) do {             \
    *(void**)(&(Slice)->ptr) = _F(mem_realloc)( (Slice)->ptr, \
        sizeof(*((Slice)->ptr)) * (Slice)->len,               \
        sizeof(*((Slice)->ptr)) * (NewAmount) );              \
    (Slice)->len = (NewAmount);                               \
} while(0)

/// @brief Free an allocated slice.
/// @param[in] Slice (Slice*) Pointer to slice to free.
#define CB_SLICE_FREE( Slice ) do {                                       \
    _F(mem_free)( (Slice)->ptr, sizeof(*((Slice)->ptr)) * (Slice)->len ); \
    (Slice)->ptr = NULL;                                                  \
    (Slice)->len = 0;                                                     \
} while(0)

/// @brief Reverse items in slice.
/// @warning This function does not check if slice is empty or not!
/// @param[in] Slice (Slice*) Pointer to slice to reverse.
#define CB_SLICE_REVERSE( Slice ) do {       \
    _F(array_reverse)(                       \
        (Slice)->ptr,                        \
        sizeof(*((Slice)->ptr)),             \
        (Slice)->len,                        \
        (char[sizeof(*((Slice)->ptr))]){} ); \
} while(0)

/// @brief Allocate new buffer.
/// @param[in] Buf    (Buffer*) Pointer to buffer to allocate.
/// @param     Amount (size_t) Number of items to allocate.
#define CB_BUF_ALLOC( Buf, Amount ) do {                   \
    *(void**)(&(Buf)->ptr) =                               \
        _F(mem_alloc)( (Amount) * sizeof(*((Buf)->ptr)) ); \
    (Buf)->cap = (Amount);                                 \
} while(0)

/// @brief Reallocate new buffer.
/// @param[in] Buf       (Buffer*) Pointer to buffer to reallocate.
/// @param     NewAmount (size_t) Number of items to reallocate.
#define CB_BUF_REALLOC( Buf, NewAmount ) do {             \
    *(void**)(&(Buf)->ptr) = _F(mem_realloc)( (Buf)->ptr, \
        sizeof(*((Buf)->ptr)) * (Buf)->cap,               \
        sizeof(*((Buf)->ptr)) * (NewAmount) );            \
    (Buf)->cap = (NewAmount);                             \
} while(0)

/// @brief Free allocated buffer.
/// @param[in] Buf (Buffer*) Pointer to buffer to free.
#define CB_BUF_FREE( Buf ) do {                                     \
    _F(mem_free)( (Buf)->ptr, sizeof(*((Buf)->ptr)) * (Buf)->cap ); \
    (Buf)->ptr = NULL;                                              \
    (Buf)->len = 0;                                                 \
    (Buf)->cap = 0;                                                 \
} while(0)

/// @brief Create many directories at once.
/// @param ... (const char*) Comma-separated list of paths of directories to create.
#define CB_DIR_CREATE_MANY( ... ) \
    __cb_dir_create_many( __VA_ARGS__ , NULL )

/// @brief Execute command.
/// @param cmd (Cmd) Command to execute.
/// @param ... (Tokens) Arguments.
/// @see __CbExecParams.
/// @return
///     - If process executed synchronously: Exit code.
///         - @c 1-255 : Process executed successfully but returned an error.
///         - @c  0    : Process executed and returned successfully.
///         - @c -1    : Process exited abnormally.
///         - @c -2    : Failed to execute process.
///     - If process executed asynchronously:
///         - @c  0 : Process executed successfully.
///         - @c -2 : Failed to execute process.
#define CB_EXEC( cmd, ... ) \
    __cb_exec( cmd, CB_STRUCT( __CbExecParams, __VA_ARGS__ ) )

/// @brief Create command literal.
/// @param ... (const char*) List of arguments for command.
#define CB_CMD( ... ) \
    CB_STRUCT( _T(Cmd), \
        .len=sizeof(((const char*[]){ __VA_ARGS__ })) / sizeof(const char*), \
        .ptr=((const char*[]){ __VA_ARGS__, NULL }) )

/// @brief Append commands to command buffer.
/// @param[in] cmd (CmdBuf*) Pointer to command buffer.
/// @param     ... (const char* literals) List of arguments for command.
#define CB_CMD_APPEND( cmd, ... ) \
    __cb_cmd_append( cmd, __VA_ARGS__, NULL )

/// @brief Initialize build system.
#define CB_BUILD_INIT() \
    _F(build_init)( argv[0], __FILE__, argc, (const char**)argv )

/// @brief Create a command line struct for input arguments from main.
/// @param     argc (int)    Argument count.
/// @param[in] argv (char**) Pointer to start of arguments.
/// @return Command line.
#define CB_CL( argc, argv ) \
    CB_STRUCT( _T(CmdLine), .len=(size_t)argc, .ptr=(const char**)argv )

/// @brief Advance to next argument.
/// @param[int] CommandLine (CmdLine*) Pointer to command line.
/// @return Command line advanced to next argument.
#define CB_CL_NEXT( CommandLine ) \
    CB_SLICE_ADVANCE( CommandLine, 1 )

/// @brief Foreach loop over command line arguments.
/// @param[in] CommandLine (CmdLine*) Pointer to command line.
/// @param     CodeSnippet (Token) Code to execute for each item. Must be wrapped in {}.
#define CB_CL_FOREACH( CommandLine, CodeSnippet ) do { \
    while( (CommandLine)->len ) { \
        CodeSnippet \
        *(CommandLine) = CB_CL_NEXT( CommandLine ); \
    } \
} while(0)

// NOTE(alicia): functions ----------------------------------------------------

/// @brief Initialize build system.
/// @param[in] path_exec Path to executable. (usually cb or cb.exe)
/// @param[in] path_src  Path to source file. (usually cb.c)
/// @param     argc      Command line argument count.
/// @param[in] argv      Pointer to command line arguments.
CB_DEF void _F(build_init)(
    const char*  path_exec,
    const char*  path_src,
    int          argc,
    const char** argv );
/// @brief Rebuild build system.
/// @param[in] path_exec     Path to executable. (usually cb or cb.exe)
/// @param[in] path_src      Path to source file. (usually cb.c)
/// @param     argc          Command line argument count.
/// @param[in] argv          Pointer to command line arguments.
/// @param[in] opt_cmd       (optional) Pointer to override rebuild command.
/// @param     should_reload If program should reload itself (Posix only).
CB_DEF void _F(build_rebuild)(
    const char*  path_exec,
    const char*  path_src,
    int          argc,
    const char** argv,
    _T(Cmd)*     opt_cmd,
    bool         should_reload );

/// @brief Compare two floating point numbers.
/// @param a, b Numbers to compare.
/// @return
///     - @c true  : @c a and @c b are equal.
///     - @c false : @c a and @c b are NOT equal.
CB_DEF bool _F(float_cmp)( float a, float b );
/// @brief Compare two double precision floating point numbers.
/// @param a, b Numbers to compare.
/// @return
///     - @c true  : @c a and @c b are equal.
///     - @c false : @c a and @c b are NOT equal.
CB_DEF bool _F(double_cmp)( double a, double b );

/// @brief Set memory allocator for the current thread.
/// @param[in] alloc  Allocator alloc function.
/// @param[in] free   Allocator free function.
/// @param[in] params Allocator context params.
CB_DEF void  _F(mem_allocator_set)( _T(AllocFN)* alloc, _T(FreeFN)* free, void* params );
/// @brief Reset memory allocator to default allocator for the current thread.
CB_DEF void  _F(mem_allocator_reset)(void);
/// @brief Allocate memory using current thread's memory allocator.
/// @param size Number of bytes to allocate.
/// @return
///     - @c NULL : Failed to allocate @c size bytes.
///     - Pointer : Pointer to allocated memory.
CB_DEF void* _F(mem_alloc)( size_t size );
/// @brief Reallocate memory using current thread's memory allocator.
/// @param[in] ptr      (optional) Pointer to memory to reallocate.
/// @param     old_size (optional) Size of memory pointed to by @c ptr in bytes.
/// @param     new_size Size to reallocate to.
/// @return
///     - @c NULL : Failed to allocate @c size bytes.
///     - Pointer : Pointer to allocated memory.
CB_DEF void* _F(mem_realloc)( void* ptr, size_t old_size, size_t new_size );
/// @brief Free allocated memory using the current thread's memory allocator.
/// @param[in] ptr  Pointer to free.
/// @param     size Size of memory pointed to by @c ptr in bytes.
CB_DEF void  _F(mem_free)( void* ptr, size_t size );

/// @brief Compare two equally-sized memory ranges.
/// @param[in] a, b Pointers to memory to compare.
/// @param     size Size of memory ranges in bytes.
/// @return
///     - @c true  : Memory ranges are equal.
///     - @c false : Memory ranges are NOT equal.
CB_DEF bool  _F(mem_cmp)( const void* a, const void* b, size_t size );
/// @brief Copy memory from source to destination.
/// @param[in] dst  Pointer to destination memory buffer.
/// @param[in] src  Pointer to source memory buffer.
/// @param     size Size of memory buffers in bytes.
/// @return @c dst.
CB_DEF void* _F(mem_copy)( void* restrict dst, const void* restrict src, size_t size );
/// @brief Move memory from source to destination.
/// @param[in] dst  Pointer to destination memory buffer.
/// @param[in] src  Pointer to source memory buffer.
/// @param     size Size of memory buffers in bytes.
/// @return @c dst.
CB_DEF void* _F(mem_move)( void* dst, const void* src, size_t size );
/// @brief Set range of bytes to given value.
/// @param[in] buf  Pointer to start of range.
/// @param     byte Value to set bytes to.
/// @param     size Size of memory range in bytes.
/// @return @c buf.
CB_DEF void* _F(mem_set)( void* buf, uint8_t byte, size_t size );

/// @brief Get next local buffer.
/// @return Local byte buffer.
CB_DEF _T(ByteBuf)* _F(local_buf)(void);
/// @brief Allocate memory from next local buffer.
/// @param size Number of bytes to allocate.
/// @return Allocated memory. Does not need to be freed.
CB_DEF char* _F(local_alloc)( size_t size );
/// @brief Write a formatted string to local buffer.
/// @param[in] fmt Format string.
/// @param     va  Variadic format string arguments.
/// @return Pointer to a local buffer with formatted text. Always null-terminated.
CB_DEF const char* _F(local_fmt_va)( const char* fmt, va_list va ) CB_FMT(1, 0);
/// @brief Write a formatted string to local buffer.
/// @param[in] fmt Format string.
/// @param     ... Format string arguments.
/// @return Pointer to a local buffer with formatted text. Always null-terminated.
CB_DEF const char* _F(local_fmt)( const char* fmt, ... ) CB_FMT(1, 2);
/// @brief Convert a path string slice to null-terminated string.
/// @param string String to copy to a local buffer.
/// @return Pointer to a local buffer with contents from @c string. Always null-terminated.
CB_DEF const char* _F(local_path)( _T(String) string );

/// @brief Reverse an array's contents.
/// @param[in] base   Pointer to start of array.
/// @param     stride Size of each item in array in bytes.
/// @param     count  Number of items in array.
/// @param[in] swap   Pointer to a buffer with size of @c stride, used for swapping items.
CB_DEF void _F(array_reverse)( void* base, size_t stride, size_t count, char* swap );

/// @brief Calculate the byte length of a null-terminated string.
/// @param[in] string Null-terminated string.
/// @return Length of string in bytes. Does not include terminating null.
CB_DEF size_t _F(cstr_len)( const char* string );

/// @brief Check if given UTF-32 rune is within ASCII range.
/// @param rune Rune to check.
/// @return
///     - @c true  : Rune is within ASCII range.
///     - @c false : Rune is NOT within ASCII range.
CB_DEF bool       _F(rune_is_ascii)( _T(Rune32) rune );
/// @brief Convert UTF-8 code units to a UTF-32 rune.
/// @param cp8 UTF-8 code units.
/// @return UTF-32 rune.
CB_DEF _T(Rune32) _F(rune_from_cp8)( _T(CodeUnits8) cp8 );

/// @brief Create UTF-8 code unit array from code units.
/// @param c0, c1, c2, c3 Code units.
/// @return UTF-8 code unit array.
CB_DEF _T(CodeUnits8) _F(cp8_from_code_units)( uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3 );
/// @brief Get the first set of code units from string slice.
/// @param      string  String slice.
/// @param[out] out_cp8 Pointer to write code units to.
/// @return Number of code units in UTF-8 code unit array.
CB_DEF size_t         _F(cp8_from_string)( _T(String) string, _T(CodeUnits8)* out_cp8 );
/// @brief Convert UTF-16 code units to UTF-8 code units.
/// @param      cp16 UTF-16 code units.
/// @param[out] cp8  UTF-8 code units.
/// @return Number of UTF-8 code units.
CB_DEF size_t _F(cp8_from_cp16)( _T(CodeUnits16) cp16, _T(CodeUnits8)* out_cp8 );
/// @brief Convert UTF-32 rune to UTF-8 code units.
/// @param cp32 UTF-32 rune.
/// @param[out] cp8  UTF-8 code units.
/// @return Number of UTF-8 code units.
CB_DEF size_t _F(cp8_from_cp32)( _T(Rune32) cp32, _T(CodeUnits8)* out_cp8 );

/// @brief Create UTF-16 code unit array from code units.
/// @param c0, c1 Code units.
/// @return UTF-16 code unit array.
CB_DEF _T(CodeUnits16) _F(cp16_from_code_units)( uint16_t c0, uint16_t c1 );
/// @brief Get first set of code units from string slice.
/// @param      utf16_len Number of code units in string.
/// @param[in]  utf16_ptr Pointer to UTF-16 string.
/// @param[out] out_cp16  Pointer to write code units to.
/// @return Number of code units in UTF-16 code unit array.
CB_DEF size_t _F(cp16_from_string)(
    size_t utf16_len, uint16_t* utf16_ptr, _T(CodeUnits16)* out_cp16 );
/// @brief Convert UTF-8 code units to UTF-16 code units.
/// @param      cp8      UTF-8 code units.
/// @param[out] out_cp16 UTF-16 code units.
/// @return Number of code units in UTF-16 code unit array.
CB_DEF size_t _F(cp16_from_cp8)( _T(CodeUnits8) cp8, _T(CodeUnits16)* out_cp16 );
/// @brief Convert UTF-32 rune to UTF-16 code units.
/// @param      cp32     UTF-32 rune.
/// @param[out] out_cp16 UTF-16 code units.
/// @return Number of code units in UTF-16 code unit array.
CB_DEF size_t _F(cp16_from_cp32)( _T(Rune32) cp32, _T(CodeUnits16)* out_cp16 );

/// @brief Convert UTF-32 code units to UTF-32 rune.
/// @note This function only exists for parity with other cp*_from_code_units functions.
/// @param c0 Code units.
/// @return UTF-32 rune.
CB_DEF _T(Rune32) _F(cp32_from_code_units)( uint32_t c0 );
/// @brief Convert UTF-8 code units to UTF-32.
/// @param cp8 UTF-8 code units.
/// @return UTF-32 rune.
CB_DEF _T(Rune32) _F(cp32_from_cp8)( _T(CodeUnits8) cp8 );
/// @brief Convert UTF-16 code units to UTF-32.
/// @param cp16 UTF-16 code units.
/// @return UTF-32 rune.
CB_DEF _T(Rune32) _F(cp32_from_cp16)( _T(CodeUnits16) cp16 );

/// @brief Compare two string slices for equality.
/// @param a, b Strings to compare.
/// @return
///     - @c true  : Strings are equal in length and contents.
///     - @c false : Strings are not equal in length or contents.
CB_DEF bool _F(string_cmp)( _T(String) a, _T(String) b );

/// @brief Find UTF-32 rune in string slice.
/// @param      string      String to search within.
/// @param      c           Rune to search for.
/// @param[out] opt_out_pos (optional) Pointer to write byte position of found rune to.
/// @return
///     - @c true  : Rune @c c was found within @c string.
///     - @c false : Rune @c c was NOT found in @c string.
CB_DEF bool _F(string_find)( _T(String) string, _T(Rune32) c, size_t* opt_out_pos );
/// @brief Find set of UTF-32 runes in string slice.
/// @param      string      String to search within.
/// @param      set         Runes to search for.
/// @param[out] opt_out_pos (optional) Pointer to write byte position of found rune to.
/// @return
///     - @c true  : Rune set @c set was found within @c string.
///     - @c false : Rune set @c set was NOT found in @c string.
CB_DEF bool _F(string_find_set)( _T(String) string, _T(Rune32Set) set, size_t* opt_out_pos );
/// @brief Find sub-string in string slice.
/// @param      string      String to search within.
/// @param      phrase      Sub-string to search for.
/// @param[out] opt_out_pos (optional) Pointer to write byte position of start of sub-string to.
/// @return
///     - @c true  : Sub-string @c phrase was found within @c string.
///     - @c false : Sub-string @c phrase was NOT found in @c string.
CB_DEF bool _F(string_find_phrase)( _T(String) string, _T(String) phrase, size_t* opt_out_pos );

/// @brief Search for UTF-32 rune in string slice from end of string.
/// @param      string      String to search within.
/// @param      c           Rune to search for.
/// @param[out] opt_out_pos (optional) Pointer to write byte position of found rune to.
/// @return
///     - @c true  : Rune @c c was found within @c string.
///     - @c false : Rune @c c was NOT found in @c string.
CB_DEF bool _F(string_find_rev)( _T(String) string, _T(Rune32) c, size_t* opt_out_pos );
/// @brief Search for set of UTF-32 runes in string slice from end of string.
/// @param      string      String to search within.
/// @param      set         Runes to search for.
/// @param[out] opt_out_pos (optional) Pointer to write byte position of found rune to.
/// @return
///     - @c true  : Rune set @c set was found within @c string.
///     - @c false : Rune set @c set was NOT found in @c string.
CB_DEF bool _F(string_find_set_rev)( _T(String) string, _T(Rune32Set) set, size_t* opt_out_pos );
/// @brief Search for sub-string in string slice from end of string.
/// @param      string      String to search within.
/// @param      phrase      Sub-string to search for.
/// @param[out] opt_out_pos (optional) Pointer to write byte position of start of sub-string to.
/// @return
///     - @c true  : Sub-string @c phrase was found within @c string.
///     - @c false : Sub-string @c phrase was NOT found in @c string.
CB_DEF bool _F(string_find_phrase_rev)( _T(String) string, _T(String) phrase, size_t* opt_out_pos );

/// @brief Trim leading whitespace from string.
/// @param string String slice to trim.
/// @return Trimmed string slice.
CB_DEF _T(String) _F(string_trim_leading_ws)( _T(String) string );
/// @brief Trim trailing whitespace from string.
/// @param string String slice to trim.
/// @return Trimmed string slice.
CB_DEF _T(String) _F(string_trim_trailing_ws)( _T(String) string );
/// @brief Trim leading and trailing whitespace from string.
/// @param string String slice to trim.
/// @return Trimmed string slice.
CB_DEF _T(String) _F(string_trim_ws)( _T(String) string );

/// @brief Split string.
/// @param      string        String to split.
/// @param      pos           Byte position to split at.
/// @param[out] opt_out_left  (optional) Pointer to write left side of split.
/// @param[out] opt_out_right (optional) Pointer to write right side of split.
CB_DEF void _F(string_split)(
    _T(String)  string,
    size_t      pos,
    _T(String)* opt_out_left,
    _T(String)* opt_out_right );

/// @brief Calculate UTF-8 length of string.
/// @param string String to calculate length for.
/// @return Number of runes in string.
CB_DEF size_t     _F(string_utf8_len)( _T(String) string );
/// @brief Get next rune in string.
/// @param      string       String.
/// @param[out] opt_out_rune (optional) Pointer to write rune to.
/// @return String advanced past rune.
CB_DEF _T(String) _F(string_utf8_next)( _T(String) string, _T(Rune32)* opt_out_rune );
/// @brief Get rune at given index.
/// @param string String to index.
/// @param index  Index of rune.
/// @return Rune.
CB_DEF _T(Rune32) _F(string_utf8_index)( _T(String) string, size_t index );

/// @brief Write formatted string to end of string buffer.
/// @param[in] buf Pointer to string buffer to append to.
/// @param[in] fmt Format string.
/// @param[in] va  Variadic format string arguments.
/// @return Length of formatted string.
CB_DEF size_t _F(string_buf_fmt_va)( _T(StringBuf)* buf, const char* fmt, va_list va ) CB_FMT(2, 0);
/// @brief Write formatted string to end of string buffer.
/// @param[in] buf Pointer to string buffer to append to.
/// @param[in] fmt Format string.
/// @param     ... Format string arguments.
/// @return Length of formatted string.
CB_DEF size_t _F(string_buf_fmt)( _T(StringBuf)* buf, const char* fmt, ... ) CB_FMT(2, 3);

/// @brief Set logger level.
/// @param level Logger level.
/// @return Logger level.
CB_DEF _T(LogLevel) _F(logger_level_set)( _T(LogLevel) level );
/// @brief Check given level against current logger level.
/// @param level Logger level to check.
/// @return
///     - @c true  : Given level is allowed to be printed.
///     - @c false : Given level is NOT allowed to be printed.
CB_DEF bool         _F(logger_level_check)( _T(LogLevel) level );

/// @brief Print logger message.
/// @param     level Logger level of message.
/// @param[in] fmt   Format string.
/// @param[in] va    Variadic format string arguments.
/// @return Number of bytes printed.
CB_DEF size_t _F(logger_output_va)( _T(LogLevel) level, const char* fmt, va_list va ) CB_FMT(2, 0);
/// @brief Print logger message.
/// @param     level Logger level of message.
/// @param[in] fmt   Format string.
/// @param     ...   Format string arguments.
/// @return Number of bytes printed.
CB_DEF size_t _F(logger_output)( _T(LogLevel) level, const char* fmt, ... ) CB_FMT(2, 3);

/// @brief Get stdout file handle.
/// @return File handle.
CB_DEF _T(File)* _F(stdout_handle)(void);
/// @brief Get stderr file handle.
/// @return File handle.
CB_DEF _T(File)* _F(stderr_handle)(void);
/// @brief Get stdin file handle.
/// @return File handle.
CB_DEF _T(File)* _F(stdin_handle)(void);

/// @brief Check if something exists at given path.
/// @param[in] path Path to check.
/// @return
///     - @c true  : Something (file,directory,etc.) exists at given path.
///     - @c false : Path does not point to anything.
CB_INL bool         _F(path_exists)( const char* path );
/// @brief Query information for item at given path.
/// @param[in]  path     Path to query info for.
/// @param[out] out_info Pointer to write file info to.
/// @return
///     - @c true  : Path exists and info was queried successfully.
///     - @c false : Either path doesn't exist or failed to query info.
CB_DEF bool         _F(path_query_info)( const char* path, _T(FileInfo)* out_info );
/// @brief Query file type for item at given path.
/// @param[in] path Path to query.
/// @return File type.
CB_INL _T(FileType) _F(path_query_file_type)( const char* path );
/// @brief Query creation time for item at given path.
/// @param[in]  path     Path to query.
/// @param[out] out_time Pointer to write creation time to.
/// @return
///     - @c true  : Path exists and time was queried successfully.
///     - @c false : Either path doesn't exist or failed to query time.
CB_INL bool         _F(path_query_time_create)( const char* path, _T(Time)* out_time );
/// @brief Query last modified time for item at given path.
/// @param[in]  path     Path to query.
/// @param[out] out_time Pointer to write last modified time to.
/// @return
///     - @c true  : Path exists and time was queried successfully.
///     - @c false : Either path doesn't exist or failed to query time.
CB_INL bool         _F(path_query_time_modify)( const char* path, _T(Time)* out_time );
/// @brief Convert relative path to full path.
/// @warning
/// This function does not append NULL!
/// @param[in] buf  Pointer to string buffer to append full path to.
/// @param[in] path Relative path to convert.
/// @return Number of bytes written to buffer.
CB_DEF size_t       _F(path_canonicalize_buf)( _T(StringBuf)* buf, const char* path );
/// @brief Convert relative path to full path.
/// @param[in] path Relative path to convert.
/// @return Full path. Storage comes from a local buffer so this pointer does not need to be freed.
CB_INL const char*  _F(path_canonicalize)( const char* path );

/// @brief Get a null file handle.
/// @return Null file handle.
CB_INL _T(File)     _F(file_null)(void);
/// @brief Check if file handle is null.
/// @param[in] file Pointer to file handle.
/// @return
///     - @c true  : File handle is null.
///     - @c false : File handle is NOT null.
CB_INL bool         _F(file_is_null)( _T(File)* file );
/// @brief Open a file handle.
/// @param[in]  path     Path to open.
/// @param      flags    Flags to open file with.
/// @param[out] out_file Pointer to write file handle to.
/// @return
///     - @c true  : Successfully opened file at given path.
///     - @c false : Failed to open file.
CB_DEF bool         _F(file_open)( const char* path, _T(FileFlags) flags, _T(File)* out_file );
/// @brief Close file handle.
/// @param[in] file Pointer to file handle to close.
CB_DEF void         _F(file_close)( _T(File)* file );
/// @brief Remove file at given path.
/// @param[in] path Path to file to remove.
/// @return
///     - @c true  : Removed file successfully.
///     - @c false : Failed to remove file.
CB_DEF bool         _F(file_remove)( const char* path );
/// @brief Query info about a file.
/// @param[in] file Pointer to file handle.
/// @return File info.
CB_DEF _T(FileInfo) _F(file_query_info)( _T(File)* file );
/// @brief Query a file's type.
/// @param[in] file Pointer to file handle.
/// @return File type.
CB_INL _T(FileType) _F(file_query_type)( _T(File)* file );
/// @brief Query a file's creation time.
/// @param[in] file Pointer to file handle.
/// @return Time.
CB_INL _T(Time)     _F(file_query_time_create)( _T(File)* file );
/// @brief Query a file's last modification time.
/// @param[in] file Pointer to file handle.
/// @return Time.
CB_INL _T(Time)     _F(file_query_time_modify)( _T(File)* file );
/// @brief Query a file's size.
/// @param[in] file Pointer to file handle.
/// @return Size of file in bytes.
CB_INL size_t       _F(file_query_size)( _T(File)* file );
/// @brief Check if file at given path can be executed by current user.
/// @param[in] path Path to file to check.
/// @return
///     - @c true  : File can be executed.
///     - @c false : File can NOT be executed.
CB_DEF bool         _F(file_is_executable)( const char* path );
/// @brief Read data from file.
/// @param[in]  file Pointer to file handle to read from.
/// @param[out] dst  Pointer to memory to write to.
/// @param      size Size of memory pointed to by @c dst in bytes.
/// @return Number of bytes read from file.
CB_DEF size_t       _F(file_read)( _T(File)* file, void* dst, size_t size );
/// @brief Open and read entire existing file.
/// @param[in]  path Path to file to read.
/// @param[out] buf  Pointer to byte buffer to append file contents to.
/// @return Number of bytes read from file.
CB_INL size_t       _F(file_read_entire)( const char* path, _T(ByteBuf)* buf );
/// @brief Write data to file.
/// @param[in] file Pointer to file handle to write to.
/// @param[in] src  Pointer to memory buffer to write.
/// @param     size Size of memory pointed to by @c src in bytes.
/// @return Number of bytes written to file.
CB_DEF size_t       _F(file_write)( _T(File)* file, const void* src, size_t size );
/// @brief Copy a file from one path to another.
/// @param[in] dst            Path to copy contents to.
/// @param[in] src            Path to copy contents from.
/// @param     fail_if_exists If operation should fail if @c dst already exists.
/// @return
///     - @c true  : Successfully copied contents from @c src to @c dst.
///     - @c false : Failed to copy file.
CB_DEF bool         _F(file_copy)( const char* dst, const char* src, bool fail_if_exists );
/// @brief Move a file from one path to another.
/// @param[in] dst            Path to move contents to.
/// @param[in] src            Path to move contents from.
/// @param     fail_if_exists If operation should fail if @c dst already exists.
/// @return
///     - @c true  : Successfully moved contents from @c src to @c dst.
///     - @c false : Failed to move file.
CB_DEF bool         _F(file_move)( const char* dst, const char* src, bool fail_if_exists );
/// @brief Seek file.
/// @param[in] file   Pointer to file handle.
/// @param     offset Offset to seek.
/// @param     type   Seek type.
/// @return New file pointer from start of file.
CB_DEF intptr_t     _F(file_seek)( _T(File)* file, intptr_t offset, _T(FileSeek) type );
/// @brief Write formatted string to file.
/// @param[in] file Pointer to file handle.
/// @param[in] fmt  Formatted string.
/// @param[in] va   Variadic format string arguments.
/// @return Number of bytes written.
CB_DEF size_t       _F(file_write_fmt_va)( _T(File)* file, const char* fmt, va_list va ) CB_FMT(2, 0);
/// @brief Write formatted string to file.
/// @param[in] file Pointer to file handle.
/// @param[in] fmt  Formatted string.
/// @param     ...  Format string arguments.
/// @return Number of bytes written.
CB_DEF size_t       _F(file_write_fmt)( _T(File*) file, const char* fmt, ... ) CB_FMT(2, 3);
/// @brief Check which file is newer.
/// @param[in] path_a, path_b Paths to check.
/// @return
///     - @c  1: @c path_b is newer.
///     - @c  0: @c path_a is newer.
///     - @c -1: Failed to get @c path_a file time.
///     - @c -2: Failed to get @c path_b file time.
CB_DEF int          _F(file_which_is_newer)( const char* path_a, const char* path_b );
/// @brief Check if target is newer than its dependencies.
/// @param[in] path Target file path.
/// @param     len  Number of dependencies.
/// @param[in] deps Pointer to list of dependencies.
/// @return
///     - @c  1: One of the target's dependencies is newer.
///     - @c  0: Target is newer than dependencies.
///     - @c -1: Failed to get target file time.
///     - @c -2: Failed to get a dependency's file time.
CB_DEF int          _F(file_check_dependencies)( const char* path, size_t len, const char** deps );

/// @brief Create a directory.
/// @param[in] path                  Path of new directory.
/// @param     should_fail_if_exists If @c true, fails if @c path already exists.
/// @return
///     - @c true  : Successfully created directory or
///                    it already exists (if @c should_fail_if_exists is false).
///     - @c false : Failed to create directory or
///                    it already exists (if @c should_fail_if_exists is true).
CB_DEF bool   _F(dir_create)( const char* path, bool should_fail_if_exists );
/// @brief Remove a directory.
/// @param[in] path         Path to directory.
/// @param     is_recursive If a directory with items in it should be recursively removed.
/// @return
///     - @c true  : Successfully removed directory.
///     - @c false : Failed to remove directory.
///                    If @c is_recursive is false and directory is not empty, always fails.
CB_DEF bool   _F(dir_remove)( const char* path, bool is_recursive );
/// @brief Copy directory and its contents to new directory.
/// @param[in] dst Path to destination directory.
/// @param[in] src Path to source directory.
/// @return
///     - @c true  : Successfully copied contents of @c src to @c dst.
///     - @c false : Failed to copy contents of @c src to @c dst.
CB_DEF bool   _F(dir_copy)( const char* dst, const char* src );
/// @brief Move directory and its contents to new directory.
/// @param[in] dst Path to destination directory.
/// @param[in] src Path to source directory.
/// @return
///     - @c true  : Successfully moved contents of @c src to @c dst.
///     - @c false : Failed to move contents of @c src to @c dst.
CB_DEF bool   _F(dir_move)( const char* dst, const char* src );
/// @brief Walk through each item in directory.
/// @note Does not traverse directory in any particular order.
/// @param[in] path   Path to directory to walk.
/// @param[in] fn     Function to run for each item in directory.
/// @param[in] params (optional) Parameters for @c fn.
/// @return Number of items traversed.
CB_DEF size_t _F(dir_walk)( const char* path, _T(DirWalkFN)* fn, void* params );

/// @brief Query current working directory.
/// @warning Result is READ ONLY!
/// @return Current working directory. Does not need to be freed.
CB_DEF const char* _F(dir_cwd_query)(void);
/// @brief Set current working directory.
/// @param[in] cwd Path to new current working directory.
/// @return
///     - @c true  : Successfully set current working directory.
///     - @c false : Failed to set current working directory.
CB_DEF bool        _F(dir_cwd_set)( const char* cwd );

/// @brief Create a null pipe handle.
/// @return Null pipe handle.
CB_INL _T(Pipe) _F(pipe_null)(void);
/// @brief Check if pipe handle is null.
/// @param[in] pipe Pointer to pipe handle.
/// @return
///     - @c true  : Pipe handle is null.
///     - @c false : Pipe handle is NOT null.
CB_INL bool     _F(pipe_is_null)( _T(Pipe)* pipe );
/// @brief Open pipe.
/// @param[out] out_read  Pointer to store read side of pipe.
/// @param[out] out_write Pointer to store write side of pipe.
/// @return
///     - @c true  : Successfully opened pipe.
///     - @c false : Failed to open pipe.
CB_DEF bool     _F(pipe_open)( _T(Pipe)* out_read, _T(Pipe)* out_write );
/// @brief Close pipe.
/// @param[in] pipe Pointer to pipe to close.
CB_DEF void     _F(pipe_close)( _T(Pipe)* pipe );
/// @brief Wait for pipe to be filled with data.
/// @param[in] pipe      Pointer to pipe handle.
/// @param     wait_msec Number of milliseconds to wait or CB_WAIT_INF.
/// @return
///     - @c true  : Pipe has data and function returned before @c wait_msec.
///     - @c false : Timeout.
CB_DEF bool     _F(pipe_wait)( _T(Pipe)* pipe, uint32_t wait_msec );
/// @brief Query how many bytes of data pipe has.
/// @param[in] pipe Pointer to pipe handle.
/// @return Number of bytes in pipe ready to be read.
CB_DEF size_t   _F(pipe_query)( _T(Pipe)* pipe );

/// @brief Reset command buffer.
/// @param[in] cmd Pointer to command buffer.
CB_DEF void _F(cmd_reset)( _T(CmdBuf)* cmd );
/// @brief Add to command buffer.
/// @param[in] cmd Pointer to command buffer.
/// @param[in] arg Argument to add to end of buffer.
CB_DEF void _F(cmd_add)( _T(CmdBuf)* cmd, const char* arg );
/// @brief Copy a command to end of command buffer.
/// @param[in] cmd Pointer to command buffer.
/// @param     src Commands to copy.
CB_DEF void _F(cmd_copy)( _T(CmdBuf)* cmd, _T(Cmd) src );
/// @brief Free command buffer memory.
/// @param[in] cmd Pointer to command buffer to free.
CB_DEF void _F(cmd_free)( _T(CmdBuf)* cmd );
/// @brief Flatten command into a single string.
/// @param      cmd    Command to flatten.
/// @param[out] string Pointer to string buffer to append to.
CB_DEF void _F(cmd_flatten)( _T(Cmd) cmd, _T(StringBuf)* string );

/// @brief Add process to process group.
/// @param[in] group Pointer to process group.
/// @param[in] proc  Pointer to process handle.
CB_DEF void _F(proc_group_add)( _T(ProcessGroup)* group, _T(Process)* proc );
/// @brief Remove finished processes from process group.
/// @param[in] group Pointer to process group.
CB_DEF void _F(proc_group_clean)( _T(ProcessGroup)* group );
/// @brief Free process group memory.
/// @param[in] group Pointer to process group.
CB_DEF void _F(proc_group_free)( _T(ProcessGroup)* group );
/// @brief Wait for all remaining processes in process group.
/// @param[in] group     Pointer to process group.
/// @param     wait_msec Number of milliseconds to wait or CB_WAIT_INF.
/// @return
///     - @c true  : Joined all processes.
///     - @c false : Timeout.
CB_DEF bool _F(proc_group_join)( _T(ProcessGroup)* group, uint32_t wait_msec );

/// @brief Create null process handle.
/// @return Null process handle.
CB_INL _T(Process) _F(proc_null)(void);
/// @brief Check if process handle is null.
/// @param[in] proc Pointer to process handle.
/// @return
///     - @c true  : Process handle is null.
///     - @c false : Process handle is NOT null.
CB_INL bool        _F(proc_is_null)( _T(Process)* proc );
/// @brief Discard process handle.
/// @param[in] proc Pointer to process handle.
CB_DEF void        _F(proc_discard)( _T(Process)* proc );
/// @brief Wait for process to finish and then discard process handle.
/// @param[in] proc      Pointer to process handle.
/// @param     wait_msec Number of milliseconds to wait for process or CB_WAIT_INF.
/// @return
///     - @c 1-255 : Process finished within time, process was not successful.
///     - @c 0     : Process finished within time and was successful.
///     - @c -1    : Process exited abnormally within time.
///     - @c -2    : Timeout.
CB_DEF int         _F(proc_wait)( _T(Process)* proc, uint32_t wait_msec );
/// @brief Send signal to process.
/// @param[in] proc Pointer to process handle.
/// @param     sig  Signal to send.
/// @return
///     - @c true  : Signal sent successfully.
///     - @c false : Failed to send signal.
CB_DEF bool        _F(proc_signal)( _T(Process)* proc, _T(ProcessSignal) sig );
/// @brief Check if process exists in PATH or at given path.
/// @param[in] path Path of process.
/// @return
///     - @c true  : Process was found.
///     - @c false : Process was NOT found.
CB_DEF bool        _F(proc_exists)( const char* path );

/// @brief Query environment value.
/// @param[in] key Name of environment variable.
/// @return
///     - @c NULL : Could not find environment variable.
///     - Pointer : Environment value. Does not need to be freed.
CB_DEF const char* _F(env_query)( const char* key );
/// @brief Set environment value.
/// @param[in] key   Name of environment variable.
/// @param[in] value Value of environment variable.
/// @return
///     - @c true  : Successfully set environment variable.
///     - @c false : Failed to set environment variable.
CB_DEF bool        _F(env_set)( const char* key, const char* value );
/// @brief Copy current environment to environment block.
/// @param[out] out_env Pointer to copy environment to.
CB_DEF void        _F(env_copy)( _T(Env)* out_env );
/// @brief Reset environment block.
/// @param[in] env Pointer to environment block.
CB_DEF void        _F(env_reset)( _T(Env)* env );
/// @brief Add environment variable to environment block.
/// @param[in] env   Pointer to environment block.
/// @param[in] key   Name of environment variable.
/// @param[in] value Value of environment variable.
CB_DEF void        _F(env_add)( _T(Env)* env, const char* key, const char* value );
/// @brief Add all environment variables to environment block.
/// @param[in] dst Pointer to environment block to append to.
/// @param[in] src Pointer to environment block copy from.
CB_DEF void        _F(env_append)( _T(Env)* dst, _T(Env)* src );
/// @brief Get environment variable from environment block.
/// @param[in] env Pointer to environment block.
/// @param[in] key Name of environment variable.
/// @return Value of environment variable.
CB_DEF _T(String)  _F(env_get)( _T(Env)* env, const char* key );
/// @brief Remove environment variable from environment block.
/// @param[in] env Pointer to environment block.
/// @param[in] key Name of environment variable.
CB_DEF void        _F(env_remove)( _T(Env)* env, const char* key );
/// @brief Dereference offset string from environment block.
/// @param[in] env Pointer to environment block.
/// @param     so  Offset string.
/// @return String.
CB_DEF _T(String)  _F(env_deref)( _T(Env)* env, _T(StringOffset) so );
/// @brief Free environment block.
/// @param[in] env Pointer to environment block.
CB_DEF void        _F(env_free)( _T(Env)* env );

/// @brief Sleep current thread.
/// @param wait_msec Number of milliseconds to sleep for.
CB_DEF void _F(mt_sleep)( uint32_t wait_msec );
/// @brief Yield current thread to scheduler.
CB_DEF void _F(mt_yield)(void);
/// @brief Wait for atom.
/// @param[in] atom      Pointer to atom.
/// @param     sentinel  Value to wait for.
/// @param     wait_msec Number of milliseconds to wait for or CB_WAIT_INF.
/// @return
///     - @c true  : Atom changed to sentinel value.
///     - @c false : Timeout.
CB_DEF bool _F(mt_spinlock)( volatile int* atom, int sentinel, uint32_t wait_msec );
/// @brief Insert compiler and software multi-threaded barrier.
CB_DEF void _F(mt_barrier)(void);
/// @brief Add to atom.
/// @param[in] atom   Pointer to atom.
/// @param     addend Value to add to atom.
/// @return Previous value of atom.
CB_DEF int  _F(mt_add)( volatile int* atom, int addend );
/// @brief Increment atom.
/// @param[in] atom Pointer to atom.
/// @return Previous value of atom.
CB_INL int  _F(mt_incr)( volatile int* atom );
/// @brief Decrement atom.
/// @param[in] atom Pointer to atom.
/// @return Previous value of atom.
CB_INL int  _F(mt_decr)( volatile int* atom );
/// @brief Exchange value of atom.
/// @param[in] atom Pointer to atom.
/// @param     exch Value to exchange atom with.
/// @return Previous value of atom.
CB_DEF int  _F(mt_exch)( volatile int* atom, int exch );
/// @brief Compare atom to value and exchange if atom matches.
/// @param[in] atom Pointer to atom.
/// @param     cmp  Value to compare.
/// @param     exch Value to exchange.
/// @return Previous value of atom.
CB_DEF int  _F(mt_cmp_exch)( volatile int* atom, int cmp, int exch );

/// @brief Reset mutex.
/// @param[in] mtx Pointer to mutex.
CB_DEF void _F(mtx_reset)( _T(Mutex)* mtx );
/// @brief Wait for mutex lock.
/// @param[in] mtx       Pointer to mutex.
/// @param     wait_msec Number of milliseconds to wait for or CB_WAIT_INF.
/// @return
///     - @c true  : Mutex is locked.
///     - @c false : Timeout.
CB_DEF bool _F(mtx_lock)( _T(Mutex)* mtx, uint32_t wait_msec );
/// @brief Unlock mutex.
/// @param[in] mtx Pointer to mutex.
CB_DEF void _F(mtx_unlock)( _T(Mutex)* mtx );

/// @brief Initialize semaphore.
/// @param[in] sem       Pointer to semaphore.
/// @param[in] opt_value (optional) Value to initialize semaphore with.
CB_DEF void _F(semaphore_init)( _T(Semaphore)* sem, int* opt_value );
/// @brief Signal semaphore.
/// @param[in] sem Pointer to semaphore.
CB_DEF void _F(semaphore_signal)( _T(Semaphore)* sem );
/// @brief Wait for semaphore to be signaled.
/// @param[in] sem       Pointer to semaphore.
/// @param     wait_msec Number of milliseconds to wait or CB_WAIT_INF.
/// @return
///     - @c true  : Semaphore was signaled within time limit.
///     - @c false : Timeout.
CB_DEF bool _F(semaphore_wait)( _T(Semaphore)* sem, uint32_t wait_msec );

/// @brief Get current time.
/// @return Time.
CB_DEF _T(Time)      _F(time_now)(void);
/// @brief Time difference.
/// @param a, b Times to compare.
/// @return Difference.
CB_DEF double        _F(time_diff)( _T(Time) a, _T(Time) b );
/// @brief Get current milliseconds.
/// @return Milliseconds.
CB_DEF double        _F(time_msec)(void);
/// @brief Get current seconds.
/// @return Seconds.
CB_DEF double        _F(time_sec)(void);
/// @brief Create time split from time value.
/// @param Posix time.
/// @return Time split.
CB_DEF _T(TimeSplit) _F(time_split_from_time)( _T(Time) time );
/// @brief Create time from time split.
/// @param[in] ts Pointer to time split.
/// @return Time.
CB_DEF _T(Time)      _F(time_from_time_split)( _T(TimeSplit)* ts );

/// @brief Hash using elf hash.
/// @param     len   Number of bytes.
/// @param[in] bytes Pointer to bytes.
/// @return Hash value.
CB_DEF _T(Hash) _F(hash_elf)( size_t len, const void* bytes );
/// @brief Hash using murmur2 hash.
/// @param     len   Number of bytes.
/// @param[in] bytes Pointer to bytes.
/// @return Hash value.
CB_DEF _T(Hash) _F(hash_murmur2)( size_t len, const void* bytes );

/// @brief Set target for dependencies.
/// @param[in] deps   Pointer to dependencies list.
/// @param[in] target Target path.
CB_DEF void   _F(deps_set_target)( _T(Deps)* deps, const char* target );
/// @brief Add dependency to dependencies list.
/// @param[in] deps       Pointer to dependencies list.
/// @param[in] dependency Dependency path.
CB_DEF void   _F(deps_add)( _T(Deps)* deps, const char* dependency );
/// @brief Reset dependencies list.
/// @param[in] deps Pointer to dependencies list.
CB_DEF void   _F(deps_reset)( _T(Deps)* deps );
/// @brief Free dependencies list.
/// @param[in] deps Pointer to dependencies list.
CB_DEF void   _F(deps_free)( _T(Deps)* deps );
/// @brief Parse dependencies from makefile dependency file.
/// @param[in]  path               Path to dependency file.
/// @param[out] out_deps           Pointer to dependencies list.
/// @param      can_replace_target If true, replaces target name if it doesn't yet exist.
/// @return Number of dependencies in file.
CB_DEF size_t _F(deps_parse_makefile)(
    const char* path, _T(Deps)* out_deps, bool can_replace_target );

// NOTE(alicia): inline functions

CB_INL _T(File) _F(file_null)(void) {
#if CB_OS_CURRENT == CB_OS_WINDOWS
    return CB_STRUCT( _T(File), .opaque_ptr=NULL );
#else
    return CB_STRUCT( _T(File), .opaque_fd=-1 );
#endif
}

CB_INL bool _F(file_is_null)( _T(File)* file ) {
#if CB_OS_CURRENT == CB_OS_WINDOWS
    return file->opaque_ptr == NULL;
#else
    return file->opaque_fd == -1;
#endif
}

CB_INL _T(Pipe) _F(pipe_null)(void) {
#if CB_OS_CURRENT == CB_OS_WINDOWS
    return CB_STRUCT( _T(Pipe), .opaque_ptr=NULL );
#else
    return CB_STRUCT( _T(Pipe), .opaque_fd=-1 );
#endif
}

CB_INL bool _F(pipe_is_null)( _T(Pipe)* pipe ) {
#if CB_OS_CURRENT == CB_OS_WINDOWS
    return pipe->opaque_ptr == NULL;
#else
    return pipe->opaque_fd == -1;
#endif
}

CB_INL _T(Process) _F(proc_null)(void) {
#if CB_OS_CURRENT == CB_OS_WINDOWS
    return CB_STRUCT( _T(Process), .opaque_ptr=NULL );
#else
    return CB_STRUCT( _T(Process), .opaque_fd=-1 );
#endif
}

CB_INL bool _F(proc_is_null)( _T(Process)* p ) {
#if CB_OS_CURRENT == CB_OS_WINDOWS
    return p->opaque_ptr == NULL;
#else
    return p->opaque_fd == -1;
#endif
}

CB_INL _T(String) _F(string_from_log_level)( _T(LogLevel) level ) {
    switch( level ) {
        case _E(LOG_INFO  ): return CB_STRING("LOG_INFO");
        case _E(LOG_WARN  ): return CB_STRING("LOG_WARN");
        case _E(LOG_ERROR ): return CB_STRING("LOG_ERROR");
        case _E(LOG_FATAL ): return CB_STRING("LOG_FATAL");
        case _E(LOG_NONE  ): return CB_STRING("LOG_NONE");
        case _E(LOG_COUNT ): break;
    }
    return CB_STRING("LOG_UNKNOWN");
}
CB_INL bool _F(log_level_from_string)( _T(String) string, _T(LogLevel)* out_level ) {
    for( size_t i = 0; i < (size_t)_E(LOG_COUNT); ++i ) {
        _T(String) current = _F(string_from_log_level)( (_T(LogLevel))i );
        if( _F(string_cmp)( current, string ) ) {
            *out_level = (_T(LogLevel))i;
            return true;
        }
    }
    return false;
}
CB_INL _T(String) _F(string_from_file_seek)( _T(FileSeek) seek ) {
    switch( seek ) {
        case _E(FS_SET): return CB_STRING("SET");
        case _E(FS_CUR): return CB_STRING("CUR");
        case _E(FS_END): return CB_STRING("END");
    }
    return CB_STRING("UNKNOWN");
}
CB_INL bool _F(file_seek_from_string)( _T(String) string, _T(FileSeek)* out_seek ) {
    for( size_t i = 0; i < (size_t)_E(FS_END) + 1; ++i ) {
        _T(String) current = _F(string_from_file_seek)( (_T(FileSeek))i );
        if( _F(string_cmp)( current, string ) ) {
            *out_seek = (_T(FileSeek))i;
            return true;
        }
    }
    return false;
}
CB_INL _T(String) _F(string_from_file_type)( _T(FileType) type ) {
    switch( type ) {
        case _E(FT_NULL): return CB_STRING("null");
        case _E(FT_FILE): return CB_STRING("file");
        case _E(FT_DIR):  return CB_STRING("directory");
        case _E(FT_PIPE): return CB_STRING("pipe");
    }
    return CB_STRING("unknown");
}
CB_INL bool _F(file_type_from_string)( _T(String) string, _T(FileType)* out_type ) {
    for( size_t i = 0; i < (size_t)_E(FT_PIPE) + 1; ++i ) {
        _T(String) current = _F(string_from_file_type)( (_T(FileType))i );
        if( _F(string_cmp)( current, string ) ) {
            *out_type = (_T(FileType))i;
            return true;
        }
    }
    return false;
}
CB_INL _T(String) _F(string_from_dir_walk_action)( _T(DirWalkAction) action ) {
    switch( action ) {
        case _E(DWA_CONTINUE): return CB_STRING("CONTINUE");
        case _E(DWA_STOP):     return CB_STRING("STOP");
        case _E(DWA_SKIP):     return CB_STRING("SKIP");
    }
    return CB_STRING("UNKNOWN");
}
CB_INL bool _F(dir_walk_action_from_string)(
    _T(String) string, _T(DirWalkAction)* out_action
) {
    for( size_t i = 0; i < (size_t)_E(DWA_SKIP) + 1; ++i ) {
        _T(String) current = _F(string_from_dir_walk_action)( (_T(DirWalkAction))i );
        if( _F(string_cmp)( current, string ) ) {
            *out_action = (_T(DirWalkAction))i;
            return true;
        }
    }
    return false;
}
CB_INL _T(String) _F(string_from_process_signal)( _T(ProcessSignal) sig ) {
    switch( sig ) {
        case _E(PSIG_NULL):  return CB_STRING("null");
        case _E(PSIG_KILL):  return CB_STRING("kill");
        case _E(PSIG_COUNT): break; 
    }
    return CB_STRING("unknown");
}
CB_INL bool _F(process_signal_from_string)(
    _T(String) string, _T(ProcessSignal)* out_sig
) {
    for( size_t i = 0; i < (size_t)_E(PSIG_COUNT); ++i ) {
        _T(String) current = _F(string_from_process_signal)( (_T(ProcessSignal))i );
        if( _F(string_cmp)( current, string ) ) {
            *out_sig = (_T(ProcessSignal))i;
            return true;
        }
    }
    return false;
}

CB_INL bool _F(path_exists)( const char* path ) {
    return _F(path_query_file_type)( path ) != _E(FT_NULL);
}
CB_INL _T(FileType) _F(path_query_file_type)( const char* path ) {
    _T(FileInfo) info = {};
    if( _F(path_query_info)( path, &info ) ) {
        return info.type;
    }
    return _E(FT_NULL);
}
CB_INL bool _F(path_query_time_create)( const char* path, _T(Time)* out_time ) {
    _T(FileInfo) info = {};
    if( _F(path_query_info)( path, &info ) ) {
        *out_time = info.time_create;
        return true;
    }
    return false;
}
CB_INL bool _F(path_query_time_modify)( const char* path, _T(Time)* out_time ) {
    _T(FileInfo) info = {};
    if( _F(path_query_info)( path, &info ) ) {
        *out_time = info.time_modify;
        return true;
    }
    return false;
}

CB_INL const char* _F(path_canonicalize)( const char* path ) {
    _T(StringBuf)* l = _F(local_buf)(); 
    _F(path_canonicalize_buf)( l, path );
    CB_BUF_PUSH( l, 0 );
    return l->ptr;
}

CB_INL size_t _F(file_query_size)( _T(File)* file ) {
    size_t seek   = _F(file_seek)( file, 0, _E(FS_CUR) );
    size_t result = _F(file_seek)( file, 0, _E(FS_END) );
    _F(file_seek)( file, seek, _E(FS_SET) );

    return result;
}

CB_INL _T(FileType) _F(file_query_type)( _T(File)* file ) {
    _T(FileInfo) info = _F(file_query_info)( file );
    return info.type;
}
CB_INL _T(Time) _F(file_query_time_create)( _T(File)* file ) {
    _T(FileInfo) info = _F(file_query_info)( file );
    return info.time_create;
}
CB_INL _T(Time) _F(file_query_time_modify)( _T(File)* file ) {
    _T(FileInfo) info = _F(file_query_info)( file );
    return info.time_modify;
}

CB_INL size_t _F(file_read_entire)( const char* path, _T(ByteBuf)* buf ) {
    _T(File) fp;
    if( !_F(file_open)( path, _E(FF_READ), &fp ) ) {
        return 0;
    }

    size_t fsize = _F(file_query_size)( &fp );

    CB_BUF_RESERVE( buf, fsize );

    size_t read_size = _F(file_read)( &fp, buf->ptr + buf->len, fsize );
    buf->len += read_size;

    _F(file_close)( &fp );
    return read_size;
}

CB_INL int _F(mt_incr)( volatile int* atom ) {
    return _F(mt_add)( atom, 1 );
}
CB_INL int _F(mt_decr)( volatile int* atom ) {
    return _F(mt_add)( atom, -1 );
}

// NOTE(alicia): internal functions

CB_INL void __cb_unused( int v, ... ) { (void)v; }

CB_DEF bool __cb_dir_create_many( const char* first, ... );

CB_DEF void __cb_cmd_append( _T(CmdBuf)* cmd, ... );

CB_DEF int __cb_exec( _T(Cmd) cmd, __CbExecParams params );


#endif /* header guard */













// NOTE(alicia): implementation

#if defined(CB_IMPL) && !defined(__CB_IMPL__H__)
#define __CB_IMPL__H__
/**
 * @file   cb.h
 * @brief  C Build System implementation.
 * @author Alicia Amarilla (smushyaa@gmail.com)
 * @date   August 20, 2025
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#if CB_OS_CURRENT == CB_OS_WINDOWS
    #define CB_LOCAL_SIZE_BYTES (CB_LOCAL_SIZE * 2)
#else
    #define CB_LOCAL_SIZE_BYTES (CB_LOCAL_SIZE)
#endif

#define CB_LOCAL_PLATFORM_COUNT (2)

#define _T(x) CB_CONCAT2( CB_PREFIX_TYPE, x )
#define _F(x) CB_CONCAT2( CB_PREFIX_FUNC, x )

void* __cb_default_alloc( void* ptr, size_t old_size, size_t new_size, void* params );
void  __cb_default_free( void* ptr, size_t size, void* params );

#if CB_OS_IS_POSIX
#include <unistd.h>

struct __CbFtwState {
    _T(DirWalkFN)* fn;
    void*          params;
    int            skip_level;
    size_t         count;
};
#endif

CB_TLS
struct __CbState {
    _T(AllocFN)* alloc;
    _T(FreeFN)*  free;
    void*        alloc_params;

    _T(File) h_stdout, h_stderr, h_stdin;

    _T(StringBuf) local_buffer[CB_LOCAL_COUNT];
    uint32_t local_index;

    _T(StringBuf) platform_buf;

    bool cwd_set;
    _T(StringBuf) cwd;

    _T(LogLevel) level;

#if CB_OS_IS_POSIX
    struct __CbFtwState ftw;
#elif CB_OS_CURRENT == CB_OS_WINDOWS
    bool out_handles_obtained;
    bool setup_console;
#endif

} __CB_STATE__ = {
    .alloc                 = __cb_default_alloc,
    .free                  = __cb_default_free,
    .alloc_params          = NULL,
#if CB_OS_IS_POSIX
    .h_stdout              = CB_STRUCT(_T(File), .opaque_fd = STDOUT_FILENO),
    .h_stderr              = CB_STRUCT(_T(File), .opaque_fd = STDERR_FILENO),
    .h_stdin               = CB_STRUCT(_T(File), .opaque_fd = STDIN_FILENO),
#else
    .h_stdout              = CB_STRUCT(_T(File), .opaque_ptr = NULL),
    .h_stderr              = CB_STRUCT(_T(File), .opaque_ptr = NULL),
    .h_stdin               = CB_STRUCT(_T(File), .opaque_ptr = NULL),
    .out_handles_obtained  = false,
#endif
    .local_buffer          = {0},
    .local_index           = 0,
    .platform_buf          = {0},
    .cwd_set               = false,
    .cwd                   = {0},
    .level                 = _E(LOG_INFO),
#if CB_OS_IS_POSIX
    .ftw                   = {},
#elif CB_OS_CURRENT == CB_OS_WINDOWS
    .setup_console = false,
#endif
};

typedef _T(Handle) _T(Thread);

struct CB_JobState {
    bool       is_running;
    int        result;
    _T(JobFN)* fn;
    void*      params;
};

#define cbs  __CB_STATE__
#define cbjq __CB_JOB_QUEUE__


void* __cb_default_alloc( void* ptr, size_t old_size, size_t new_size, void* params ) {
    (void)params;

    if( ptr ) {
        void* result = realloc( ptr, new_size );
        if( !result ) {
            return NULL;
        }
        memset( (char*)result + old_size, 0, new_size - old_size );
        return result;
    } else {
        return calloc( 1, new_size );
    }
}
void __cb_default_free( void* ptr, size_t size, void* params ) {
    (void)params;
    if( !ptr ) {
        return;
    }
    free(ptr);
}

void _F(build_init)(
    const char*  path_exec,
    const char*  path_src,
    int          argc,
    const char** argv
) {
    _T(CmdLine) cl = CB_CL( argc, argv );
    cl = CB_CL_NEXT( &cl );

    if( !_F(path_exists)( __FILE__ ) ) {
        CB_PANIC(
            "build_init: %s not found! build system MUST be run from source code directory!",
            __FILE__ );
    }
    if( !_F(path_exists)( path_src ) ) {
        CB_PANIC(
            "build_init: %s not found! build system MUST be run from source code directory!",
            path_src );
    }

    bool should_rebuild =
        _F(file_check_dependencies)( path_exec, 2, (const char*[]){ path_src, __FILE__ } ) != 0;

    if( !should_rebuild ) {
        const char* old_name = _F(local_fmt)( "%s.old", path_exec );
        if( _F(path_exists)( old_name ) ) {
            _F(file_remove)( old_name );
        }

        return;
    }

    CB_INFO( CB_COLOR_CYAN "changes detected in build source, rebuilding . . ." CB_COLOR_RESET );
    _F(build_rebuild)( path_exec, path_src, cl.len, cl.ptr, NULL, true );
}
_Noreturn
void _F(build_rebuild)(
    const char*  path_exec,
    const char*  path_src,
    int          argc,
    const char** argv,
    _T(Cmd)*     opt_cmd,
    bool         should_reload
) {
    bool is_windows = false;
    bool is_msvc    = false;

#if CB_COMPILER_CURRENT == CB_COMPILER_UNKNOWN
    #if __cplusplus
        _T(String) compiler = CB_STRING("c++");
    #else
        _T(String) compiler = CB_STRING("cc");
    #endif
#elif CB_COMPILER_CURRENT == CB_COMPILER_GCC
    #if __cplusplus
        _T(String) compiler = CB_STRING("g++");
    #else
        _T(String) compiler = CB_STRING("gcc");
    #endif
#elif CB_COMPILER_CURRENT == CB_COMPILER_CLANG
    #if __cplusplus
        _T(String) compiler = CB_STRING("clang++");
    #else
        _T(String) compiler = CB_STRING("clang");
    #endif
#elif CB_COMPILER_CURRENT == CB_COMPILER_MSVC
    _T(String) compiler = CB_STRING("cl");
    is_msvc = true;
#endif

#if CB_OS_CURRENT == CB_OS_WINDOWS
    is_windows = true;
#endif

    double start = _F(time_msec)();

    _T(String) exec = CB_STRING_FROM_CSTR( path_exec );

    _T(CmdBuf)    cmd    = {};
    _T(StringBuf) string = {};

    if( opt_cmd ) {
        _F(cmd_copy)( &cmd, *opt_cmd );
    } else {
        CB_CMD_APPEND( &cmd, compiler.ptr, path_src );

        if( is_msvc ) {
            _F(string_buf_fmt)( &string, "/Fe%" CB_STRING_FMT, CB_STRING_ARG(&exec) );
            CB_BUF_PUSH( &string, 0 );

            CB_CMD_APPEND( &cmd, "/nologo", string.ptr );

            string.len = 0;
        } else {
            CB_CMD_APPEND( &cmd, "-o", exec.ptr );
        }
    }

    _F(cmd_add)( &cmd, "-DCB_BOOTSTRAPPED" );

    _F(cmd_flatten)( cmd.cmd, &string );
    CB_BUF_PUSH( &string, 0 );

    CB_INFO( CB_COLOR_CYAN "rebuilding with command: %s" CB_COLOR_RESET, string.ptr );
    string.len = 0;

    _F(string_buf_fmt)( &string, "%s.old", exec.ptr );
    CB_BUF_PUSH( &string, 0 );

    switch( _F(path_query_file_type)( string.ptr ) ) {
        case _E(FT_NULL): break;
        case _E(FT_FILE): {
            if( !_F(file_remove)( string.ptr ) ) {
                CB_PANIC( "build_rebuild: failed to remove %s!", string.ptr );
            }
        } break;
        case _E(FT_PIPE):
        case _E(FT_DIR): {
            CB_PANIC( "build_rebuild: %s is not a file!", string.ptr );
        } break;
    }

    if( !_F(file_move)( string.ptr, exec.ptr, false ) ) {
        CB_PANIC( "build_rebuild: failed to rename existing executable!" );
    }

    _T(Process) pid = _F(proc_null)();

    if( CB_EXEC( cmd.cmd, .proc=&pid ) != 0 ) {
        CB_PANIC( "build_rebuild: failed to rebuild!" );
    }

    int exit_code = _F(proc_wait)( &pid, CB_WAIT_INF );
    if( exit_code ) {
        if( !_F(file_move)( exec.ptr, string.ptr, false ) ) {
            CB_ERROR( "build_rebuild: failed to rename executable!" );
        }
        CB_PANIC( "build_rebuild: failed to rebuild!" );
    }

    string.len = 0;

    if( is_msvc ) {
        _F(string_buf_fmt)( &string, "%" CB_STRING_FMT, CB_STRING_ARG(&exec) );
        size_t dotpos = 0;
        if( _F(string_find_rev)( string.slice, '.', &dotpos ) ) {
            string.len = dotpos;
        }
        _F(string_buf_fmt)( &string, ".obj" );
        CB_BUF_PUSH( &string, 0 );

        if( _F(path_exists)( string.ptr ) ) {
            _F(file_remove)( string.ptr );
        }
    }

    double end = _F(time_msec)();
    CB_INFO( "build_rebuild: rebuilt in %fmsec", end - start );

    if( !should_reload ) {
        exit(0);
    }

    if( is_windows ) {
        CB_WARN( "build_rebuild: cannot reload program on windows! please run command again." );
        exit(0);
    }

    CB_INFO( CB_COLOR_CYAN "build_rebuild: reloading . . ." CB_COLOR_RESET );

    _F(cmd_reset)( &cmd );
    _F(cmd_add)( &cmd, exec.ptr );
    for( int i = 0; i < argc; ++i ) {
        _F(cmd_add)( &cmd, argv[i] );
    }

    exit_code = 0;
    if( (exit_code = CB_EXEC( cmd.cmd )) < 0 ) {
        CB_PANIC( "build_rebuild: failed to reload!" );
    }

    exit( exit_code );
}

bool _F(float_cmp)( float a, float b ) {
    float diff = a - b;
    if( diff < 0.0f ) {
        diff = -diff;
    }
    return diff < CB_FLT_EPSILON;
}
bool _F(double_cmp)( double a, double b ) {
    double diff = a - b;
    if( diff < 0.0 ) {
        diff = -diff;
    }
    return diff < CB_DBL_EPSILON;
}

void  _F(mem_allocator_set)( _T(AllocFN)* alloc, _T(FreeFN)* free, void* params ) {
    cbs.alloc        = alloc;
    cbs.free         = free;
    cbs.alloc_params = params;
}
void  _F(mem_allocator_reset)(void) {
    _F(mem_allocator_set)( __cb_default_alloc, __cb_default_free, NULL );
}
void* _F(mem_alloc)( size_t size ) {
    return cbs.alloc( NULL, 0, size, cbs.alloc_params );
}
void* _F(mem_realloc)( void* ptr, size_t old_size, size_t new_size ) {
    return cbs.alloc( ptr, old_size, new_size, cbs.alloc_params );
}
void  _F(mem_free)( void* ptr, size_t size ) {
    cbs.free( ptr, size, cbs.alloc_params );
}

bool _F(mem_cmp)( const void* a, const void* b, size_t size ) {
    return memcmp( a, b, size ) == 0;
}
void* _F(mem_copy)( void* restrict dst, const void* restrict src, size_t size ) {
    return memcpy( dst, src, size );
}
void* _F(mem_move)( void* dst, const void* src, size_t size ) {
    return memmove( dst, src, size );
}
void* _F(mem_set)( void* buf, uint8_t byte, size_t size ) {
    return memset( buf, byte, size );
}

_T(ByteBuf) * _F(local_buf)(void) {
    uint32_t index = (cbs.local_index++) % CB_LOCAL_COUNT;

    _T(ByteBuf) * result = cbs.local_buffer + index;

    if( result->ptr ) {
        _F(mem_set)( result->ptr, 0, result->len );
    }
    result->len = 0;

    return result;
}
char* _F(local_alloc)( size_t size ) {
    _T(ByteBuf)* buf = _F(local_buf)();

    CB_BUF_RESERVE( buf, size );

    return buf->ptr;
}
const char* _F(local_fmt_va)( const char* fmt, va_list va ) {
    va_list va2;
    va_copy( va2, va );

    size_t required = vsnprintf( NULL, 0, fmt, va2 );

    va_end( va2 );

    char* ptr = _F(local_alloc)( required );

    vsnprintf( ptr, required, fmt, va );

    return ptr;
}
const char* _F(local_fmt)( const char* fmt, ... ) {
    va_list va;

    va_start( va, fmt );
    const char* result = _F(local_fmt_va)( fmt, va );
    va_end( va );

    return result;
}
const char* _F(local_path)( _T(String) string ) {
    char* result = _F(local_alloc)( string.len + 1 );

    return _F(mem_copy)( result, string.ptr, string.len );
}

void _F(array_reverse)( void* base, size_t stride, size_t count, char* swap ) {
    for( size_t i = 0; i < (count / 2); ++i ) {
        size_t offset0 = i * stride;
        size_t offset1 = (count - 1 - i) * stride;

        _F(mem_copy)( swap, (char*)base + offset0, stride );

        _F(mem_copy)( (char*)base + offset0, (char*)base + offset1, stride );
        _F(mem_copy)( (char*)base + offset1, swap, stride );
    }
}

size_t _F(cstr_len)( const char* string ) {
    return (size_t)strlen( string );
}

bool _F(rune_is_ascii)( _T(Rune32) rune ) {
    return rune <= 0x7f;
}
_T(Rune32) _F(rune_from_cp8)( _T(CodeUnits8) cp8 ) {
    _T(Rune32) result;

    if( cp8.cp[0] < 0x80 ) {

        result = cp8.cp[0];
        
    } else if( (cp8.cp[0] & 0xE0) == 0xC0 ) {


        result = cp8.cp[0] & 0x1F;
        result = (result << 6) | (cp8.cp[1] & 0x3F);

    } else if( (cp8.cp[0] & 0xF0) == 0xE0 ) {

        result = cp8.cp[0] & 0x0F;
        result = (result << 6) | (cp8.cp[1] & 0x3F);
        result = (result << 6) | (cp8.cp[2] & 0x3F);

    } else if( (cp8.cp[0] & 0xF8) ) {

        result = cp8.cp[0] & 0x07;
        result = (result << 6) | (cp8.cp[1] & 0x37);
        result = (result << 6) | (cp8.cp[2] & 0x37);
        result = (result << 6) | (cp8.cp[3] & 0x37);

    } else {

        result = CB_CP32_REPLACEMENT_CHARACTER;

    }
    return result;
}

_T(CodeUnits8) _F(cp8_from_code_units)( uint8_t c0, uint8_t c1, uint8_t c2, uint8_t c3 ) {
    _T(CodeUnits8) result;
    result.cp[0] = c0;
    result.cp[1] = c1;
    result.cp[2] = c2;
    result.cp[3] = c3;
    return result;
}
size_t _F(cp8_from_string)( _T(String) string, _T(CodeUnits8)* out_cp8 ) {
    if( !string.len ) {
        return 0;
    }

    const uint8_t* uc = (const uint8_t*)string.ptr;

    if( !(uc[0] & ~0x7F) ) {
        *out_cp8 = _F(cp8_from_code_units)( uc[0], 0, 0, 0 );
        return 1;
    } else if( (uc[0] & 0xE0) == 0xC0 ) {
        if( string.len >= 2 ) {
            *out_cp8 = _F(cp8_from_code_units)( uc[0], uc[1], 0, 0 );
            return 2;
        } else {
            goto error;
        }
    } else if( (uc[0] & 0xF0) == 0xE0 ) {
        if( string.len >= 3 ) {
            *out_cp8 = _F(cp8_from_code_units)( uc[0], uc[1], uc[2], 0 );
            return 3;
        } else {
            goto error;
        }
    } else if( (uc[0] & 0xF8) == 0xF0 ) {
        if( string.len >= 4 ) {
            *out_cp8 = _F(cp8_from_code_units)( uc[0], uc[1], uc[2], uc[3] );
            return 4;
        } else {
            goto error;
        }
    }

error:
    *out_cp8 = CB_CP8_REPLACEMENT_CHARACTER;
    return 1;
}
size_t _F(cp8_from_cp16)( _T(CodeUnits16) cp16, _T(CodeUnits8)* out_cp8 ) {
    _T(Rune32) rune = _F(cp32_from_cp16)( cp16 );
    return _F(cp8_from_cp32)( rune, out_cp8 );
}
size_t _F(cp8_from_cp32)( _T(Rune32) cp32, _T(CodeUnits8)* out_cp8 ) {
    if( cp32 <= 0x007F ) {
        *out_cp8 = _F(cp8_from_code_units)( (uint8_t)cp32, 0, 0, 0 );
        return 1;
    } else if( cp32 <= 0x07FF ) {
        *out_cp8 = _F(cp8_from_code_units)(
            ((cp32 >> 6) & 0x1F) | 0xC0, 
            ((cp32     ) & 0x3F) | 0x80,
            0, 0 );
        return 2;
    } else if( cp32 <= 0xFFFF ) {
        *out_cp8 = _F(cp8_from_code_units)(
            ((cp32 >> 12) & 0x0F) | 0xE0,
            ((cp32 >>  6) & 0x3F) | 0x80,
            ((cp32      ) & 0x3F) | 0x80,
            0 );
        return 3;
    } else if( cp32 <= 0x10FFFF ) {
        *out_cp8 = _F(cp8_from_code_units)(
            ((cp32 >> 18) & 0x07) | 0xF0,
            ((cp32 >> 12) & 0x3F) | 0x80,
            ((cp32 >>  6) & 0x3F) | 0x80,
            ((cp32      ) & 0x3F) | 0x80 );
        return 4;
    } else {
        *out_cp8 = CB_CP8_REPLACEMENT_CHARACTER;
        return 3;
    }

    return 1;
}

_T(CodeUnits16) _F(cp16_from_code_units)( uint16_t c0, uint16_t c1 ) {
    _T(CodeUnits16) result;
    result.cp[0] = c0;
    result.cp[1] = c1;
    return result;
}
size_t _F(cp16_from_string)( size_t utf16_len, uint16_t* utf16_ptr, _T(CodeUnits16)* out_cp16 ) {
    if( !utf16_len ) {
        return 0;
    }

    if( utf16_ptr[0] <= 0xD7FF ) {
        *out_cp16 = _F(cp16_from_code_units)( utf16_ptr[0], 0 );
        return 1;
    } else if( utf16_ptr[0] <= 0xDBFF ) {
        if( utf16_len >= 2 ) {
            *out_cp16 = _F(cp16_from_code_units)( utf16_ptr[0], utf16_ptr[1] );
            return 2;
        } else {
            goto error;
        }
    }

error:
    *out_cp16 = CB_CP16_REPLACEMENT_CHARACTER;
    return 1;
}
size_t _F(cp16_from_cp8)( _T(CodeUnits8) cp8, _T(CodeUnits16)* out_cp16 ) {
    _T(Rune32) rune = _F(cp32_from_cp8)( cp8 );
    return _F(cp16_from_cp32)( rune, out_cp16 );
}
size_t _F(cp16_from_cp32)( _T(Rune32) cp32, _T(CodeUnits16)* out_cp16 ) {
    if( cp32 <= 0xFFFF ) {
        if( cp32 >= 0xD800 && cp32 <= 0xDFFF ) {
            *out_cp16 = CB_CP16_REPLACEMENT_CHARACTER;
        } else {
            out_cp16->cp[0] = cp32;
        }
        return 1;
    } else if( cp32 <= 0x10FFFF ) {
        uint32_t value = cp32 - 0x10000;

        out_cp16->cp[0] = (uint16_t)((value >>    10) + 0xD800);
        out_cp16->cp[1] = (uint16_t)((value  & 0x3FF) + 0xDC00);
        return 2;
    } else {
        *out_cp16 = CB_CP16_REPLACEMENT_CHARACTER;
        return 1;
    }

    return 0;
}

_T(Rune32) _F(cp32_from_code_units)( uint32_t c0 ) {
    return c0;
}
_T(Rune32) _F(cp32_from_cp8)( _T(CodeUnits8) cp8 ) {
    _T(Rune32) result = 0;

    if( cp8.cp[0] < 0x80 ) {
        result = cp8.cp[0];
    } else if( (cp8.cp[0] & 0xE0) == 0xC0 ) {
        result = cp8.cp[0] & 0x1F;
        result = (result << 6) | (cp8.cp[1] & 0x3F);
    } else if( (cp8.cp[0] & 0xF0) == 0xE0 ) {
        result = cp8.cp[0] & 0x0F;
        result = (result << 6) | (cp8.cp[1] & 0x3F);
        result = (result << 6) | (cp8.cp[2] & 0x3F);
    } else if( (cp8.cp[0] & 0xF8) ) {
        result = cp8.cp[0] & 0x07;
        result = (result << 6) | (cp8.cp[1] & 0x37);
        result = (result << 6) | (cp8.cp[2] & 0x37);
        result = (result << 6) | (cp8.cp[3] & 0x37);
    } else {
        result = CB_CP32_REPLACEMENT_CHARACTER;
    }

    return result;
}
_T(Rune32) _F(cp32_from_cp16)( _T(CodeUnits16) cp16 ) {
    _T(Rune32) result;

    if( cp16.cp[0] <= 0xD7FF ) {
        result = cp16.cp[0];
    } else if( cp16.cp[0] <= 0xDBFF ) {
        uint16_t hi = ( cp16.cp[0] - 0xD800 ) * 0x400;
        uint16_t lo = ( cp16.cp[1] - 0xDC00 );

        result = (lo | hi) + 0x10000;
    } else {
        result = CB_CP32_REPLACEMENT_CHARACTER;
    }

    return result;
}

bool _F(string_cmp)( _T(String) a, _T(String) b ) {
    if( a.len != b.len ) {
        return false;
    }
    return _F(mem_cmp)( a.ptr, b.ptr, a.len );
}

bool __cb_find_ascii( _T(String) string, char c, size_t* opt_out_pos ) {
    CB_FOREACH( &string, {
        if( *v == c ) {
            if( opt_out_pos ) {
                *opt_out_pos = i;
            }
            return true;
        }
    }, v, i );
    
    return false;
}

bool _F(string_find)( _T(String) string, _T(Rune32) c, size_t* opt_out_pos ) {
    if( _F(rune_is_ascii)( c ) ) {
        return __cb_find_ascii( string, c, opt_out_pos );
    }

    _T(String) remaining, substr;
    remaining = substr = string;

    _T(Rune32) at = 0;

    while( (remaining = _F(string_utf8_next)( substr, &at )).len ) {
        if( c == at ) {
            if( opt_out_pos ) {
                *opt_out_pos = (size_t)substr.ptr - (size_t)string.ptr;
            }
            return true;
        }
        substr = remaining;
    }

    return false;
}

bool __cb_find_set_ascii( _T(String) string, _T(Rune32Set) set, size_t* opt_out_pos ) {
    for( size_t i = 0; i < string.len; ++i ) {
        char c = string.ptr[i];
        for( size_t j = 0; j < set.len; ++j ) {
            if( c == set.ptr[j] ) {
                if( opt_out_pos ) {
                    *opt_out_pos = i;
                }
                return true;
            }
        }
    }
    return false;
}

bool _F(string_find_set)( _T(String) string, _T(Rune32Set) set, size_t* opt_out_pos ) {
    bool is_ascii = true;
    for( size_t i = 0; i < set.len; ++i ) {
        if( !_F(rune_is_ascii)( set.ptr[i] ) ) {
            is_ascii = false;
            break;
        }
    }
    if( is_ascii ) {
        return __cb_find_set_ascii( string, set, opt_out_pos );
    }

    _T(String) remaining, substr;
    remaining = substr = string;

    _T(Rune32) at = 0;

    while( (remaining = _F(string_utf8_next)( substr, &at )).len ) {
        for( size_t i = 0; i < set.len; ++i ) {
            _T(Rune32) c = set.ptr[i];

            if( c == at ) {
                if( opt_out_pos ) {
                    *opt_out_pos = (size_t)substr.ptr - (size_t)string.ptr;
                }
                return true;
            }
        }
        substr = remaining;
    }

    return false;
}
bool _F(string_find_phrase)( _T(String) string, _T(String) phrase, size_t* opt_out_pos ) {
    _T(String) substr = string;
    _T(Rune32) first  = _F(string_utf8_index)( phrase, 0 );
    while( substr.len ) {
        size_t pos = 0;
        if( !_F(string_find)( substr, first, &pos ) ) {
            return false;
        }

        substr = CB_SLICE_ADVANCE( &substr, pos );

        if( substr.len < phrase.len ) {
            return false;
        }

        _T(String) cmp = substr;
        cmp.len = phrase.len;

        substr = CB_SLICE_ADVANCE( &substr );

        if( _F(string_cmp)( cmp, phrase ) ) {
            if( opt_out_pos ) {
                *opt_out_pos = (size_t)cmp.ptr - (size_t)string.ptr;
                return true;
            }
        }
    }

    return false;
}

bool _F(string_find_rev)( _T(String) string, _T(Rune32) c, size_t* opt_out_pos ) {
    // TODO(alicia): UTF-8

    for( size_t i = string.len; i-- > 0; ) {
        if( string.ptr[i] == c ) {
            if( opt_out_pos ) {
                *opt_out_pos = i;
            }
            return true;
        }
    }

    return false;
}
bool _F(string_find_set_rev)( _T(String) string, _T(Rune32Set) set, size_t* opt_out_pos ) {
    // TODO(alicia): UTF-8

    for( size_t i = string.len; i-- > 0; ) {
        for( size_t j = 0; j < set.len; ++j ) {
            char c = set.ptr[j];

            if( string.ptr[i] == c ) {
                if( opt_out_pos ) {
                    *opt_out_pos = i;
                }
                return true;
            }
        }
    }

    return false;
}
bool _F(string_find_phrase_rev)( _T(String) string, _T(String) phrase, size_t* opt_out_pos ) {
    for( size_t i = string.len; i-- > 0; ) {
        _T(String) part;
        part.ptr = string.ptr + i;
        part.len = string.len - i;

        if( part.len >= phrase.len && part.ptr[0] == phrase.ptr[0] ) {
            part.len = phrase.len;

            if( _F(string_cmp)( part, phrase ) ) {
                if( opt_out_pos ) {
                    *opt_out_pos = i;
                }
                return true;
            }
        }
    }

    return false;
}

#define CB_WHITESPACE_SET { ' ', '\t', '\n', '\r' }

_T(String) _F(string_trim_leading_ws)( _T(String) string ) {
    const char ws[] = CB_WHITESPACE_SET;

    size_t offset = 0;
    for( size_t i = 0; i < string.len; ++i ) {
        for( size_t j = 0; j < CB_ARRAY_LEN(ws); ++j ) {
            if( string.ptr[i] != ws[j] ) {
                return CB_SLICE_ADVANCE( &string, i );
            }
        }
    }
    return CB_SLICE_ADVANCE( &string, string.len );
}
_T(String) _F(string_trim_trailing_ws)( _T(String) string ) {
    const char ws[] = CB_WHITESPACE_SET;

    size_t offset = 0;
    for( size_t i = string.len; i-- > 0; ) {
        for( size_t j = 0; j < CB_ARRAY_LEN(ws); ++j ) {
            if( string.ptr[i] != ws[j] ) {
                _T(String) result = string;
                result.len = i + 1;
                return result;
            }
        }
    }

    _T(String) result = string;
    result.len = 0;
    return result;
}
_T(String) _F(string_trim_ws)( _T(String) string ) {
    return _F(string_trim_leading_ws)( _F(string_trim_trailing_ws)( string ) );
}

#undef CB_WHITESPACE_SET

void _F(string_split)(
    _T(String)  string,
    size_t      pos,
    _T(String)* opt_out_left,
    _T(String)* opt_out_right
) {
    if( opt_out_left ) {
        opt_out_left->ptr = string.ptr;
        opt_out_left->len = pos;
    }
    if( opt_out_right ) {
        opt_out_right->ptr = string.ptr + pos;
        opt_out_right->len = string.len - pos;
    }
}

size_t _F(string_utf8_len)( _T(String) string ) {
    size_t res = 0;
    for( size_t i = 0; i < string.len; ++i ) {
        uint8_t byte = ((uint8_t*)string.ptr)[i];
        if( (byte & 0xC0) != 0x80 ) {
            res++;
        }
    }
    return res;
}
_T(String) _F(string_utf8_next)( _T(String) string, _T(Rune32)* opt_out_rune ) {
    _T(CodeUnits8) cp8 = {};

    size_t advance = _F(cp8_from_string)( string, &cp8 );

    if( opt_out_rune ) {
        *opt_out_rune = _F(rune_from_cp8)( cp8 );
    }
    return CB_SLICE_ADVANCE( &string, advance );
}
_T(Rune32) _F(string_utf8_index)( _T(String) string, size_t index ) {
    size_t counter     = 0;
    size_t byte_offset = 0;
    for( ; byte_offset < string.len; ++byte_offset ) {
        if( counter == index ) {
            break;
        }
        uint8_t byte = *(((uint8_t*)string.ptr) + byte_offset);
        if( (byte & 0xC0) != 0x80 ) {
            counter++;
        }
    }

    _T(CodeUnits8) cp8 = {};
    _F(cp8_from_string)( CB_SLICE_ADVANCE( &string, byte_offset ), &cp8 );
    return _F(rune_from_cp8)( cp8 );
}

size_t _F(string_buf_fmt_va)( _T(StringBuf)* buf, const char* fmt, va_list va ) {
    va_list va2;
    va_copy( va2, va );

    size_t len = (size_t)vsnprintf( NULL, 0, fmt, va2 );

    va_end( va2 );

    CB_BUF_RESERVE( buf, len + 1 );

    size_t result = (size_t)vsnprintf( buf->ptr + buf->len, buf->cap - buf->len, fmt, va );

    buf->len += result;
    return result;
}
size_t _F(string_buf_fmt)( _T(StringBuf)* buf, const char* fmt, ... ) {
    va_list va;
    va_start( va, fmt );
    size_t result = _F(string_buf_fmt_va)( buf, fmt, va );
    va_end( va );
    return result;
}

_T(LogLevel) _F(logger_level_set)( _T(LogLevel) level ) {
    return cbs.level = level;
}
bool _F(logger_level_check)( _T(LogLevel) level ) {
    return (cbs.level < _E(LOG_NONE)) && level >= cbs.level;
}

size_t _F(logger_output_va)( _T(LogLevel) level, const char* fmt, va_list va ) {
    if( !_F(logger_level_check( level )) ) {
        return 0;
    }

    _T(File)*   file  = _F(stdout_handle)();
    const char* color = CB_COLOR_RESET;

    switch( level ) {
        case _E(LOG_COUNT):
        case _E(LOG_NONE):
        case _E(LOG_INFO): {
        } break;
        case _E(LOG_WARN): {
            color = CB_COLOR_YELLOW;
        } break;
        case _E(LOG_ERROR): {
            file  = _F(stderr_handle)();
            color = CB_COLOR_RED;
        } break;
        case _E(LOG_FATAL): {
            file  = _F(stderr_handle)();
            color = CB_COLOR_MAGENTA;
        } break;
    }

    size_t result = 0;
    result += _F(file_write_fmt)( file, "%s", color );
    result += _F(file_write_fmt_va)( file, fmt, va );
    result += _F(file_write_fmt)( file, CB_COLOR_RESET );

    return result;
}
size_t _F(logger_output)( _T(LogLevel) level, const char* fmt, ... ) {
    va_list va;
    va_start( va, fmt );
    size_t result = _F(logger_output_va)( level, fmt, va );
    va_end( va );
    return result;
}

void __cb_platform_get_handles(void);

_T(File)* _F(stdout_handle)(void) {
    __cb_platform_get_handles();
    return &cbs.h_stdout;
}
_T(File)* _F(stderr_handle)(void) {
    __cb_platform_get_handles();
    return &cbs.h_stderr;
}
_T(File)* _F(stdin_handle)(void) {
    __cb_platform_get_handles();
    return &cbs.h_stdin;
}

bool _F(file_copy)( const char* dst, const char* src, bool fail_if_exists ) {
    _T(FileType) ft     = _F(path_query_file_type)( dst );
    bool         exists = ft != _E(FT_NULL);

    if( fail_if_exists && exists ) {
        CB_ERROR(
            "file_copy: file '%s' already exists! type: %s",
            dst, _F(string_from_file_type)(ft).ptr );
        return false;
    }

    char temp[1024] = {};

    _T(File) dstf, srcf;
    _T(FileFlags) dst_flags, src_flags;
    dst_flags = _E(FF_WRITE);
    src_flags = _E(FF_READ);

    if( exists ) {
        dst_flags |= _E(FF_TRUNCATE);
    } else {
        dst_flags |= _E(FF_CREATE);
    }
    if( _F(file_is_executable)( dst ) ) {
        dst_flags |= _E(FF_EXECUTE);
    }

    if( !_F(file_open)( dst, dst_flags, &dstf ) ) {
        return false;
    }
    if( !_F(file_open)( src, src_flags, &srcf ) ) {
        _F(file_close)( &dstf );
        return false;
    }

    size_t rem = _F(file_query_size)( &srcf );
    while( rem ) {
        size_t read_size = rem;
        if( read_size > sizeof(temp) ) {
            read_size = sizeof(temp);
        }

        _F(file_read)( &srcf, temp, read_size );
        _F(file_write)( &dstf, temp, read_size );

        rem -= read_size;
    }

    _F(file_close)( &srcf );
    _F(file_close)( &dstf );
    return true;
}
bool _F(file_move)( const char* dst, const char* src, bool fail_if_exists ) {
    if( !_F(file_copy)( dst, src, fail_if_exists ) ) {
        return false;
    }

    _F(file_remove)( src );
    return true;
}
size_t _F(file_write_fmt)( _T(File*) file, const char* fmt, ... ) {
    va_list va;
    va_start( va, fmt );
    size_t res = _F(file_write_fmt_va)( file, fmt, va );
    va_end( va );
    return res;
}
int _F(file_which_is_newer)( const char* path_a, const char* path_b ) {
    _T(Time) time_a, time_b;

    if( !_F(path_query_time_create)( path_a, &time_a ) ) {
        return -1;
    }
    if( !_F(path_query_time_create)( path_b, &time_b ) ) {
        return -2;
    }

    return _F(time_diff)( time_a, time_b ) < 0.0;
}
int _F(file_check_dependencies)( const char* path, size_t len, const char** deps ) {
    _T(Time) t;
    
    if( !_F(path_query_time_create)( path, &t ) ) {
        return -1;
    }

    for( size_t i = 0; i < len; ++i ) {
        _T(Time) other;

        if( !_F(path_query_time_create)( deps[i], &other ) ) {
            int result = (int)i;
            return -(result + 2);
        }

        double diff = _F(time_diff)( t, other );
        if( diff < 0.0 ) {
            return i + 1;
        } else if( diff > 0.0 ) {
            continue;
        } else {
            continue;
        }
    }

    return 0;
}

struct __CbDirRemoveRecursiveFiles {
    bool is_successful;
};

_T(DirWalkAction) __cb_dir_remove_recursive_files(
    const char* path, _T(DirWalkInfo)* info, void* params
) {
    struct __CbDirRemoveRecursiveFiles* p = (struct __CbDirRemoveRecursiveFiles*)params;
    if( info->file_type == _E(FT_FILE) ) {
        if( !_F(file_remove)( path ) ) {
            p->is_successful = false;
            return _E(DWA_STOP);
        }
    } else {

        if( !_F(dir_remove)( path, true ) ) {
            return _E(DWA_STOP);
        }

        return _E(DWA_SKIP);
    }
    return _E(DWA_CONTINUE);
}
bool __cb_dir_remove_recursive( const char* path ) {
    struct __CbDirRemoveRecursiveFiles p = {};
    p.is_successful = true;

    _F(dir_walk)( path, __cb_dir_remove_recursive_files, &p );

    if( !p.is_successful ) {
        return false;
    }

    return _F(dir_remove)( path, false );
}

struct __CbDirCopyState {
    _T(StringBuf) string;
    size_t        base_len;
    bool          is_successful;
};

_T(DirWalkAction) __cb_dir_copy( const char* path, _T(DirWalkInfo)* info, void* params ) {
    struct __CbDirCopyState* state = (struct __CbDirCopyState*)params;

    _T(String) p;
    p.ptr = (char*)path;
    p.len = info->path_len;

    CB_BUF_APPEND( &state->string, p.ptr, p.len + 1 );

    if( info->file_type == _E(FT_FILE) ) {
        state->is_successful = _F(file_copy)( state->string.ptr, path, true );
    } else if( info->file_type == _E(FT_DIR) ) {
        state->is_successful = _F(dir_create)( state->string.ptr, true );
    }

    state->string.len = state->base_len;

    if( !state->is_successful ) {
        return _E(DWA_STOP);
    }

    return _E(DWA_CONTINUE);
}

bool _F(dir_copy)( const char* dst, const char* src ) {
    struct __CbDirCopyState state = {};

    _T(String) dst_path = CB_STRING_FROM_CSTR( dst );

    if( !_F(dir_create)( dst, true ) ) {
        return false;
    }

    CB_BUF_APPEND( &state.string, dst_path.ptr, dst_path.len );
    CB_BUF_PUSH( &state.string, '/' );

    state.base_len = state.string.len;

    _F(dir_walk)( src, __cb_dir_copy, &state );

    CB_BUF_FREE( &state.string );

    return state.is_successful;
}

bool _F(dir_move)( const char* dst, const char* src ) {
    if( !_F(dir_copy)( dst, src ) ) {
        return false;
    }

    return _F(dir_remove)( src, true );
}

void _F(cmd_reset)( _T(CmdBuf)* cmd ) {
    cmd->len        = 0;
    cmd->string.len = 0;
}
void _F(cmd_add)( _T(CmdBuf)* cmd, const char* arg ) {
    const char* ptr = NULL;
    if( arg ) {
        size_t arglen = _F(cstr_len)( arg );
        size_t rem    = (cmd->string.cap - cmd->string.len);
        if( rem < (arglen + 1) ) {
            for( size_t i = 0; i < cmd->len; ++i ) {
                size_t offset = (size_t)cmd->ptr[i] - (size_t)cmd->string.ptr;

                cmd->ptr[i] = (const char*)offset;
            }

            size_t old_size = cmd->string.cap;
            size_t new_size = cmd->string.cap + ((arglen + 1) - rem) + 16;

            cmd->string.ptr = _F(mem_realloc)( cmd->string.ptr, old_size, new_size );
            cmd->string.cap = new_size;

            for( size_t i = 0; i < cmd->len; ++i ) {
                size_t offset = (size_t)cmd->ptr[i];

                cmd->ptr[i] = cmd->string.ptr + offset;
            }
        }

        ptr = cmd->string.ptr + cmd->string.len;
        _F(mem_copy)( cmd->string.ptr + cmd->string.len, arg, arglen + 1 );
        cmd->string.len += arglen + 1;
    }

    if( (cmd->cap - cmd->len) < 2 ) {
        CB_BUF_RESERVE( cmd, 8 );
    }
    cmd->ptr[cmd->len++] = ptr;
    cmd->ptr[cmd->len]   = NULL;
}
void _F(cmd_copy)( _T(CmdBuf)* cmd, _T(Cmd) src ) {
    for( size_t i = 0; i < src.len; ++i ) {
        _F(cmd_add)( cmd, src.ptr[i] );
    }
}
void _F(cmd_free)( _T(CmdBuf)* cmd ) {
    CB_BUF_FREE( &cmd->string );
    CB_BUF_FREE( cmd );
}
void _F(cmd_flatten)( _T(Cmd) cmd, _T(StringBuf)* string ) {
    for( size_t i = 0; i < cmd.len; ++i ) {
        if( !cmd.ptr[i] ) {
            break;
        }

        _T(String) arg = CB_STRING_FROM_CSTR( cmd.ptr[i] );
        arg = _F(string_trim_ws)( arg );

        if( !arg.len ) {
            continue;
        }

        if(
            arg.ptr[0] == '"' &&
            arg.ptr[arg.len - 1] == '"'
        ) {
            arg = CB_SLICE_ADVANCE( &arg );
            if( arg.len ) {
                arg.len--;
            }
        }

        if( !arg.len ) {
            continue;
        }

        CB_BUF_APPEND( string, arg.ptr, arg.len );
        if( (i + 1) != cmd.len ) {
            CB_BUF_PUSH( string, ' ' );
        }
    }
}

void _F(proc_group_add)( _T(ProcessGroup)* group, _T(Process)* proc ) {
    _T(ProcessData) pd = {};
    pd.handle    = *proc;
    pd.exit_code = -2;

    for( size_t i = 0; i < group->len; ++i ) {
        if( _F(mem_cmp)( &group->ptr[i].handle, &pd.handle, sizeof(pd.handle)) ) {
            return;
        }
    }

    CB_BUF_PUSH( group, pd );
}
void _F(proc_group_clean)( _T(ProcessGroup)* group ) {
    for( size_t i = 0; i < group->len; ++i ) {
        if( group->ptr[i].exit_code >= -1 ) {
            CB_BUF_REMOVE_SWAP( group, i );
            i--;
        }
    }
}
void _F(proc_group_free)( _T(ProcessGroup)* group ) {
    CB_BUF_FREE( group );
}
bool __cb_proc_group_join_inf( _T(ProcessGroup)* group ) {
    for( ;; ) {
        size_t complete_count = 0;

        for( size_t i = 0; i < group->len; ++i ) {
            _T(ProcessData)* pd = group->ptr + i;

            if( pd->exit_code >= -1 ) {
                complete_count++;
                continue;
            }

            pd->exit_code = _F(proc_wait)( &pd->handle, CB_WAIT_INF );

            complete_count++;
        }

        if( complete_count >= group->len ) {
            break;
        }

        _F(mt_yield)();
    }

    return true;
}
bool _F(proc_group_join)( _T(ProcessGroup)* group, uint32_t wait_msec ) {
    if( wait_msec == CB_WAIT_INF ) {
        return __cb_proc_group_join_inf( group );
    }

    double start = _F(time_msec)();

    for( ;; ) {
        size_t complete_count = 0;

        for( size_t i = 0; i < group->len; ++i ) {
            _T(ProcessData)* pd = group->ptr + i;

            if( pd->exit_code >= -1 ) {
                complete_count++;
                continue;
            }

            int wait_result = _F(proc_wait)( &pd->handle, 0 );

            if( wait_result >= -1 ) {
                pd->exit_code = wait_result;
            } else {
                return false;
            }
        }

        if( complete_count >= group->len ) {
            break;
        }

        double elapsed = _F(time_msec)() - start;
        if( (uint32_t)elapsed >= wait_msec ) {
            return false;
        }

        _F(mt_yield)();
    }

    return true;
}


void _F(env_append)( _T(Env)* dst, _T(Env)* src ) {
    for( size_t i = 0; i < src->len; ++i ) {
        _T(String) key, value;
        key   = _F(env_deref)( src, src->ptr[i].key );
        value = _F(env_deref)( src, src->ptr[i].value );
        _F(env_add)( dst, key.ptr, value.ptr );
    }
}
void _F(env_reset)( _T(Env)* env ) {
    env->len        = 0;
    env->string.len = 0;
}
_T(StringOffset) __cb_env_new_string( _T(Env)* env, _T(String) src ) {
    _T(StringOffset) result;
    result.len = src.len;

    CB_BUF_RESERVE( &env->string, src.len );

    result.offset = env->string.len;
    CB_BUF_APPEND( &env->string, src.ptr, src.len + 1 );

    return result;
}
void __cb_env_set( _T(Env)* env, size_t index, _T(String) value ) {
    env->ptr[index].value = __cb_env_new_string( env, value );
}
void __cb_env_add( _T(Env)* env, _T(String) key, _T(String) value ) {
    _T(EnvKV) kv = {};
    kv.key   = __cb_env_new_string( env, key );
    kv.value = __cb_env_new_string( env, value );

    CB_BUF_PUSH( env, kv );
}
void _F(env_add)( _T(Env)* env, const char* key_cc, const char* value_cc ) {
    _T(String) key, value;
    key.len = _F(cstr_len)( key_cc );
    key.ptr = (char*)key_cc;

    value.len = _F(cstr_len)( value_cc );
    value.ptr = (char*)value_cc;

    bool   key_found = false;
    size_t key_index = 0;
    for( size_t i = 0; i < env->len; ++i ) {
        _T(String) current = _F(env_deref)( env, env->ptr[i].key );

        if( _F(string_cmp)( key, current ) ) {
            key_found = true;
            key_index = i;
            break;
        }
    }

    if( key_found ) {
        __cb_env_set( env, key_index, value );
    } else {
        __cb_env_add( env, key, value );
    }
}
_T(String) _F(env_get)( _T(Env)* env, const char* key ) {
    _T(String) skey;
    skey.len = _F(cstr_len)( key );
    skey.ptr = (char*)key;

    _T(String) result = {};
    CB_FOREACH( env, {
        _T(String) current = _F(env_deref)( env, kv->key );

        if( _F(string_cmp)( current, skey ) ) {
            result = _F(env_deref)( env, kv->value );
            break;
        }
    }, kv );

    return result;
}
void _F(env_remove)( _T(Env)* env, const char* key ) {
    _T(String) string;
    string.len = _F(cstr_len)( key );
    string.ptr = (char*)key;

    for( size_t i = 0; i < env->len; ++i ) {
        _T(String) current = _F(env_deref)( env, env->ptr[i].key );

        if( _F(string_cmp)( string, current ) ) {
            env->len--;
            if( env->len ) {
                env->ptr[i] = env->ptr[env->len];
            }

            break;
        }
    }
}
_T(String) _F(env_deref)( _T(Env)* env, _T(StringOffset) so ) {
    _T(String) result;
    result.len = so.len;
    result.ptr = env->string.ptr + so.offset;
    return result;
}
void _F(env_free)( _T(Env)* env ) {
    CB_BUF_FREE( &env->string );
    CB_BUF_FREE( env );
    // NOTE(alicia): CB_BUF_FREE will set all fields to zero
}

void _F(mtx_reset)( _T(Mutex)* mtx ) {
    _F(mt_exch)( &mtx->atom, 0 );
}
bool _F(mtx_lock)( _T(Mutex)* mtx, uint32_t wait_msec ) {
    if( !_F(mt_spinlock)( &mtx->atom, 0, wait_msec ) ) {
        return false;
    }

    _F(mt_exch)( &mtx->atom, 1 );
    return true;
}
void _F(mtx_unlock)( _T(Mutex)* mtx ) {
    _F(mt_exch)( &mtx->atom, 0 );
}

void __cb_spinlock( volatile int* atom, int sentinel ) {
    for( ;; ) {
        _F(mt_cmp_exch)( atom, sentinel, sentinel );
        if( *atom == sentinel ) {
            break;
        }

        _F(mt_barrier)();
        _F(mt_yield)();
    }
}
bool _F(mt_spinlock)( volatile int* atom, int sentinel, uint32_t wait_msec ) {
    if( wait_msec == CB_WAIT_INF ) {
        __cb_spinlock( atom, sentinel );
        return true;
    }

    double start = _F(time_msec)();
    for( ;; ) {
        double current = _F(time_msec)();
        double elapsed = current - start;
        if( elapsed >= (double)wait_msec ) {
            return false;
        }

        _F(mt_barrier)();

        _F(mt_cmp_exch)( atom, sentinel, sentinel );
        if( *atom == sentinel ) {
            break;
        }

        _F(mt_barrier)();
        _F(mt_yield)();
    }

    return true;
}

void _F(semaphore_init)( _T(Semaphore)* sem, int* opt_value ) {
    if( opt_value ) {
        sem->atom = *opt_value;
    } else {
        sem->atom = 0;
    }
    _F(mtx_reset)( &sem->mtx );
}
void _F(semaphore_signal)( _T(Semaphore)* sem ) {
    _F(mtx_lock)( &sem->mtx, CB_WAIT_INF );
    _F(mt_incr)( &sem->atom );
    _F(mtx_unlock)( &sem->mtx );
}
void __cb_semaphore_wait( _T(Semaphore)* sem ) {
    // NOTE(alicia): no mt_yield because mtx_lock already has one
    for( ;; ) {
        _F(mtx_lock)( &sem->mtx, CB_WAIT_INF );
        if( sem->atom > 0 ) {
            _F(mt_decr)( &sem->atom );
            _F(mtx_unlock)( &sem->mtx );
            return;
        }
        _F(mtx_unlock)( &sem->mtx );
    }
}
bool _F(semaphore_wait)( _T(Semaphore)* sem, uint32_t wait_msec ) {
    if( wait_msec == CB_WAIT_INF ) {
        __cb_semaphore_wait( sem );
        return true;
    }

    // NOTE(alicia): no mt_yield because mtx_lock already has one

    double   start = _F(time_msec)();
    uint32_t rem   = wait_msec;
    for( ;; ) {
        if( !_F(mtx_lock)( &sem->mtx, rem ) ) {
            return false;
        }

        if( sem->atom > 0 ) {
            _F(mt_decr)( &sem->atom );
            _F(mtx_unlock)( &sem->mtx );
            return true;
        }

        _F(mtx_unlock)( &sem->mtx );
        double current = _F(time_msec)();
        double elapsed = current - start;

        if( (uint32_t)elapsed > wait_msec ) {
            return false;
        }

        rem -= (uint32_t)elapsed;
    }
}

double _F(time_diff)( _T(Time) a, _T(Time) b ) {
    return difftime( a, b );
}
_T(Time) _F(time_from_time_split)( _T(TimeSplit)* ts ) {
    struct tm tm;
    tm.tm_year = ts->year  - 1900;
    tm.tm_mon  = ts->month - 1;
    tm.tm_mday = ts->day;
    tm.tm_hour = ts->hour;
    tm.tm_min  = ts->minute;
    tm.tm_sec  = ts->second;

    return mktime( &tm );
}

_T(Hash) _F(hash_elf)( size_t len, const void* bytes ) {
    _T(Hash) result = {};
    uint32_t hi, lo;
    hi = lo = 0;

    for( size_t i = 0; i < len; ++i ) {
        uint32_t carry = (lo >> 28) & 0xF;
        lo = (lo << 4) + ((uint8_t*)bytes)[i];
        hi = (hi << 4) | carry;

        uint32_t x = hi & 0xF0000000u;
        if( x ) {
            hi ^= x >> 24;
        }
        hi &= ~x;
    }

    result.lo = lo;
    result.hi = hi;

    return result;
}
_T(Hash) _F(hash_murmur2)( size_t len, const void* bytes ) {
    // TODO(alicia): convert to use only uint32_t to maintain compat with 32-bit?

    #define M           0xc6a4a7935bd1e995
    #define R           47
    #define SEED        0xA13F346234624
    #define FALLTHROUGH __attribute__((fallthrough))

    uint64_t h = SEED ^ ( len * M );

    const uint64_t* data = (const uint64_t*)bytes;
    const uint64_t* end  = data + (len / sizeof(uint64_t));

    while( data != end ) {
        uint64_t k = *data++;

        k *= M;
        k ^= k >> R;
        k *= M;

        h ^= k;
        h *= M;
    }

    const uint8_t* data2 = (const uint8_t*)data;

    switch( len & 7 ) {
        case 7: h ^= (uint64_t)(data2[6]) << 48;
            FALLTHROUGH;
        case 6: h ^= (uint64_t)(data2[5]) << 40;
            FALLTHROUGH;
        case 5: h ^= (uint64_t)(data2[4]) << 32;
            FALLTHROUGH;
        case 4: h ^= (uint64_t)(data2[3]) << 24;
            FALLTHROUGH;
        case 3: h ^= (uint64_t)(data2[2]) << 16;
            FALLTHROUGH;
        case 2: h ^= (uint64_t)(data2[1]) << 8;
            FALLTHROUGH;
        case 1: h ^= (uint64_t)(data2[0]);
            h *= M;
            break;
    }

    h ^= h >> R;
    h *= M;
    h ^= h >> R;

    #undef SEED
    #undef M
    #undef R
    #undef FALLTHROUGH

    _T(Hash) hash;
    hash.lo = h & 0xFFFFFFFF;
    hash.hi = h >> 32;

    return hash;
}

size_t __cb_deps_add_string( _T(Deps)* deps, const char* cstr ) {
    _T(String) string = CB_STRING_FROM_CSTR( cstr );

    if( (deps->string.cap - deps->string.len) < (string.len + 1) ) {
        bool   has_target    = deps->target != NULL;
        size_t target_offset = 0;
        if( has_target ) {
            target_offset = (size_t)deps->target - (size_t)deps->string.ptr;
        }

        for( size_t i = 0; i < deps->len; ++i ) {
            deps->ptr[i] = (const char*)( (size_t)deps->ptr[i] - (size_t)deps->string.ptr );
        }

        CB_BUF_RESERVE( &deps->string, string.len + 16 );

        for( size_t i = 0; i < deps->len; ++i ) {
            deps->ptr[i] = deps->string.ptr + (size_t)deps->ptr[i];
        }

        if( has_target ) {
            deps->target = deps->string.ptr + target_offset;
        }
    }

    size_t result = deps->string.len;

    CB_BUF_APPEND( &deps->string, string.ptr, string.len + 1 );

    return result;
}
void _F(deps_set_target)( _T(Deps)* deps, const char* target ) {
    size_t offset = __cb_deps_add_string( deps, target );
    deps->target  = deps->string.ptr + offset;
}
void _F(deps_add)( _T(Deps)* deps, const char* dependency ) {
    size_t offset = __cb_deps_add_string( deps, dependency );
    const char* ptr = deps->string.ptr + offset;
    CB_BUF_PUSH( deps, ptr );
}
void _F(deps_reset)( _T(Deps)* deps ) {
    deps->len        = 0;
    deps->string.len = 0;
    deps->target     = NULL;
}
void _F(deps_free)( _T(Deps)* deps ) {
    CB_BUF_FREE( &deps->string );
    CB_BUF_FREE( deps );
    deps->target = NULL;
}
size_t _F(deps_parse_makefile)( const char* path, _T(Deps)* deps, bool can_replace_target ) {
    _T(StringBuf) depfile = {};
    if( !_F(file_read_entire)( path, &depfile ) ) {
        return 0;
    }

    _T(String) contents, target, dependencies;

    contents = depfile.slice;

    size_t dep_count = 0;

    size_t colon = 0;
    if( !_F(string_find)( contents, ':', &colon ) ) {
        goto end;
    }

    _F(string_split)( contents, colon, &target, &dependencies );

    dependencies = CB_SLICE_ADVANCE( &dependencies );

    if( !deps->target || can_replace_target ) {
        _F(deps_set_target)( deps, _F(local_fmt)( "%" CB_STRING_FMT, CB_STRING_ARG(&target) ) );
    }

    while( dependencies.len ) {
        _T(String) dep = dependencies;

        _T(Rune32Set) set = CB_RUNE_SET( ' ', '\\', '\n' );

        size_t end_of_path = 0;
        if( _F(string_find_set)( dep, set, &end_of_path ) ) {
            dep.len = end_of_path;
        }

        dependencies = CB_SLICE_ADVANCE( &dependencies, dep.len + 1 );

        dep = _F(string_trim_ws)( dep );

        if( dep.len ) {
            _F(deps_add)( deps, _F(local_fmt)( "%" CB_STRING_FMT, CB_STRING_ARG(&dep) ) );
            dep_count++;
        }
    }

end:
    CB_BUF_FREE( &depfile );
    return dep_count;
}

bool __cb_dir_create_many( const char* first, ... ) {
    bool result = true;

    va_list va;
    va_start( va, first );

    const char* arg = first;
    while( arg ) {
        _T(FileType) ft = _F(path_query_file_type)( arg );
        switch( ft ) {
            case _E(FT_NULL): {
                CB_INFO( "creating '%s' . . .", arg );
                if( !_F(dir_create)( arg, false ) ) {
                    CB_ERROR( "failed to create '%s'", arg );
                    result = false;
                    goto early_return;
                }
            } break;
            case _E(FT_DIR): {
                CB_INFO( "dir '%s' exists", arg );
            } break;
            case _E(FT_FILE):
            case _E(FT_PIPE): {
                CB_ERROR( "'%s' already exists as a file!", arg );
                result = false;
            } break;
        }

        arg = va_arg( va, const char* );
    }

early_return:
    va_end( va );

    return result;
}
void __cb_cmd_append( _T(CmdBuf)* cmd, ... ) {
    va_list va;
    va_start( va, cmd );

    const char* arg = NULL;

    for( ;; ) {
        arg = va_arg( va, const char* );
        if( !arg ) {
            break;
        }

        _F(cmd_add)( cmd, arg );
    }

    va_end( va );
}

// NOTE(alicia): Posix implementation -----------------------------------------

#if CB_OS_IS_POSIX

#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <ftw.h>
#include <poll.h>

_T(FileType) __cb_file_type_from_stat( const struct stat* st ) {
    if( S_ISREG( st->st_mode ) ) {
        return _E(FT_FILE);
    } else if( S_ISDIR( st->st_mode ) ) {
        return _E(FT_DIR);
    } else {
        return _E(FT_NULL);
    }
}

void __cb_platform_get_handles(void) {
    // NOTE(alicia): POSIX handles are always available.
}

double __cb_msec_from_timespec( struct timespec* ts ) {
    double result = 0.0;
    result += (double)ts->tv_nsec / 1000000.0;
    result += (double)ts->tv_sec * 1000.0;
    return result;
}
void __cb_timespec_from_msec( uint32_t msec, struct timespec* out_timespec ) {
    out_timespec->tv_sec  = msec / 1000;
    out_timespec->tv_nsec = (msec % 1000) * 1000000;
}
void __cb_timespec_from_msec_abs( uint32_t msec, struct timespec* out_timespec ) {
    struct timespec ts;
    _F(mem_set)( &ts, 0, sizeof(ts) );
    __cb_timespec_from_msec( msec, &ts );

    struct timespec current;
    clock_gettime( CLOCK_REALTIME, &current );

    ts.tv_nsec += current.tv_nsec;
    ts.tv_sec  += current.tv_sec;
    if( ts.tv_nsec >= 999999999 ) {
        ts.tv_sec++;
        ts.tv_nsec -= 999999999;
    }
    *out_timespec = ts;
}

bool _F(path_query_info)( const char* path, _T(FileInfo)* out_info ) {
    _T(FileInfo) fi = {};
    fi.type = _E(FT_NULL);

    struct stat st;
    if( stat( path, &st ) ) {
        *out_info = fi;
        return false;
    }

    fi.size        = st.st_size;
    fi.time_modify = st.st_ctime;
    fi.time_create = st.st_mtime;
    fi.type        = __cb_file_type_from_stat( &st );

    *out_info = fi;

    return true;
}
size_t _F(path_canonicalize_buf)( _T(StringBuf)* buf, const char* path ) {
    char*  allocated = realpath( path, NULL );
    size_t len       = _F(cstr_len)( allocated );

    size_t start_len = buf->len;

    CB_BUF_APPEND( buf, allocated, len );

    free(allocated);
    return buf->len - start_len;
}

bool _F(file_open)( const char* path, _T(FileFlags) flags, _T(File)* out_file ) {
    int    oflag = 0;
    mode_t mode  = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    // mode_t mode  = S_IRWXU;
    if( ( flags & (_E(FF_READ) | _E(FF_WRITE)) ) == (_E(FF_READ) | _E(FF_WRITE)) ) {
        oflag = O_RDWR;
    } else if( ( flags & (_E(FF_READ)) ) == (_E(FF_READ)) ) {
        oflag = O_RDONLY;
    } else if( ( flags & (_E(FF_WRITE)) ) == (_E(FF_WRITE)) ) {
        oflag = O_WRONLY;
    }

    if( ( flags & (_E(FF_APPEND)) ) == (_E(FF_APPEND)) ) {
        oflag |= O_APPEND;
    }

    if( ( flags & (_E(FF_CREATE)) ) == (_E(FF_CREATE)) ) {
        oflag |= O_CREAT | O_EXCL;

        if( (flags & (_E(FF_EXECUTE))) == (_E(FF_EXECUTE)) ) {
            mode |= S_IXUSR;
        }
    }
    if( ( flags & (_E(FF_TRUNCATE)) ) == (_E(FF_TRUNCATE)) ) {
        oflag |= O_TRUNC;
    }

    int fd = open( path, oflag, mode );

    if( fd < 0 ) {
        CB_ERROR( "file_open: %s", strerror(errno));
        return false;
    }

    out_file->opaque_fd = fd;

    return true;
}
void _F(file_close)( _T(File)* file ) {
    close( file->opaque_fd );
    file->opaque_fd = -1;
}
bool _F(file_remove)( const char* path ) {
    return unlink( path ) == 0;
}
_T(FileInfo) _F(file_query_info)( _T(File)* file ) {
    _T(FileInfo) fi = {};
    fi.type = _E(FT_NULL);

    struct stat st;
    if( fstat( file->opaque_fd, &st ) ) {
        return fi;
    }

    fi.size        = st.st_size;
    fi.time_modify = st.st_ctime;
    fi.time_create = st.st_mtime;
    fi.type        = __cb_file_type_from_stat( &st );

    return fi;
}
size_t _F(file_read)( _T(File)* file, void* dst, size_t size ) {
    return (size_t)read( file->opaque_fd, dst, size );
}
size_t _F(file_write)( _T(File)* file, const void* src, size_t size ) {
    return (size_t)write( file->opaque_fd, src, size );
}
bool _F(file_is_executable)( const char* path ) {
    return access( path, X_OK ) == 0;
}
intptr_t _F(file_seek)( _T(File)* file, intptr_t offset, _T(FileSeek) type ) {
    return lseek( file->opaque_fd, offset, type );
}
size_t _F(file_write_fmt_va)( _T(File)* file, const char* fmt, va_list va ) {
    int res = vdprintf( file->opaque_fd, fmt, va );
    if( res >= 0 ) {
        return (size_t)res;
    } else {
        return 0;
    }
}
bool _F(dir_create)( const char* path, bool should_fail_if_exists ) {
    if( should_fail_if_exists ) {
        _T(FileType) ft = _F(path_query_file_type)( path );
        if( ft != _E(FT_NULL) ) {
            CB_ERROR(
                "dir_create: '%s' already exists! type: %s",
                path, _F(string_from_file_type)(ft).ptr );
            return false;
        }
    }

    if( mkdir( path, S_IRWXU ) ) {
        CB_ERROR( "dir_create: %s", strerror( errno ) );
        return false;
    }
    return true;
}

bool _F(dir_remove)( const char* path, bool is_recursive ) {
    if( is_recursive ) {
        return __cb_dir_remove_recursive( path );
    } else {
        if( rmdir( path ) ) {
            CB_ERROR( "dir_remove: '%s' %s", path, strerror(errno) );
            return false;
        } else {
            return true;
        }
    }
}

int __cb_nftw( const char* fpath, const struct stat* st, int typeflag, struct FTW* ftwbuf ) {
    CB_UNUSED(typeflag);

    _T(String) path = CB_STRING_FROM_CSTR(fpath);

    struct __CbFtwState* state = &cbs.ftw;

    if( !state->count ) {
        state->count++;
        return 0;
    }

    if( state->skip_level >= 0 ) {
        if( ftwbuf->level == state->skip_level ) {
            return 0;
        } else {
            state->skip_level = -1;
        }
    }

    _T(DirWalkInfo) info = {};
    info.file_type        = __cb_file_type_from_stat( st );
    info.file_time_create = st->st_ctime;
    info.file_time_modify = st->st_mtime;
    info.file_size        = st->st_size;
    info.path_len         = path.len;
    info.path_name_offset = ftwbuf->base;

    for( size_t i = path.len; i-- > 0; ) {
        if( path.ptr[i] == '/' ) {
            break;
        }
        if( path.ptr[i] == '.' ) {
            info.path_has_ext    = true;
            info.path_ext_offset = i;
            break;
        }
    }

    info.level = ftwbuf->level - 1;

    state->count++;

    switch( state->fn( fpath, &info, state->params ) ) {
        case _E(DWA_CONTINUE): break;
        case _E(DWA_STOP):     return 1;
        case _E(DWA_SKIP): {
            state->skip_level = ftwbuf->level + 1;
        } break;
    }

    return 0;
}

size_t _F(dir_walk)( const char* path, _T(DirWalkFN)* fn, void* params ) {
    struct __CbFtwState* state = _F(mem_set)( &cbs.ftw, 0, sizeof(cbs.ftw) );

    state->fn         = fn;
    state->params     = params;
    state->skip_level = -1;
    state->count      = 0;

    if( nftw( path, __cb_nftw, 5, 0 ) < 0 ) {
        CB_ERROR( "dir_walk: %s", strerror(errno) );
        return 0;
    }
    return state->count;
}

const char* _F(dir_cwd_query)(void) {
    if( !cbs.cwd_set ) {
        cbs.cwd_set = true;
        CB_BUF_RESERVE( &cbs.cwd, CB_MAX_PATH );
        getcwd( cbs.cwd.ptr, CB_MAX_PATH - 1 );
    }
    return cbs.cwd.ptr;
}
bool _F(dir_cwd_set)( const char* cwd ) {
    size_t len = _F(cstr_len)( cwd );

    if( chdir( cwd ) ) {
        CB_ERROR( "dir_cwd_set: %s", strerror(errno) );
        return false;
    }

    CB_INFO( "chdir: '%s'", cwd );

    cbs.cwd_set = true;
    cbs.cwd.len = 0;
    CB_BUF_APPEND( &cbs.cwd, cwd, len + 1 );
    return true;
}
bool _F(pipe_open)( _T(Pipe)* out_read, _T(Pipe)* out_write ) {
    int fd[2];
    if( pipe( fd ) ) {
        CB_ERROR( "pipe_open: %s", strerror(errno) );
        return false;
    }

    out_read->opaque_fd  = fd[0];
    out_write->opaque_fd = fd[1];
    return true;
}
void _F(pipe_close)( _T(Pipe)* pipe ) {
    close( pipe->opaque_fd );
    pipe->opaque_fd = -1;
}
bool _F(pipe_wait)( _T(Pipe)* pipe, uint32_t wait_msec ) {
    int timeout = wait_msec;
    if( wait_msec == CB_WAIT_INF ) {
        timeout = -1;
    }
    struct pollfd pfd = {};
    pfd.fd     = pipe->opaque_fd;
    pfd.events = POLLIN;
    if( poll( &pfd, 1, timeout ) <= 0 ) {
        return false;
    }
    return true;
}
size_t _F(pipe_query)( _T(Pipe)* pipe ) {
    int result = 0;
    if( ioctl( pipe->opaque_fd, FIONREAD, &result ) == 0 ) {
        return (size_t)result;
    }
    return 0;
}

void _F(proc_discard)( _T(Process)* proc ) {
    CB_UNUSED(proc);
}
int __cb_proc_wait( _T(Process)* proc ) {
    int wstatus = 0;
    pid_t value = waitpid( proc->opaque_fd, &wstatus, 0 );
    if( value < 0 ) {
        CB_ERROR( "proc_wait: %s", strerror(errno) );
        return -2;
    }
    if( WIFEXITED( wstatus ) ) {
        return WEXITSTATUS( wstatus );
    } else {
        return -1;
    }
}
int _F(proc_wait)( _T(Process)* proc, uint32_t wait_msec ) {
    if( wait_msec == CB_WAIT_INF ) {
        return __cb_proc_wait( proc );
    }

    double start = _F(time_msec)();
    for( ;; ) {
        double current = _F(time_msec)();
        double elapsed = current - start;
        if( elapsed >= (double)wait_msec ) {
            break;
        }

        int wstatus = 0;
        pid_t value = waitpid( proc->opaque_fd, &wstatus, WNOHANG );

        if( value == 0 ) {
            _F(mt_yield)();
            continue;
        }

        if( value < 0 ) {
            CB_ERROR( "proc_wait: %s", strerror(errno) );
            return -1;
        }

        if( WIFEXITED(wstatus) ) {
            return WEXITSTATUS(wstatus);
        } else {
            return -3;
        }
    }

    return -2;
}
bool _F(proc_signal)( _T(Process)* proc, _T(ProcessSignal) sig ) {
    int signal = 0;
    switch( sig ) {
        case _E(PSIG_KILL): {
            return kill( proc->opaque_fd, SIGKILL ) == 0;
        } break;
        case _E(PSIG_NULL):
        case _E(PSIG_COUNT): break;
    }

    return false;
}
bool _F(proc_exists)( const char* path ) {
    char mini_buf[255 + sizeof("which %s > /dev/null 2>&1")] = {};
    snprintf( mini_buf, sizeof(mini_buf), "which %s > /dev/null 2>&1", path );
    return system( mini_buf ) == 0;
}

const char* _F(env_query)( const char* key ) {
    return getenv( key );
}
bool _F(env_set)( const char* key, const char* value ) {
    if( setenv( key, value, true ) ) {
        CB_ERROR( "env_set: %s", strerror(errno) );
        return false;
    }
    return true;
}

extern char** environ;

void _F(env_copy)( _T(Env)* out_env ) {
    for( char** env = environ; *env; env++ ) {
        _T(String) kv;
        kv.len = _F(cstr_len)( *env );
        kv.ptr = *env;

        _T(String) key;
        _T(String) value;

        size_t eq = 0;
        if( _F(string_find)( kv, '=', &eq ) ) {
            _F(string_split)( kv, eq, &key, &value );
            value = CB_SLICE_ADVANCE( &value );

            const char* k = _F(local_fmt)( "%" CB_STRING_FMT, CB_STRING_ARG(&key) );
            const char* v = _F(local_fmt)( "%" CB_STRING_FMT, CB_STRING_ARG(&value) );

            _F(env_add)( out_env, k, v );
        }

    }
}

void _F(mt_sleep)( uint32_t wait_msec ) {
    if( !wait_msec ) {
        return;
    }

    struct timespec ts;
    _F(mem_set)( &ts, 0, sizeof(ts) );
    __cb_timespec_from_msec( wait_msec, &ts );

    struct timespec rem;
    _F(mem_set)( &rem, 0, sizeof(rem) );

    while( clock_nanosleep( CLOCK_REALTIME, 0, &ts, &rem ) ) {
        ts = rem;
    }
}
void _F(mt_yield)(void) {
    sched_yield();
}

void _F(mt_barrier)(void) {
    // TODO(alicia): ARM or other CPUs
    __asm__ volatile ("mfence":::"memory");
}
int _F(mt_add)( volatile int* atom, int addend ) {
    return __sync_fetch_and_add( atom, addend );
}
int _F(mt_exch)( volatile int* atom, int exch ) {
    return __sync_val_compare_and_swap( atom, *atom, exch );
}
int _F(mt_cmp_exch)( volatile int* atom, int cmp, int exch ) {
    return __sync_val_compare_and_swap( atom, cmp, exch );
}

_T(Time) _F(time_now)(void) {
    return time(NULL);
}
double _F(time_msec)(void) {
    struct timespec ts;
    clock_gettime( CLOCK_MONOTONIC_RAW, &ts );

    return __cb_msec_from_timespec( &ts );
}
double _F(time_sec)(void) {
    return _F(time_msec)() / 1000.0;
}
_T(TimeSplit) _F(time_split_from_time)( _T(Time) time ) {
    struct tm tm;
    localtime_r( &time, &tm );
    _T(TimeSplit) result;

    result.year   = tm.tm_year + 1900;
    result.month  = tm.tm_mon + 1;
    result.day    = tm.tm_mday;
    result.hour   = tm.tm_hour;
    result.minute = tm.tm_min;
    result.second = tm.tm_sec % 60;

    return result;
}

bool __cb_exec_async( _T(Cmd) cmd, __CbExecParams params, _T(Process)* out_pid ) {
    if( !cmd.len || cmd.ptr[cmd.len] ) {
        CB_ERROR( "exec: command requires a NULL string at the end!" );
        return false;
    }

    int fd_stdin  = params.pstdin  ? params.pstdin->opaque_fd  : STDIN_FILENO;
    int fd_stdout = params.pstdout ? params.pstdout->opaque_fd : STDOUT_FILENO;
    int fd_stderr = params.pstderr ? params.pstderr->opaque_fd : STDERR_FILENO;

    if( params.wd ) {
        CB_INFO( "exec: chdir: '%s'", params.wd );
    }

    _T(StringBuf) string = {};

    if( params.env ) {
        CB_FOREACH( params.env, {
            _T(String) key   = _F(env_deref)( params.env, kv->key );
            _T(String) value = _F(env_deref)( params.env, kv->value );

            _F(string_buf_fmt)(
                &string,
                "%" CB_STRING_FMT "=%" CB_STRING_FMT " ",
                CB_STRING_ARG(&key), CB_STRING_ARG(&value) );
        }, kv );
    }

    _F(cmd_flatten)( cmd, &string );
    CB_BUF_PUSH( &string, 0 );

    CB_INFO( "  > %s", string.ptr );

    CB_BUF_FREE( &string );

    pid_t pid = fork();
    if( pid < 0 ) {
        CB_ERROR( "exec: failed to fork!" );
        return false;
    }

    // NOTE(alicia): thread where program was executed
    if( pid ) {
        out_pid->opaque_fd = pid;
        return true;
    }

    // NOTE(alicia): thread where program will run

    if( params.wd ) {
        chdir( params.wd );
    }

    if( dup2( fd_stdin, STDIN_FILENO ) < 0 ) {
        CB_ERROR( "exec: failed to duplicate stdin!" );
    }

    if( dup2( fd_stdout, STDOUT_FILENO ) < 0 ) {
        CB_ERROR( "exec: failed to duplicate stdout!" );
    }

    if( dup2( fd_stderr, STDERR_FILENO ) < 0 ) {
        CB_ERROR( "exec: failed to duplicate stderr!" );
    }

    if( params.env ) {
        CB_FOREACH( params.env, {
            _T(String) key   = _F(env_deref)( params.env, kv->key );
            _T(String) value = _F(env_deref)( params.env, kv->value );

            setenv( key.ptr, value.ptr, true );
        }, kv );
    }

    // NOTE(alicia): execvp will only return if command failed to execute.
    execvp( cmd.ptr[0], (char* const*)(cmd.ptr) );

    CB_FATAL( "exec: failed to execute %s!", cmd.ptr[0] );
    abort();
}
int __cb_exec_sync( _T(Cmd) cmd, __CbExecParams params ) {
    _T(Process) pid;
    if( __cb_exec_async( cmd, params, &pid ) ) {
        return _F(proc_wait)( &pid, CB_WAIT_INF );
    }
    return -2;
}
int __cb_exec( _T(Cmd) cmd, __CbExecParams params ) {
    if( params.proc || params.group ) {
        _T(Process) pid;
        if( __cb_exec_async( cmd, params, &pid ) ) {
            if( params.proc ) {
                *params.proc = pid;
            }
            if( params.group ) {
                _F(proc_group_add)( params.group, &pid );
            }
            return 0;
        }
        return -2;
    } else {
        return __cb_exec_sync( cmd, params );
    }
}

#endif /* Posix */

// NOTE(alicia): Windows implementation ---------------------------------------

#if CB_OS_CURRENT == CB_OS_WINDOWS

#include <windows.h>

enum {
    __CB_WINDOWS_PATH_RELATIVE,
    __CB_WINDOWS_PATH_HOME,
    __CB_WINDOWS_PATH_ABSOLUTE,
};

#if !defined(__CB_INTERNAL_WINDOWS_TESTS)
struct __CbWindowsStringParams {
    size_t  opt_string_len;
    bool    should_reset_buffer;
    bool    should_append_null;
    // if function converts UTF-8 to UTF-16, returns number of wide characters.
    //
    // otherwise, returns number of bytes.
    size_t* result_len;
};

struct __CbWindowsStringParamsQuick {
    size_t  opt_string_len;
    bool    should_reset_buffer;
    bool    should_append_null;
    // if function converts UTF-8 to UTF-16, returns number of wide characters.
    //
    // otherwise, returns number of bytes.
    size_t* result_len;

    _T(StringBuf)* opt_buf;
};
#endif

static
size_t __cb_internal_wide_len( const wchar_t* wide ) {
    size_t result = 0;
    while( *wide++ ) {
        result++;
    }
    return result;
}
static
int __cb_internal_wide_cmp( const wchar_t* a, const wchar_t* b ) {
    while( *a && *a == *b ) {
        ++a; ++b;
    }
    return (int)( *a - *b );
}

static
size_t __cb_internal_windows_wide_from_utf8(
    _T(StringBuf)* buf, const char* ptr, struct __CbWindowsStringParams params
) {
    size_t string_len = params.opt_string_len;
    if( !string_len ) {
        string_len = _F(cstr_len)( ptr );
    }

    if( params.should_reset_buffer ) {
        buf->len = 0;
    }

    size_t offset = buf->len;

    size_t wide_len = MultiByteToWideChar( CP_UTF8, 0, ptr, string_len, NULL, 0 );

    CB_BUF_RESERVE( buf, (wide_len + 1) * 2 );

    MultiByteToWideChar(
        CP_UTF8, 0,
        ptr, string_len,
        (wchar_t*)( buf->ptr + buf->len ),
        (buf->cap - buf->len) / 2 );

    buf->len += wide_len * 2;

    if( params.result_len ) {
        *params.result_len = wide_len;
    }

    if( params.should_append_null ) {
        wchar_t nul = 0;
        CB_BUF_APPEND( buf, (char*)&nul, 2 );
    }

    return offset;
}
static
size_t __cb_internal_windows_utf8_from_wide(
    _T(StringBuf)* buf, const wchar_t* ptr, struct __CbWindowsStringParams params
) {
    size_t string_len = params.opt_string_len;
    if( !string_len ) {
        string_len = __cb_internal_wide_len( ptr );
    }

    if( params.should_reset_buffer ) {
        buf->len = 0;
    }

    size_t offset = buf->len;

    size_t len =
        WideCharToMultiByte( CP_UTF8, 0, ptr, string_len, NULL, 0, 0, 0 );

    CB_BUF_RESERVE( buf, len + 1 );

    WideCharToMultiByte(
        CP_UTF8, 0,
        ptr, string_len,
        buf->ptr + buf->len,
        buf->cap - buf->len,
        0, 0 );

    buf->len += len;

    if( params.result_len ) {
        *params.result_len = len;
    }

    if( params.should_append_null ) {
        CB_BUF_PUSH( buf, 0 );
    }

    return offset;
}

static
size_t __cb_internal_windows_wide_path_from_utf8_long(
    _T(StringBuf)* buf, const char* ptr, struct __CbWindowsStringParams params
) {
    size_t len = params.opt_string_len;
    if( !len ) {
        len = _F(cstr_len)( ptr );
    }

    if( params.should_reset_buffer ) {
        buf->len = 0;
    }

    size_t offset = buf->len;

    size_t wide_len = 0;

    struct __CbWindowsStringParams params2;
    params2.opt_string_len      = len;
    params2.result_len          = &wide_len;
    params2.should_append_null  = false;
    params2.should_reset_buffer = false;

    #define PUSH( ch ) do { \
        wchar_t wide_ch = ch; \
        CB_BUF_APPEND( buf, (char*)&wide_ch, 2 ); \
    } while(0)

    #define __APPEND( wide_literal, opt_len, ... ) do { \
        wchar_t* append_string = wide_literal; \
        size_t   append_len = opt_len; \
        if( !append_len ) { \
            append_len = __cb_internal_wide_len( append_string ); \
        } \
        CB_BUF_APPEND( buf, (char*)append_string, append_len * 2 ); \
    } while(0)

    #define APPEND( wide_literal, ... ) \
        __APPEND( wide_literal __VA_OPT__(,) __VA_ARGS__, 0 )

    if( !ptr || !len ) {
        goto end;
    }

    int path_type = __CB_WINDOWS_PATH_RELATIVE;

    if( len >= sizeof("A:") ) {
        if(
            isalpha( ptr[0] ) &&
            (ptr[1] == ':') &&
            (ptr[2] == '/' || ptr[2] == '\\')
        ) {
            path_type = __CB_WINDOWS_PATH_ABSOLUTE;
        }
    }

    if( ptr[0] == '~' ) {
        path_type = __CB_WINDOWS_PATH_HOME;
    }

    APPEND( L"\\\\?\\" );

    bool has_leading_separator = false;

    switch( path_type ) {
        case __CB_WINDOWS_PATH_ABSOLUTE: {
            size_t off = __cb_internal_windows_wide_from_utf8(
                buf, ptr, CB_STRUCT(struct __CbWindowsStringParams, .opt_string_len=3) );

            wchar_t* w = (wchar_t*)(buf->ptr + off);

            if( w[2] == '/' ) {
                w[2] = '\\';
            }

            ptr += 3;
            len -= 3;
            has_leading_separator = true;
        } break;
        case __CB_WINDOWS_PATH_RELATIVE: {
            size_t prefix_len = GetCurrentDirectoryW( 0, 0 );

            CB_BUF_RESERVE( buf, (prefix_len + 1) * 2 );

            size_t prefix_offset = buf->len;

            prefix_len = GetCurrentDirectoryW(
                (buf->cap - buf->len) / 2,
                (wchar_t*)(buf->ptr + buf->len) );

            buf->len += prefix_len * 2;

            wchar_t* prefix = (wchar_t*)(buf->ptr + offset);
            if( prefix_len && (prefix[prefix_len - 1] != '\\' || prefix[prefix_len -1] != '/') ) {
                PUSH( '\\' );
                has_leading_separator = true;
            }
        } break;
        case __CB_WINDOWS_PATH_HOME: {
            size_t prefix_len = GetEnvironmentVariableW( L"HOMEDRIVE", 0, 0 );
            prefix_len       += GetEnvironmentVariableW( L"HOMEPATH", 0, 0 );

            CB_BUF_RESERVE( buf, (prefix_len + 1) * 2 );

            prefix_len = GetEnvironmentVariableW(
                L"HOMEDRIVE", (wchar_t*)( buf->ptr + buf->len ), (buf->cap - buf->len) / 2 );
            buf->len += prefix_len * 2;

            prefix_len = GetEnvironmentVariableW(
                L"HOMEPATH", (wchar_t*)( buf->ptr + buf->len ), (buf->cap - buf->len) / 2 );
            buf->len += prefix_len * 2;

            PUSH( '\\' );
            has_leading_separator = true;

            ptr++;
            len--;
        } break;
    }

    size_t minimum_len = sizeof("\\\\?\\A:");

    while( len ) {
        size_t chunk_len = len;

        for( size_t i = 0; i < len; ++i ) {
            if( ptr[i] == '/' || ptr[i] == '\\' ) {
                chunk_len = i;
                break;
            }
        }

        const char* chunk = ptr;

        if( chunk_len == len ) {
            ptr += chunk_len;
            len = 0;
        } else {
            ptr += chunk_len + 1;
            len -= chunk_len + 1;
        }

        if( !chunk_len ) {
            continue;
        }

        bool cvt = false;
        switch( chunk_len ) {
            case 1: {
                if( _F(mem_cmp)( ".", chunk, chunk_len ) ) {
                    continue;
                } else {
                    cvt = true;
                }
            } break;
            case 2: {
                if( _F(mem_cmp)( "..", chunk, chunk_len ) ) {
                    wchar_t* at          = (wchar_t*)( buf->ptr + offset );
                    size_t   current_len = (buf->len - offset) / 2;

                    for( size_t i = current_len; i-- > 0; ) {
                        if( current_len && (i == (current_len - 1)) ) {
                            continue;
                        }
                        if( at[i] == '\\' ) {
                            current_len = i;
                            break;
                        }
                    }

                    if( current_len < minimum_len ) {
                        current_len = minimum_len;
                    }

                    buf->len = offset + (current_len * 2);
                } else {
                    cvt = true;
                }
            } break;
            default: {
                cvt = true;
            } break;
        }

        if( !cvt ) {
            continue;
        }

        if( has_leading_separator ) {
            has_leading_separator = false;
        } else {
            PUSH( '\\' );
        }

        params2.opt_string_len = chunk_len;
        __cb_internal_windows_wide_from_utf8( buf, chunk, params2 );
    }

end:
    if( params.result_len ) {
        *params.result_len = (buf->len - offset) / 2;
    }

    if( params.should_append_null ) {
        PUSH( 0 );
    }

    #undef PUSH
    #undef APPEND
    #undef __APPEND
    return offset;
}

static
size_t __cb_internal_windows_wide_path_from_utf8_short(
    _T(StringBuf)* buf, const char* ptr, struct __CbWindowsStringParams params
) {
    size_t offset = __cb_internal_windows_wide_from_utf8( buf, ptr, params );

    wchar_t* scan = (wchar_t*)(buf->ptr + offset);

    while( *scan ) {
        if( *scan == '/' ) {
            *scan = '\\';
        }
        scan++;
    }

    return offset;
}

static
size_t __cb_internal_windows_wide_path_from_utf8(
    _T(StringBuf)* buf, const char* ptr, struct __CbWindowsStringParams params
) {
    if( !params.opt_string_len ) {
        params.opt_string_len = _F(cstr_len)( ptr );
    }

    if( params.opt_string_len < MAX_PATH ) {
        return __cb_internal_windows_wide_path_from_utf8_short( buf, ptr, params );
    } else {
        return __cb_internal_windows_wide_path_from_utf8_long( buf, ptr, params );
    }
}

static
size_t __cb_internal_windows_utf8_path_from_wide(
    _T(StringBuf)* buf, const wchar_t* ptr, struct __CbWindowsStringParams params
) {
    size_t len = params.opt_string_len;
    if( !len ) {
        len = __cb_internal_wide_len( ptr );
    }

    if( len >= sizeof("\\\\?") ) {
        if( memcmp( ptr, L"\\\\?\\", sizeof(L"\\\\?") ) == 0 ) {
            len -= sizeof("\\\\?");
            ptr += sizeof("\\\\?");
        }
    }

    params.opt_string_len = len;
    return __cb_internal_windows_utf8_from_wide( buf, ptr, params );
}

static
wchar_t* __cb_internal_windows_quick_wide_path(
    const char* ptr, struct __CbWindowsStringParamsQuick params
) {
    _T(StringBuf)* buf = params.opt_buf;
    if( !buf ) {
        buf = &cbs.platform_buf;
    }

    struct __CbWindowsStringParams params2 = *(struct __CbWindowsStringParams*)&params;

    size_t offset = __cb_internal_windows_wide_path_from_utf8( buf, ptr, params2 );

    return (wchar_t*)(buf->ptr + offset);
}

static
char* __cb_internal_windows_quick_utf8_path(
    const wchar_t* ptr, struct __CbWindowsStringParamsQuick params
) {
    _T(StringBuf)* buf = params.opt_buf;
    if( !buf ) {
        buf = &cbs.platform_buf;
    }

    struct __CbWindowsStringParams params2 = *(struct __CbWindowsStringParams*)&params;

    size_t offset = __cb_internal_windows_utf8_path_from_wide( buf, ptr, params2 );

    return buf->ptr + offset;
}

#define wide_from_utf8( buf, ptr, ... ) \
    __cb_internal_windows_wide_from_utf8( \
        buf, ptr, CB_STRUCT( struct __CbWindowsStringParams __VA_OPT__(,) __VA_ARGS__ ) )

#define utf8_from_wide( buf, ptr, ... ) \
    __cb_internal_windows_utf8_from_wide( \
        buf, ptr, CB_STRUCT( struct __CbWindowsStringParams __VA_OPT__(,) __VA_ARGS__ ) )

#define wide_path_from_utf8( buf, ptr, ... ) \
    __cb_internal_windows_wide_path_from_utf8( \
        buf, ptr, CB_STRUCT( struct __CbWindowsStringParams __VA_OPT__(,) __VA_ARGS__ ) )

#define utf8_path_from_wide( buf, ptr, ... ) \
    __cb_internal_windows_utf8_path_from_wide( \
        buf, ptr, CB_STRUCT( struct __CbWindowsStringParams __VA_OPT__(,) __VA_ARGS__ ) )

#define quick_wide_path( ptr, ... ) \
    __cb_internal_windows_quick_wide_path( \
        ptr, CB_STRUCT( struct __CbWindowsStringParamsQuick, \
            .should_reset_buffer=true, .should_append_null=true __VA_OPT__(,) __VA_ARGS__ ) )

#define quick_utf8_path( ptr, ... ) \
    __cb_internal_windows_quick_utf8_path( \
        ptr, CB_STRUCT( struct __CbWindowsStringParamsQuick, \
            .should_reset_buffer=true, .should_append_null=true __VA_OPT__(,) __VA_ARGS__ ) )

static
_T(FileType) __cb_windows_file_type_from_attrib( DWORD attrib ) {
    if( attrib == INVALID_FILE_ATTRIBUTES ) {
        return _E(FT_NULL);
    }

    if( attrib & FILE_ATTRIBUTE_DIRECTORY ) {
        return _E(FT_DIR);
    } else {
        return _E(FT_FILE);
    }
}
static
_T(Time) __cb_windows_time_from_filetime( FILETIME ft ) {
    #define WINDOWS_TICKS_PER_SECOND (10000000)
    #define WINDOWS_TO_POSIX_DIFF    (11644473600ULL)

    ULARGE_INTEGER uli;
    uli.LowPart  = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;

    _T(Time) res = (_T(Time))(
        (uli.QuadPart / WINDOWS_TICKS_PER_SECOND) - WINDOWS_TO_POSIX_DIFF );

    #undef WINDOWS_TICKS_PER_SECOND
    #undef WINDOWS_TO_POSIX_DIFF
    return res;
}

bool _F(path_query_info)( const char* path, _T(FileInfo)* out_info ) {
    wchar_t* wpath = quick_wide_path( path );
    WIN32_FILE_ATTRIBUTE_DATA data = {};
    if( !GetFileAttributesExW( wpath, GetFileExInfoStandard, &data ) ) {
        return false;
    }

#if CB_ARCH_IS_64BIT
    /* Read file size */ {
        ULARGE_INTEGER li;
        li.LowPart  = data.nFileSizeLow;
        li.HighPart = data.nFileSizeHigh;

        out_info->size = li.QuadPart;
    }
#else
    out_info->size = data.nFileSizeLow;
#endif
    
    out_info->type =
        __cb_windows_file_type_from_attrib( data.dwFileAttributes );
    out_info->time_create =
        __cb_windows_time_from_filetime( data.ftCreationTime );
    out_info->time_modify =
        __cb_windows_time_from_filetime( data.ftLastWriteTime );

    return true;
}
size_t _F(path_canonicalize_buf)( _T(StringBuf)* buf, const char* path ) {
    if( !path ) {
        return 0;
    }

    size_t wide_len    = 0;
    size_t wide_offset = __cb_internal_windows_wide_path_from_utf8_long(
        &cbs.platform_buf, path,
        CB_STRUCT( struct __CbWindowsStringParams,
            .should_reset_buffer=true, .result_len=&wide_len ) );

    wchar_t* wide = (wchar_t*)(cbs.platform_buf.ptr + wide_offset);

    wide     += sizeof("\\\\?");
    wide_len -= sizeof("\\\\?");

    size_t result = utf8_from_wide( buf, wide, .opt_string_len=wide_len );

    // remove trailing path separator if it exists
    if( (buf->len - result) && (buf->ptr + result)[(buf->len - result) - 1] == '\\' ) {
        buf->len--;
    }

    return result;
}

bool _F(file_open)( const char* path, _T(FileFlags) flags, _T(File)* out_file ) {
    wchar_t* wpath = quick_wide_path( path );

    DWORD dwDesiredAccess       = 0;
    DWORD dwShareMode           = 0;
    DWORD dwCreationDisposition = OPEN_EXISTING;
    DWORD dwFlagsAndAttributes  = 0;

    if( ( flags & ( _E(FF_READ) ) ) == ( _E(FF_READ) ) ) {
        dwDesiredAccess |= GENERIC_READ;
    }
    if( ( flags & ( _E(FF_WRITE) ) ) == ( _E(FF_WRITE) ) ) {
        dwDesiredAccess |= GENERIC_WRITE;
    }

    if( ( flags & ( _E(FF_CREATE) ) ) == ( _E(FF_CREATE) ) ) {
        dwCreationDisposition = OPEN_ALWAYS;
        if(
            (flags & _E(FF_EXECUTE) ) ==
            _E(FF_EXECUTE)
        ) {
            dwDesiredAccess |= GENERIC_EXECUTE;
        }
    } else if( ( flags & ( _E(FF_TRUNCATE) ) ) == ( _E(FF_TRUNCATE) ) ) {
        dwCreationDisposition = TRUNCATE_EXISTING;
    }

    bool append = ( flags & ( _E(FF_APPEND) ) ) == ( _E(FF_APPEND) );

    HANDLE handle = CreateFileW(
        wpath, dwDesiredAccess, dwShareMode, 0,
        dwCreationDisposition, dwFlagsAndAttributes, 0 );

    if( !handle || (handle == INVALID_HANDLE_VALUE) ) {
        return false;
    }

    out_file->opaque_ptr = handle;

    if( append ) {
        _F(file_seek)( out_file, 0, _E(FS_END) );
    }

    return true;
}
void _F(file_close)( _T(File)* file ) {
    if( file && file->opaque_ptr ) {
        CloseHandle( file->opaque_ptr );
        _F(mem_set)( file, 0, sizeof(*file) );
    }
}
bool _F(file_remove)( const char* path ) {
    wchar_t* wpath = quick_wide_path( path );
    if( DeleteFileW( wpath ) ) {
        return true;
    }
    return false;
}
_T(FileInfo) _F(file_query_info)( _T(File)* file ) {
    BY_HANDLE_FILE_INFORMATION info;
    _F(mem_set)( &info, 0, sizeof(info) );

    _T(FileInfo) result;
    _F(mem_set)( &result, 0, sizeof(result) );

    if( GetFileInformationByHandle( file->opaque_ptr, &info ) ) {
#if CB_ARCH_IS_64BIT
        ULARGE_INTEGER li;
        li.LowPart  = info.nFileSizeLow;
        li.HighPart = info.nFileSizeHigh;

        result.size = li.QuadPart;
#else
        result.size = info.nFileSizeLow;
#endif

        result.type =
            __cb_windows_file_type_from_attrib( info.dwFileAttributes );
        result.time_create =
            __cb_windows_time_from_filetime( info.ftCreationTime );
        result.time_modify =
            __cb_windows_time_from_filetime( info.ftLastWriteTime );
    }

    return result;
}
size_t _F(file_read)( _T(File)* file, void* dst, size_t size ) {
#if CB_ARCH_IS_64BIT
    uint32_t part_a_size =
        size > 0xFFFFFFFF ? 0xFFFFFFFF : size;
    void*    part_a      = dst;
    uint32_t part_b_size =
        part_a_size == 0xFFFFFFFF ? size - part_a_size : 0;
    void*    part_b      = (void*)((uint8_t*)dst + part_a_size);

    size_t total_read_size = 0;

    DWORD read_size = 0;
    if( !ReadFile( file->opaque_ptr, part_a, part_a_size, &read_size, NULL ) ) {
        return 0;
    }

    total_read_size += read_size;

    if( !part_b_size ) {
        return total_read_size;
    }

    read_size = 0;
    if( !ReadFile( file->opaque_ptr, part_b, part_b_size, &read_size, NULL ) ) {
        return total_read_size;
    }

    return total_read_size + read_size;
#else
    DWORD read_size = 0;
    if( !ReadFile( file->opaque_ptr, dst, size, &read_size ) ) {
        return 0;
    }
    return read_size;
#endif
}

size_t __cb_windows_file_write( _T(File)* file, const void* src, size_t size ) {
#if CB_ARCH_IS_64BIT
    uint32_t part_a_size =
        size > 0xFFFFFFFF ? 0xFFFFFFFF : size;
    void*    part_a      = (void*)src;
    uint32_t part_b_size =
        part_a_size == 0xFFFFFFFF ? size - part_a_size : 0;
    void*    part_b      = (void*)((uint8_t*)src + part_a_size);

    size_t total_write_size = 0;

    DWORD write_size = 0;
    if( !WriteFile( file->opaque_ptr, part_a, part_a_size, &write_size, NULL ) ) {
        return 0;
    }

    total_write_size += write_size;

    if( !part_b_size ) {
        return total_write_size;
    }

    write_size = 0;
    if( !WriteFile( file->opaque_ptr, part_b, part_b_size, &write_size, NULL ) ) {
        return total_write_size;
    }

    return total_write_size + write_size;
#else
    DWORD write_size = 0;
    if( !WriteFile( file->opaque_ptr, src, size, &write_size ) ) {
        return 0;
    }
    return write_size;
#endif
}
void __cb_windows_setup_console(void) {
    if( cbs.setup_console ) {
        return;
    }

    cbs.setup_console = true;

    SetConsoleCP( CP_UTF8 );
    SetConsoleOutputCP( CP_UTF8 );
}
size_t __cb_windows_console_write( _T(File)* file, const void* src, size_t size ) {
    __cb_windows_setup_console();

#if CB_ARCH_IS_64BIT
    const void* part_a      = src;
    DWORD       part_a_size = size >= 0xFFFFFFFF ? 0xFFFFFFFF : size;
    const void* part_b      = (const void*)((uint8_t*)src + part_a_size);
    DWORD       part_b_size = size > part_a_size ? size - part_a_size : 0;

    DWORD part_a_write = 0;
    if( !WriteConsoleA( file->opaque_ptr, part_a, part_a_size, &part_a_write, NULL ) ) {
        return 0;
    }

    if( !part_b_size ) {
        return part_a_write;
    }

    DWORD part_b_write = 0;
    if( !WriteConsoleA( file->opaque_ptr, part_b, part_b_size, &part_b_write, NULL ) ) {
        return part_a_write;
    }

    return part_a_write + part_b_write;
#else
    DWORD written = 0;
    WriteConsoleA( file->opaque_ptr, src, size, &written, NULL );
    return written;
#endif

}

size_t _F(file_write)( _T(File)* file, const void* src, size_t size ) {
    if( !file || !file->opaque_ptr ) {
        return 0;
    }

    DWORD type = GetFileType( file->opaque_ptr );

    size_t result = 0;
    switch( type ) {
        case FILE_TYPE_CHAR: {
            result += __cb_windows_console_write( file, src, size );
        } break;
        default: {
            result += __cb_windows_file_write( file, src, size );
        } break;
    }

    return result;
}
bool _F(file_is_executable)( const char* path ) {
    _T(String) string = CB_STRING_FROM_CSTR( path );

    size_t dot = 0;
    if( _F(string_find_rev)( string, '.', &dot ) ) {
        string = CB_SLICE_ADVANCE( &string, dot );

        return _F(string_cmp)( string, CB_STRING(".exe") );
    }

    return false;
}
intptr_t _F(file_seek)( _T(File)* file, intptr_t offset, _T(FileSeek) type ) {
    DWORD dwMoveMethod = FILE_BEGIN;
    switch( type ) {
        case _E(FS_CUR): {
            dwMoveMethod = FILE_CURRENT;
        } break;
        case _E(FS_SET): {
            dwMoveMethod = FILE_BEGIN;
        } break;
        case _E(FS_END): {
            dwMoveMethod = FILE_END;
        } break;
    }
#if CB_ARCH_IS_64BIT
    LARGE_INTEGER move = { .QuadPart = offset }, new_pointer = {};
    SetFilePointerEx(
        file->opaque_ptr, move, &new_pointer, dwMoveMethod );
    return new_pointer.QuadPart;
#else
    return SetFilePointer(
        file->opaque_ptr, offset, NULL, dwMoveMethod );
#endif
}
size_t _F(file_write_fmt_va)( _T(File)* file, const char* fmt, va_list va ) {
    cbs.platform_buf.len = 0;
    _F(string_buf_fmt_va)( &cbs.platform_buf, fmt, va );

    return _F(file_write)( file, cbs.platform_buf.ptr, cbs.platform_buf.len );
}

bool _F(dir_create)( const char* path, bool should_fail_if_exists ) {
    wchar_t* wpath = quick_wide_path( path );
    if( CreateDirectoryW( wpath, NULL ) ) {
        return true;
    }
    return false;
}
bool _F(dir_remove)( const char* path, bool is_recursive ) {
    if( is_recursive ) {
        return __cb_dir_remove_recursive( path );
    } else {
        wchar_t* wpath = quick_wide_path( path );
        if( RemoveDirectoryW( wpath ) ) {
            return true;
        } else {
            return false;
        }
    }
}

_T(DirWalkAction) __cb_windows_dir_walk(
    _T(DirWalkFN)* fn, void* params, _T(StringBuf)* buf,
    size_t start_len, WIN32_FIND_DATAW* data, _T(DirWalkInfo)* info,
    size_t* count
) {
    wchar_t* wpath = (wchar_t*)buf->ptr;

    HANDLE handle = FindFirstFileExW( wpath, FindExInfoBasic, data, FindExSearchNameMatch, 0, 0 );
    if( handle == INVALID_HANDLE_VALUE ) {
        return _E(DWA_STOP);
    }

    for( ;; ) {
        if(
            (__cb_internal_wide_cmp( L".", data->cFileName ) == 0) ||
            (__cb_internal_wide_cmp( L"..", data->cFileName ) == 0)
        ) {
            if( FindNextFileW( handle, data ) ) {
                continue;
            } else {
                break;
            }
        }

        buf->len = start_len;
        wchar_t ap = 0;
        ap = '\\';
        CB_BUF_APPEND( buf, (char*)&ap, 2 );

        size_t file_len = __cb_internal_wide_len( data->cFileName );

        CB_BUF_RESERVE( buf, (file_len + 1) * 2 );

        CB_BUF_APPEND( buf, (char*)(data->cFileName), file_len * 2 );

        size_t file_path_len = buf->len / 2;

        ap = 0;
        CB_BUF_APPEND( buf, (char*)&ap, 2 );

        // max path
        CB_BUF_RESERVE( buf, 4096 );

        // skip leading \\\\?\\ because it's part of windows long path support
        wpath = ((wchar_t*)buf->ptr) + sizeof("\\\\?");

        const char* path = quick_utf8_path( wpath, .should_reset_buffer=false );

        info->path_len = _F(cstr_len)( path );

        info->path_name_offset = 0;
        for( size_t i = info->path_len; i-- > 0; ) {
            if( path[i] == '\\' ) {
                info->path_name_offset = i + 1;
                break;
            }
        }

        for( size_t i = info->path_len; i-- > 0; ) {
            if( i == info->path_name_offset ) {
                break;
            }
            if( path[i] == '.' ) {
                info->path_has_ext    = true;
                info->path_ext_offset = i;
                break;
            }
        }

#if CB_ARCH_IS_64BIT
        /* read file size */ {
            ULARGE_INTEGER li;
            li.LowPart  = data->nFileSizeLow;
            li.HighPart = data->nFileSizeHigh;

            info->file_size = li.QuadPart;
        }
#else
        info->file_size = data->nFileSizeLow;
#endif

        info->file_type =
            __cb_windows_file_type_from_attrib( data->dwFileAttributes );

        _T(DirWalkAction) action = fn( path, info, params );
        *count += 1;

        switch( action ) {
            case _E(DWA_CONTINUE): {
                if( info->file_type == _E(FT_DIR) ) {
                    // remove null
                    buf->len -= 2;

                    ap = '\\';
                    CB_BUF_APPEND( buf, (char*)&ap, 2 );
                    ap = '*';
                    CB_BUF_APPEND( buf, (char*)&ap, 2 );
                    ap = 0;
                    CB_BUF_APPEND( buf, (char*)&ap, 2 );

                    info->level++;

                    action = __cb_windows_dir_walk(
                        fn, params, buf, buf->len - 6, data, info, count );

                    switch( action ) {
                        case _E(DWA_CONTINUE): break;
                        case _E(DWA_STOP): {
                            CloseHandle( handle );
                        } return action;
                        case _E(DWA_SKIP): break;
                    }

                    info->level--;
                }
            } break;
            case _E(DWA_SKIP):
                break;
            case _E(DWA_STOP): {
                CloseHandle( handle );
            } return action;
        }

        if( !FindNextFileW( handle, data ) ) {
            break;
        }
    }

    CloseHandle( handle );

    return _E(DWA_CONTINUE);
}
size_t _F(dir_walk)( const char* path, _T(DirWalkFN)* fn, void* params ) {
    _T(StringBuf) buf;
    _F(mem_set)( &buf, 0, sizeof(buf) );

    size_t off = __cb_internal_windows_wide_path_from_utf8_long(
        &buf, path, CB_STRUCT( struct __CbWindowsStringParams, .should_append_null=true ) );

    wchar_t* pt = (wchar_t*)(buf.ptr + off);

    // get rid of terminating null
    buf.len -= 2;

    wchar_t wch = 0;

    // append separator if it doesn't exist
    size_t wlen = buf.len / 2;
    if( wlen && pt[wlen - 1] != '\\' ) {
        wch = '\\';
        CB_BUF_APPEND( &buf, (char*)&wch, 2 );
    }

    wch = '*';
    CB_BUF_APPEND( &buf, (char*)&wch, 2 );
    wch = 0;
    CB_BUF_APPEND( &buf, (char*)&wch, 2 );

    size_t start_len = buf.len - 6; // \*0

    WIN32_FIND_DATAW data;
    _T(DirWalkInfo)  info;

    _F(mem_set)( &data, 0, sizeof(data) );
    _F(mem_set)( &info, 0, sizeof(info) );

    size_t count = 0;

    __cb_windows_dir_walk(
        fn, params, &buf, start_len, &data, &info, &count );

    CB_BUF_FREE( &buf );

    return count;
}
const char* _F(dir_cwd_query)(void) {
    if( !cbs.cwd_set ) {
        cbs.cwd_set = true;

        DWORD len = GetCurrentDirectoryW( 0, 0 );

        cbs.platform_buf.len = 0;
        CB_BUF_RESERVE( &cbs.platform_buf, (len + 1) * 2 );

        len = GetCurrentDirectoryW(
            (cbs.platform_buf.cap - cbs.platform_buf.len) / 2,
            (wchar_t*)cbs.platform_buf.ptr );

        cbs.platform_buf.len += len * 2;

        // null terminator
        cbs.platform_buf.len += 2;

        // try to avoid reallocating in windows_utf8
        CB_BUF_RESERVE( &cbs.platform_buf, CB_MAX_PATH );

        const char* utf8 = quick_utf8_path(
            (wchar_t*)cbs.platform_buf.ptr, .opt_string_len=len, .should_reset_buffer=false );

        size_t utf8_len = _F(cstr_len)( utf8 );

        cbs.cwd.len = 0;
        CB_BUF_APPEND( &cbs.cwd, utf8, utf8_len + 1 );
    }

    return cbs.cwd.ptr;
}
bool _F(dir_cwd_set)( const char* cwd ) {
    // TODO(alicia): edit wide_path_from_utf8
    // so that it prepends \\\\?\\ after checking if cwd already has it
    // if it does, don't prepend \\\\?\\ cause that causes problems

    size_t path_len = 0;
    wchar_t* wcwd = quick_wide_path( cwd, .result_len=&path_len );

    if( path_len > MAX_PATH ) {
        return false;
    }

    if( !SetCurrentDirectoryW( wcwd ) ) {
        return false;
    }

    cbs.cwd_set = true;
    cbs.cwd.len = 0;

    size_t cwd_len = _F(cstr_len)( cwd );
    CB_BUF_APPEND( &cbs.cwd, cwd, cwd_len + 1 );

    return true;
}

void __cb_platform_get_handles(void) {
    if( cbs.out_handles_obtained ) {
        return;
    }

    cbs.out_handles_obtained = true;
    cbs.h_stdout.opaque_ptr = GetStdHandle( STD_OUTPUT_HANDLE );
    cbs.h_stderr.opaque_ptr = GetStdHandle( STD_ERROR_HANDLE );
    cbs.h_stdin.opaque_ptr  = GetStdHandle( STD_INPUT_HANDLE );
}

bool _F(pipe_open)( _T(Pipe)* out_read, _T(Pipe)* out_write ) {
    HANDLE read, write;

    // NOTE(alicia): 
    // bInheritHandle set to TRUE because
    // otherwise these pipes can't be passed to a child process.
    SECURITY_ATTRIBUTES sa = {};
    sa.nLength        = sizeof(sa);
    sa.bInheritHandle = TRUE;

    if( !CreatePipe( &read, &write, &sa, 0 ) ) {
        return false;
    }

    out_read->opaque_ptr  = read;
    out_write->opaque_ptr = write;
    return true;
}
void _F(pipe_close)( _T(Pipe)* pipe ) {
    if( pipe && pipe->opaque_ptr ) {
        CloseHandle( (HANDLE)pipe->opaque_ptr );
        _F(mem_set)( pipe, 0, sizeof(*pipe) );
    }
}
void __cb_windows_pipe_wait_inf( _T(Pipe)* pipe ) {
    for( ;; ) {
        DWORD available = 0;
        if( PeekNamedPipe( pipe->opaque_ptr, NULL, 0, NULL, &available, NULL ) && available > 0 ) {
            return;
        }

        _F(mt_yield)();
    }
}
bool _F(pipe_wait)( _T(Pipe)* pipe, uint32_t wait_msec ) {
    if( wait_msec == CB_WAIT_INF ) {
        __cb_windows_pipe_wait_inf( pipe );
        return true;
    }

    double start_msec = _F(time_msec)();

    for( ;; ) {
        DWORD available = 0;
        if( PeekNamedPipe( pipe->opaque_ptr, NULL, 0, NULL, &available, NULL ) && available > 0 ) {
            return true;
        }

        double elapsed = _F(time_msec)() - start_msec;

        if( (uint32_t)elapsed >= wait_msec ) {
            break;
        }

        _F(mt_yield)();
    }

    return false;
}
size_t _F(pipe_query)( _T(Pipe)* pipe ) {
    DWORD available = 0;
    if( PeekNamedPipe( pipe->opaque_ptr, NULL, 0, NULL, &available, 0 ) ) {
        return available;
    }
    return 0;
}

void _F(proc_discard)( _T(Process)* proc ) {
    if( proc && proc->opaque_ptr ) {
        CloseHandle( (HANDLE)proc->opaque_ptr );
        _F(mem_set)( proc, 0, sizeof(*proc) );
    }
}
int _F(proc_wait)( _T(Process)* proc, uint32_t wait_msec ) {
    DWORD result = WaitForSingleObject( proc->opaque_ptr, wait_msec );
    switch( result ) {
        case WAIT_OBJECT_0:
            break;
        case WAIT_TIMEOUT:
            return -2;
        default: return -3;
    }

    DWORD exit_code = 0;
    if( !GetExitCodeProcess( proc->opaque_ptr, &exit_code ) ) {
        return -2;
    }

    _F(proc_discard)( proc );
    return exit_code;
}
bool _F(proc_signal)( _T(Process)* proc, _T(ProcessSignal) sig ) {
    switch( sig ) {
        case _E(PSIG_KILL): {
            bool result = TerminateProcess( proc->opaque_ptr, -1 );
            if( result ) {
                _F(proc_discard)( proc );
            }

            return result;
        } break;
        case _E(PSIG_NULL):
        case _E(PSIG_COUNT): break;
    }
    return true;
}
bool _F(proc_exists)( const char* path ) {
    cbs.platform_buf.len = 0;
    _F(string_buf_fmt)( &cbs.platform_buf, "WHERE %s /Q", path );
    return system( cbs.platform_buf.ptr ) == 0;
}

const char* _F(env_query)( const char* key ) {
    wchar_t* wkey = (wchar_t*)(
        cbs.platform_buf.ptr +
        wide_from_utf8(
            &cbs.platform_buf, key, .should_append_null=true, .should_reset_buffer=true ) );

    size_t required_size = GetEnvironmentVariableW( wkey, NULL, 0 );

    CB_BUF_RESERVE( &cbs.platform_buf, ( required_size + 1 ) * 2 );

    size_t len = GetEnvironmentVariableW(
        wkey,
        (wchar_t*)(cbs.platform_buf.ptr + cbs.platform_buf.len),
        (cbs.platform_buf.cap - cbs.platform_buf.len) / 2 );

    wchar_t* wptr = (wchar_t*)(cbs.platform_buf.ptr + cbs.platform_buf.len);

    cbs.platform_buf.len += (len + 1) * 2;

    // this is to try to ensure that __cb_windows_utf8 doesn't reallocate.
    CB_BUF_RESERVE( &cbs.platform_buf, required_size * 2 );

    return
        cbs.platform_buf.ptr + utf8_from_wide( &cbs.platform_buf, wptr, .should_append_null=true );
}
bool _F(env_set)( const char* key, const char* value ) {
    size_t key_offset = wide_from_utf8(
        &cbs.platform_buf, key, .should_reset_buffer=true, .should_append_null=true );
    size_t value_offset = wide_from_utf8(
        &cbs.platform_buf, value, .should_append_null=true );

    wchar_t* wkey   = (wchar_t*)(cbs.platform_buf.ptr + key_offset);
    wchar_t* wvalue = (wchar_t*)(cbs.platform_buf.ptr + value_offset);

    return SetEnvironmentVariableW( wkey, wvalue );
}
void _F(env_copy)( _T(Env)* out_env ) {
    LPWCH strings = GetEnvironmentStringsW();
    if( !strings ) {
        return;
    }

    LPWCH var = strings;
    while( *var ) {
        size_t len = __cb_internal_wide_len( var );

        wchar_t* wkey    = var;
        size_t   key_len = 0;
        for( size_t i = 0; i < len; ++i ) {
            if( var[i] == '=' ) {
                key_len = i;
                break;
            }
        }

        wchar_t* wvalue    = wkey + key_len + 1;
        size_t   value_len = len  - (key_len + 1);

        size_t key_offset = utf8_from_wide(
            &cbs.platform_buf, wkey,
            .opt_string_len=key_len, .should_append_null=true, .should_reset_buffer=true );

        size_t value_offset = utf8_from_wide(
            &cbs.platform_buf, wvalue,
            .opt_string_len=value_len, .should_append_null=true );

        const char* key   = cbs.platform_buf.ptr + key_offset;
        const char* value = cbs.platform_buf.ptr + value_offset;

        _F(env_add)( out_env, key, value );

        var += len + 1;
    }

    FreeEnvironmentStringsW( strings );
}

void _F(mt_sleep)( uint32_t wait_msec ) {
    Sleep( (DWORD)wait_msec );
}
void _F(mt_yield)(void) {
    SwitchToThread();
}
void _F(mt_barrier)(void) {
    _ReadWriteBarrier();
}
int _F(mt_add)( volatile int* atom, int addend ) {
    return InterlockedExchangeAdd( (volatile long*)atom, addend );
}
int _F(mt_exch)( volatile int* atom, int exch ) {
    return InterlockedExchange( (volatile long*)atom, exch );
}
int _F(mt_cmp_exch)( volatile int* atom, int cmp, int exch ) {
    return InterlockedCompareExchange( (volatile long*)atom, cmp, exch );
}

_T(Time) _F(time_now)(void) {
    FILETIME ft;
    _F(mem_set)( &ft, 0, sizeof(ft) );
    GetSystemTimeAsFileTime( &ft );

    return __cb_windows_time_from_filetime( ft );
}
double _F(time_msec)(void) {
    LARGE_INTEGER qpf;
    QueryPerformanceFrequency( &qpf );
    LARGE_INTEGER qpc;
    QueryPerformanceCounter( &qpc );

    return ((double)qpc.QuadPart / (double)qpf.QuadPart) * 1000.0;
}
double _F(time_sec)(void) {
    LARGE_INTEGER qpf;
    QueryPerformanceFrequency( &qpf );
    LARGE_INTEGER qpc;
    QueryPerformanceCounter( &qpc );

    return ((double)qpc.QuadPart / (double)qpf.QuadPart);
}
_T(TimeSplit) _F(time_split_from_time)( _T(Time) time ) {
    struct tm tm;
    localtime_s( &tm, &time );

    _T(TimeSplit) split;

    split.year   = tm.tm_year + 1900;
    split.month  = tm.tm_mon + 1;
    split.day    = tm.tm_mday;
    split.hour   = tm.tm_hour;
    split.minute = tm.tm_min;
    split.second = tm.tm_sec % 60;

    return split;
}

bool __cb_windows_exec( _T(Cmd) cmd, __CbExecParams* params, _T(Process)* out_proc ) {
    STARTUPINFOW        startup;
    _F(mem_set)( &startup, 0, sizeof(startup) );
    PROCESS_INFORMATION info;
    _F(mem_set)( &info, 0, sizeof(info) );

    startup.cb         = sizeof(startup);
    startup.hStdInput  = GetStdHandle( STD_INPUT_HANDLE );
    startup.hStdOutput = GetStdHandle( STD_OUTPUT_HANDLE );
    startup.hStdError  = GetStdHandle( STD_ERROR_HANDLE );

    BOOL bInheritHandles = FALSE;
    if( params->pstdin && params->pstdin->opaque_ptr ) {
        startup.hStdInput = (HANDLE)params->pstdin->opaque_ptr;
        bInheritHandles   = TRUE;
    }
    if( params->pstdout && params->pstdout->opaque_ptr ) {
        startup.hStdOutput = (HANDLE)params->pstdout->opaque_ptr;
        bInheritHandles    = TRUE;
    }
    if( params->pstderr && params->pstderr->opaque_ptr ) {
        startup.hStdError = (HANDLE)params->pstderr->opaque_ptr;
        bInheritHandles   = TRUE;
    }
    if( bInheritHandles ) {
        startup.dwFlags |= STARTF_USESTDHANDLES;
    }

    _T(StringBuf) str;
    str.len = str.cap = 0;
    str.ptr = NULL;

    for( size_t i = 0; i < cmd.len; ++i ) {
        const char* arg = cmd.ptr[i];
        if( !arg || !*arg ) {
            continue;
        }

        _T(String) sarg = CB_STRING_FROM_CSTR(arg);

        bool has_whitespace = _F(string_find_set)(
            sarg, CB_RUNE_SET( ' ', '\t', '\n', '\r' ), NULL );

        wchar_t quote = '"';
        if( has_whitespace ) {
            CB_BUF_APPEND( &str, (char*)&quote, 2 );
        }

        wide_from_utf8( &str, sarg.ptr, .opt_string_len=sarg.len );

        if( has_whitespace ) {
            CB_BUF_APPEND( &str, (char*)&quote, 2 );
        }

        if( (i + 1) < cmd.len ) {
            wchar_t space = ' ';
            CB_BUF_APPEND( &str, (char*)&space, 2 );
        } else {
            wchar_t nul = 0;
            CB_BUF_APPEND( &str, (char*)&nul, 2 );
        }
    }

    size_t env_offset = str.len;
    size_t wd_offset  = 0;

    wchar_t* cmdline, *env, *wd;
    cmdline = env = wd = NULL;

    if( params->wd ) {
        CB_INFO( "exec: chdir: '%s'", params->wd );

        wd_offset = wide_from_utf8( &str, params->wd, .should_append_null=true );

        env_offset = str.len;
    }

    if( params->env ) {
        LPWCH env_block = GetEnvironmentStringsW();

        if( env_block ) {
            wchar_t* scan = env_block;

            while( *scan ) {
                size_t kv_len = __cb_internal_wide_len( scan );
                CB_BUF_APPEND( &str, (char*)scan, (kv_len + 1) * 2 );
                scan += kv_len + 1;
            }

            FreeEnvironmentStringsW( env_block );
        }

        for( size_t i = 0; i < params->env->len; ++i ) {
            _T(EnvKV)* kv = params->env->ptr + i;

            _T(String) key   = _F(env_deref)( params->env, kv->key );
            _T(String) value = _F(env_deref)( params->env, kv->value );

            wide_from_utf8( &str, key.ptr, .opt_string_len=key.len );

            wchar_t eq = '=';
            CB_BUF_APPEND( &str, (char*)&eq, 2 );


            wide_from_utf8( &str, value.ptr, .opt_string_len=value.len, .should_append_null=true );
        }
        wchar_t nul = 0;
        CB_BUF_APPEND( &str, (char*)&nul, 2 );

        env = (wchar_t*)(str.ptr + env_offset);
    }
    cmdline = (wchar_t*)str.ptr;
    wd      = (wchar_t*)(str.ptr + wd_offset);

    DWORD dwCreationFlags = 0;
    if( env ) {
        dwCreationFlags = CREATE_UNICODE_ENVIRONMENT;

        logger_output( LOG_INFO, "[I]   > " );

        for( size_t i = 0; i < params->env->len; ++i ) {
            _T(EnvKV)* kv = params->env->ptr + i;

            _T(String) key   = _F(env_deref)( params->env, kv->key );
            _T(String) value = _F(env_deref)( params->env, kv->value );

            logger_output(
                LOG_INFO,
                "%" CB_STRING_FMT "=%" CB_STRING_FMT " ",
                CB_STRING_ARG(&key), CB_STRING_ARG(&value) );
        }

        logger_output( LOG_INFO, "%S\n", cmdline );
    } else {
        CB_INFO( "  > %S", cmdline );
    }

    BOOL result = CreateProcessW(
        NULL, cmdline, NULL, NULL,
        bInheritHandles, dwCreationFlags, env, wd, &startup, &info );
    DWORD error_code = GetLastError();

    CB_BUF_FREE( &str );

    if( result ) {
        out_proc->opaque_ptr = info.hProcess;
        CloseHandle( info.hThread );
        return true;
    }

    // error
    (void)error_code;
    return false;
}
int __cb_exec( _T(Cmd) cmd, __CbExecParams params ) {
    _T(Process) proc = _F(proc_null)();

    if( !__cb_windows_exec( cmd, &params, &proc ) ) {
        return -2;
    }

    if( params.proc || params.group ) {
        if( params.proc ) {
            *params.proc = proc;
        }
        if( params.group ) {
            _F(proc_group_add)( params.group, &proc );
        }
        return 0;
    } else {
        return _F(proc_wait)( &proc, CB_WAIT_INF );
    }
}

#undef wide_from_utf8
#undef utf8_from_wide
#undef wide_path_from_utf8
#undef utf8_path_from_wide
#undef quick_wide_path
#undef quick_utf8_path

#endif /* Windows */

#undef cbs
#undef cbjq
#undef CB_LOCAL_SIZE_BYTES
#undef CB_LOCAL_PLATFORM_COUNT
#endif /* implementation */

