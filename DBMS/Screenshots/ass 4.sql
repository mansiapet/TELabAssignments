

CREATE TABLE borrower(
roll_no INT PRIMARY KEY,
name VARCHAR(55),
issue_date DATE,
book_name VARCHAR(155),
status CHAR(1)
);

CREATE TABLE fine(
roll_no INT PRIMARY KEY,
return_date DATE,
amount INT,
CONSTRAINT `fk_rollno` FOREIGN KEY (roll_no) REFERENCES borrower(roll_no) ON DELETE CASCADE
);

insert into borrower(roll_no,name,issue_date,book_name, status)
values
(1,'Sam','2024-08-30',"The Book of Fantasy", 'I'),
(2,'Prabhu','2024-09-10',"The Alchemist", 'I'),
(3,'Nilesh','2024-09-02',"The Hobbit", 'I'),
(4,'Mansi','2024-08-27',"Lord of the Rings", 'I'),
(5,'Arinjay','2024-09-05',"Rich Dad Poor Dad", 'I'),
(6,'Drishti','2024-08-28',"48 Laws of Power", 'I');


DELIMITER //
CREATE OR REPLACE PROCEDURE calc_fine(IN r INT, IN n VARCHAR(55))
BEGIN
  DECLARE i_date DATE;
  DECLARE fine_amt INT DEFAULT 0;
  DECLARE day_count INT DEFAULT 0;
  DECLARE EXIT HANDLER FOR SQLEXCEPTION,NOT FOUND
  BEGIN 
    select 'record not found';
  END;
  DECLARE EXIT HANDLER FOR 1062 SELECT 'fine already paid!';
  SELECT issue_date INTO i_date FROM borrower where roll_no = r AND name = n;
  SELECT DATEDIFF(CURDATE(), i_date) INTO day_count;
  IF (day_count >= 15 AND day_count <= 30) then
    set fine_amt = 5*day_count;
    INSERT INTO fine(roll_no, return_date, amount) VALUES(r, CURDATE(), fine_amt);
  ELSEIF (day_count > 30) then
    set fine_amt = 50*day_count;
    INSERT INTO fine(roll_no, return_date, amount) VALUES(r, CURDATE(), fine_amt);
  END IF;
  update borrower set status = 'R' where roll_no = r AND name = n;
END; 
//
DELIMITER ;
  
call calc_fine(1, 'Sam');
call calc_fine(1, 'Sam');

select * from borrower;
select * from fine;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  