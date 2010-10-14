var old_x = 0, old_y = 0;
var button = "none";
var delay_send = 2000; ///< nb msec to send an img request to the server

//Object.prototype.clone = function() {
//   var newObj = ( this instanceof Array ) ? [] : {};
//   for ( i in this ) {
//       if ( i == 'clone' )
//           continue;
//       if ( this[ i ] && typeof this[ i ] == 'object' )
//           newObj[ i ] = this[ i ].clone();
//       else
//           newObj[ i ] = this[ i ];
//   } return newObj;
//};

function equal_obj( a, b ) {
   if( typeof( a ) != 'object' || a == null )
       return a == b;
   for( var i in a )
       if ( ! equal_obj( a[ i ], b[ i ] ) )
           return 0;
   return 1;
}

function sub_3( a, b ) {
    return [ a[ 0 ] - b[ 0 ], a[ 1 ] - b[ 1 ], a[ 2 ] - b[ 2 ] ];
}

function add_3( a, b ) {
    return [ a[ 0 ] + b[ 0 ], a[ 1 ] + b[ 1 ], a[ 2 ] + b[ 2 ] ];
}

function mus_3( a, b ) { // mul by scalar
    return [ a * b[ 0 ], a * b[ 1 ], a * b[ 2 ] ];
}

function dot_3( a, b ) {
    return a[ 0 ] * b[ 0 ] + a[ 1 ] * b[ 1 ] + a[ 2 ] * b[ 2 ];
}

function cro_3( a, b ) {
    return [ a[ 1 ] * b[ 2 ] - a[ 2 ] * b[ 1 ], a[ 2 ] * b[ 0 ] - a[ 0 ] * b[ 2 ], a[ 0 ] * b[ 1 ] - a[ 1 ] * b[ 0 ] ];
}

function len_3( a ) {
    return Math.sqrt( a[ 0 ] * a[ 0 ] + a[ 1 ] * a[ 1 ] + a[ 2 ] * a[ 2 ] );
}

function nor_3( a ) {
    var ld = 1 / len_3( a );
    return [ a[ 0 ] * ld, a[ 1 ] * ld, a[ 2 ] * ld ];
}

function rot_3( V, R ) {
    var a = len_3( R ) + 1e-40;
    var x = R[ 0 ] / a;
    var y = R[ 1 ] / a;
    var z = R[ 2 ] / a;
    var c = Math.cos( a );
    var s = Math.sin( a );
    return [
        ( x*x+(1-x*x)*c ) * V[ 0 ] + ( x*y*(1-c)-z*s ) * V[ 1 ] + ( x*z*(1-c)+y*s ) * V[ 2 ],
        ( y*x*(1-c)+z*s ) * V[ 0 ] + ( y*y+(1-y*y)*c ) * V[ 1 ] + ( y*z*(1-c)-x*s ) * V[ 2 ],
        ( z*x*(1-c)-y*s ) * V[ 0 ] + ( z*y*(1-c)+x*s ) * V[ 1 ] + ( z*z+(1-z*z)*c ) * V[ 2 ]
    ];
}

function rotate_cam( cam_data, x, y, z ) {
    var R = cam_data.IP.s_to_w_vec( [ x, y, z ] );

    cam_data.IP.X = rot_3( cam_data.IP.X, R );
    cam_data.IP.Y = rot_3( cam_data.IP.Y, R );
    cam_data.IP.O = add_3( cam_data.C, rot_3( sub_3( cam_data.IP.O, cam_data.C ), R ) );

}

function get_T_from_I( src, oi ) {
    var m = src[ oi + 0 ] / 16777216 + src[ oi + 1 ] / 65536 + src[ oi + 2 ] / 256;
    var e = ( 256 * src[ oi + 5 ] + src[ oi + 4 ] ) - 32768;
    var s = src[ oi + 6 ];
    return ( s ? -1.0 : 1.0 ) * m * Math.pow( 2.0, e );
}

function get_I_from_I( src, oi ) {
    return src[ oi + 0 ] + src[ oi + 1 ] * 256 + src[ oi + 2 ] * 65536;
}

