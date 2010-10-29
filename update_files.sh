echo Makefile > Metil.files
for d in src doc
do
    for t in '*.h'  '*.cpp' '*.cu' '*.txt' '*.py' '*.js' '*.html' '*.css'
    do
        for i in `find $d -name "$t"`; do echo $i >> Metil.files; done
    done
done
