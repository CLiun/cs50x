-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Check crime report
SELECT description
FROM crime_scene_reports
WHERE year = 2024 AND month = 7 AND day = 28
AND street = 'Humphrey Street';
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts

-- Check interview at 10:15am
SELECT name, transcript
FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28;
-- 161 Ruth. Sometime within ten minutes of the theft, car in the bakery parking lot and drive away.
-- 162 Eugene. ATM on Leggett Street and saw the thief there withdrawing some money.
-- 163 RAymond. As the thief was leaving the bakery, they called someone who talked to them for less than a minute. earliest flight out of Fiftyville tomorrow

-- Check ATM
CREATE TABLE suspicion_atm AS
SELECT account_number
FROM atm_transactions
WHERE year = 2024 AND month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- Check bakery
CREATE TABLE suspicion_car AS
SELECT license_plate
FROM bakery_security_logs
WHERE year = 2024 AND month = 7 AND day = 28
AND hour = 10 AND minute <= 25 AND minute > 15
AND activity = 'exit';

-- Check phone call
CREATE TABLE suspicion_call AS
SELECT caller, receiver
FROM phone_calls
WHERE year = 2024 AND month = 7 AND day = 28
AND duration <= 60;

-- Check passenger
CREATE TABLE suspicion_passport AS
SELECT passport_number
FROM passengers
WHERE flight_id in
(
    SELECT id
    FROM flights
    WHERE year = 2024 AND month = 7 AND day = 29
    AND origin_airport_id =
    (
        SELECT id
        FROM airports
        WHERE city = 'Fiftyville'
    )
    ORDER BY hour, minute
    LIMIT 1
);

-- Find person
CREATE TABLE suspicion_id_name AS
SELECT id, name
FROM people
WHERE phone_number in
(
    SELECT caller
    FROM suspicion_call
)
AND passport_number in
(
    SELECT passport_number
    FROM suspicion_passport
)
AND license_plate in
(
    SELECT license_plate
    FROM suspicion_car
);

SELECT name
FROM suspicion_id_name
JOIN bank_accounts
ON bank_accounts.person_id = suspicion_id_name.id
WHERE account_number in
(
    SELECT account_number
    FROM suspicion_atm
);
-- Thief: Bruce

-- Find flight
SELECT city,
FROM airports
WHERE id in
(
    SELECT destination_airport_id
    FROM flights
    WHERE year = 2024 AND month = 7 AND day = 29
    AND origin_airport_id =
    (
        SELECT id
        FROM airports
        WHERE city = 'Fiftyville'
    )
    ORDER BY hour, minute
    LIMIT 1
)
;
-- New York City

-- Find Accomplice
SELECT name
FROM people
WHERE phone_number in
(
    SELECT receiver
    FROM suspicion_call
    WHERE caller =
    (
        SELECT phone_number
        FROM people
        WHERE name = 'Bruce'
    )
);
-- Robin
