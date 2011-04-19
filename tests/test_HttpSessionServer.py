import httplib, os

def request( host, port, url, data = "", method = "POST" ):
    server = httplib.HTTP( host, port )
    server.putrequest( method, url )
    server.putheader( "Content-Length", str( len( data ) ) )
    server.endheaders()
    server.send( data )
    returncode, returnmsg, headers = server.getreply()
    if returncode == 200:  # OK
        f = server.getfile()
        res = f.read()
        a = res.find( "\n\n" )
        b = res.find( "\n\r\n" )
        if a >= 0 and b >= 0:
            return res[ min( a + 2, b + 3 ) : ]
        if a >= 0:
            return res[ a + 2 : ]
        if b >= 0:
            return res[ b + 3 : ]
        return res
    return ""

os.system( "sleep 1" )
session_id = request( 'localhost', 10000, "/new_session?type=test" )
print "session_id", session_id
print "req", request( 'localhost', 10000, "/cmd?session_id=" + session_id, "toto" )
