--Вывести название тарифа с минимальной абонентской платой, его оператора и 
--информацию о предоставляемом интернет трафике, количеству минут и смс в месяц
SELECT TOP 1 WITH TIES Operator_name,Tarif_name, internet_trafic, call_minutes, sms_count, pay_info
FROM Tarif,Average_price, Operator , Tarif_points
WHERE Tarif.Average_price_id = Average_price.Price_id
AND Operator.Operator_id=Tarif.Operator_id
AND Average_price.Abonent_plata_mes>0
AND Tarif.Point_id = Tarif_points.Point_id
ORDER BY Average_price.Abonent_plata_mes

