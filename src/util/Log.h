#pragma once

class Log
{
    static bool _verbose;

public:
    static void Write( const char* msg, ... );
    static void WriteLine( const char* msg, ... );
    static void Line( const char* msg, ... );

    static void Write( const char* msg, va_list args );
    static void WriteLine( const char* msg, va_list args );

    static void Error( const char* msg, ... );
    static void WriteError( const char* msg, ... );
    static void Error( const char* msg, va_list args );
    static void WriteError( const char* msg, va_list args );

    inline static void SetVerbose( bool enabled ) { _verbose = enabled; }
    
    static void Verbose( const char* msg, ...  );
    static void VerboseWrite( const char* msg, ...  );

    static void Flush();
    static void FlushError();

    static void NewLine();

#if DBG_LOG_ENABLE
    static void Debug( const char* msg, ... );
    static void DebugV( const char* msg, va_list args );
    static void DebugWrite( const char* msg, size_t size );
#else
    static inline void Debug( const char* msg, ... ) {}
    static void DebugV( const char* msg, va_list args ) {}
    static void DebugWrite( const char* msg, size_t size ) {}
#endif

    static void SafeWrite( const char* msg, size_t size );

private:

    static FILE* GetOutStream();
    static FILE* GetErrStream();
    static void PrintTimestamp(FILE* stream);


private:
    static FILE* _outStream;
    static FILE* _errStream;

void Log::PrintTimestamp(FILE* stream) {
    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    fprintf(stream, "[%s] ", timestamp);
}

void Log::Line(const char* msg, ...) {
    va_list args;
    va_start(args, msg);

    FILE* stream = GetOutStream();
    PrintTimestamp(stream);
    vfprintf(stream, msg, args);
    fprintf(stream, "\n");

    va_end(args);
}

};
