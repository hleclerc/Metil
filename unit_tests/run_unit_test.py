# -*- coding: utf-8 -*-
import os, stat

def create_html_link( href, text ):
    return '<a href="' + href + '" > ' + text + ' </a>'

def create_html_image( href, alt='' ):
    return '<img src="' + href + '" alt="' + alt + '"> '

def extract_leaf( s ):
    i = s.rfind( '/' )
    if (i >= 0):
        return s[i+1: ]
    else:
        return s

class ReportOfSourceFile:
    def __init__( self, filenameCpp, compilationReturn ):
        self.filename_cpp      = filenameCpp[2:]  # [2:] pour enlever le ./
        self.filename_log      = filenameCpp[2:-4] + ".log"  # [2:] pour enlever le ./
        self.filename_log_cerr = filenameCpp[2:-4] + ".logcerr"  # [2:] pour enlever le ./
        if ( compilationReturn == 0 ):
            self.compilationResult = True
        else:
            self.compilationResult = False
        self.resultReport      = True & self.compilationResult
        self.compilationReturn = compilationReturn
        self.htmlReport        = ""
    def display( self ):
        print " source filename    = ", self.filename_cpp
        print " filename_log       = ", self.filename_log
        print " filename_log_cerr  = ", self.filename_log_cerr
        print " result             = ", self.resultReport
        print " compilation        = ", self.compilationResult
        print " compilation return = ", self.compilationReturn
        print " html               = <<<", self.htmlReport, ">>>"   
        

class Tests:
    def __init__( self, relative_dir_unit_test, list_dir_include = [] ):
        self.GlobalResult = True
        self.icon = [ '../doc/images/red.png', '../doc/images/green.png' ]
        self.iconDownload = '../doc/images/eye.png'
        self.textOfIcon = [ 'FAIL', 'OK' ]
        #self.command = 'metil_comp -DDEBUG_ALLOC_LEVEL_1 '
        self.command = 'metil_comp -DTESTING -DNO_SIG_NAN '
        for dir in list_dir_include:
            self.command = self.command + ' -I' + dir + ' '
        self.relative_dir_unit_test = relative_dir_unit_test
        self.listResult = []

    def find_and_exec( self, directory, list_forbidden_dir_source ):
        self.GlobalResult = True
        for filename_ in os.listdir( directory ):
            filename = directory + "/" + filename_
            if stat.S_ISDIR( os.stat( filename )[ stat.ST_MODE ] ) and filename_ not in list_forbidden_dir_source :
                self.find_and_exec( filename )
            elif filename[-4:] == ".cpp": 
                filename_log = filename[:-4] + ".log"
                filename_log_cerr = filename[:-4] + ".logcerr"
                compilation_res = os.system( self.command + filename + " > " + filename_log + "  2> " + filename_log_cerr )
                r = ReportOfSourceFile( filename, compilation_res )
                self.listResult.append( r )
                print filename + ' -> ' + str( compilation_res )
                if ( compilation_res == 0 ): # compilation réussie
                    entree = open( filename_log, 'r' )
                    tokens = entree.read().split()
                    entree.close()
                    nb_tokens = len ( tokens )
                    k = 0
                    ### analyse du fichier log
                    while ( k < nb_tokens ):
                        if (tokens[k] == '__UNIT_TESTING_REPORT__'):
                            ### détermination du nom du test
                            name_test = ""
                            if ( k + 1 < nb_tokens ) and tokens[k+1] == '@@':
                                k += 2
                                while ( k < nb_tokens ) and tokens[k] != '@@':
                                    name_test += tokens[k]
                                    name_test += ' '
                                    k += 1
                                k += 1
                            else:
                                name_test += tokens[k+1] 
                                k += 2 
                           
                            ### Nous cherchons ensuite le token >=>=>=> pour connaître le résultat du test
                            while ( k < nb_tokens ):
                                if (tokens[k] == '>=>=>=>' ):
                                    if ( tokens[k+1] == 'OK' ):
                                        j = 1
                                    else:
                                        j = 0
                                    self.GlobalResult &= j
                                    r.resultReport &= j
                                    r.htmlReport += ' <td> ' + name_test + ' </td> <td  align="center" >' + create_html_image( self.icon[j], tokens[k+1] ) + '</td> <td align="center" > ' + create_html_link( self.relative_dir_unit_test + r.filename_log, create_html_image( self.iconDownload ) ) + ' </td>\n\t</tr>\n'
                                    k += 1
                                    break
                                k += 1
                        k += 1

    def run( self, namefile_html, directory, list_forbidden_dir_source = [] ):
        self.find_and_exec( directory, list_forbidden_dir_source )
        html = file( namefile_html, "w" )
        html.write('\n<br>\n<br> Global Result   :  '+ create_html_image( self.icon[ self.GlobalResult ], self.textOfIcon[ self.GlobalResult ] ) + '\n<br>\n<br>Results :  \n<br>\n<br>' )
        html.write('\n\n<table cellpadding="2" width="100%" cellspacing="1" border="0" class="indextable" >\n\t<tr>\n\t\t<th class="titleheader" width="40%" align="left" > Source File Test </th> <th class="titleheader" width="15%" > Compilation </th> <th class="titleheader" width="15%" > Test Result </th> <th class="titleheader" align="center" width="15%" > Log File </th> <th class="titleheader" align="center" width="15%" > Log Cerr File </th>\n\t</tr>\n' )
        
        for r in self.listResult:
            #r.display()
            if not r.compilationResult:
                html.write( '\t<tr>\n\t\t<td>' + create_html_link( self.relative_dir_unit_test + r.filename_cpp, r.filename_cpp ) + ' </td> ' ) 
            else:
                html.write( '\t<tr>\n\t\t<td>' + create_html_link( '#' + r.filename_cpp, r.filename_cpp ) + ' </td> ' )
            html.write( '<td  align="center" > ' + create_html_image( self.icon[ r.compilationResult ], self.textOfIcon[ r.compilationResult ] ) +  ' </td> <td  align="center" > ' + create_html_image( self.icon[ r.resultReport ], self.textOfIcon[ r.resultReport ] ) + ' </td> <td align="center" > ' + create_html_link( self.relative_dir_unit_test + r.filename_log, create_html_image( self.iconDownload ) ) + ' </td> <td align="center" > ' + create_html_link( self.relative_dir_unit_test + r.filename_log_cerr, create_html_image( self.iconDownload ) ) + ' </td>\n\t</tr>\n' )
        html.write( '</table>\n<br>' )
        
        html.write('\n<br> Results by source file : \n<br>' )
        displayTable = False 
        for r in self.listResult:
            displayTable |= r.compilationResult
        if displayTable:
            for r in self.listResult:
                if r.compilationResult:
                    html.write('\n<br> <a name ="' + r.filename_cpp + '" > </a> ' + create_html_link( self.relative_dir_unit_test + r.filename_cpp, r.filename_cpp ) + ' : \n<br>\n<br>' )
                    html.write( '\n\n<table cellpadding="2" width="100%" cellspacing="1" border="0" class="indextable" >\n\t<tr>\n\t\t<th class="titleheader" width="70%"  align="left" > Test </th> <th class="titleheader" width="15%"  align="center" > Result </th> <th class="titleheader" width="15%"  align="center" > Log File </th>\n\t</tr>\n' )
                    html.write( r.htmlReport )
                    html.write( '</table>\n<br>\n<br>' )
        else:
            html.write( 'No result\n<br>\n<br>\n<br>' )
    
t = Tests( "../unit_tests/", [ os.getcwd() + "/../src/" ] )
t.run( "report.html", ".", [ "compilations" ] )

