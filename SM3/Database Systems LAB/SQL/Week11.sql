create database saadm;
use saadm;

CREATE TABLE BOOKS (
    ID INT PRIMARY KEY,
    Title VARCHAR(100),
    Author VARCHAR(80),
    YearPublished INT,
    Price DECIMAL(10 , 2 )
);

CREATE TABLE STUDENTS (
    StudentID INT PRIMARY KEY,
    FirstName VARCHAR(50),
    LastName VARCHAR(50),
    Age INT,
    Grade VARCHAR(10)
);

DELETE FROM STUDENTS WHERE STUDENTID = 1;
DELETE FROM STUDENTS WHERE STUDENTID = 2;
DELETE FROM STUDENTS WHERE STUDENTID = 3;
DELETE FROM STUDENTS WHERE STUDENTID = 4;
DELETE FROM STUDENTS WHERE STUDENTID = 5;

CREATE TABLE ORDERS (
    OrderID INT PRIMARY KEY,
    CustomerID INT,
    OrderDate DATE,
    TotalAmount DECIMAL(10 , 2 )
);

CREATE TABLE PRODUCTS (
    ProductID INT PRIMARY KEY,
    ProductName VARCHAR(100),
    Category VARCHAR(100),
    QuantityInStock INT,
    Price DECIMAL(10 , 2 )
);

CREATE TABLE EMPLOYEES (
    EmployeeID INT PRIMARY KEY,
    Name VARCHAR(100),
    Position VARCHAR(100),
    Salary DECIMAL(10 , 2 ),
    HireDate DATE
);

INSERT INTO BOOKS(ID, Title, Author, YearPublished, Price) VALUES
	(1, 'Book1', 'Author1', 2001, 9.99),
    (2, 'Book2', 'Author2', 2002, 6.99),
    (3, 'Book3', 'Author3', 2003, 4.99),
    (4, 'Book4', 'Author4', 2004, 19.99),
    (5, 'Book5', 'Author5', 2005, 8.99);

INSERT INTO STUDENTS(StudentID, FirstName, LastName, Age, Grade) VALUES
    (1, 'Ali', 'Raza', 22, 'A'),
    (2, 'Ahmed', 'Usman', 21, 'B'),
    (3, 'Soban', 'Ahmed', 18, 'A'),
    (4, 'Muhammd', 'Hadi', 21, 'D'),
    (5, 'Hamza', 'Ali', 24, 'C');

INSERT INTO ORDERS(OrderID, CustomerID, OrderDate, TotalAmount) VALUES
    (1, 101, '2024-01-01', 49.99),
    (2, 102, '2024-01-05', 19.99),
    (3, 103, '2024-01-10', 29.99),
    (4, 104, '2024-01-15', 99.99),
    (5, 105, '2024-01-20', 39.99);

INSERT INTO PRODUCTS(ProductID, ProductName, Category, QuantityInStock, Price) VALUES
    (1, 'RTX 4090', 'Electronics', 50, 1299.99),
    (2, 'Pixel 9 Pro XL', 'Electronics', 200, 1499.99),
    (3, '64GB RAM DDR5', 'Electronics', 150, 199.99),
    (4, 'PS5', 'Electronics', 30, 699.99),
    (5, 'Pencil Pouch', 'Stationery', 500, 1.99);

INSERT INTO EMPLOYEES(EmployeeID, Name, Position, Salary, HireDate) VALUES
    (1, 'Ayesha Khan', 'Manager', 65000.00, '2020-06-01'),
    (2, 'Ali Raza', 'Sales Representative', 45000.00, '2021-09-15'),
    (3, 'Zainab Ahmed', 'HR Specialist', 50000.00, '2019-03-20'),
    (4, 'Usman Sheikh', 'Software Engineer', 85000.00, '2022-11-10'),
    (5, 'Fatima Noor', 'Marketing Executive', 55000.00, '2018-01-05');
    
UPDATE BOOKS SET Price = 550.00 WHERE ID = 1;
UPDATE BOOKS SET Price = 1300.00 WHERE ID = 4;
UPDATE BOOKS SET Price = 750.00 WHERE ID = 3;
UPDATE BOOKS SET Price = 850.00 WHERE ID = 5;
UPDATE BOOKS SET Price = 400.00 WHERE ID = 2;