function draw_img_on_canvas( canvas ) {
    var w = canvas.width;
    var h = canvas.height;
    var mwh = Math.min( w, h );
    var off_zznv = 4 * w * h;

    var ctx = canvas.getContext( '2d' );
    var lineargradient = ctx.createLinearGradient( 0, 0, 0, h );
    lineargradient.addColorStop( 0.0, "rgb( 0, 0, 0 )" );
    lineargradient.addColorStop( 0.5, "rgb( 0, 0, 40 )" );
    lineargradient.addColorStop( 1.0, "rgb( 0, 0, 150 )" );
    ctx.fillStyle = lineargradient;
    ctx.fillRect( 0, 0, w, h );

    if ( equal_obj( canvas.cam_data.IP, canvas.cam_data.RP ) ) {
        ctx.drawImage(
            canvas.cam_data.img_rgba,
            0, 0, w, 3 * h + 1
        );
    } else {
        // copy img in hidden canvas
        var hidden_src_canvas = canvas.cam_data.hidden_src_canvas;
        var hidden_ctx = hidden_src_canvas.getContext('2d');
        if ( hidden_src_canvas.there_s_a_new_img ) {
            hidden_src_canvas.there_s_a_new_img = false;
            hidden_src_canvas.width  = w;
            hidden_src_canvas.height = 3 * h + 1;
            hidden_ctx.drawImage( canvas.cam_data.img_rgba, 0, 0 );
        }
        var src_pix = hidden_ctx.getImageData( 0, 0, w, 3 * h + 1 );
        var src_data = src_pix.data;

        var old_d = canvas.cam_data.RP.d;
        var new_d = canvas.cam_data.IP.d;
        var old_p = Math.tan( canvas.cam_data.RP.a * 3.14159 / 180 ) / mwh;
        var new_p = Math.tan( canvas.cam_data.IP.a * 3.14159 / 180 ) / mwh;
        var old_O = canvas.cam_data.RP.O, old_X = canvas.cam_data.RP.X, old_Y = canvas.cam_data.RP.Y, old_Z = cro_3( old_Y, old_X );
        var new_O = canvas.cam_data.IP.O, new_X = canvas.cam_data.IP.X, new_Y = canvas.cam_data.IP.Y, new_Z = cro_3( new_Y, new_X );

        var oi = 4 * 3 * w * h;
        var z_min = get_T_from_I( src_data, oi + 0  );
        var z_max = get_T_from_I( src_data, oi + 8  );
        var rz_mi = get_I_from_I( src_data, oi + 16 );
        var rz_ma = get_I_from_I( src_data, oi + 20 );
        var z_mi  = ( ( rz_mi - 1.0 ) / 65534.0 * ( z_max - z_min ) + z_min ); // screen space
        var z_ma  = ( ( rz_ma - 1.0 ) / 65534.0 * ( z_max - z_min ) + z_min );

        var t0 = new Date().getTime();
        var size_rect = canvas.cam_data.size_disp_rect;
        for( var y = 0; y < h; y += size_rect ) {
            var y_s = y - h / 2 + size_rect / 2.0;
            var y_r = y_s * new_d / mwh;
            for( var x = 0; x < w; x += size_rect ) {
                var x_s = ( x - w / 2 + size_rect / 2.0 );
                var x_r = x_s * new_d / mwh;

                //
                var new_P = [
                    new_O[ 0 ] + x_r * new_X[ 0 ] + y_r * new_Y[ 0 ],
                    new_O[ 1 ] + x_r * new_X[ 1 ] + y_r * new_Y[ 1 ],
                    new_O[ 2 ] + x_r * new_X[ 2 ] + y_r * new_Y[ 2 ]
                ];
                var new_D = nor_3( [
                    new_Z[ 0 ] + new_p * ( x_s * new_X[ 0 ] + y_s * new_Y[ 0 ] ),
                    new_Z[ 1 ] + new_p * ( x_s * new_X[ 1 ] + y_s * new_Y[ 1 ] ),
                    new_Z[ 2 ] + new_p * ( x_s * new_X[ 2 ] + y_s * new_Y[ 2 ] )
                ] );

                // new_P
                var d_mi = ( z_mi * old_d / mwh - dot_3( new_P, old_Z ) ) / dot_3( new_D, old_Z );
                var d_ma = ( z_ma * old_d / mwh - dot_3( new_P, old_Z ) ) / dot_3( new_D, old_Z );

                var inter_mi = [
                    new_P[ 0 ] + d_mi * new_D[ 0 ] - old_O[ 0 ],
                    new_P[ 1 ] + d_mi * new_D[ 1 ] - old_O[ 1 ],
                    new_P[ 2 ] + d_mi * new_D[ 2 ] - old_O[ 2 ]
                ];

                var inter_ma = [
                    new_P[ 0 ] + d_ma * new_D[ 0 ] - old_O[ 0 ],
                    new_P[ 1 ] + d_ma * new_D[ 1 ] - old_O[ 1 ],
                    new_P[ 2 ] + d_ma * new_D[ 2 ] - old_O[ 2 ]
                ];

                var x_mi = w / 2 + dot_3( inter_mi, old_X ) * mwh / old_d, y_mi = h / 2 + dot_3( inter_mi, old_Y ) * mwh / old_d;
                var x_ma = w / 2 + dot_3( inter_ma, old_X ) * mwh / old_d, y_ma = h / 2 + dot_3( inter_ma, old_Y ) * mwh / old_d;
                x_mi /= 1.0 + old_p * z_mi; y_mi /= 1.0 + old_p * z_mi;
                x_ma /= 1.0 + old_p * z_ma; y_ma /= 1.0 + old_p * z_ma;

                var d_mm = Math.max( Math.abs( x_ma - x_mi ), Math.abs( y_ma - y_mi ) ) + 1e-40;
                for( var i = 0.0; i <= d_mm; i += 1.0 ) {
                    var x_md = Math.round( x_mi + i / d_mm * ( x_ma - x_mi ) );
                    var y_md = Math.round( y_mi + i / d_mm * ( y_ma - y_mi ) );
                    var z_md = z_mi + i / d_mm * ( z_ma - z_mi );
                    if ( x_md >= 0 && x_md < w && y_md >= 0 && y_md < h ) {
                        var o = 4 * ( y_md * w + x_md );
                        var zu = src_data[ off_zznv + o + 0 ] + src_data[ off_zznv + o + 1 ] * 256;
                        if ( zu != 65535 ) {
                            var z = z_min + zu / 65534.0 * ( z_max - z_min );
                            if ( z <= z_md ) {
                                var r = src_data[ off_zznv + o + 1 ], g = r, b = r;
                                // var r = src_data[ o + 0 ];
                                // var g = src_data[ o + 1 ];
                                // var b = src_data[ o + 2 ];
                                // var a = src_data[ o + 3 ];
                                ctx.fillStyle = "rgb( " + r + ", " + g + ", " + b + " )";
                                ctx.fillRect( x, y, size_rect, size_rect );
                                break;
                            }
                        }
                    }
                }
            }
        }

        var t1 = new Date().getTime() - t0;
        document.getElementById("com").firstChild.data = pz_mi + " <> " + pz_ma + " <> " + t1;
    }

}

