SELECT DISTINCT(title)
FROM movies
WHERE id IN
(
    SELECT DISTINCT(movies.id)
    FROM movies
    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON people.id = stars.person_id
    WHERE people.name = "Jennifer Lawrence"
) AND id IN
(
    SELECT DISTINCT(movies.id)
    FROM movies
    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON people.id = stars.person_id
    WHERE people.name = "Bradley Cooper"
);

