CREATE DATABASE bazooka;
USE bazooka;

CREATE TABLE Customers (
    ID INT PRIMARY KEY,
    Name VARCHAR(100),
    City VARCHAR(100)
);

CREATE TABLE Products (
    ProductID INT PRIMARY KEY,
    ProductName VARCHAR(100),
    Price DECIMAL(10 , 2 )
);

CREATE TABLE Orders (
    OrderID INT PRIMARY KEY,
    CustomerID INT,
    ProductID INT,
    Amount DECIMAL(10 , 2 ),
    Region VARCHAR(50),
    FOREIGN KEY (CustomerID)
        REFERENCES Customers (ID),
    FOREIGN KEY (ProductID)
        REFERENCES Products (ProductID)
);

INSERT INTO Customers (ID, Name, City) VALUES
(1, 'Alice', 'New York'),
(2, 'Bob', 'Los Angeles'),
(3, 'Charlie', 'Chicago'),
(4, 'Diana', 'New York');

INSERT INTO Products (ProductID, ProductName, Price) VALUES
(10, 'Laptop', 800),
(20, 'Phone', 600),
(30, 'Tablet', 400);

INSERT INTO Orders (OrderID, CustomerID, ProductID, Amount, Region) VALUES
(101, 1, 10, 200, 'East'),
(102, 2, 20, 150, 'West'),
(103, 3, 30, 300, 'Midwest'),
(104, 1, 20, 100, 'East'),
(105, 4, 10, 250, 'East');

-- 1. Find customers from New York who placed orders in the East region.
SELECT DISTINCT
    c.Name, c.City
FROM
    Customers c
        JOIN
    Orders o ON c.ID = o.CustomerID
WHERE
    c.City = 'New York'
        AND o.Region = 'East';

-- 2. Find products with a price greater than ANY product ordered by CustomerID
SELECT 
    p.ProductName, p.Price
FROM
    Products p
WHERE
    p.Price > ANY (SELECT 
            p2.Price
        FROM
            Orders o
                JOIN
            Products p2 ON o.ProductID = p2.ProductID
        WHERE
            o.CustomerID = 1);

-- 3. Find products priced higher than ALL products in the Phone category (assume Phone has ProductID 20).
SELECT 
    p.ProductName, p.Price
FROM
    Products p
WHERE
    p.Price > ALL (SELECT 
            p2.Price
        FROM
            Products p2
        WHERE
            p2.ProductID = 20);

-- 4. Find customers who have placed at least one order in the East region.
SELECT DISTINCT
    c.Name, c.City
FROM
    Customers c
        JOIN
    Orders o ON c.ID = o.CustomerID
WHERE
    o.Region = 'East';

-- 5. Find products ordered by customers from New York.
SELECT DISTINCT
    p.ProductName, p.Price
FROM
    Products p
        JOIN
    Orders o ON p.ProductID = o.ProductID
        JOIN
    Customers c ON o.CustomerID = c.ID
WHERE
    c.City = 'New York';

-- 6. Find customers (Name, City) who placed orders in the East region and are from New York.
SELECT DISTINCT
    c.Name, c.City
FROM
    Customers c
        JOIN
    Orders o ON c.ID = o.CustomerID
WHERE
    c.City = 'New York'
        AND o.Region = 'East';

-- 7. List products (ProductName, Price) priced higher than ANY product ordered by CustomerID 1 (Alice).
SELECT 
    p.ProductName, p.Price
FROM
    Products p
WHERE
    p.Price > ANY (SELECT 
            p2.Price
        FROM
            Orders o
                JOIN
            Products p2 ON o.ProductID = p2.ProductID
        WHERE
            o.CustomerID = 1);

-- 8. Find customers (Name, City) whose total order amount exceeds ALL individual orders in the West region.
SELECT 
    c.Name, c.City
FROM
    Customers c
        JOIN
    Orders o ON c.ID = o.CustomerID
GROUP BY c.Name , c.City
HAVING SUM(o.Amount) > ALL (SELECT 
        o2.Amount
    FROM
        Orders o2
    WHERE
        o2.Region = 'West');

-- 9. List customers (Name, City) who placed orders in all regions where their city’s customers have ordered.
SELECT DISTINCT c.Name, c.City
FROM Customers c
WHERE NOT EXISTS (
    SELECT o.Region
    FROM Orders o
    JOIN Customers c2 ON o.CustomerID = c2.ID
    WHERE c2.City = c.City
    GROUP BY o.Region
    EXCEPT
    SELECT o.Region
    FROM Orders o
    WHERE o.CustomerID = c.ID
);

-- 10. Show customers (Name, City) and their most expensive product purchased.
SELECT 
    c.Name, c.City, p.ProductName, p.Price AS MaxPrice
FROM
    Customers c
        JOIN
    Orders o ON c.ID = o.CustomerID
        JOIN
    Products p ON o.ProductID = p.ProductID
WHERE
    p.Price = (SELECT 
            MAX(p2.Price)
        FROM
            Products p2
                JOIN
            Orders o2 ON p2.ProductID = o2.ProductID
        WHERE
            o2.CustomerID = c.ID)
ORDER BY c.Name;

-- 11. Find the product with the second-highest price (ProductName, Price).
SELECT 
    ProductName, Price
FROM
    Products
WHERE
    Price = (SELECT 
            MAX(Price)
        FROM
            Products
        WHERE
            Price < (SELECT 
                    MAX(Price)
                FROM
                    Products));

-- 12. List customers (Name, City) whose total order amount is greater than the average total of their city.
SELECT 
    c.Name, c.City
FROM
    Customers c
        JOIN
    Orders o ON c.ID = o.CustomerID
GROUP BY c.Name , c.City
HAVING SUM(o.Amount) > (SELECT 
        AVG(total_amount)
    FROM
        (SELECT 
            SUM(o2.Amount) AS total_amount
        FROM
            Orders o2
        JOIN Customers c2 ON o2.CustomerID = c2.ID
        WHERE
            c2.City = c.City
        GROUP BY c2.ID) AS city_totals);

-- 13. Find products (ProductName, Price) that were never ordered in the East region.
SELECT 
    p.ProductName, p.Price
FROM
    Products p
WHERE
    p.ProductID NOT IN (SELECT DISTINCT
            o.ProductID
        FROM
            Orders o
        WHERE
            o.Region = 'East');

-- 14. Find customers (Name, City) who have ordered every product available.
SELECT 
    c.Name, c.City
FROM
    Customers c
WHERE
    NOT EXISTS( SELECT 
            p.ProductID
        FROM
            Products p
        WHERE
            NOT EXISTS( SELECT 
                    o.OrderID
                FROM
                    Orders o
                WHERE
                    o.CustomerID = c.ID
                        AND o.ProductID = p.ProductID));

-- 15. List each customer’s most recent order (Name, OrderID, Amount).
SELECT 
    c.Name, o.OrderID, o.Amount
FROM
    Customers c
        JOIN
    Orders o ON c.ID = o.CustomerID
WHERE
    o.OrderID IN (SELECT 
            MAX(OrderID)
        FROM
            Orders
        WHERE
            CustomerID = c.ID)
ORDER BY c.Name;