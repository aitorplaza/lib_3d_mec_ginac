#!/bin/bash

#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Library General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
#


if [ $# != 2 ]
then
   echo "Usage: $0 filename-es.mec filename-en.mec"
   echo
   echo "The comand overwrites filename-en.mec if it exists,  filename-es.mec and filename-en.mec can be the same file."
   exit
fi

if [ ! -e $1 ]
then
   echo "El fichero '$1' no existe."
   exit
fi

tmpFile=$1.$$.tmp

sed \
-e "/#include <math.h>/d" \
-e "/double _/d" \
-e "/void p(/d" \
-e "s/{/\/*{*\//g" \
-e "s/}/ \/*}*\//g" \
-e "/return/d" \
$1 > $tmpFile

cp -v $tmpFile $2
#echo "Borra fichero temporal '$tmpFile' ..."
rm $tmpFile
