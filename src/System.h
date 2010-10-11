#ifndef SYSTEM_H
#define SYSTEM_H

#include "String.h"

BEG_METIL_NAMESPACE

// files
//String cur_dir(); // current directory
//String get_env( const String &var ); //
//void set_env( const String &var, const String &val ); //
//String canonicalize_filename( const String &f ); /// /tata/../grot\toto/ -> /grot/toto
//String absolute_filename( const String &f ); /// ./grot//toto/ -> /pouet/grot/toto
//String directory_of( const String &filename );
//String filename_without_dir_of( const String &filename );
int create_directory( String filename, bool check_if_exists = true );
//SI64 last_modification_time_or_zero_of_file_named( const char   *n );
//SI64 last_modification_time_or_zero_of_file_named( const String &n );
//bool file_exists( const String &n );
//void rm( const String &file ); // rm file

//// system info
//String get_os_type();
//String get_cpu_type();
//bool term_supports_color(); ///< return true if terminal supports escape color sequences

///**
//  @brief Can be used to sweep a directory

//  Example :
//\code
//for(DirectoryIterator f("/home"); f; ++f )
//    PRINT( *f );
//\endcode
//*/
//struct DirectoryIterator {
//    DirectoryIterator( const String &directory );
//    ~DirectoryIterator();
//    operator bool() const;
//    DirectoryIterator &operator++();
//    String operator*() const;

//    void *dir;
//    void *dir_ent;
//};

//// time
//double time_of_day_in_sec();

// execution
int exec_cmd( String f, bool display = true );

END_METIL_NAMESPACE

#endif // SYSTEM_H
