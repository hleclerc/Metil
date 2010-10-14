#ifndef METILSERVER_H
#define METILSERVER_H

#include <String.h>
#include <map>

BEG_METIL_NAMESPACE;

class MetilSession;

/**
*/
class MetilServer {
public:
    MetilServer( const String &base_dir );
    ~MetilServer();

    bool run( int port );

private:
    bool get_page( String addr, String data, int sd_current );

    std::map<int,MetilSession *> sessions;
    String base_dir;
};

END_METIL_NAMESPACE;

#endif // METILSERVER_H
