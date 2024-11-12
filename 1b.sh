create()
{
echo "** Create Database **";
db=stud
touch $db
echo "database created successfully";
}

# Function to display the database
show()
{
db=stud
echo "** Display Database **";
echo "Records present in current database $db are as follows";
echo "********";

cat "$db"

echo "********";
echo "Thank you";
}

# Function to insert record in given database
insert()
{
db=stud;
echo "*Insert Record ****";
echo "How many records you want to enter";
read no
while [ $no -gt 0 ]
do
echo "enter the Name email and address of the student";
read name email address
record=$name"|"$email"|"$address;
echo "$record" >> "$db" 
echo "Record inserted successfully";
no=$(($no - 1));
done
}

delete()
{
echo "** Delete Record***";
echo "enter the name of student to delete particular record";
read name1
if grep -i "$name1" "$db"
then
sed -i "/$name1/d" "$db"
echo "record deleted successfully";
else
echo "record not found in database"
fi
}

search()
{
echo "*Search Record ****";
echo "enter the name of student to be search in given database";
read name

if grep -i "$name" "$db";

then
echo "record found in given database";
else
echo "record not matched so search again";
fi

}

modify()
{
echo "*Modify Record ****";
echo "enter the name of student in record to be modify";
read name
if grep -i "$name" "$db"
then
echo "record found you can modify now";
#now you can delete previous record and insert new to modify it
sed -i "/$name/d" "$db"
echo "enter the correct Name, email and address of the student";
read name email address
record=$name"|"$email"|"$address ;
echo "$record" >> "$db" 
echo "Record modified successfully";
else
echo "record cannot modify as it is not found in database";
fi

}


Menu="1)Create Database
2)Display Database
3)Insert Record
4)Delete Record
5)Search Record
6)Modify Record
7)Exit";
clear
echo "**Menu***"
while true
do
echo "$Menu";
echo "Please enter your choice";
read ch
case $ch in
1) create
;;
2) show
;; 
3) insert
;;
4) delete
;;
5) search
;;
6) modify
;;
7) exit
;;
*) echo "you entered wrong choice please enter again from 1 to 7"; 
;;
esac
done
