create table Dept2(Dept_id int PRIMARY KEY auto_increment, Dept_name varchar(50), Location varchar(50));
drop table Employee2;
create table Employee2(Emp_id int PRIMARY KEY auto_increment, Dept_id int, Emp_fname varchar(50) not null,Emp_lname varchar(50),Emp_position varchar(50) not null default 0, Emp_salary int not null, Emp_joindate date, foreign key(Dept_id) references Dept(Dept_id) on delete cascade on update cascade);
create table Project2(Proj_id int PRIMARY KEY auto_increment, Dept_id int, Proj_name varchar(50) not null default ' ',  Proj_location varchar(50) not null default ' ', Proj_cost int not null default 0, Proj_year DATE, foreign key(Dept_id) references Dept(Dept_id) on delete cascade on update cascade);
insert into Dept2(Dept_id, Dept_name, Location) values(1, 'Computer', 'Pune');
insert into Dept2(Dept_name, Location) values('IT','Mumbai');
select * from Dept2;
Update Dept2 set Location='New York' where Dept_id=1;
Update Dept2 set Location='San Francisco' where Dept_id=2;
insert into Dept2(Dept_name, Location) values ('Finance', 'Chicago'),
    ('Marketing', 'Los Angeles'),
    ('Sales', 'Seattle'),
    ('Legal', 'Boston'),
    ('R&D', 'Austin'),
    ('Operations', 'Denver'),
    ('Support', 'Atlanta'),
    ('Logistics', 'Houston');
    
select * from Dept2;

insert into Employee2(Emp_id, Dept_id , Emp_fname,Emp_lname ,Emp_position , Emp_salary, Emp_joindate) values(1, 1, 'John', 'Doe', 'HR Manager', 70000, '2020-05-10');

insert into Employee2(Dept_id , Emp_fname,Emp_lname ,Emp_position , Emp_salary, Emp_joindate) values (2, 'Jane', 'Smith', 'Software Engineer', 85000, '2019-04-15'),
    (3, 'Bob', 'Johnson', 'Financial Analyst', 65000, '2021-01-20'),
    ( 4, 'Alice', 'Brown', 'Marketing Specialist', 60000, '2018-11-05'),
    ( 5, 'Tom', 'White', 'Sales Representative', 55000, '2020-03-12'),
    ( 6, 'Sam', 'Green', 'Legal Advisor', 80000, '2017-09-23'),
    ( 7, 'Chris', 'Black', 'Research Scientist', 95000, '2022-06-30'),
    ( 8, 'Jessica', 'Davis', 'Operations Manager', 90000, '2019-08-19'),
    ( 9, 'David', 'Martinez', 'Support Engineer', 60000, '2021-10-25'),
    ( 10, 'Laura', 'Garcia', 'Logistics Coordinator', 58000, '2020-02-14');
    
select * from Employee2;

    INSERT INTO Project2(Proj_id, Dept_id, Proj_name, Proj_Location, Proj_Cost, Proj_year) VALUES
    (1, 1, 'Employee Engagement', 'New York', 200000, '2022-01-01'),
    (2, 2, 'App Development', 'San Francisco', 500000, '2021-05-15'),
    (3, 3, 'Annual Financial Report', 'Chicago', 150000, '2021-12-01'),
    (4, 4, 'Ad Campaign', 'Los Angeles', 300000, '2022-06-10'),
    (5, 5, 'Sales Strategy', 'Seattle', 250000, '2021-09-30'),
    (6, 6, 'Compliance Audit', 'Boston', 100000, '2022-03-20'),
    (7, 7, 'Product Research', 'Austin', 750000, '2023-02-01'),
    (8, 8, 'Warehouse Operations', 'Denver', 400000, '2021-07-15'),
    (9, 9, 'Customer Support Optimization', 'Atlanta', 350000, '2022-11-05'),
    (10, 10, 'Supply Chain Overhaul', 'Houston', 600000, '2023-04-18');
select * from Employee2;
select * from Project2;
SELECT * from Dept2;
select * from Employee2 where Dept_id in(select Dept_id from Dept where Dept_name='Computer' or Dept_name='IT') and Emp_fname like 'J%' or Emp_fname like 'H%';
select count(distinct Emp_position) as Noofpositions from Employee2;
SET SQL_SAFE_UPDATES = 0;

update Employee2 set Emp_salary=Emp_salary * 1.1 where Emp_joindate <'2020-01-01';

SET FOREIGN_KEY_CHECKS =0;
DELETE FROM Dept2 where Location='Atlanta';

select Proj_name from Project2 where Proj_location='Chicago';
select * from Project2 where Proj_cost between 150000 and 300000;
select avg(Proj_cost) as Averagecost from Project2;
select * from Project2 order by Proj_cost desc limit 1;
select Emp_id, Emp_fname from Employee2 order by Emp_lname desc;
select Proj_name,Proj_location ,Proj_cost from Project2 where year(Proj_year)=2021 or year(Proj_year)=2020;

