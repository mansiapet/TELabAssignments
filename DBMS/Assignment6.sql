create table old_employee(employee_id int primary key, name varchar(50),salary int);
create table new_employee(employee_id int primary key, name varchar(50),salary int);

insert into old_employee(employee_id,name,salary) values (101, 'Alice', 50000),
     (102, 'Bob', 60000),
    (103, 'Charlie', 55000),
  (104, 'David', 70000),
    (105, 'Eve', 65000);

insert INTO new_employee (employee_id, name, salary) VALUES
    (101, 'Alice', 50000),
   (104, 'David', 70000);
 DELIMITER //   
create procedure addemp()
BEGIN
declare e_id int;
declare e_name varchar(50);
declare e_salary int;
DECLARE i cursor for
select employee_id,name,salary from old_employee;
open i;
read_loop: LOOP
fetch i into e_id,e_name,e_salary;
if row_count()=0 then 
LEAVE read_loop;
END IF;
IF NOT EXISTS (select * from new_employee where employee_id=e_id) then
insert into new_employee(employee_id,name,salary) values(e_id,e_name_e_salary);
END IF;
END LOOP;
CLOSE i;
END//
call addemp();
select * from new_employee;
select * from old_employee;