CREATE DATABASE LAB7;
USE LAB7;

CREATE TABLE Customers (
    CustomerID INT PRIMARY KEY,
    Name VARCHAR(50),
    City VARCHAR(50)
);

INSERT INTO Customers (CustomerID, Name, City) VALUES
(1, 'Alice', 'New York'),
(2, 'Bob', 'Los Angeles'),
(3, 'Charlie', 'Chicago'),
(4, 'Diana', 'New York');

CREATE TABLE Orders (
    OrderID INT PRIMARY KEY,
    CustomerID INT,
    ProductID INT,
    Amount INT,
    Region VARCHAR(50),
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID),
    FOREIGN KEY (ProductID) REFERENCES Products(ProductID)
);

INSERT INTO Orders (OrderID, CustomerID, ProductID, Amount, Region) VALUES
(101, 1, 10, 200, 'East'),
(102, 2, 20, 150, 'West'),
(103, 3, 30, 300, 'Midwest'),
(104, 1, 20, 100, 'East'),
(105, 4, 10, 250, 'East');

CREATE TABLE Products (
    ProductID INT PRIMARY KEY,
    ProductName VARCHAR(50),
    Price INT
);

INSERT INTO Products (ProductID, ProductName, Price) VALUES
(10, 'Laptop', 800),
(20, 'Phone', 600),
(30, 'Tablet', 400);

-- 1. Find customers (Name, City) who have placed an order where the amount is higher than the average order amount of customers from the same city, but only if their total spending is also above the city-wide average.
SELECT c.Name, c.City
FROM Customers c
JOIN Orders o ON c.CustomerID = o.CustomerID
WHERE o.Amount > (
    SELECT AVG(o2.Amount)
    FROM Orders o2
    JOIN Customers c2 ON o2.CustomerID = c2.CustomerID
    WHERE c2.City = c.City
)
AND (
    SELECT SUM(o3.Amount)
    FROM Orders o3
    WHERE o3.CustomerID = c.CustomerID
) > (
    SELECT AVG(total_spent)
    FROM (
        SELECT c2.City, SUM(o2.Amount) AS total_spent
        FROM Orders o2
        JOIN Customers c2 ON o2.CustomerID = c2.CustomerID
        WHERE c2.City = c.City
        GROUP BY c2.CustomerID
    ) AS city_avg
);

-- 2. List products (ProductName, Price) that have been ordered by at least two distinct customers, ensuring that the product price is greater than the highest-priced product ordered by CustomerID 1.
SELECT p.ProductName, p.Price
FROM Products p
WHERE p.Price > COALESCE((
    SELECT MAX(p2.Price)
    FROM Products p2
    JOIN Orders o2 ON p2.ProductID = o2.ProductID
    WHERE o2.CustomerID = 1
), 0)  -- Handle case where CustomerID 1 has no orders
AND p.ProductID IN (
    SELECT o3.ProductID
    FROM Orders o3
    GROUP BY o3.ProductID
    HAVING COUNT(DISTINCT o3.CustomerID) >= 2
);

-- 3. Find customers (Name, City) who placed an order where the amount is higher than the highest single order amount of any customer from the same city, but only if they have placed at least two orders.
SELECT c.Name, c.City
FROM Customers c
JOIN Orders o ON c.CustomerID = o.CustomerID
WHERE o.Amount > (
    SELECT MAX(o2.Amount)
    FROM Orders o2
    JOIN Customers c2 ON o2.CustomerID = c2.CustomerID
    WHERE c2.City = c.City AND c2.CustomerID <> c.CustomerID
)
AND (
    SELECT COUNT(*)
    FROM Orders o3
    WHERE o3.CustomerID = c.CustomerID
) >= 2;

-- 4. Show customers (Name, City) whose total spending is greater than the total spending of every other customer from their city, ensuring they have at least three distinct orders. 
SELECT c.Name, c.City
FROM Customers c
JOIN Orders o ON c.CustomerID = o.CustomerID
GROUP BY c.CustomerID, c.Name, c.City
HAVING SUM(o.Amount) > ALL (
    SELECT SUM(o2.Amount)
    FROM Orders o2
    JOIN Customers c2 ON o2.CustomerID = c2.CustomerID
    WHERE c2.City = c.City AND c2.CustomerID <> c.CustomerID
    GROUP BY c2.CustomerID
)
AND COUNT(DISTINCT o.OrderID) >= 3;

-- 5. INSERT new customers into a backup table if they have placed an order in every region where at least one other customer from their city has ordered.
CREATE TABLE Customer_Backup (
    CustomerID INT PRIMARY KEY,
    Name VARCHAR(255),
    City VARCHAR(255)
);
INSERT INTO Customer_Backup (CustomerID, Name, City)
SELECT DISTINCT C.CustomerID, C.Name, C.City
FROM Customers C
WHERE NOT EXISTS (
    SELECT 1 FROM (
        SELECT DISTINCT O.Region FROM Orders O
        WHERE O.CustomerID = C.CustomerID
    ) AS CustomerRegions
    WHERE CustomerRegions.Region NOT IN (
        SELECT DISTINCT O2.Region FROM Orders O2
        JOIN Customers C2 ON O2.CustomerID = C2.CustomerID
        WHERE C2.City = C.City
    )
);

-- 6. UPDATE the price of all products that have been ordered by at least two distinct customers, increasing their price by 15%, but only if they have also been ordered in at least two different regions.
SET SQL_SAFE_UPDATES = 0;

UPDATE Products p
JOIN (
    SELECT ProductID
    FROM Orders
    GROUP BY ProductID
    HAVING COUNT(DISTINCT CustomerID) >= 2 
    AND COUNT(DISTINCT Region) >= 2
) o ON p.ProductID = o.ProductID
SET p.Price = p.Price * 1.15;

SET SQL_SAFE_UPDATES = 1;


-- 7. DELETE all orders where the order amount is lower than the minimum order amount placed in the same region by a customer who has at least two orders in that region.
CREATE TEMPORARY TABLE TempMinOrders AS
SELECT O2.Region, MIN(O2.Amount) AS MinOrderAmount
FROM Orders O2
WHERE O2.CustomerID IN (
    SELECT CustomerID
    FROM Orders
    GROUP BY CustomerID, Region
    HAVING COUNT(*) >= 2
)
GROUP BY O2.Region;

DELETE FROM Orders
WHERE Amount < (
    SELECT MinOrderAmount
    FROM TempMinOrders
    WHERE Orders.Region = TempMinOrders.Region
);

DROP TEMPORARY TABLE TempMinOrders;

-- 8. INSERT products into a special discount table if they have been ordered by at least two customers from different cities and their price is below the average price of products ordered in the same region.
CREATE TABLE IF NOT EXISTS DiscountProducts (
    ProductID INT PRIMARY KEY,
    ProductName VARCHAR(255),
    Price INT
);

INSERT INTO DiscountProducts (ProductID, ProductName, Price)
SELECT DISTINCT p.ProductID, p.ProductName, p.Price
FROM Products p
JOIN Orders o ON p.ProductID = o.ProductID
WHERE p.ProductID IN (
    SELECT o2.ProductID
    FROM Orders o2
    JOIN Customers c2 ON o2.CustomerID = c2.CustomerID
    GROUP BY o2.ProductID
    HAVING COUNT(DISTINCT c2.City) >= 2
)
AND p.Price < (
    SELECT AVG(p2.Price)
    FROM Products p2
    JOIN Orders o3 ON p2.ProductID = o3.ProductID
    WHERE o3.Region = o.Region
);
