echo Makefile > Metil.files
echo TODO.txt >> Metil.files
for d in src doc tests
do
    for t in '*.h'  '*.cpp' '*.cu' '*.txt' '*.py' '*.js' '*.html' '*.css' '*.files'
    do
        for i in `find $d -name "$t"`; do echo $i >> Metil.files; done
    done
done
