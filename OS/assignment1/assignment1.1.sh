while [ 1 -eq 1 ]
do
echo "\n\n1.Create Database\n2.View Database\n3.Insert A Record\n4.Delete A Record\n5.Modify A Record\n6.Result\n7.Exit\nEnter your choice : \c"
read ch
case $ch in
1) echo "Enter the filename : \c"
   read filename

   touch $filename;;
2) cat $filename;;
3) echo "Enter first name : \c"
   read fname
	 
   echo "Enter last name : \c"
   read lname
   
   echo "Enter mark M1 : \c"
   read m1
   
   echo "Enter mark M2 : \c"
   read m2
   
   echo "Enter mark M3 : \c"
   read m3
   
   echo "$fname | $lname | $m1 | $m2 | $m3 |" | cat >> $filename
   sort $filename > temp.lst
   cat temp.lst > $filename
   rm temp.lst;;
   
4) echo "Enter the firstname to delete : \c"
   read fname
   grep -v $fname $filename | tee temp.lst
   cat temp.lst > $filename
   rm temp.lst;;
   
5) echo "Enter the firstname to modify : \c"
   read fname

   echo "Enter the Modified Details..."
   
   echo "Enter mark M1 : \c"
   read m1
   x=`grep $fname $filename | cut -f3 -d "|"`
   
   echo "Enter mark M2 : \c"
   read m2
   y=`grep $fname $filename | cut -f4 -d "|"`
   
   echo "Enter mark M3 : \c"
   read m3
   z=`grep $fname $filename | cut -f5 -d "|"` 
   
   sed "s/$x/$m1/" $filename > temp.lst
   sed "s/$y/$m2/" temp.lst > $filename
   sed "s/$z/$m3/" $filename > temp.lst 
   sort temp.lst > $filename
	;;
6) echo "Enter the name of student : \c"
   read fname 
   x=`grep $fname $filename | cut -f3 -d "|"`   
   y=`grep $fname $filename | cut -f4 -d "|"`
   z=`grep $fname $filename | cut -f5 -d "|"` 
   
   temp=`expr $x + $y + $z`
   ans=`expr $temp / 3`
   echo "Your Result : $ans % \c"
   
   if [ $ans -lt 40 ]
   	then 
   	echo "Fail !"
   	
   	elif [ $ans -ge 40 -a $ans -lt 60 ]
   	then 
   	echo "Second Class !"
   	
   	elif [ $ans -ge 60 -a $ans -lt 800 ]
   	then 
   	echo "First Class !"
   	
   	elif [ $ans -ge 80 ]
   	then 
   	echo "Distinction !"
   	fi
	;;
7) rm $filename 
   exit;;
*);;
esac
done
