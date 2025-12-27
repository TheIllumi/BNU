CREATE DATABASE CompanyDB_Week4;
USE CompanyDB_Week4;

CREATE TABLE Departments (
    DepartmentID INT PRIMARY KEY,
    DepartmentName VARCHAR(50) NOT NULL
);

INSERT INTO Departments (DepartmentID, DepartmentName) VALUES
(1, 'HR'),
(2, 'Finance'),
(3, 'IT'),
(4, 'Marketing');

CREATE TABLE Employees (
    EmployeeID INT PRIMARY KEY,
    FirstName VARCHAR(50) NOT NULL,
    LastName VARCHAR(50) NOT NULL,
    DepartmentID INT,
    Salary DECIMAL(10,2),
    FOREIGN KEY (DepartmentID) REFERENCES Departments(DepartmentID)
);

INSERT INTO Employees (EmployeeID, FirstName, LastName, DepartmentID, Salary) VALUES
(101, 'John', 'Doe', 1, 50000.00),
(102, 'Jane', 'Smith', 2, 60000.00),
(103, 'Mike', 'Johnson', 3, 55000.00),
(104, 'Anna', 'Brown', 4, 70000.00),
(105, 'Mark', 'Wilson', 2, 65000.00),
(106, 'Sarah', 'Taylor', NULL, 50000.00);

-- Q1: Display the employee details along with their department names using an INNER JOIN.

SELECT e.EmployeeID, e.FirstName, e.LastName, e.Salary, d.DepartmentName
FROM Employees e
INNER JOIN Departments d ON e.DepartmentID = d.DepartmentID;

-- Q2: Display all employees, including those without a department, using a LEFT JOIN.

SELECT e.EmployeeID, e.FirstName, e.LastName, e.Salary, d.DepartmentName
FROM Employees e
LEFT JOIN Departments d ON e.DepartmentID = d.DepartmentID;

-- Q3: Display all departments, including those without any employees, using a RIGHT JOIN.

SELECT e.EmployeeID, e.FirstName, e.LastName, e.Salary, d.DepartmentName
FROM Employees e
RIGHT JOIN Departments d ON e.DepartmentID = d.DepartmentID;

-- Q4: Display all possible combinations of employees and departments using CROSS JOIN.

SELECT e.EmployeeID, e.FirstName, e.LastName, d.DepartmentID, d.DepartmentName
FROM Employees e
CROSS JOIN Departments d;

-- Q5: Display pairs of employees who work in the same department.

SELECT e1.EmployeeID AS Employee1_ID, e1.FirstName AS Employee1_Name, 
       e2.EmployeeID AS Employee2_ID, e2.FirstName AS Employee2_Name, 
       d.DepartmentName
FROM Employees e1
JOIN Employees e2 ON e1.DepartmentID = e2.DepartmentID 
                 AND e1.EmployeeID < e2.EmployeeID
JOIN Departments d ON e1.DepartmentID = d.DepartmentID;