function update_img_src( canvas ) { // draw_canvas
    // update transformation matrix
    if ( ! canvas.cam_data.C ) {
        var c_x = 0.5 * ( canvas.cam_data.max_pos[ 0 ] + canvas.cam_data.min_pos[ 0 ] );
        var c_y = 0.5 * ( canvas.cam_data.max_pos[ 1 ] + canvas.cam_data.min_pos[ 1 ] );
        var c_z = 0.5 * ( canvas.cam_data.max_pos[ 2 ] + canvas.cam_data.min_pos[ 2 ] );
        var d_x = canvas.cam_data.max_pos[ 0 ] - canvas.cam_data.min_pos[ 0 ];
        var d_y = canvas.cam_data.max_pos[ 1 ] - canvas.cam_data.min_pos[ 1 ];
        var d_z = canvas.cam_data.max_pos[ 2 ] - canvas.cam_data.min_pos[ 2 ];
        var d_m = Math.max( d_x, Math.max( d_y, d_z ) );
        if ( ! d_m )
            d_m = 1.0;

        canvas.cam_data.C = [ c_x, c_y, c_z ];

        canvas.cam_data.IP = {
            O : [ c_x, c_y, c_z ],
            X : [ 1.0, 0.0, 0.0 ],
            Y : [ 0.0, 1.0, 0.0 ],
            d : 1.5 * d_m,
            a : 10,
            s_to_w_vec : function( V ) { ///< screen orientation to real world.
                var Z = cro_3( this.Y, this.X );
                return [
                    V[ 0 ] * this.X[ 0 ] + V[ 1 ] * this.Y[ 0 ] + V[ 2 ] * Z[ 0 ],
                    V[ 0 ] * this.X[ 1 ] + V[ 1 ] * this.Y[ 1 ] + V[ 2 ] * Z[ 1 ],
                    V[ 0 ] * this.X[ 2 ] + V[ 1 ] * this.Y[ 2 ] + V[ 2 ] * Z[ 2 ]
                ];
            }
        };
    }

    //
    var img_src = "img?mode=get_img";
    img_src += "&counter=" + new Date().getTime();
    img_src += "&s=" + canvas.cam_data.img_session_id;
    img_src += "&w=" + canvas.width;
    img_src += "&h=" + canvas.height;
    img_src += "&O=" + canvas.cam_data.IP.O;
    img_src += "&X=" + canvas.cam_data.IP.X;
    img_src += "&Y=" + canvas.cam_data.IP.Y;
    img_src += "&d=" + canvas.cam_data.IP.d;
    img_src += "&a=" + canvas.cam_data.IP.a;

    //
    canvas.cam_data.img_rgba = new Image();
    canvas.cam_data.img_rgba.onload = function() {
        canvas.cam_data.hidden_src_canvas.there_s_a_new_img = true;
        canvas.cam_data.RP = canvas.cam_data.IP.clone();
        draw_img_on_canvas( canvas );
    }
    canvas.cam_data.img_rgba.src = img_src;
}


