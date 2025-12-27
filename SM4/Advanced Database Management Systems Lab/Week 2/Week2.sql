create DATABASE Saad;
use Saad;

/*1. Create Table on the basis of table and data given above. Data types and size have to be decidedby you and may vary.*/

CREATE TABLE Customers_Table (
    CustomerID INT PRIMARY KEY,
    FirstName VARCHAR(30),
    LastName VARCHAR(30),
    Age INT,
    Gender VARCHAR(1),
    Address VARCHAR(60),
    City VARCHAR(40),
    State VARCHAR(10),
    ZipCode INT,
    Email VARCHAR(40)
);

SELECT 
    *
FROM
    Customers_Table;
   
/*2. Also Insert data into table as described above.*/

INSERT INTO Customers_Table (CustomerID, FirstName, LastName, Age, Gender, Address, City, State, ZipCode, Email) VALUES
(1, 'Alice', 'Johnson', 30, 'F', '123 Elm St', 'New York', 'NY', 10001, 'alicejohnson@example.com'),
(2, 'Bob', 'Williams', 45, 'M', '456 Maple St', 'Los Angeles', 'CA', 90001, 'bobwilliams@example.com'),
(3, 'Charlie', 'Brown', 49, 'M', '789 Oak St', 'Chicago', 'IL', 60601, 'charliebrown@example.com'),
(4, 'Diana', 'Evans', 34, 'F', '321 Pine St', 'Houston', 'TX', 77001, 'dianaevans@example.com'),
(5, 'Ethan', 'Wright', 37, 'M', '654 Birch St', 'Phoenix', 'AZ', 85001, 'ethanwright@example.com'),
(6, 'Fiona', 'Adams', 26, 'F', '987 Cedar St', 'Philadelphia', 'PA', 19101, 'fionaadams@example.com'),
(7, 'George', 'Miller', 33, 'M', '111 Spruce St', 'San Diego', 'CA', 92101, 'georgemiller@example.com'),
(8, 'Hannah', 'Taylor', 30, 'F', '222 Willow St', 'Dallas', 'TX', 75201, 'hannahtaylor@example.com'),
(9, 'Ian', 'Thomas', 25, 'M', '333 Cherry St', 'San Jose', 'CA', 95101, 'ianthomas@example.com'),
(10, 'Julia', 'Wilson', 36, 'F', '444 Poplar St', 'Austin', 'TX', 73301, 'juliawilson@example.com'),
(11, 'Kevin', 'Lee', 42, 'M', '555 Aspen St', 'Denver', 'CO', 80201, 'kevinlee@example.com'),
(12, 'Laura', 'Hall', 28, 'F', '666 Hickory St', 'Seattle', 'WA', 98101, 'laurahall@example.com'),
(13, 'Mark', 'Harris', 31, 'M', '777 Redwood St', 'Portland', 'OR', 97201, 'markharris@example.com'),
(14, 'Natalie', 'King', 27, 'F', '888 Cypress St', 'Miami', 'FL', 33101, 'natalieking@example.com'),
(15, 'Oliver', 'Lewis', 44, 'M', '999 Chestnut St', 'Boston', 'MA', 02101, 'oliverlewis@example.com'),
(16, 'Peter', 'Carter', 41, 'M', '101 Walnut St', 'Atlanta', 'GA', 30301, 'petercarter@example.com'),
(17, 'Rachel', 'Adams', 29, 'F', '202 Pineapple St', 'Nashville', 'TN', 37201, 'racheladams@example.com'),
(18, 'Samuel', 'Clark', 39, 'M', '303 Magnolia St', 'New Orleans', 'LA', 70101, 'samuelclark@example.com'),
(19, 'Teresa', 'Scott', 40, 'F', '404 Peach St', 'Charlotte', 'NC', 28201, 'teresascott@example.com'),
(20, 'Victor', 'Young', 37, 'M', '505 Palm St', 'Tampa', 'FL', 33601, 'victoryoung@example.com'),
(21, 'Wendy', 'Baker', 46, 'F', '606 Dogwood St', 'Indianapolis', 'IN', 46201, 'wendybaker@example.com'),
(22, 'Xavier', 'Martin', 30, 'M', '707 Oakwood St', 'Columbus', 'OH', 43201, 'xaviermartin@example.com'),
(23, 'Yolanda', 'Nelson', 25, 'F', '808 Cedarwood St', 'Detroit', 'MI', 48201, 'yolandanelson@example.com'),
(24, 'Zack', 'Brooks', 36, 'M', '909 Redwood St', 'Memphis', 'TN', 38101, 'zackbrooks@example.com'),
(25, 'Amber', 'Sanders', 33, 'F', '100 Birch St', 'Kansas City', 'MO', 64101, 'ambersanders@example.com'),
(26, 'Brian', 'Murphy', 47, 'M', '120 Spruce St', 'Jacksonville', 'FL', 32201, 'brianmurphy@example.com'),
(27, 'Cynthia', 'Reed', 31, 'F', '130 Birch St', 'Oklahoma City', 'OK', 73101, 'cynthiareed@example.com'),
(28, 'Dennis', 'Head', 34, 'M', '140 Maple St', 'Louisville', 'KY', 40201, 'dennisreed@example.com'),
(29, 'Elaine', 'Carter', 45, 'F', '150 Oak St', 'Omaha', 'NE', 68101, 'elainecarter@example.com'),
(30, 'Frank', 'Howard', 36, 'M', '150 Apple St', 'Orlando', 'FL', 32801, 'frankhoward@example.com');

