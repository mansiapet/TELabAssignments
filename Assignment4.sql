create database Practical;
use Practical;

#ASSIGNMENT4
create table Borrower(Roll_no int Primary key,Name varchar(30),DateofIssue DATE,Book_name varchar(20),Status varchar(1) default 'I');
create table Fine(Roll_no INT, Fine_date DATE, Amt int, foreign key(Roll_no) references Borrower(Roll_no));
insert into Borrower(Roll_no,Name,DateofIssue,Book_name) values (1,'Sam','2024-08-30',"The Book of Fantasy"),
 (2,'Prabhu','2024-09-10',"The Alchemist"),
(3,'Nilesh','2024-09-02',"The Hobbit"),
 (4,'Mansi','2024-08-27',"Lord of the Rings"),
 (5,'Arinjay','2024-09-05',"Rich Dad Poor Dad"),
 (6,'Drishti','2024-08-28',"48 Laws of Power");
 
 DELIMITER //
 
 Create procedure calc_fine1(IN rollno INT, IN bookname varchar(20))
 BEGIN
 DECLARE idate DATE;
 DECLARE day INT;
 DECLARE fine INT DEFAULT 0;
 DECLARE v_fine_threshold INT default 1000;
 
 Select DateofIssue into idate from Borrower where Roll_no=rollno and Book_name=bookname;
 IF idate is NULL then
    SIGNAL sqlstate '45000' set message_text="Record not found of given roll number and name";
END IF;

set day=DATEDIFF(curdate(),idate);

IF day between 15 and 30 then
  SET fine=day*5;
ELSEIF day>30 then
  SET fine=(30*5)+((day-30)*50);
END IF;

IF fine>v_fine_threshold then
   SIGNAL SQLSTATE '45000' set message_text=" Fine exceeds allowable threshold";
ELSE 
   UPDATE Borrower set status='R' where Roll_no=rollno and Book_name=bookname;
   INSERT INTO Fine(Roll_no, Fine_date,Amt) values(rollno,curdate(),fine);
END IF;
END;
//
UPDATE Borrower set DateofIssue='2024-10-15' where Roll_no=4;
call calc_fine1(4,"Lord of the Rings");
select * from Borrower;


