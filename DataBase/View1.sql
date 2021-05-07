DROP VIEW tarifpopular
go

CREATE VIEW tarifpopular(operator_name,tarif_name, abcount)
AS (SELECT DISTINCT o.operator_name ,t1.tarif_name, abcount
	FROM operator o,tarif t,(
		 SELECT Tarif_name, COUNT(*) as abcount
		FROM Operator o, Tarif t, Abonent a, Connection c
		WHERE o.Operator_id = t.operator_id
		AND a.abonent_id = c.Abonent_id
		AND c.Tarif_id = t.Tarif_id 
		GROUP BY tarif_name) t1
		WHERE o.operator_id = t.operator_id
		AND t1.Tarif_name=t.tarif_name
); 
go
	SELECT * FROM tarifpopular
	go
	SELECT * FROM tarifpopular
	WHERE operator_name LIKE '%Мегафон%'
	go
	SELECT top 1 * 
	FROM tarifpopular 
	ORDER BY abcount desc
	go 
	SELECT * FROM tarifpopular 
	ORDER BY tarif_name,