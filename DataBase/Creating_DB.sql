
ALTER TABLE Salon
DROP CONSTRAINT FK_Salon;
ALTER TABLE Helping_info
DROP CONSTRAINT FK_help;
ALTER TABLE Tarif
DROP CONSTRAINT FK_avprice;
ALTER TABLE Tarif
DROP CONSTRAINT FK_Point;
ALTER TABLE Tarif
DROP CONSTRAINT FK_tarif;
ALTER TABLE Dop_uslugi
DROP CONSTRAINT FK_Usl;
ALTER TABLE Connection
DROP CONSTRAINT FK_abonent;
ALTER TABLE Connection
DROP CONSTRAINT FK_tarifconnect;

DROP table Salon;
DROP table Helping_info;
DROP table Dop_uslugi;
DROP table Tarif;
DROP table Tarif_points;
DROP table Operator;
DROP table Average_price;
DROP table Abonent;
DROP table Connection;

SET DATEFORMAT dmy;
CREATE TABLE Operator (
	Operator_id int NOT NULL identity(1,1),
	Operator_name nvarchar(50) NOT NULL,
	Operator_site nvarchar(50),
	Operator_tel_number bigint,
	Operator_main_adress nvarchar(200)
	CONSTRAINT PK_Operator PRIMARY KEY (Operator_id)
	
  );


	CREATE TABLE Salon (
		Salon_id int NOT NULL identity (1,1) PRIMARY KEY ,
		Operator_id int NOT NULL,
		Salon_adress nvarchar(1000) NOT NULL,
		Salon_tel_number bigint NOT NULL,
		CONSTRAINT FK_Salon FOREIGN KEY (Operator_id) REFERENCES Operator (Operator_id) ON UPDATE CASCADE ON DELETE CASCADE
	);
CREATE TABLE Dop_uslugi (
	Usluga_id int NOT NULL identity(1,1) PRIMARY KEY,
	Operator_id int NOT NULL,
	Usl_name nvarchar(50) NOT NULL,
	Usl_description nvarchar(200) NOT NULL,
	Uslovie_of_payment nvarchar(100) NOT NULL,
	CONSTRAINT FK_Usl FOREIGN KEY (Operator_id) REFERENCES [Operator]([Operator_id]) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE Helping_info (
	Help_center_id int NOT NULL identity(1,1) PRIMARY KEY,
	Operator_id int NOT NULL ,
	Call_center_number bigint NOT NULL,
	Helping_site nvarchar(50) NOT NULL,
	Helping_email nvarchar(50) NOT NULL,
	CONSTRAINT FK_help FOREIGN KEY (Operator_id) REFERENCES [Operator]([Operator_id]) ON UPDATE CASCADE ON DELETE CASCADE
 );
 	CREATE TABLE Average_price (
	Price_id int identity(1,1) PRIMARY KEY,
	Abonent_plata_mes float,
	rub_gb float,
	rub_min float,
	rub_sms float,
	)
	CREATE TABLE Tarif_points(
	Point_id int NOT NULL identity(1,1) PRIMARY KEY,
	internet_trafic NVARCHAR(50),
	call_minutes NVARCHAR(50),
	sms_count NVARCHAR(50),
	pay_info NVARCHAR(50),
	average_month_pay int,
	)
	CREATE TABLE Tarif (
	Tarif_id int identity(1,1) NOT NULL PRIMARY KEY,
	Point_id int NOT NULL ,
	Average_price_id int NOT NULL,
	Operator_id int NOT NULL,
	Tarif_name nvarchar(50) NOT NULL,
	CONSTRAINT FK_tarif FOREIGN KEY (Operator_id) REFERENCES [Operator]([Operator_id]) ON UPDATE CASCADE ON DELETE CASCADE,
	CONSTRAINT FK_Point FOREIGN KEY (Point_id) REFERENCES [Tarif_points]([Point_id]) ON UPDATE CASCADE ON DELETE CASCADE,
	CONSTRAINT FK_avprice FOREIGN KEY (Average_price_id) REFERENCES [Average_price]([Price_id]) ON UPDATE CASCADE ON DELETE CASCADE
);
	CREATE TABLE Abonent(
	abonent_id int identity(1,1) NOT NULL,
	name nvarchar(50)
	CONSTRAINT PK_abonent PRIMARY KEY(abonent_id)
	) 
	CREATE TABLE Connection(
	Abonent_id int,
	Tarif_id int,
	Connect_date datetime,
	CONSTRAINT PK_connect PRIMARY KEY (Abonent_id, Tarif_id),
	CONSTRAINT FK_abonent FOREIGN KEY (Abonent_id) REFERENCES [Abonent]([Abonent_id]) ON UPDATE CASCADE ON DELETE CASCADE,
	CONSTRAINT FK_tarifconnect FOREIGN KEY (Tarif_id) REFERENCES [Tarif]([Tarif_id]) ON UPDATE CASCADE ON DELETE CASCADE
	)

	