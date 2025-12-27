-- Create a Database --
CREATE DATABASE CompanyDB;
USE CompanyDB;

-- Create Tables --
CREATE TABLE Employees (
    EmployeeID INT PRIMARY KEY,
    FirstName VARCHAR(50),
    LastName VARCHAR(50),
    DepartmentID INT,
    Salary DECIMAL(10, 2)
);

CREATE TABLE Departments (
    DepartmentID INT PRIMARY KEY,
    DepartmentName VARCHAR(50)
);

-- Insert Sample Data into Tables --
INSERT INTO Departments (DepartmentID, DepartmentName) VALUES
(1, 'HR'),
(2, 'Finance'),
(3, 'IT'),
(4, 'Marketing');

INSERT INTO Employees (EmployeeID, FirstName, LastName, DepartmentID, Salary) VALUES
(101, 'John', 'Doe', 1, 50000),
(102, 'Jane', 'Smith', 2, 60000),
(103, 'Mike', 'Johnson', 3, 55000),
(104, 'Anna', 'Brown', 4, 70000),
(105, 'Mark', 'Wilson', 2, 65000),
(106, 'Sarah', 'Taylor', NULL, 50000);

SELECT * FROM Employees;

-- INNER JOIN --
-- Question: Display the employee details along with their department names using an INNER JOIN. --
SELECT Employees.EmployeeID, Employees.FirstName, Employees.LastName, Departments.DepartmentName
FROM Employees
INNER JOIN Departments ON Employees.DepartmentID = Departments.DepartmentID;

-- LEFT OUTER JOIN --
-- Question: Display all employees, including those without a department, using a LEFT JOIN.--
SELECT Employees.EmployeeID, Employees.FirstName, Employees.LastName, Departments.DepartmentName
FROM Employees
LEFT JOIN Departments ON Employees.DepartmentID = Departments.DepartmentID;

-- RIGHT OUTER JOIN--
-- Question: Display all departments, including those without any employees, using a RIGHT JOIN.--
SELECT Employees.EmployeeID, Employees.FirstName, Departments.DepartmentName
FROM Employees
RIGHT JOIN Departments ON Employees.DepartmentID = Departments.DepartmentID;

-- FULL OUTER JOIN--
-- MySQL does not support FULL OUTER JOIN directly, but it can be emulated using a UNION. --
-- Question: Display all employees and departments, showing records even if there is no match.--
SELECT Employees.EmployeeID, Employees.FirstName, Employees.LastName, Departments.DepartmentName
FROM Employees
LEFT JOIN Departments ON Employees.DepartmentID = Departments.DepartmentID

UNION

SELECT Employees.EmployeeID, Employees.FirstName, Employees.LastName, Departments.DepartmentName
FROM Employees
RIGHT JOIN Departments ON Employees.DepartmentID = Departments.DepartmentID;

-- CROSS JOIN--
-- Question: Display all possible combinations of employees and departments.--
SELECT Employees.FirstName, Departments.DepartmentName
FROM Employees
CROSS JOIN Departments;

-- SELF JOIN --
-- Question: Display pairs of employees who work in the same department.--
SELECT e1.FirstName AS Employee1, e2.FirstName AS Employee2, e1.DepartmentID
FROM Employees e1
JOIN Employees e2 ON e1.DepartmentID = e2.DepartmentID
WHERE e1.EmployeeID <> e2.EmployeeID;


-- End of Lab Task --

