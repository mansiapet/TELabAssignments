Create table Stud_marks(roll int primary key, name varchar(20),totalmarks int);

insert into Stud_marks(roll,name,totalmarks) values (1,'Ayush',1000),(2,'Nilesh',950),(3,'Prabhu',875),(4,'Mansi',1200),(5,'Arinjay',875);

DELIMITER //
create procedure proc_Grade(IN rollno int, OUT grade varchar(50))
BEGIN
DECLARE studmarks int;
select totalmarks into studmarks from Stud_marks where roll=rollno;
IF studmarks between 990 and 1500 then
 SET grade='Distinction';
ELSEIF studmarks between 900 and 989 then  #ITS ELSEIF not ELSE IF
 SET grade='First Class';
ElSEIF studmarks between 825 and 899 then
 SET grade='Higher Second Class';
ELSE
  SET grade='Lower Class';
END IF;
END;
//

create function funcgrade(rollno INT)
RETURNS VARCHAR(50)
BEGIN

DECLARE Grade VARCHAR(50);
call proc_Grade(rollno,Grade);
RETURN GRADE;
END;

select roll, name,totalmarks,funcgrade(roll) as CLASS from Stud_marks;