CREATE DATABASE saad;
USE saad;

CREATE TABLE Students (
    student_id INT PRIMARY KEY,
    student_name VARCHAR(100) NOT NULL,
    department_id INT,
    enrollment_year INT,
    FOREIGN KEY (department_id) REFERENCES Departments(department_id) ON DELETE CASCADE
);

CREATE TABLE Courses (
    course_id INT PRIMARY KEY,
    course_name VARCHAR(100) NOT NULL,
    department_id INT,
    credits INT,
    FOREIGN KEY (department_id) REFERENCES Departments(department_id) ON DELETE CASCADE
);

CREATE TABLE Enrollments (
    enrollment_id INT PRIMARY KEY AUTO_INCREMENT,
    student_id INT,
    course_id INT,
    semester ENUM('Fall', 'Spring') NOT NULL,
    grade VARCHAR(5),
    FOREIGN KEY (student_id) REFERENCES Students(student_id) ON DELETE CASCADE,
    FOREIGN KEY (course_id) REFERENCES Courses(course_id) ON DELETE CASCADE
);

CREATE TABLE Departments (
    department_id INT PRIMARY KEY,
    department_name VARCHAR(100) NOT NULL,
    department_head VARCHAR(100)
);

INSERT INTO Departments (department_id, department_name, department_head) VALUES
(1, 'Computer Science', 'Dr. Alice Johnson'),
(2, 'Mathematics', 'Dr. Bob Smith'),
(3, 'Physics', 'Dr. Carol White'),
(4, 'Literature', 'Dr. David Green');

INSERT INTO Students (student_id, student_name, department_id, enrollment_year) VALUES
(101, 'John Doe', 1, 2021),
(102, 'Jane Smith', 2, 2020),
(103, 'Emily Davis', 3, 2022),
(104, 'Michael Brown', 1, 2019),
(105, 'Sarah Wilson', 4, 2023);

INSERT INTO Courses (course_id, course_name, department_id, credits) VALUES
(201, 'Introduction to CS', 1, 4),
(202, 'Data Structures', 1, 3),
(203, 'Calculus', 2, 4),
(204, 'Quantum Mechanics', 3, 5),
(205, 'English Literature', 4, 3),
(206, 'Algorithms', 1, 4);

INSERT INTO Enrollments (enrollment_id, student_id, course_id, semester, grade) VALUES
(301, 101, 201, 'Fall', 'A'),
(302, 101, 202, 'Spring', 'B'),
(303, 102, 203, 'Fall', 'A-'),
(304, 103, 204, 'Spring', 'B+'),
(305, 104, 206, 'Fall', 'A'),
(306, 105, 205, 'Spring', 'B'),
(307, 101, 203, 'Spring', 'B-'),
(308, 102, 201, 'Fall', 'C+');

-- 1.)List all students along with the courses they have enrolled in.
SELECT s.student_id, s.student_name, c.course_id, c.course_name
FROM Students as s
JOIN Enrollments as e ON s.student_id = e.student_id
JOIN Courses as c ON e.course_id = c.course_id;

-- 2.) Find the names of students who have taken courses offered by the Computer Science department.

SELECT DISTINCT s.student_id, s.student_name
FROM Students AS s
JOIN Enrollments AS e ON s.student_id = e.student_id
JOIN Courses AS c ON e.course_id = c.course_id
JOIN Departments AS d ON c.department_id = d.department_id
WHERE d.department_name = 'Computer Science';

-- 3.) Show the grades obtained by each student for each course in the Fall semester.

SELECT s.student_id, s.student_name, c.course_name, e.grade
FROM Students AS s
JOIN Enrollments AS e ON s.student_id = e.student_id
JOIN Courses AS c ON e.course_id = c.course_id
WHERE e.semester = 'Fall';

-- 4.) List all students and the courses they have taken, including students who have not enrolled in any courses.

SELECT s.student_id, s.student_name, c.course_id, c.course_name
FROM Students AS s
LEFT JOIN Enrollments AS e ON s.student_id = e.student_id
LEFT JOIN Courses AS c ON e.course_id = c.course_id;

-- 5.) Display all courses along with the names of students enrolled in them, even if a course has no students enrolled.

SELECT c.course_id, c.course_name, s.student_id, s.student_name
FROM Courses AS c
LEFT JOIN Enrollments AS e ON c.course_id = e.course_id
LEFT JOIN Students AS s ON e.student_id = s.student_id;

-- 6.) List all enrollments, including details about students even if the course information is not available.

SELECT e.enrollment_id, s.student_id, s.student_name, c.course_id, c.course_name, e.semester, e.grade
FROM Enrollments AS e
LEFT JOIN Students AS s ON e.student_id = s.student_id
LEFT JOIN Courses AS c ON e.course_id = c.course_id;

-- 7.) Generate a list of all possible student-course pairs, even if a student is not enrolled in the course.

SELECT s.student_id, s.student_name, c.course_id, c.course_name
FROM Students AS s
CROSS JOIN Courses AS c;

-- 8.) Find pairs of students who are in the same department.

SELECT s1.student_id AS student1_id, s1.student_name AS student1_name,
       s2.student_id AS student2_id, s2.student_name AS student2_name,
       d.department_name
FROM Students AS s1
JOIN Students AS s2 ON s1.department_id = s2.department_id
AND s1.student_id < s2.student_id
JOIN Departments AS d ON s1.department_id = d.department_id;

-- 9.) Identify departments where multiple students enrolled in the same year.

SELECT department_id, enrollment_year, COUNT(*) AS student_count
FROM Students
GROUP BY department_id, enrollment_year
HAVING COUNT(*) > 1;

-- 10.) List the students who have taken courses outside their department and the grades they obtained.

SELECT s.student_id, s.student_name, c.course_name, e.grade, d1.department_name AS student_department, d2.department_name AS course_department
FROM Students AS s
JOIN Enrollments AS e ON s.student_id = e.student_id
JOIN Courses AS c ON e.course_id = c.course_id
JOIN Departments AS d1 ON s.department_id = d1.department_id
JOIN Departments AS d2 ON c.department_id = d2.department_id
WHERE s.department_id != c.department_id;

-- 11.) Find the department heads whose departments have the most students enrolled in courses for the Fall semester.

SELECT d.department_head, d.department_name, COUNT(e.student_id) AS total_enrollments
FROM Departments AS d
JOIN Courses AS c ON d.department_id = c.department_id
JOIN Enrollments AS e ON c.course_id = e.course_id
WHERE e.semester = 'Fall'
GROUP BY d.department_head, d.department_name
ORDER BY total_enrollments DESC
LIMIT 1;

-- 12.) Show the average grade per course for each department.

SELECT d.department_name, c.course_name, AVG(CASE 
        WHEN e.grade = 'A' THEN 4.0
        WHEN e.grade = 'A-' THEN 3.7
        WHEN e.grade = 'B+' THEN 3.3
        WHEN e.grade = 'B' THEN 3.0
        WHEN e.grade = 'B-' THEN 2.7
        WHEN e.grade = 'C+' THEN 2.3
        WHEN e.grade = 'C' THEN 2.0
        WHEN e.grade = 'D' THEN 1.0
        WHEN e.grade = 'F' THEN 0.0
        ELSE NULL
    END) AS avg_gpa
FROM Departments AS d
JOIN Courses AS c ON d.department_id = c.department_id
JOIN Enrollments AS e ON c.course_id = e.course_id
GROUP BY d.department_name, c.course_name;