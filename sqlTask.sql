CREATE SCHEMA geo_test;

create table geo_test.test_point(
    id bigserial primary key,
    task integer,
    x numeric(15,2),
    y numeric(15,2),
    z numeric(15,2)
);

create table geo_test.task(
    id bigserial primary key,
    name varchar(255)
);

ALTER TABLE geo_test.test_point
ADD CONSTRAINT fk_id
FOREIGN KEY (task)
REFERENCES geo_test.task(id);

create index on geo_test.test_point(id,task); 

insert into geo_test.task(id, name) values (1, 'testName');

INSERT INTO geo_test.test_point(id, task, x,y,z) VALUES (1,1,1,0,0);
INSERT INTO geo_test.test_point(id, task, x,y,z) VALUES (2,1,0,1,0);
INSERT INTO geo_test.test_point(id, task, x,y,z) VALUES (3,1,0,0,1);

select * from geo_test.test_point where id = 2;
