var key_down_beg_repeat = 300;
var key_down_con_repeat =  30;
var timer_key_down = null;
var python_commands = "";

function my_xml_http_request() {
    if( window.XMLHttpRequest ) // Firefox
        return new XMLHttpRequest();
    if ( window.ActiveXObject ) // Internet Explorer
        return new ActiveXObject("Microsoft.XMLHTTP");
    alert("Votre navigateur ne supporte pas les objets XMLHTTPRequest...");
}

function send_async_xml_http_request( url, data, func ) {
    var xhr_object = my_xml_http_request();
    xhr_object.open( "POST", url, true );
    xhr_object.onreadystatechange = function() {
        if( this.readyState == 4 && this.status == 200 )
            func( this.responseText );
    };
    xhr_object.send( data );
}

function queue_python_cmd( cmd ) {
    python_commands += cmd + "\n";
}

function exec_python_cmds() {
    send_async_xml_http_request( "exec.py", python_commands, function( rep ) {
        c = {};
        alert( rep );
        eval( rep );
        if ( c.err && c.err.length )
            alert( c.err );
    } );
    python_commands = "";
}

function get_login() {
    return "<b>login@sc:$</b> ";
}

function code_to_html( code ) {
    return code.replace( / /gi, "&nbsp;" ).replace( /\n/gi, "<br/>" );
}

function update_text( doc ) {
    txt = "<tt>";
    for( var i in doc.lines ) {
        var item = doc.lines[ i ];
        if ( i != 0 )
            txt += "<br/>";
        txt += item.prompt

        txt += code_to_html( item.cmd.slice( 0, item.cursor ) );
        txt += '<u>'; //  class="cursor"
        txt += code_to_html( item.cursor < item.cmd.length ? item.cmd.charAt( item.cursor ) : " " );
        txt += '</u>';
        txt += code_to_html( item.cmd.slice( item.cursor + 1 ) );

        if ( item.out )
            txt += "<br/>" + code_to_html( item.out );
        if ( item.err )
            txt += "<br/>" + code_to_html( item.err );
    }
    txt += "</tt>";

    //
    doc.open();
    doc.write( txt );
    doc.close();

    doc.frame.contentWindow.scrollTo( 0, doc.height );
}

function new_line() {
    return { cmd : "", cursor : 0, prompt : get_login() };
}

function key_up( evt ) {
    if ( timer_key_down != null ) {
        clearTimeout( timer_key_down );
        timer_key_down = null;
    }
}