function restart_timer_until_src_update( canvas ) {
    if ( canvas.cam_data.current_timer_until_src_update )
        clearTimeout( canvas.cam_data.current_timer_until_src_update );
    canvas.cam_data.current_timer_until_src_update = setTimeout( function() { update_img_src( canvas ); }, delay_send );
}


function img_mouse_down( evt ) {
    if ( ! evt ) evt = window.event;

    // code from http://unixpapa.com/js/mouse.html
    if ( evt.which == null )
        button = ( evt.button < 2 ) ? "LEFT" : ( ( evt.button == 4 ) ? "MIDDLE" : "RIGHT" );
    else
        button = ( evt.which  < 2 ) ? "LEFT" : ( ( evt.which  == 2 ) ? "MIDDLE" : "RIGHT" );

    this.onmousemove = img_mouse_move;
    this.onmouseout  = img_mouse_out;
    old_x = evt.clientX - this.offsetLeft;
    old_y = evt.clientY - this.offsetTop;

    if( evt.preventDefault ) evt.preventDefault();
    evt.returnValue = false;
    return false;
}

function img_mouse_up( evt ) {
    this.onmousemove = null;
}

function img_mouse_out( evt ) {
    this.onmousemove = null;
}

function img_mouse_move( evt ) {
    if ( ! evt ) evt = window.event;

    var new_x = evt.clientX - this.offsetLeft;
    var new_y = evt.clientY - this.offsetTop ;
    if ( new_x == old_x && new_y == old_y )
        return;

    var mwh = Math.min( this.width, this.height );
    if ( button == "LEFT" ) { // rotate
        if ( evt.shiftKey ) {
            var a = Math.atan2( new_y - h / 2.0, new_x - w / 2.0 ) - Math.atan2( old_y - h / 2.0, old_x - w / 2.0 );
            rotate_cam( this.cam_data, 0.0, 0.0, a );
        } else {
            var x = 2.0 * ( old_x - new_x ) / mwh;
            var y = 2.0 * ( new_y - old_y ) / mwh;
            rotate_cam( this.cam_data, y, x, 0.0 );
        }
    } else if ( button == "MIDDLE" ) { // pan
        var x = this.cam_data.IP.d * ( new_x - old_x ) / mwh;
        var y = this.cam_data.IP.d * ( new_y - old_y ) / mwh;
        for( var d = 0; d < 3; ++d )
            this.cam_data.IP.O[ d ] -= x * this.cam_data.IP.X[ d ] + y * this.cam_data.IP.Y[ d ];
    }

    draw_img_on_canvas( this );
    restart_timer_until_src_update( this );

    old_x = new_x;
    old_y = new_y;
}

