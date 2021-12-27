/*
DROP TABLE fly;
DROP TABLE captain;
DROP TABLE flight;
DROP TABLE route;
*/

CREATE TABLE route (
  rid Integer PRIMARY KEY,
  departure_city varchar2(255) default NULL,
  arrival_city varchar2(255) default NULL,
  distance NUMERIC
);

CREATE TABLE flight (
  fid Integer PRIMARY KEY,
  rid Integer default NULL references route(rid),
  planeid varchar(255) default NULL,
  day Integer,
  flighthour numeric(3,1)
);

CREATE TABLE captain (
  cid INTEGER PRIMARY KEY,
  cname varchar2(255) default NULL,
  experiencehour numeric(6,1)
);

CREATE TABLE fly (
  cid NUMERIC default NULL references captain(cid),
  fid NUMERIC default NULL references flight(fid)
);

INSERT INTO route VALUES(1,'Macau','Hong Kong',64);
INSERT INTO route VALUES(2,'Hong Kong','Macau',64);
INSERT INTO route VALUES(3,'London','Hong Kong',9646);
INSERT INTO route VALUES(4,'Hong Kong','London',9646);
INSERT INTO route VALUES(5,'Hong Kong','Beijing',1972);
INSERT INTO route VALUES(6,'Beijing','Hong Kong',1972);
INSERT INTO route VALUES(7,'Seoul','Beijing',957);
INSERT INTO route VALUES(8,'Beijing','Seoul',957);
INSERT INTO route VALUES(9,'Beijing','Shanghai',1069);
INSERT INTO route VALUES(10,'Hong Kong','Shanghai',1069);
INSERT INTO route VALUES(11,'New Delhi','Hong Kong',4255);
INSERT INTO route VALUES(12,'Singapore','Hong Kong',2569);
INSERT INTO route VALUES(13,'New Delhi','Singapore',4130);
INSERT INTO route VALUES(14,'Singapore','Sydney',6304);
INSERT INTO route VALUES(15,'Macau','Paris',9618);
INSERT INTO route VALUES(16,'Hong Kong','Concorde City',17320);
INSERT INTO route VALUES(17,'Shanghai','Hong Kong',1069);
INSERT INTO route VALUES(18,'Hong Kong','Seoul',2097);
INSERT INTO route VALUES(19,'Seoul','Tokyo',1161);
INSERT INTO route VALUES(20,'Tokyo','Hong Kong',2892);
INSERT INTO route VALUES(21,'Tokyo','Vancouver',7567);
INSERT INTO route VALUES(22,'Vancouver','Macau',10318);

INSERT INTO flight VALUES(1,15,'A136',20131225,8.5);
INSERT INTO flight VALUES(2,3,'A136',20131226,9);
INSERT INTO flight VALUES(3,10,'A136',20131227,4.5);
INSERT INTO flight VALUES(4,6,'A136',20131229,5.1);
INSERT INTO flight VALUES(5,16,'A136',20140101,3);
INSERT INTO flight VALUES(6,6,'B777',20131212,5.2);
INSERT INTO flight VALUES(7,5,'B777',20131213,5);
INSERT INTO flight VALUES(8,9,'B777',20131214,4.7);
INSERT INTO flight VALUES(9,17,'B777',20131224,4.2);
INSERT INTO flight VALUES(10,18,'B777',20131225,3.5);
INSERT INTO flight VALUES(11,19,'B777',20131225,2.3);
INSERT INTO flight VALUES(12,21,'B777',20131226,13.8);
INSERT INTO flight VALUES(13,22,'B777',20131228,12.9);
INSERT INTO flight VALUES(14,3,'B747',20131221,10.3);
INSERT INTO flight VALUES(15,10,'B747',20131222,5);
INSERT INTO flight VALUES(16,17,'B747',20131222,3.7);
INSERT INTO flight VALUES(17,4,'B747',20131223,10.8);
INSERT INTO flight VALUES(18,3,'B747',20131224,12);
INSERT INTO flight VALUES(19,2,'B747',20131225,1.3);
INSERT INTO flight VALUES(20,1,'B747',20131225,1.5);
INSERT INTO flight VALUES(21,7,'A125',20131224,3.5);
INSERT INTO flight VALUES(22,8,'A125',20131226,3.6);

INSERT INTO captain VALUES(1,'Holiday Ho',2718);
INSERT INTO captain VALUES(2,'Sam Tong',31415);
INSERT INTO captain VALUES(3,'Danny Bong',4520);
INSERT INTO captain VALUES(4,'Tommy Cheng',6180);
INSERT INTO captain VALUES(5,'Joe Doe',7774);
INSERT INTO captain VALUES(6,'Amy Tin',4718);
INSERT INTO captain VALUES(7,'Bob Leung',9745);
INSERT INTO captain VALUES(8,'David Pang',14142);
INSERT INTO captain VALUES(9,'Sean Kwok',24816);

INSERT INTO fly VALUES(1,20);
INSERT INTO fly VALUES(2,20);
INSERT INTO fly VALUES(3,17);
INSERT INTO fly VALUES(6,18);
INSERT INTO fly VALUES(4,4);
INSERT INTO fly VALUES(4,6);
INSERT INTO fly VALUES(8,12);
INSERT INTO fly VALUES(9,13);
INSERT INTO fly VALUES(5,17);
INSERT INTO fly VALUES(1,12);
INSERT INTO fly VALUES(2,13);
INSERT INTO fly VALUES(7,2);
INSERT INTO fly VALUES(5,8);
INSERT INTO fly VALUES(5,9);
INSERT INTO fly VALUES(5,19);
INSERT INTO fly VALUES(5,20);
INSERT INTO fly VALUES(6,6);
INSERT INTO fly VALUES(6,7);
INSERT INTO fly VALUES(6,8);
INSERT INTO fly VALUES(9,1);
INSERT INTO fly VALUES(8,4);
