create database SocialMedia;
use SocialMedia;

CREATE TABLE Users (
    user_id INT PRIMARY KEY,
    username VARCHAR(50),
    age INT,
    country VARCHAR(50),
    number_of_tweets INT
);

INSERT INTO Users (user_id, username, age, country, number_of_tweets) VALUES
(1, 'Alice', 25, 'USA', 5),
(2, 'Bob', 30, 'Canada', 2),
(3, 'Charlie', 28, 'Pakistan', 0),
(4, 'David', 35, 'UK', 7),
(5, 'Emma', 22, 'Pakistan', 3);

CREATE TABLE Followers (
    user_id INT,
    follower_id INT,
    FOREIGN KEY (user_id) REFERENCES Users(user_id),
    FOREIGN KEY (follower_id) REFERENCES Users(user_id)
);

INSERT INTO Followers (user_id, follower_id) VALUES
(1, 2),
(1, 3),
(2, 4),
(2, 5),
(3, 1),
(3, 5),
(4, 3),
(4, 5),
(5, 2);

CREATE TABLE Tweets (
    tweet_id INT PRIMARY KEY,
    user_id INT,
    tweet_content VARCHAR(255),
    tweet_date DATETIME,
    FOREIGN KEY (user_id) REFERENCES Users(user_id)
);

INSERT INTO Tweets (tweet_id, user_id, tweet_content, tweet_date) VALUES
(1, 1, 'Loving the new #AI updates', '2025-02-01 10:00:00'),
(2, 1, 'Just had coffee! ☕', '2025-02-02 12:30:00'),
(3, 2, 'Excited for #Census results', '2025-02-03 15:45:00'),
(4, 2, 'Big data is the future! #Tech', '2025-02-05 09:20:00'),
(5, 4, 'Coding in Python is fun! #Code', '2025-02-07 14:10:00'),
(6, 4, 'Working on a new project!!', '2025-02-09 18:00:00'),
(7, 5, 'AI will change the world! #AI', '2025-02-10 08:30:00');

CREATE TABLE Hashtags (
    tweet_id INT,
    hashtag VARCHAR(50),
    FOREIGN KEY (tweet_id) REFERENCES Tweets(tweet_id)
);

INSERT INTO Hashtags (tweet_id, hashtag) VALUES
(1, '#AI'),
(3, '#Census'),
(4, '#Tech'),
(5, '#Code'),
(7, '#AI');

CREATE TABLE Interests (
    interest_id INT PRIMARY KEY,
    description VARCHAR(50)
);

INSERT INTO Interests (interest_id, description) VALUES
(1, 'AI'),
(2, 'Machine Learning'),
(3, 'Coding'),
(4, 'Data Science'),
(5, 'Music');

CREATE TABLE UserInterests (
    user_id INT,
    interest_id INT,
    FOREIGN KEY (user_id) REFERENCES Users(user_id),
    FOREIGN KEY (interest_id) REFERENCES Interests(interest_id)
);

INSERT INTO UserInterests (user_id, interest_id) VALUES
(1, 1),
(1, 3),
(2, 2),
(2, 4),
(3, 5),
(4, 3),
(5, 1),
(5, 4);

-- 1. What is the maximum, minimum, average and standard deviation of ages of the users? (Search Standard Dev function)
SELECT
	max(age) as max_age,
    min(age) as min_age,
    avg(age) as avg_age,
    STDDEV(age) as stddev_age
from Users;

-- 2. Give the name of the user who has the highest number of followers.
select u.username
from Users u
join (
	select user_id, count(follower_id) as follower_count
    from Followers
    group by user_id
    order by follower_count desc
    limit 1
) sub on u.user_id = sub.user_id;

-- 3. Give name of the user who has second highest followers.
SELECT u.username
FROM Users u
JOIN (
    SELECT user_id, COUNT(follower_id) AS follower_count
    FROM Followers
    GROUP BY user_id
    ORDER BY follower_count DESC
    LIMIT 1 OFFSET 1
) sub ON u.user_id = sub.user_id;

-- 4. List names of all the users who have never tweeted.
SELECT username
FROM Users
WHERE user_id NOT IN (SELECT DISTINCT user_id FROM Tweets);

-- 5. List all the hashtags and usernames and number of times that user used that hashtag.
SELECT u.username, h.hashtag, COUNT(*) AS usage_count
FROM Tweets t
JOIN Hashtags h ON t.tweet_id = h.tweet_id
JOIN Users u ON t.user_id = u.user_id
GROUP BY u.username, h.hashtag;

-- 6. Find the users who have never used the hashtag #Census.
SELECT username
FROM Users
WHERE user_id NOT IN (
    SELECT DISTINCT t.user_id
    FROM Tweets t
    JOIN Hashtags h ON t.tweet_id = h.tweet_id
    WHERE h.hashtag = '#Census'
);

-- 7. List all the usernames that have never been followed. Using Set operation.
SELECT username
FROM Users
WHERE user_id NOT IN (SELECT DISTINCT follower_id FROM Followers);

-- 8. List all the usernames that have never been followed. Using Exist Clause.
SELECT username
FROM Users u
WHERE NOT EXISTS (
    SELECT 1 FROM Followers f WHERE f.follower_id = u.user_id
);

-- 9. Find the most common interest of users. (The interest with the largest number of users). Also find the least common interest.
-- Find the most common interest (Interest with the maximum number of users)
SELECT UI.interest_id, I.description, COUNT(UI.user_id) AS MaxCount
FROM UserInterests UI
JOIN Interests I ON UI.interest_id = I.interest_id
GROUP BY UI.interest_id, I.description
HAVING COUNT(UI.user_id) = (
    SELECT MAX(NumInterests)
    FROM (
        SELECT COUNT(user_id) AS NumInterests
        FROM UserInterests
        GROUP BY interest_id
    ) AS Inters
);

-- Find the least common interest (Interest with the minimum number of users)
SELECT UI.interest_id, I.description, COUNT(UI.user_id) AS MinCount
FROM UserInterests UI
JOIN Interests I ON UI.interest_id = I.interest_id
GROUP BY UI.interest_id, I.description
HAVING COUNT(UI.user_id) = (
    SELECT MIN(NumInterests)
    FROM (
        SELECT COUNT(user_id) AS NumInterests
        FROM UserInterests
        GROUP BY interest_id
    ) AS Inters
);


-- 10. Show total tweets per country. The result should be in order of country name.
SELECT country, SUM(number_of_tweets) AS total_tweets
FROM Users
GROUP BY country
ORDER BY country;

-- 11. List names of all the users whose number of tweets is more than the average number of tweets per user.
SELECT username
FROM Users
WHERE number_of_tweets > (SELECT AVG(number_of_tweets) FROM Users);

-- 12. Give the name of the users who have at least one follower from Pakistan.
SELECT DISTINCT u.username
FROM Users u
JOIN Followers f ON u.user_id = f.user_id
JOIN Users f_user ON f.follower_id = f_user.user_id
WHERE f_user.country = 'Pakistan';

-- 13. Show the interest ID and description of interest with the most number of users.
SELECT i.interest_id, i.description, COUNT(ui.user_id) AS user_count
FROM UserInterests ui
JOIN Interests i ON ui.interest_id = i.interest_id
GROUP BY i.interest_id, i.description
ORDER BY user_count DESC
LIMIT 1;