function img_mouse_wheel( evt ) {
    if ( ! evt ) evt = window.event;

    // browser compatibility -> stolen from http://unixpapa.com/js/mouse.html
    var delta = 0;
    if ( evt.wheelDelta ) {
        delta = evt.wheelDelta / 120.0;
        if ( window.opera )
            delta = - delta;
    } else if ( evt.detail )
        delta = - evt.detail / 3.0;

    //
    var coeff = Math.pow( 1.2, delta );

    // get position of the click in the real world
    var mwh = Math.min( this.width, this.height );
    var x = ( evt.clientX - this.offsetLeft - this.width  / 2 ) * this.cam_data.IP.d / mwh;
    var y = ( evt.clientY - this.offsetTop  - this.height / 2 ) * this.cam_data.IP.d / mwh;
    var O = this.cam_data.IP.O;
    var X = this.cam_data.IP.X;
    var Y = this.cam_data.IP.Y;
    var P = [ O[ 0 ] + x * X[ 0 ] + y * Y[ 0 ], O[ 1 ] + x * X[ 1 ] + y * Y[ 1 ], O[ 2 ] + x * X[ 2 ] + y * Y[ 2 ] ];

    // update cam_data
    this.cam_data.IP.d /= coeff;
    for( var d = 0; d < 3; d += 1 )
        this.cam_data.IP.O[ d ] = P[ d ] + ( O[ d ] - P[ d ] ) / coeff;

    // redraw
    draw_img_on_canvas( this );
    restart_timer_until_src_update( this );

    if( evt.preventDefault ) evt.preventDefault();
    evt.returnValue = false;
}


function rot_img( canvas, x, y, z ) {
    rotate_cam( canvas.cam_data, x, y, z );
    update_img_src( canvas );
}


function reg_mesh( canvas_name, name ) {
    // canvas = document.getElementById( canvas_name );
    // send_async_xml_http_request( "img?mode=add_meshes&s=" + canvas.cam_data.img_session_id + "&names=" + name, function ( rep ) { eval( rep ); } );
    queue_python_cmd( 'b = BasicMesh()' );
    queue_python_cmd( 'b.add_node( 0, 0, 0 )' );
    queue_python_cmd( 'b.add_node( 1, 0, 0 )' );
    queue_python_cmd( 'b.add_node( 0, 1, 0 )' );
    queue_python_cmd( 'b.add_triangle( 0, 1, 2 )' );
    queue_python_cmd( 'c = make_cs( b, MachineId.gpu( 0 ) )' );
    queue_python_cmd( 'd = DisplayItem_BasicMesh( c )' );
    queue_python_cmd( 'cst_obj.append( c )' );
    queue_python_cmd( 'cst_obj.append( d )' );
    queue_python_cmd( canvas_name + '.add_item( d )' );
}

function fit_img( canvas_name ) {
    queue_python_cmd( canvas_name + '.fit()' );
}

function display_img( canvas_name ) {
    queue_python_cmd( canvas_name + '.render()' );
    queue_python_cmd( canvas_name + '.copy_gpu_to_cpu()' );
    queue_python_cmd( canvas_name + '.save_png( "test.png" )' );
    queue_python_cmd( 'import os' );
    queue_python_cmd( 'os.system( "display test.png" )' );
    send_python_cmds();
    // send_async_xml_http_request( "exec.py", src, function ( rep ) { c = {}; eval( rep ); } );
}

function img_init( canvas_name ) {
    canvas = document.getElementById( canvas_name );

    if ( canvas.addEventListener )
        canvas.addEventListener( "DOMMouseScroll", img_mouse_wheel, false );
    canvas.onmousedown  = img_mouse_down;
    canvas.onmouseup    = img_mouse_up;
    canvas.onmousewheel = img_mouse_wheel;
    canvas.onkeypress   = function ( evt ) { rot_img( canvas, 0, 0, 0.1 ); }

    canvas.cam_data = {
        size_disp_rect : 5,
    };

    canvas.cam_data.hidden_src_canvas = document.createElement("canvas");
    canvas.cam_data.hidden_src_canvas.style.display = "none";
    document.body.appendChild( canvas.cam_data.hidden_src_canvas );

    // first python commands
    queue_python_cmd( "from server_objects import *" );
    queue_python_cmd( canvas.id + " = BitmapDisplay()" );
    queue_python_cmd( "cst_obj = []" );
}
