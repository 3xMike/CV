--��������� ����������� ����� � ���-�� ������ �� 1 ��, �� 1 ������, �� 1 ��� � 1.2 ���� � ������� ���
BEGIN TRAN 
	UPDATE Average_price
	SET Abonent_plata_mes = 1.2*Abonent_plata_mes, rub_gb = 1.2 * rub_gb, rub_min = 1.2 * rub_min, rub_sms = 1.2 * rub_sms
	WHERE Price_id IN (
		SELECT Price_id 
		FROM Average_price, Tarif, Operator
		WHERE Average_price.Price_id = Tarif.Average_price_id
		AND Operator.Operator_id = Tarif.Operator_id
		AND Operator_name LIKE '%���%'
	)
	SELECT * FROM Average_price
ROLLBACK