function key_down( evt ) {
    var event = evt || window.event;
    var repaint = false;
    var caught  = false;
    var doc = this;
    var current_line = doc.lines[ doc.lines.length - 1 ];

    // cur to previous word
    function l_cur( cmd, cursor ) {
        if ( cursor )
            cursor -= 1;
        // skip the spaces
        while ( cursor > 0 && cmd[ cursor ] == " " )
            cursor -= 1;
        // skip the word
        while ( cursor > 0 && cmd[ cursor - 1 ] != " " )
            cursor -= 1;
        return cursor;
    }
    
    // cur to next word
    function r_cur( cmd, cursor ) {
        // skip the word
        while ( cursor < cmd.length && cmd[ cursor ] != " " )
            cursor += 1;
        // skip the spaces
        while ( cursor < cmd.length && cmd[ cursor ] == " " )
            cursor += 1;
        return cursor;
    }

    // current_line.cmd += event.keyCode;
    switch ( event.keyCode ) {
        case 13: // CR
            // new prompt
            doc.lines.push( new_line() );

            // send a request -> repaint
            send_async_xml_http_request( "exec.py", current_line.cmd, function( rep ) {
                var c = current_line;
                eval( rep );
                update_text( doc );
                doc.onkeydown  = key_down;
                doc.onkeypress = null;
            } );
        case 0 : // ?
        case 16: // shift
        case 17: // ctrl
        case 18: // meta
            doc.onkeydown  = key_down;
            doc.onkeypress = null;
            event.preventDefault();
            return false;

        case 9 : // tab
        case 20: // caps-lock
        case 27: // esc
            caught = true;
            break;
        case 8 : // backspace
            if ( event.ctrlKey ) {
                var old_cursor = current_line.cursor;
                current_line.cursor = l_cur( current_line.cmd, current_line.cursor );
                current_line.cmd = current_line.cmd.slice( 0, current_line.cursor ) + current_line.cmd.slice( old_cursor );
            } else {
                current_line.cmd = current_line.cmd.slice( 0, current_line.cursor - 1 ) + current_line.cmd.slice( current_line.cursor );
                current_line.cursor = Math.max( current_line.cursor - 1, 0 );
            }
            repaint = true;
            break;
        case 46: // suppr
            if ( event.ctrlKey ) {
                var new_cursor = r_cur( current_line.cmd, current_line.cursor );
                current_line.cmd = current_line.cmd.slice( 0, current_line.cursor ) + current_line.cmd.slice( new_cursor );
            } else
                current_line.cmd = current_line.cmd.slice( 0, current_line.cursor ) + current_line.cmd.slice( current_line.cursor + 1 );
            repaint = true;
            break;
        case 36: // beg line
            current_line.cursor = 0;
            repaint = true;
            break;
        case 35: // end line
            current_line.cursor = current_line.cmd.length;
            repaint = true;
            break;
        case 38: // up
            current_line.cursor = Math.min( current_line.cmd.length, current_line.cursor + 1 );
            repaint = true;
            break;
        case 40: // down
            current_line.cursor = Math.max( 0, current_line.cursor - 1 );
            repaint = true;
            break;
        case 37: // left
            if ( event.ctrlKey )
                current_line.cursor = l_cur( current_line.cmd, current_line.cursor );
            else
                current_line.cursor = Math.max( 0, current_line.cursor - 1 );
            repaint = true;
            break;
        case 39: // right
            if ( event.ctrlKey )
                current_line.cursor = r_cur( current_line.cmd, current_line.cursor );
            else
                current_line.cursor = Math.min( current_line.cmd.length, current_line.cursor + 1 );
            repaint = true;
            break;
        case 86: // V
            if ( event.ctrlKey ) {
                txt = window.clipboardData.getData( "Text" );
                current_line.cmd += txt;
                current_line.cursor += txt.length;
                repaint = true;
            }
            break;
    }

    //
    if ( repaint )
        update_text( this );

    //
    if ( caught || repaint ) {
        this.onkeydown  = key_down;
        this.onkeypress = null;
        this.onkeyup    = key_up;
        event.preventDefault();
        
        dur = timer_key_down != null ? key_down_con_repeat : key_down_beg_repeat;
        timer_key_down = setTimeout( function() {
            if ( timer_key_down != null )
                doc.onkeydown( evt );
        }, dur );
        return false;
    }

    this.onkeydown  = key_down ;
    this.onkeypress = key_press;
    return true; // because we want keypress
}

function key_press( evt ) {
    var event = evt || window.event;
    var current_line = this.lines[ this.lines.length - 1 ];

    var old_cmd = current_line.cmd;
    current_line.cmd = old_cmd.slice( 0, current_line.cursor );
    current_line.cmd += String.fromCharCode( event.which || event.charCode ); //
    current_line.cmd += old_cmd.slice( current_line.cursor, old_cmd.length );
    current_line.cursor += 1;
    // current_line.cmd += event.keyCode;

    update_text( this );

    this.onkeydown  = key_down ;
    this.onkeypress = key_press;
    event.preventDefault();
    return false;
}

function init_frame_as_terminal( name ) {
    var my_frame = document.getElementById( name );
    var doc = my_frame.contentDocument;
    if ( ! doc )
        doc = my_frame.contentWindow.document;
    doc.frame = my_frame;
    doc.lines = [ new_line() ];
    update_text( doc );

    doc.onkeydown  = key_down ;
    my_frame.style.visibility = "visible";
}





