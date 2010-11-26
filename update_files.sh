echo Makefile > Metil.files
echo TODO.txt >> Metil.files
for d in src doc tests unit_tests
do
    for t in '*.h'  '*.cpp' '*.cu' '*.txt' '*.py' '*.js' '*.html' '*.css' '*.files' '*.i'
    do
        for i in `find $d -name "$t" -a -not -wholename "*/compilations/*"`
        do
            echo $i >> Metil.files
        done
    done
done
