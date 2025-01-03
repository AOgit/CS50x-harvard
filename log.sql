-- Keep a log of any SQL queries you execute as you solve the mystery.
-- list all of the tables in the database.
.tables

airports              crime_scene_reports   people
atm_transactions      flights               phone_calls
bakery_security_logs  interviews
bank_accounts         passengers

-- Begin from research crime_scene_reports table

SELECT * FROM crime_scene_reports WHERE YEAR = 2024 AND MONTH = 7 AND DAY = 28 AND street = "Humphrey Street";
 295 | 2024 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.  |
| 297 | 2024 | 7     | 28  | Humphrey Street | Littering took place at 16:36. No known witnesses.


-- Discover interviews table

SELECT * FROM interviews WHERE YEAR = 2024 AND MONTH = 7 AND DAY = 28 AND transcript LIKE "%bakery%";
-------------------------------------------------------------+
| id  |  name   | year | month | day |                                                                                                                                                     transcript                                                                                                                                                      |
+-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 161 | Ruth    | 2024 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| 162 | Eugene  | 2024 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| 163 | Raymond | 2024 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
+-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

-- Discover bakery_security_logs table
SELECT bakery_security_logs.*, people.name
	FROM bakery_security_logs
	JOIN people ON people.license_plate = bakery_security_logs.license_plate
	WHERE YEAR = 2024 AND MONTH = 7 AND DAY = 28 AND hour = 10 AND (minute >= 15 AND minute <= 25);

+-----+------+-------+-----+------+--------+----------+---------------+---------+
| id  | year | month | day | hour | minute | activity | license_plate |  name   |
+-----+------+-------+-----+------+--------+----------+---------------+---------+
| 260 | 2024 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       | Vanessa |
| 261 | 2024 | 7     | 28  | 10   | 18     | exit     | 94KL13X       | Bruce   |
| 262 | 2024 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       | Barry   |
| 263 | 2024 | 7     | 28  | 10   | 19     | exit     | 4328GD8       | Luca    |
| 264 | 2024 | 7     | 28  | 10   | 20     | exit     | G412CB7       | Sofia   |
| 265 | 2024 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       | Iman    |
| 266 | 2024 | 7     | 28  | 10   | 23     | exit     | 322W7JE       | Diana   |
| 267 | 2024 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       | Kelsey  |
+-----+------+-------+-----+------+--------+----------+---------------+---------+


-- Discover atm_transactions table and persons, who withdraw money

SELECT people.name, people.license_plate,  atm_transactions.*
FROM atm_transactions
JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON people.id = bank_accounts.person_id
WHERE YEAR = 2024 AND MONTH = 7 AND DAY = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

+---------+---------------+-----+----------------+------+-------+-----+----------------+------------------+--------+
|  name   | license_plate | id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+---------+---------------+-----+----------------+------+-------+-----+----------------+------------------+--------+
| Bruce   | 94KL13X       | 267 | 49610011       | 2024 | 7     | 28  | Leggett Street | withdraw         | 50     |
| Diana   | 322W7JE       | 336 | 26013199       | 2024 | 7     | 28  | Leggett Street | withdraw         | 35     |
| Brooke  | QX4YZN3       | 269 | 16153065       | 2024 | 7     | 28  | Leggett Street | withdraw         | 80     |
| Kenny   | 30G67EN       | 264 | 28296815       | 2024 | 7     | 28  | Leggett Street | withdraw         | 20     |
| Iman    | L93JTIZ       | 288 | 25506511       | 2024 | 7     | 28  | Leggett Street | withdraw         | 20     |
| Luca    | 4328GD8       | 246 | 28500762       | 2024 | 7     | 28  | Leggett Street | withdraw         | 48     |
| Taylor  | 1106N58       | 266 | 76054385       | 2024 | 7     | 28  | Leggett Street | withdraw         | 60     |
| Benista | 8X428L0       | 313 | 81061156       | 2024 | 7     | 28  | Leggett Street | withdraw         | 30     |
+---------+---------------+-----+----------------+------+-------+-----+----------------+------------------+--------+

-- Discover flights table
SELECT origin.full_name AS origin_name, dest.full_name AS dest_name, flights.*
FROM flights
JOIN airports AS origin ON origin.id = flights.origin_airport_id
JOIN airports AS dest ON dest.id = flights.destination_airport_id
WHERE origin.city = "Fiftyville"
AND YEAR = 2024 AND MONTH = 7 AND DAY = 29
ORDER BY hour
/*LIMIT 1;*/

