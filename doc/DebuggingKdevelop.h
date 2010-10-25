/*!

\page DebuggingKdevelopPage Debugging with Kdevelop

    @section DebuggingKdevelopOption
    
        - Go to the menu item Project > Project Options > Run Options and in the edit line Executable, set : PATH/MAIN where PATH is the path of your executable and MAIN its name.
        
        - Go to the menu item Project > Project Options > Debugger and set the edit line Debugger Executable at /usr/bin/gdb or the absolute path of your gdb.
        
        It's finish !
        
    @section RunningDebbugingSession Running a debbuging session
     
        you can put breakpoint at left of a line with the mousse ( right click ).
        Thus you compile your program F8 and launch it F9. So the debugger stop on the first breakpoint and you ca read the value of local variables in the window Variables ( at left ).
        To stop, click in the red cross icon. 
          
        @image html kdevelopCapture.jpg
        
        
        
*/
