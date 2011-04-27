#ifndef HTTPSESSIONSERVER_H
#define HTTPSESSIONSERVER_H

#include "HttpServer.h"
#include "Ptr.h"
#include <map>

BEG_METIL_NAMESPACE;

/**

*/
class HttpSessionServer : public HttpServer {
public:
    struct Session : public ObjectWithCptUse {
        virtual void request ( String &out, const String &addr, const String &post );
        virtual void exec_cmd( String &out, const String &cmd , String &post );
    };
    struct Factory : public ObjectWithCptUse {
        virtual Session *create( const String &type, const String &post ) const = 0;
    };

    HttpSessionServer( const String &page_dir = "html" );

    void add_factory( const String &name, Factory *factory );
    virtual void request( String &out, const String &addr, const String &post );

protected:
    std::map<String,Ptr<Factory> > factories;
    std::map<String,Ptr<Session> > sessions;
    String page_dir;
};

END_METIL_NAMESPACE;

#endif // HTTPSESSIONSERVER_H