+-----------------------------+-------------------------------------+----+-------------------+------------------------+------+-------+-----+------+--------+
|         origin_name         |              dest_name              | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+-----------------------------+-------------------------------------+----+-------------------+------------------------+------+-------+-----+------+--------+
| Fiftyville Regional Airport | LaGuardia Airport                   | 36 | 8                 | 4                      | 2024 | 7     | 29  | 8    | 20     |
| Fiftyville Regional Airport | O'Hare International Airport        | 43 | 8                 | 1                      | 2024 | 7     | 29  | 9    | 30     |
| Fiftyville Regional Airport | San Francisco International Airport | 23 | 8                 | 11                     | 2024 | 7     | 29  | 12   | 15     |
| Fiftyville Regional Airport | Tokyo International Airport         | 53 | 8                 | 9                      | 2024 | 7     | 29  | 15   | 20     |
| Fiftyville Regional Airport | Logan International Airport         | 18 | 8                 | 6                      | 2024 | 7     | 29  | 16   | 0      |
+-----------------------------+-------------------------------------+----+-------------------+------------------------+------+-------+-----+------+--------+

LaGuardia Airport  is  destination_airport and fly id = 36

-- Discover passengers table
SELECT people.*, passengers.*
FROM passengers
JOIN people ON people.passport_number = passengers.passport_number
WHERE flight_id = 36;
+--------+--------+----------------+-----------------+---------------+-----------+-----------------+------+
|   id   |  name  |  phone_number  | passport_number | license_plate | flight_id | passport_number | seat |
+--------+--------+----------------+-----------------+---------------+-----------+-----------------+------+
| 953679 | Doris  | (066) 555-9701 | 7214083635      | M51FA04       | 36        | 7214083635      | 2A   |
| 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       | 36        | 1695452385      | 3B   |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       | 36        | 5773159633      | 4A   |
| 651714 | Edward | (328) 555-1152 | 1540955065      | 130LD9Z       | 36        | 1540955065      | 5C   |
| 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       | 36        | 8294398571      | 6C   |
| 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       | 36        | 1988161715      | 6D   |
| 395717 | Kenny  | (826) 555-1652 | 9878712108      | 30G67EN       | 36        | 9878712108      | 7A   |
| 467400 | Luca   | (389) 555-5198 | 8496433585      | 4328GD8       | 36        | 8496433585      | 7B   |
+--------+--------+----------------+-----------------+---------------+-----------+-----------------+------+

-- get 2 person in this flight who talking with each other

SELECT *
FROM phone_calls
WHERE YEAR = 2024 AND MONTH = 7 AND DAY = 28
AND receiver IN
(
	SELECT people.phone_number
	FROM passengers
	JOIN people ON people.passport_number = passengers.passport_number
	WHERE flight_id = 36
)
AND caller IN
(
	SELECT people.phone_number
	FROM passengers
	JOIN people ON people.passport_number = passengers.passport_number
	WHERE flight_id = 36
);

+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 279 | (826) 555-1652 | (066) 555-9701 | 2024 | 7     | 28  | 55       |
+-----+----------------+----------------+------+-------+-----+----------+


-- Caller (Theaf) -  Kenny, ACCOMPLICE - Doris, Escape to LaGuardia



-- recognize the thief
SELECT *
FROM people
WHERE
people.id IN
(
	SELECT people.id
	FROM bakery_security_logs
	JOIN people ON people.license_plate = bakery_security_logs.license_plate
	WHERE YEAR = 2024 AND MONTH = 7 AND DAY = 28 AND hour = 10 AND (minute >= 15 AND minute <= 25)
)
AND people.id IN
(
	SELECT people.id
	FROM atm_transactions
	JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
	JOIN people ON people.id = bank_accounts.person_id
	WHERE YEAR = 2024 AND MONTH = 7 AND DAY = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"
)
AND people.id IN
(
	SELECT people.id
	FROM passengers
	JOIN people ON people.passport_number = passengers.passport_number
	WHERE flight_id = 36
)
AND people.id IN
(
	SELECT people.id
	FROM phone_calls
	JOIN people ON people.phone_number = phone_calls.caller
	WHERE YEAR = 2024 AND MONTH = 7 AND DAY = 28 AND duration <=60
);

+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+-------+----------------+-----------------+---------------+

-- recognize the ACCOMPLICE

SELECT phone_calls.*, people.name AS receiver_name
FROM phone_calls
JOIN people ON people.phone_number = phone_calls.receiver
WHERE YEAR = 2024 AND MONTH = 7 AND DAY = 28
AND caller = "(367) 555-5533"

+-----+----------------+----------------+------+-------+-----+----------+---------------+
| id  |     caller     |    receiver    | year | month | day | duration | receiver_name |
+-----+----------------+----------------+------+-------+-----+----------+---------------+
| 233 | (367) 555-5533 | (375) 555-8161 | 2024 | 7     | 28  | 45       | Robin         |
+-----+----------------+----------------+------+-------+-----+----------+---------------+

