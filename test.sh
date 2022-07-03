#!/bin/bash

count=`ls -1 src/*.c 2>/dev/null | wc -l`

if [ $count == 0 ] ; then
    cat ./badfile.txt
    echo ""
    echo "         No pude encontrar tus archivos."
    echo "  ¿Seguro que el zip tiene el formato correcto?"
    echo ""
    echo "Asegurate de no tener un directorio extra en el zip."
    echo ""
fi

if [ -f "tree.txt" ] ; then
    echo "Archivos Entregados"
    echo "==================="
    echo ""
    cat "tree.txt"
    echo ""
fi

echo "Compilación y pruebas"
echo "====================="
echo ""

make -f makefile-chanutron clean    2>&1
make -f makefile-chanutron valgrind 2>&1

RETVAL=$?

if [ $RETVAL  -ne 0 ]; then
    exit 1;
fi

echo ""
echo "Parece que tu TP pasa todas las pruebas."
echo ""
cat success.txt

exit 0
