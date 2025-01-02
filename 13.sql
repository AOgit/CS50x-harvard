SELECT DISTINCT(people.name)
FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE people.name != "Kevin Bacon" AND movies.id IN
(
	SELECT DISTINCT(movies.id)
	FROM movies
	JOIN stars ON stars.movie_id = movies.id
	JOIN people ON people.id = stars.person_id
	WHERE people.name = "Kevin Bacon"
);
