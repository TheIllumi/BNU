-- Base Person table
CREATE TABLE Person (
    SSN INT PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    Sex ENUM('male', 'female') NOT NULL,
    Address VARCHAR(100),
    Birth_Date DATE NOT NULL
);

-- Employee Table
CREATE TABLE Employee (
    SSN INT PRIMARY KEY,
    Salary DECIMAL(10, 2),
    FOREIGN KEY (SSN) REFERENCES Person(SSN)
);

-- Alumnus Table
CREATE TABLE Alumnus (
    SSN INT PRIMARY KEY,
    FOREIGN KEY (SSN) REFERENCES Person(SSN)
);

-- Degrees Table (Multivalued attribute for Alumnus)
CREATE TABLE Degree (
    Degree_ID INT AUTO_INCREMENT PRIMARY KEY,
    SSN INT,
    Degree_Year INT,
    Degree_Type VARCHAR(50),
    Major VARCHAR(50),
    FOREIGN KEY (SSN) REFERENCES Alumnus(SSN)
);

-- Student Table
CREATE TABLE Student (
    SSN INT PRIMARY KEY,
    Major_Dept VARCHAR(50),
    FOREIGN KEY (SSN) REFERENCES Person(SSN)
);

-- Graduate Student Table
CREATE TABLE Graduate_Student (
    SSN INT PRIMARY KEY,
    Degree_Program VARCHAR(50),
    FOREIGN KEY (SSN) REFERENCES Student(SSN)
);

-- Undergraduate Student Table
CREATE TABLE Undergraduate_Student (
    SSN INT PRIMARY KEY,
    Class VARCHAR(20),
    FOREIGN KEY (SSN) REFERENCES Student(SSN)
);

-- Student Assistant Table
CREATE TABLE Student_Assistant (
    SSN INT PRIMARY KEY,
    Percent_Time DECIMAL(5, 2),
    FOREIGN KEY (SSN) REFERENCES Employee(SSN)
);

-- Research Assistant Table
CREATE TABLE Research_Assistant (
    SSN INT PRIMARY KEY,
    Project VARCHAR(50),
    FOREIGN KEY (SSN) REFERENCES Student_Assistant(SSN)
);

-- Teaching Assistant Table
CREATE TABLE Teaching_Assistant (
    SSN INT PRIMARY KEY,
    Course VARCHAR(50),
    FOREIGN KEY (SSN) REFERENCES Student_Assistant(SSN)
);

-- Staff Table
CREATE TABLE Staff (
    SSN INT PRIMARY KEY,
    Position VARCHAR(50),
    FOREIGN KEY (SSN) REFERENCES Employee(SSN)
);

-- Faculty Table
CREATE TABLE Faculty (
    SSN INT PRIMARY KEY,
    `Rank` VARCHAR(50),
    FOREIGN KEY (SSN) REFERENCES Employee(SSN)
);