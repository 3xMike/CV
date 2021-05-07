--Вывести названия операторов, средняя абонентская плата которых 
--ниже средней абонентской платы всех операторов
SELECT Operator_name, averprice 
FROM 
	(
		SELECT Operator_name, AVG(Abonent_plata_mes) averprice
		FROM Operator, Average_price , Tarif
		WHERE Operator.Operator_id = Tarif.Operator_id
		AND  Tarif.Average_price_id = Average_price.Price_id 
		AND Abonent_plata_mes>0
		GROUP BY Operator_name
	) t1
	WHERE averprice <= 
		(
		SELECT AVG(Abonent_plata_mes)
		FROM Average_price
		)