UPDATE Students SET Grade = 'B' WHERE StudentID = 4;
UPDATE Students SET Grade = 'A' WHERE StudentID = 5;
UPDATE Students SET Grade = 'C' WHERE StudentID = 2;
UPDATE Students SET Grade = 'D' WHERE StudentID = 3;
UPDATE Students SET Grade = 'F' WHERE StudentID = 1;

UPDATE Orders SET TotalAmount = 1200.00 WHERE OrderID = 1;
UPDATE Orders SET TotalAmount = 800.00 WHERE OrderID = 5;
UPDATE Orders SET TotalAmount = 2200.00 WHERE OrderID = 2;
UPDATE Orders SET TotalAmount = 500.00 WHERE OrderID = 3;
UPDATE Orders SET TotalAmount = 1500.00 WHERE OrderID = 4;

UPDATE Products SET QuantityInStock = QuantityInStock - 2 WHERE ProductID = 1;
UPDATE Products SET QuantityInStock = QuantityInStock - 5 WHERE ProductID = 2;
UPDATE Products SET QuantityInStock = QuantityInStock - 10 WHERE ProductID = 3;
UPDATE Products SET QuantityInStock = QuantityInStock - 3 WHERE ProductID = 4;
UPDATE Products SET QuantityInStock = QuantityInStock - 15 WHERE ProductID = 5;

UPDATE Employees SET Salary = Salary * 1.10 WHERE EmployeeID = 2;
UPDATE Employees SET Salary = Salary * 1.14 WHERE EmployeeID = 1;
UPDATE Employees SET Salary = Salary * 1.11 WHERE EmployeeID = 3;
UPDATE Employees SET Salary = Salary * 1.15 WHERE EmployeeID = 4;
UPDATE Employees SET Salary = Salary * 1.10 WHERE EmployeeID = 5;

DELETE FROM BOOKS WHERE ID = 1;
DELETE FROM BOOKS WHERE ID = 2;
DELETE FROM BOOKS WHERE ID = 3;
DELETE FROM BOOKS WHERE ID = 4;
DELETE FROM BOOKS WHERE ID = 5;

DELETE FROM STUDENTS WHERE Grade = 'A';
DELETE FROM STUDENTS WHERE Grade = 'B';
DELETE FROM STUDENTS WHERE Grade = 'D';
DELETE FROM STUDENTS WHERE Grade = 'C';
DELETE FROM STUDENTS WHERE Grade = 'F';

DELETE FROM ORDERS WHERE TotalAmount < 1000;
DELETE FROM ORDERS WHERE TotalAmount < 1200;
DELETE FROM ORDERS WHERE TotalAmount < 800;
DELETE FROM ORDERS WHERE TotalAmount < 500;
DELETE FROM ORDERS WHERE TotalAmount < 1500;

DELETE FROM PRODUCTS WHERE Category = 'Electronics' LIMIT 1;
DELETE FROM PRODUCTS WHERE Category = 'Electronics' LIMIT 1;
DELETE FROM PRODUCTS WHERE Category = 'Electronics' LIMIT 1;
DELETE FROM PRODUCTS WHERE Category = 'Electronics' LIMIT 1;
DELETE FROM PRODUCTS WHERE Category = 'Electronics' LIMIT 1;

DELETE FROM EMPLOYEES WHERE Salary < 70000;
DELETE FROM EMPLOYEES WHERE Salary < 80000;
DELETE FROM EMPLOYEES WHERE Salary < 90000;
DELETE FROM EMPLOYEES WHERE Salary < 60000;
DELETE FROM EMPLOYEES WHERE Salary < 100000;

DELETE FROM BOOKS WHERE ID IN (1, 2, 3, 4, 5);
DELETE FROM STUDENTS WHERE Grade IN ('A', 'B', 'D', 'C', 'F');
DELETE FROM ORDERS WHERE TotalAmount < 500;
DELETE FROM PRODUCTS WHERE ProductID IN (1, 2, 3, 4, 5);
DELETE FROM EMPLOYEES WHERE EmployeeID IN (1, 2, 3, 4, 5);

SELECT * FROM BOOKS;
SELECT * FROM STUDENTS;
SELECT * FROM ORDERS;
SELECT * FROM PRODUCTS;
SELECT * FROM EMPLOYEES;