/*3. Write an SQL query to remove all data from the Customers table but keep the structure intact.*/

TRUNCATE TABLE Customers_Table;

/*5. Write an SQL query to find customers aged between 25 and 45.*/

SELECT 
    *
FROM
    Customers_Table
WHERE
    Age BETWEEN 25 AND 45;
   
/*6. Retrieve customers whose Zip Code falls between &#39;10000&#39; and &#39;50000&#39;.*/

SELECT 
    *
FROM
    Customers_Table
WHERE
    ZipCode BETWEEN 10000 AND 50000;
   
/*7. Get a list of customers with Customer Id between 10 and 20, ordered by LastName.*/

SELECT 
    *
FROM
    Customers_Table
WHERE
    CustomerID BETWEEN 10 AND 20
ORDER BY LastName;

/*8. Write a query to find customers not in the age range of 30 to 50.*/

SELECT 
    *
FROM
    Customers_Table
WHERE
    Age NOT BETWEEN 30 AND 50;
   
/*9. Retrieve all customers sorted by FirstName in ascending order.*/

SELECT 
    *
FROM
    Customers_Table
ORDER BY FirstName ASC;

/*10. Write a query to list customers sorted by Age in descending order.*/

SELECT 
    *
FROM
    Customers_Table
ORDER BY Age DESC;

/*11. Get all customers ordered first by State (ascending) and then by City (descending).*/

SELECT * FROM Customers_Table ORDER BY State ASC, City DESC;

/*12. What happens if you use ORDER BY 2 DESC? Explain with an example.*/

SELECT * FROM Customers_Table ORDER BY 2 DESC;

/*13. Modify a query to sort customers by State, then Age (descending), then FirstName.*/

SELECT * FROM Customers_Table ORDER BY State ASC, Age DESC, FirstName ASC;

/*14. Write an SQL query to count the number of customers in each State.*/

SELECT State, COUNT(*) AS CustomerCount FROM Customers_Table GROUP BY State;

/*15. Retrieve the average age of customers in each state.*/

SELECT State, AVG(Age) AS AverageAge FROM Customers_Table GROUP BY State;

/*16. Find out how many customers belong to each gender (M/F).*/

SELECT Gender, COUNT(*) AS CustomerCount FROM Customers_Table GROUP BY Gender;

/*17. List all cities along with the total number of customers in each city.*/

SELECT City, COUNT(*) AS CustomerCount FROM Customers_Table GROUP BY City;

/*19. Write an SQL query to combine the list of all customers from California (CA) and New York (NY).*/

SELECT * FROM Customers_Table WHERE State = 'CA' OR State = 'NY';

/*20. Retrieve all customers aged below 30 and all customers aged above 50 using UNION.*/

SELECT * FROM Customers_Table WHERE Age < 30
UNION
SELECT * FROM Customers_Table WHERE Age > 50;

/*21. Write a query to display unique cities from the Customers table using UNION.*/

SELECT City FROM Customers_Table UNION SELECT City FROM Customers_Table;

/*24. Write an SQL query to get customers from TX and TX again, and observe duplicate records.*/

SELECT * FROM Customers_Table WHERE State = 'TX' UNION ALL SELECT * FROM Customers_Table WHERE State = 'TX';

/*25. Retrieve all customers aged below 30 and above 50 ensuring duplicates are not removed.*/

SELECT * FROM Customers_Table WHERE Age < 30 UNION ALL SELECT * FROM Customers_Table WHERE Age > 50;