while [ 1 -eq 1 ]
do
echo "\n\n1.Create Database\n2.View Database\n3.Insert A Record\n4.Delete A Record\n5.Modify A Record\n6.Exit\nEnter your choice :\c"
echo "\n"
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
   
   echo "Enter city : \c"
   read city
   
   echo "$fname | $lname | $city" | cat >> $filename
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

   z=`grep $fname $filename | cut -f3 -d "|"`

   echo "Enter the Modified Details...\nEnter city name : \c"
   read  cname
	 
   #echo "Enter last name : \c"
   #read  nlname
   
   #echo "Enter city : \c"
   #read  ncity
   
   sed "s/$z/$cname/" $filename > temp.lst
   sort temp.lst > $filename
	;;
6) rm $filename 
   exit;;
*);;
esac
done
