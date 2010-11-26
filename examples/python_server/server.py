# -*- coding: utf-8 -*-
import SocketServer
import cStringIO
import os, sys

def content_type( addr ):
    if addr.endswith( ".html" ):
        return "text/html"
    if addr.endswith( ".js" ):
        return "text/javascript"
    if addr.endswith( ".css" ):
        return "text/css"
    if addr.endswith( ".png" ):
        return "image/png"
    return "text/plain"
        
def to_js_string( data ):
    return data.replace( "\n", "\\n" ).replace( "'", "\\'" )
        
class MetilServer( SocketServer.BaseRequestHandler ):
    def exec_data( self, data ):
        self.request.send(
            "HTTP/1.0 200 Ok\r\n"
            "Content-Type: test/javascript\r\n"
            "\r\n"
        )
        
        globals()[ "request" ] = self.request
        sys.stdout = cStringIO.StringIO()
        sys.stderr = cStringIO.StringIO()
        try:
            exec data in globals()
        except Exception as e:
            print >> sys.stderr, e
        
        self.request.send(
            "c.out = '" + to_js_string( sys.stdout.getvalue().strip() ) + "';\r\n"
            "c.err = '" + to_js_string( sys.stderr.getvalue().strip() ) + "';\r\n"
        )
        
    def handle( self ):
        data = self.request.recv( 4096 )
        line = data[ 0 : data.find( "\n" ) ]
        addr = line.split()[ 1 ]
        if addr == "/":
            addr = "/index.html"

        if os.path.exists( "pages" + addr ):
            self.request.send(
                "HTTP/1.0 200 Ok\r\n" +
                "Content-Type: " + content_type( addr ) + "\r\n" +
                "\r\n" +
                file( "pages" + addr ).read()
            )
        elif addr == "/exec.py":
            pos = data.find( "\n\n" )
            if pos >= 0:
                self.exec_data( data[ pos + 2 : ] )
            pos = data.find( "\r\n\r\n" )
            if pos >= 0:
                self.exec_data( data[ pos + 4 : ] )
        else:
            self.request.send(
                "HTTP/1.0 404 Not Found\r\n"
                "\r\n"
            )
        

for PORT in range( 8000, 8010 ):
    try:
        socket_server = SocketServer.TCPServer( ( "", PORT ), MetilServer )
        
        print PORT
        #os.system( "rekonq http://localhost:" + str( PORT ) + " &" )
        #os.system( "chromium-browser --app=http://localhost:" + str( PORT ) + " &" )
        os.system( "firefox -jsconsole http://localhost:" + str( PORT ) + " &" )
        socket_server.serve_forever()
    except SocketServer.socket.error:
        continue
    break

